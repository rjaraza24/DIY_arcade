#include <Servo.h>
int relay = 3; //#button
int scoreRelay = 12; //#relay
int motorRelay = 11 ; // trigger ng motor 
int IRslot = 6; //#outer IR
int IRslot2 = 5; //inner ir
int conCW = 8; //RED POSITIVE MTR BLUE
int conCCW =9; //BLACK NEGATIVE MTR GRN
int enA = 13;
int scanning = 6000;
//boolean setup = true;
boolean detect = false;
boolean scan = false;
boolean go = false;
boolean complete = false;
boolean Rpressed = false;


void setup()
{
//  pinMode(led, OUTPUT);
  pinMode(scoreRelay, OUTPUT);
  pinMode(motorRelay, OUTPUT);
  pinMode(relay, INPUT_PULLUP);
  pinMode(IRslot, INPUT);
  pinMode(IRslot2, INPUT);
  pinMode(conCW, OUTPUT);
  pinMode(conCCW, OUTPUT);
  digitalWrite(scoreRelay, HIGH);  
  digitalWrite(motorRelay, HIGH);
  Rpressed = false;
 digitalWrite(enA, 150);
  delay(1000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, LOW);
    delay(4000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, HIGH);    
delay(10000);
//  rises(300);
}

void loop() {
  if(digitalRead(IRslot) == LOW && complete == false && go == false){
    detect = true;
    digitalWrite(conCCW, LOW);
    digitalWrite(conCW, HIGH);
  }
  if(digitalRead(IRslot2) == LOW && detect == true){
    delay(1000);
    detect = false;
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, HIGH);
    complete = true;
    scan = true;
    delay(scanning);
  }
  if(digitalRead(relay) == HIGH){
    go = false;
    delay(150);
    }
//    if(digitalRead(relay) == LOW && digitalRead(IRslot2) == LOW){
//    go = true;
//    delay(150);
//    }  
    if(digitalRead(relay) == LOW ){
    go = true;
    delay(150);
    }  
  if(scan == true && go == false){
//    delay(3000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, LOW);
    delay(8000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, HIGH);    
    scan = false;
    complete = false;
    delay(2000);
    
  }
 
  if(scan == true && go == true && Rpressed == false){
    delay(500);
   digitalWrite(scoreRelay, LOW);
   digitalWrite(motorRelay, LOW);
  delay(500); 
   digitalWrite(scoreRelay, HIGH);
   digitalWrite(motorRelay, HIGH);
//    go = false;
    scan = false;
    complete = false;
    Rpressed = true;

    
  }

  if(Rpressed == true){
    delay(500);
        digitalWrite(conCCW, LOW);
    digitalWrite(conCW, HIGH);
    delay(10000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, HIGH);  
    Rpressed = false;
        delay(2000);
            go = false;
            delay(5000);
  }
}
