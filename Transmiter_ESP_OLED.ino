#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

#define TFT_CS    3
#define TFT_DC    17
#define TFT_SCLK  14
#define TFT_MOSI  13
#define TFT_RST   15

Adafruit_ST7789 *_tft = NULL;

int lastRCBatt;
int lastRemotBatt;
int lastmode;
int lastpitchang;
int rollpitchang;


//Adafruit_ST7789 tft = Adafruit_ST7789(3, 17, 15); //cs, dc, res

void setup() {
  Serial.begin(115200);

  SPIClass *spi = new SPIClass(HSPI);
  spi->begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  _tft = new Adafruit_ST7789(spi, TFT_CS, TFT_DC, TFT_RST);
  // 80MHz should work, but you may need lower speeds
  _tft->setSPISpeed(80000000);
  // this will vary depending on your display
  _tft->init(240, 240, SPI_MODE2);
  _tft->fillScreen(0x0002);
  _tft->setRotation(2);     //to 90 deg
  _tft->setTextSize(2); //1 is default 6x8, 2 is 12x16, 3 is 18x24
  Serial.println("Finish SetUp");
}

void loop() {  
  Serial.print(analogRead(34));
  Serial.print("    ");
  int Read = map(analogRead(34), 0, 4095, -180, 180);
  Serial.print(Read);
  Serial.print("    ");

  yew(Read);

  /*
  

  //_tft->drawLine(0, 120, 240, 120, ST77XX_BLACK); //axis of symmetry
  //_tft->drawLine(120, 0, 120, 240, ST77XX_BLACK);
*/
}

void SCREEN(){
}

void RCBatt(int RCBatt){
  if (lastRCBatt != RCBatt){
    _tft->fillRoundRect(2, 2, lastRCBatt, 10, 8, 0x0002);    
  }
  _tft->fillRoundRect(2, 2, RCBatt, 10, 8, ST77XX_GREEN);

  lastRCBatt = RCBatt;
}

void RemotBatt(int RemotBatt){
  if (lastRemotBatt != RemotBatt){
    _tft->fillRoundRect(188, 2, lastRemotBatt, 10, 8, 0x0002);   
  }
  _tft->fillRoundRect(188, 2, RemotBatt, 10, 8, ST77XX_GREEN);

  lastRemotBatt = RemotBatt;
}

void MODE(int mode){
  _tft->setCursor(70, 0);
  _tft->setTextSize(4);

  
  if (lastmode != mode){
      _tft->fillRoundRect(60, 0 , 180, 50, 0, 0x0002);  
  }


  switch (mode) {
    case 0:
    _tft->setTextColor(ST77XX_WHITE);
    _tft->print("MODE");
      break;

    case 1:
    _tft->setTextColor(ST77XX_WHITE);
    _tft->print("GYRO");
      break;

    case 2:
    _tft->setTextColor(ST77XX_WHITE);
    _tft->print("ANGE");
      break;
  }


  lastmode = mode;
}

void pitch(int pitchang){
  
  if (lastpitchang != pitchang){
    _tft->fillRoundRect(170, 40 , 54, 180, 0, 0x0002);
  }

  int pitchline = map(pitchang, -180, 180, 220, 40);
  _tft->drawLine(225, 40, 235, 40, ST77XX_WHITE);
  _tft->drawLine(225, 70, 235, 70, ST77XX_WHITE);
  _tft->drawLine(225, 100, 235, 100, ST77XX_WHITE);
  _tft->drawLine(225, 130, 235, 130, ST77XX_WHITE);
  _tft->drawLine(225, 160, 235, 160, ST77XX_WHITE);
  _tft->drawLine(225, 190, 235, 190, ST77XX_WHITE);
  _tft->drawLine(225, 220, 235, 220, ST77XX_WHITE);
  _tft->drawLine(215, pitchline, 220, pitchline, ST77XX_WHITE); //Pitch Ang
  _tft->setCursor(170, 123);
  _tft->setTextSize(2);
  _tft->println(pitchang);

  lastpitchang = pitchang;
}

void roll(int rollang){
  
  if (rollpitchang != rollang){
    _tft->fillRoundRect(30, 170 , 190, 54, 0, 0x0002);
  }

  int rollline = map(rollang, -180, 180, 30, 210);
  _tft->drawLine(30, 225, 30, 235, ST77XX_WHITE);
  _tft->drawLine(60, 225, 60, 235, ST77XX_WHITE);
  _tft->drawLine(90, 225, 90, 235, ST77XX_WHITE);
  _tft->drawLine(120, 225, 120, 235, ST77XX_WHITE);
  _tft->drawLine(150, 225, 150, 235, ST77XX_WHITE);
  _tft->drawLine(180, 225, 180, 235, ST77XX_WHITE);
  _tft->drawLine(210, 225, 210, 235, ST77XX_WHITE);
  _tft->drawLine(rollline, 210, rollline, 215, ST77XX_WHITE); //Pitch Ang

  _tft->setCursor(110, 190);
  _tft->setTextSize(2);
  _tft->println(rollang);
  
  rollpitchang = rollang;
}

void yew(int yewang){
  _tft->drawCircle(120, 95, 30, ST77XX_WHITE);

  if (rollpitchang != rollang){
    _tft->fillCircle(120, 95, 29, 0x0002);
  }

  _tft->drawLine(119, 95, 121, 80, ST77XX_RED);
}