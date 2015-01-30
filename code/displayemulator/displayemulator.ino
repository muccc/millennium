// Nortel Millennium Payphone display-emulator
// rudimentary emulator for a CU20026SCPB-T23A display
//
// Full pinout can be found at
// http://wiki.muc.ccc.de/millennium:boards#connector_pinout
//
// This code aims at Arduino Nano w/ ATMega328.
// If needed, change the pinout in the definitions below.
//
// This code comes with no warranty, blablabla.
//
// Please report bugfixes to https://github.com/muccc/millennium
// or mail the author at martin@muc.ccc.de

//     Arduino name / Arduino pin / Pin on VFD
#define     d0             3     //Pin 15 on VFD
#define     d1             4     //Pin 13 on VFD
#define     d2             5     //Pin 11 on VFD
#define     d3             6     //Pin 9 on VFD
#define     d4             7     //Pin 7 on VFD
#define     d5             8     //Pin 5 on VFD
#define     d6             9     //Pin 3 on VFD
#define     d7            10     //Pin 1 on VFD
/*
#define     x1             4     //Pin 17 on VFD
#define     x2            NC     //Pin 19 on VFD
#define     x3            NC     //Pin 21 on VFD
#define     x4            NC     //Pin 23 on VFD
#define     x5            NC     //Pin 25 on VFD
#define     x6            NC     //Pin 20 on VFD
*/

void setup() {
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);
  attachInterrupt(0, readInput, FALLING);
  Serial.begin(9600);
  Serial.write("Setup complete");
}

void loop() {
}

void readInput() {
  byte v;
  bitWrite(v, 7, digitalRead(d0));
  bitWrite(v, 6, digitalRead(d1));
  bitWrite(v, 5, digitalRead(d2));
  bitWrite(v, 4, digitalRead(d3));
  bitWrite(v, 3, digitalRead(d4));
  bitWrite(v, 2, digitalRead(d5));
  bitWrite(v, 1, digitalRead(d6));
  bitWrite(v, 0, digitalRead(d7));
  Serial.write(v);
}
