
#include <EEPROM.h>
// ADRES 0 PWM DEĞERİ
// ADRES 1 KIRMIZI
// ADRES 2 MAVİ
// ADRES 3 YEŞİL

#define CLK 2
#define DT 3
#define SW 4

#define red 9
#define grn 5
#define blue 6

bool cnt = 0;
bool cnt1 = 0;
bool cnt2 = 0;
int enc = 0;


#define b1 10
#define b2 11
#define b3 12

int rval = 0;
int gval = 0;
int bval = 0;
int yc = 0;

int counter = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

void setup() {

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT);

  pinMode(red, OUTPUT);
  pinMode(grn, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(grn, LOW);
  digitalWrite(blue, LOW);

  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);

  counter = EEPROM.read(0);//PWM
  rval = EEPROM.read(1);//KIRMIZI DURUMU
  bval = EEPROM.read(2);//MAVI DURUMU
  gval = EEPROM.read(3);//YESIL DURUMU

  lastStateCLK = digitalRead(CLK);
}

void loop() {

  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      counter = counter - 10;
      EEPROM.write(1, counter);
      if (counter <= 1) {
        counter = 0;
      }
    }

    else {
      counter = counter + 10;
      EEPROM.write(1, counter);
      if (counter >= 240) {
        counter = 250;
      }
    }
  }

  lastStateCLK = currentStateCLK;
  int btnState = digitalRead(SW);

  if (btnState == LOW) {
    if (millis() - lastButtonPress > 250) {
      enc++;
    }
    lastButtonPress = millis();
  }

  if(enc == 1 && counter > 9){
    counter = counter - 10;
    delay(80);
  }
 
  if(enc == 2){
    counter = 100;
    enc = 0;
  }


  if (digitalRead(b1) == LOW && cnt == 0) {
    rval++;
    EEPROM.write(1,1);
    cnt = 1;
  }
  if (digitalRead(b1) == HIGH && cnt == 1) {
    cnt = 0;
  }


  if (digitalRead(b2) == LOW && cnt1 == 0) {
    gval++;
    EEPROM.write(3,1);
    cnt1 = 1;
  }
  if (digitalRead(b2) == HIGH && cnt1 == 1) {
    cnt1 = 0;
  }


  if (digitalRead(b3) == LOW && cnt2 == 0) {
    bval++;
    EEPROM.write(2,1);
    cnt2 = 1;
  }
  if (digitalRead(b3) == HIGH && cnt2 == 1) {
    cnt2 = 0;
  }


 
  if (rval == 1) {
    analogWrite(red, counter);
  }

  if (gval == 1) {
    analogWrite(grn, counter);
  }

  if (bval == 1) {
    analogWrite(blue, counter);
   }


  if (rval == 0) {
    analogWrite(red, 0);
  }
  if (bval == 0) {
    analogWrite(blue, 0);
  }

  if (gval == 0) {
    analogWrite(grn, 0);
  }

  if (rval > 1) {
    rval = 0;
    EEPROM.write(1,0);
  }

  if (gval > 1) {
    EEPROM.write(3,0);
    gval = 0;
  }

  if (bval > 1) {
    EEPROM.write(2,0);
    bval = 0;
    }
 
  }
