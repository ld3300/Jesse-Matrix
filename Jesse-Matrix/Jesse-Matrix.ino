int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int time = 200;
const int index = 59;

byte data;
byte dataArray[index];

void setup() {
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);

  //Back and forth 1 by 1 (x2)
  dataArray[0] = 0x80;
  dataArray[1] = 0x40;
  dataArray[2] = 0x20;
  dataArray[3] = 0x10;
  dataArray[4] = 0x08;
  dataArray[5] = 0x04;
  dataArray[6] = 0x02;
  dataArray[7] = 0x01;
  dataArray[8] = 0x02;
  dataArray[9] = 0x04;
  dataArray[10] = 0x08;
  dataArray[11] = 0x10;
  dataArray[12] = 0x20;
  dataArray[13] = 0x40;
  dataArray[14] = 0x80;
  dataArray[15] = 0x40;
  dataArray[16] = 0x20;
  dataArray[17] = 0x10;
  dataArray[18] = 0x08;
  dataArray[19] = 0x04;
  dataArray[20] = 0x02;
  dataArray[21] = 0x01;
  dataArray[22] = 0x02;
  dataArray[23] = 0x04;
  dataArray[24] = 0x08;
  dataArray[25] = 0x10;
  dataArray[26] = 0x20;
  dataArray[27] = 0x40;
  dataArray[28] = 0x80;
  //Pulse (x2)
  dataArray[29] = 0x18;
  dataArray[30] = 0x3C;
  dataArray[31] = 0x7E;
  dataArray[32] = 0xFF;
  dataArray[33] = 0x7E;
  dataArray[34] = 0x3C;
  dataArray[35] = 0x18;
  dataArray[36] = 0x3C;
  dataArray[37] = 0x7E;
  dataArray[38] = 0xFF;
  dataArray[39] = 0x7E;
  dataArray[40] = 0x3C;
  dataArray[41] = 0x18;
  //Trail - 3 led follow
  dataArray[42] = 0x08;
  dataArray[43] = 0x18;
  dataArray[44] = 0x38;
  dataArray[45] = 0x70;
  dataArray[46] = 0xE0;
  dataArray[47] = 0xC0;
  dataArray[48] = 0x80;
  dataArray[49] = 0x00;
  dataArray[50] = 0x01;
  dataArray[51] = 0x03;
  dataArray[52] = 0x07;
  dataArray[53] = 0x0E;
  dataArray[54] = 0x1C;
  dataArray[55] = 0x38;
  dataArray[56] = 0x70;
  dataArray[57] = 0xE0;
  dataArray[58] = 0xC0;
}

void loop() {
  for (int j = 0; j < index; j++) {
    data = dataArray[j];
    digitalWrite(latchPin, 0);
    
    shiftOut(dataPin, clockPin, data);
    
    digitalWrite(latchPin, 1);
    delay(time);
  }
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  
  for (i = 7; i >= 0; i--) {
    digitalWrite(myClockPin, 0);
    
    if (myDataOut & (1<<i)) {
      pinState = 1;
    } else {
      pinState = 0;
    }
    
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
  digitalWrite(myClockPin, 0);
}
