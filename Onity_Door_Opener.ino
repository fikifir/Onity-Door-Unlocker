//////////////////////////////////////Hardware setup//////////////////////////////////
// Arduino UNO
// 5.6k resistor
// Crystal
// DC (coaxial) barrel connector, 5mm outer diameter, 2.1mm inner diameter
//////////////////////////////////////Wiring Diagram//////////////////////////////////
// Attach the resistor 5.6K from 3.3v power on the Arduino to digital IO pin 3.
// Attach digital IO pin 3 to the inner contact on the DC connector.
// Attach ground from the Arduino to the outer contact on the DC connector.

//////////////////////////////////////Alternative/////////////////////////////////////
// 3.3v Arduino Power ---> 5.6K Resistor
// 5.6K Resistor --------> Digital IO pin 3
// Digital IO pin 3 -----> Inner DC Plug connector
// Ground ---------------> Outer DC Plug connector

//////////////////////////////////////Hardware setup//////////////////////////////////
// 1 ATMega328 (pre-loaded with the sketch)
// 5.6k resistor
// 30 ohm resistor
// 16Mhz Crystal
// 3.3v Zener diode
// A23 12V Battery
// SPST tall mini push button (momentary on)
// DC (coaxial) barrel connector, 5mm outer diameter, 2.1mm inner diameter
// Protoboard 1-3/4in. X 1-1/2in

//////////////////////////////////////Wiring Diagram//////////////////////////////////
// PB6 -----------> 16Mhz XTAL
// 16Mhz XTAL ----> PB7
// 

/////////////////////////////////////Code Start/////////////////////////////////////

#define CONSERVATIVE

int ioPin = 3;
#define BUFSIZE 200
unsigned char buf[BUFSIZE];

#define pullLow() pinMode(ioPin, OUTPUT)
#define pullHigh() pinMode(ioPin, INPUT)

unsigned char dbits[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0};

unsigned char bits[][144] = {
  {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 0, 1, 0, 0, 0, 1, 0, 
    0, 1, 

    1, 0, 0, 0, 1, 0, 0, 0, 1, 
    1, 0, 1, 0, 0, 1, 0, 1, 1, 
    1, 1, 0, 0, 0, 0, 1, 1, 1, 
    0, 0, 0, 1, 1, 1, 0, 1, 1,

    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  }, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0}
};

unsigned char bval;

void wentLow() {
  bval = 1;
}

void setup() {
}

bool open() {
  pinMode(ioPin, OUTPUT);
  digitalWrite(ioPin, LOW);
  pinMode(ioPin, INPUT);
  digitalWrite(ioPin, LOW);

  for(int i = 0; i < sizeof(dbits); ++i) {
    if(dbits[i] == 0) {
      pullLow();
      delayMicroseconds(16);
      pullHigh();
      delayMicroseconds(190);
    } else {
      pullLow();
      delayMicroseconds(16);
      pullHigh();
      delayMicroseconds(56);
      pullLow();
      delayMicroseconds(16);
      pullHigh();
      delayMicroseconds(112);
    }
  }

  pullLow();
  delayMicroseconds(16);
  pullHigh();

  bval = 0;
  attachInterrupt(1, wentLow, FALLING);

  unsigned int i = 0;
  while(digitalRead(ioPin) == HIGH && i++ < 32767) {}
  if(i == 32767)
    return false;

  delayMicroseconds(20);
  for(int i = 0; i < 164; ++i) {
    buf[i] = 0;
    pullLow();
    delayMicroseconds(8);
    pullHigh();
    bval = 0;
    delayMicroseconds(184);
    buf[i] = bval;
  }

  for(int i = 0; i < 32+3; ++i)
    bits[0][50+i] = buf[22+i];

  for(int i = 0; i < 8; ++i)
    bits[0][86+i] = bits[0][50+i] ^ bits[0][50+9+i] ^ bits[0][50+18+i] ^ bits[0][50+27+i];
  bits[0][86] ^= 1;
  bits[0][87] ^= 0;
  bits[0][88] ^= 1;
  bits[0][89] ^= 1;
  bits[0][90] ^= 1;
  bits[0][91] ^= 0;
  bits[0][92] ^= 1;
  bits[0][93] ^= 1;

#ifdef CONSERVATIVE
  delay(100);
#endif
  for(int j = 0; j < 11; ++j) {
    for(int i = 0; i < sizeof(bits[j]); ++i) {
      if(bits[j][i] == 0) {
        pullLow();
        delayMicroseconds(16);
        pullHigh();
        delayMicroseconds(190);
      } else {
        pullLow();
        delayMicroseconds(16);
        pullHigh();
        delayMicroseconds(56);
        pullLow();
        delayMicroseconds(16);
        pullHigh();
        delayMicroseconds(112);
      }
    }
#ifdef CONSERVATIVE
    delayMicroseconds(2700);
#else
    delayMicroseconds(500);
#endif
  }
  return true;
}

void loop() {
    open();
}

