#include <SPI.h>
#include <MFRC522.h>
#include "U8glib.h"

#define buzz 6
//RFID
#define RST_PIN    5   // 
#define SS_PIN    3    //
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

U8GLIB_ST7920_128X64_1X u8g(9, 8, 7); //SCK = en = 18, MOSI = rw = 16, CS = di = 17
const char *menu_strings[10] = { "  ОЖИДАНИЕ", "  ПРОХОДИTE", " 3AПPEЩEHO", " ТРИ", " ЧЕТЫРЕ", " ПЯТЬ", " ШЕСТЬ", "СЕМЬ", "  ПPOBEPKA", " ОШИБКА" };


int dosend=0;
int a2;

String str, str1;

void setup() {
  Serial.begin(9600);
  Serial.println("S E T U P");

  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();
  
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  rfidtimer();
  u8g.firstPage();  
  do {
    draw(0);
  } while( u8g.nextPage() );

  pinMode(buzz, OUTPUT);
  tone(buzz, 1000);
  delay(100);
  noTone(buzz);
}

void loop() {
  delay(1);

if (dosend==1){
    dosend = 0;
  
  u8g.firstPage();  
  do {
    draw(8);
  } while( u8g.nextPage() );
  
  tone(buzz, 1000);
  delay(100);
  noTone(buzz);
  delay(1000);
  
  tone(buzz, 1000);
  delay(500);
  tone(buzz, 2000);
  delay(400);
  noTone(buzz);

  u8g.firstPage();  
  do {
    draw(1);
  } while( u8g.nextPage() );
  delay(1000);
  u8g.firstPage();  
  do {
    draw(0);
  } while( u8g.nextPage() );
}
}

