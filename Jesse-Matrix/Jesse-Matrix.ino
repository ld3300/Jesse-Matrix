int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int time = 200;
const int index = 59;

byte data;
//byte dataArray[index];
byte dataArray = 1;  //no longer need an array

int pattNumber = 0;     //variable to indicate next pattern
int curPattern = 0;

int numPatterns = 6;    // How many patterns in the case statement

void setup() {
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  pattNumber = pattNumber % numPatterns;
  patterns();
  
//  for (int j = 0; j < index; j++) {
    data = dataArray;
    digitalWrite(latchPin, 0);
    
    shiftOut(dataPin, clockPin, data);
    
    digitalWrite(latchPin, 1);
    delay(time);
//  }
}

void patterns(){
  switch (pattNumber) {
    case 0:
      //Back and forth 1 by 1 (x2)  Simple Method
      if (curPattern < 8) {
        dataArray *= 2;
      }
      else if (curPattern < 16) {
        dataArray /= 2;
      }
      curPattern += 1;
      if (curPattern == 16) {
        curPattern = 0;
        pattNumber += 1; //add one to pattNumber
      }
    break;
    case 1:
      //Pulse (x2)
      if (curPattern == 0 || curPattern == 6 || curPattern == 12) {
        dataArray = 0x18; //24
      }
      else if(curPattern == 1 || curPattern == 5 || curPattern == 7 || curPattern == 11) {
        dataArray = 0x3C; //60
      }
      else if(curPattern == 2 || curPattern == 4 || curPattern == 8 || curPattern == 10) {
        dataArray = 0x7E; //126
      }
      else if(curPattern == 3 || curPattern == 6 || curPattern == 9) {
        dataArray = 0xFF; //255
      }
      curPattern += 1;
      if (curPattern == 13) {
        curPattern = 0;
        pattNumber += 1;
      }
    break;
    case 2: 
      dataArray += 1;
      curPattern += 1;
      if (curPattern == 255) {
        curPattern = 0;
        pattNumber += 1;
      }
    break;
    case 3: 
      dataArray -= 1;
      curPattern += 1;
      if (curPattern == 255) {
        curPattern = 0;
        pattNumber += 1;
      }
    break;
    case 4:
      randomSeed(analogRead(0));
      dataArray = random(255);
      curPattern += 1;
      if (curPattern == 25) {
        curPattern = 0;
        pattNumber += 1;
      }
    break;
    case 5:
      if (curPattern == 0) {
        dataArray = 0;
      }
      else if (curPattern <= 8) {
        dataArray << 1;
        dataArray += 1;
      }
      else if (curPattern <= 16) {
        dataArray >> 1;
      }
      curPattern +=1;
      if (curPattern == 25) {
        curPattern = 0;
        pattNumber += 1;
      }
    break;
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
