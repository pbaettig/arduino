#define STROBE 17
#define DATA 18
#define CLOCK 19

void pulseClock() {
  digitalWrite(CLOCK, HIGH);
  delay(1);
  digitalWrite(CLOCK, LOW);
}

void shiftOutBit(bool in) {
  int w = in ? HIGH : LOW;
  digitalWrite(DATA, w);

  pulseClock();
}

void shiftOutTwoBytes(int in) {
  byte upper = in >> 8;
  byte lower = in & 0xff;

  shiftOut(DATA, CLOCK, MSBFIRST, upper);
  shiftOut(DATA, CLOCK, MSBFIRST, lower);
}


void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(STROBE, OUTPUT);
  pinMode(CLOCK, OUTPUT);

  digitalWrite(DATA, LOW);
  digitalWrite(STROBE, LOW);
  digitalWrite(CLOCK, LOW);

  digitalWrite(STROBE, LOW);
  shiftOutTwoBytes(0xffff);
  digitalWrite(STROBE, HIGH);
  delay(500);

  Serial.begin(9600);
  Serial.println("Reset\n");
  
}
int counter = 0;
unsigned int value = 0;
bool goingUp = true;

void loop() {

  if(goingUp && counter == 16) {
    // going down
    goingUp = false;
  }

  if(!goingUp && counter == 0) {
    // going up again
    goingUp = true;
    value = 0;
  }

  if(goingUp) {
    value += 1 << counter++;
  } else {
    value -= 1 << counter--;
  }
  
  

  digitalWrite(STROBE, LOW);
  shiftOutTwoBytes(value);
  digitalWrite(STROBE, HIGH);

   delay(25);
}
