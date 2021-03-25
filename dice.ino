// boilerplate code taken from: https://create.arduino.cc/projecthub/SAnwandter1/programming-8x8-led-matrix-23475a
// another clutch website: https://xantorohara.github.io/led-matrix-editor/#

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

byte oneFace[] = {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
byte twoFace[] = {B00000000,B00000110,B00000110,B00000000,B00000000,B01100000,B01100000,B00000000};
byte threeFace[] = {B00000000,B00000110,B00000110,B00011000,B00011000,B01100000,B01100000,B00000000};
byte fourFace[] = {B00000000,B01100110,B01100110,B00000000,B00000000,B01100110,B01100110,B00000000};
byte fiveFace[] = {B00000000,B01100110,B01100110,B00011000,B00011000,B01100110,B01100110,B00000000};
byte sixFace[] = {B01100110,B01100110,B00000000,B01100110,B01100110,B00000000,B01100110,B01100110};

int buttonState = 0;

void setup() 
{
    // Open serial port
    Serial.begin(9600);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, INPUT);
}

int randomN() {
  return random(1, 7);
}

byte * getPattern(int number) {
  switch (number) {
    case 1: 
      return oneFace;
    case 2:
      return twoFace;
    case 3:
      return threeFace;
    case 4:
      return fourFace;
    case 5:
      return fiveFace;
    case 6:
      return sixFace;
  }
}

void rollDie() {
    delay(5);
    for (int i = 0; i < 6; i++) {
      byte* pattern = getPattern(randomN());
      for (int j = 0; j < 210; j++) {
        drawScreen(pattern);
      }
    }
    byte* truePattern = getPattern(randomN());
    for (int i = 0; i < 3000; i++) {
      drawScreen(truePattern);
    }
}

void loop() {
  buttonState = digitalRead(A4);
  if (buttonState) {
    rollDie();
  }
  
}
void  drawScreen(byte buffer2[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        // count next row
     {
        digitalWrite(rows[i], HIGH);    //initiate whole row
        for (byte a = 0; a < 8; a++)    // count next row
        {
          // if You set (~buffer2[i] >> a) then You will have positive
          digitalWrite(col[a], (~buffer2[i] >> a) & 0x01); // initiate whole column
          
          delayMicroseconds(10);       // uncoment deley for diferent speed of display
          //delayMicroseconds(1000);
          //delay(10);
          //delay(100);
          
          digitalWrite(col[a], 1);      // reset whole column
        }
        digitalWrite(rows[i], LOW);     // reset whole row
        // otherwise last row will intersect with next row
    }
}
