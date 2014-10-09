////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////                                                                            ////
////                        VFD Test Code for CU20026SCPB-T23A                  ////
////                              Author: Wes D & Mark M                        ////
////                                 Date: 2/17/2014                            ////
////                                  Version: 1.00                             ////
////                            Platform: Arduino Mega 2560                     ////
////                                                                            ////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// These pins are based on a Arduino Mega 2560. But can be run on any Arduino 
// I have tested with enough pins. And just to be clear, this could just as
// easily be run on a Pic or Pi or Beagle, you name it. 
//     Arduino name / Arduino pin / Pin on VFD
#define     d0            22     //Pin 15 on VFD
#define     d1            24     //Pin 13 on VFD
#define     d2            26     //Pin 11 on VFD
#define     d3            28     //Pin 9 on VFD
#define     d4            30     //Pin 7 on VFD
#define     d5            32     //Pin 5 on VFD
#define     d6            34     //Pin 3 on VFD
#define     d7            36     //Pin 1 on VFD
#define     x1            38     //Pin 17 on VFD
#define     x2            40     //Pin 19 on VFD
#define     x3            42     //Pin 21 on VFD
#define     x4            44     //Pin 23 on VFD
#define     x5            46     //Pin 25 on VFD
#define     x6            48     //Pin 20 on VFD

int scrollDelay;

void setup() {
  pinMode(d0,OUTPUT);
  pinMode(d1,OUTPUT);
  pinMode(d2,OUTPUT);
  pinMode(d3,OUTPUT);
  pinMode(d4,OUTPUT);
  pinMode(d5,OUTPUT);
  pinMode(d6,OUTPUT);
  pinMode(d7,OUTPUT);
  pinMode(x1,OUTPUT);
  pinMode(x2,OUTPUT);
  pinMode(x3,OUTPUT);
  pinMode(x4,OUTPUT);
  pinMode(x5,OUTPUT);
  pinMode(x6,OUTPUT);
  pinMode(12,OUTPUT);

  //Default States
  digitalWrite(12, HIGH);
  digitalWrite(d0, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);

  digitalWrite(x1, HIGH);
  digitalWrite(x2, LOW);
  digitalWrite(x3, HIGH);
  digitalWrite(x4, LOW);
  digitalWrite(x5, HIGH);
  digitalWrite(x6, LOW);
  
}

void vfdreset() {
  //According to an anonymous source, this needs to be done once and a while because of corrupt 
  //characters appearing on the screen. We have confirmed this. The reset is very fast, you can 
  //shorten the delays a bit, but you will have to play around to see what works for you.
  digitalWrite(x6, HIGH);
  delay(2);
  digitalWrite(x6, LOW);  
  delay(10);
}

void vfdtest() {
  //This will kick off the VFD internal test. Basically just steps through all the characters 
  //built in to the display. 
  //Procedure is, hold x5 (VFD Display pin 25) low for 100ms during a reset. Reset does not start until x6 (VFD Display pin 20) is low again. 
  digitalWrite(x5,LOW); 
  digitalWrite(x6,HIGH); 
  delay(50); //This can be shorter, but best results showed this was good.
  digitalWrite(x6,LOW);
  delay(100); //NO TOUCHY!
  delay(15000); //This counter is running while the test sequence is running. Make this longer if you like, the display will keep looping the test until you restart
  digitalWrite(x6, HIGH);
  delay(10);
  digitalWrite(x6, LOW);
  digitalWrite(x5, HIGH);  
}

void loop() {
    scrollDelay = 1;
    vfdreset();    
    delay(200);
    writeCharacter(20u);
    delay(200);
    writeCharacter(18); //Turn off Scroll Mode
    writeCharacter('P');
    writeCharacter('l');
    writeCharacter('e');
    writeCharacter('a');
    writeCharacter('s');
    writeCharacter('e');
    writeCharacter(' ');
    writeCharacter('l');
    writeCharacter('i');
    writeCharacter('f');
    writeCharacter('t');
    writeCharacter(' ');
    writeCharacter('r');
    writeCharacter('e');
    writeCharacter('c');
    writeCharacter('e');
    writeCharacter('i');
    writeCharacter('v');
    writeCharacter('e');
    writeCharacter('r');
    writeCharacter(13);
    writeCharacter(21); //Turn on scroll mode
    for (int i = 0;i < 200; i++) { //This will prevent the re-write of line one and excesive screen resets.
      scrollDelay =150; //Slow down the scroll speed.
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter('H');
      writeCharacter('e');
      writeCharacter('l');
      writeCharacter('l');
      writeCharacter('o');
      writeCharacter(' ');
      writeCharacter('W');
      writeCharacter('o');
      writeCharacter('r');
      writeCharacter('l');
      writeCharacter('d');
      writeCharacter(',');
      writeCharacter(' ');
      writeCharacter('H');
      writeCharacter('o');
      writeCharacter('p');
      writeCharacter('e');
      writeCharacter(' ');
      writeCharacter('y');
      writeCharacter('o');
      writeCharacter('u');
      writeCharacter(' ');
      writeCharacter('e');
      writeCharacter('n');
      writeCharacter('j');
      writeCharacter('o');
      writeCharacter('y');
      writeCharacter(' ');
      writeCharacter('t');
      writeCharacter('h');
      writeCharacter('i');
      writeCharacter('s');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter('P');
      writeCharacter('u');
      writeCharacter('t');
      writeCharacter(' ');
      writeCharacter('a');
      writeCharacter(' ');
      writeCharacter('l');
      writeCharacter('o');
      writeCharacter('o');
      writeCharacter('n');
      writeCharacter('i');
      writeCharacter('e');
      writeCharacter(' ');
      writeCharacter('i');
      writeCharacter('n');
      writeCharacter(' ');
      writeCharacter('t');
      writeCharacter('h');
      writeCharacter('e');
      writeCharacter(' ');
      writeCharacter('s');
      writeCharacter('l');
      writeCharacter('o');
      writeCharacter('t');
      writeCharacter(' ');
      writeCharacter('f');
      writeCharacter('o');
      writeCharacter('r');
      writeCharacter(' ');
      writeCharacter('t');
      writeCharacter('h');
      writeCharacter('e');
      writeCharacter(' ');
      writeCharacter('d');
      writeCharacter('a');
      writeCharacter('n');
      writeCharacter('c');
      writeCharacter('i');
      writeCharacter('n');
      writeCharacter('g');
      writeCharacter(' ');
      writeCharacter('g');
      writeCharacter('i');
      writeCharacter('r');
      writeCharacter('l');
      writeCharacter('s');
      writeCharacter('.');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      writeCharacter(' ');
      delay(5000);
  }
}

void writeCharacter(byte v) {
  digitalWrite(x1, LOW); //Prepare to write
  digitalWrite(d0, bitRead(v,7));
  digitalWrite(d1, bitRead(v,6));
  digitalWrite(d2, bitRead(v,5));
  digitalWrite(d3, bitRead(v,4));
  digitalWrite(d4, bitRead(v,3));
  digitalWrite(d5, bitRead(v,2));
  digitalWrite(d6, bitRead(v,1));
  digitalWrite(d7, bitRead(v,0));
  digitalWrite(x1, HIGH); //Write Complete
  delay(scrollDelay); 

}
