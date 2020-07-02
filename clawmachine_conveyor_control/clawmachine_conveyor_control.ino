 /*
Using 2 7-segment displays with the 74HC595 shift registers
CC by-sa-nc 3.0
http://tronixstuff.wordpress.com
*/

#include <Servo.h>
int relay = 5;
int videokeR = 6;
int IRslot = 3;
int IRslot2 = 8;
int conCW = 4;
int conCCW =9;
int BarR = 7;
int enA = 12;


int pwmDC = 240;

//boolean setup = true;
boolean detect = false;
boolean scan = false;
boolean go = false;
boolean complete = false;
boolean Rpressed = false;


void setup()
{
  Serial.begin(9600);
    pinMode(enA, OUTPUT);
  analogWrite(enA, pwmDC);
  delay(500);
//  pinMode(led, OUTPUT);
  pinMode(videokeR, OUTPUT);
  pinMode(BarR, OUTPUT);
  pinMode(relay, INPUT_PULLUP);
  pinMode(IRslot, INPUT);
  pinMode(IRslot2, INPUT);
  pinMode(conCW, OUTPUT);
  pinMode(conCCW, OUTPUT);
  digitalWrite(videokeR, HIGH);
    digitalWrite(BarR, HIGH);

  Rpressed = false;

  delay(3000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, LOW);
    Serial.println("reverse");
    delay(5000);
    digitalWrite(conCCW, LOW);
    digitalWrite(conCW, LOW);    
    Serial.println("stop");

delay(500);
//  rises(300);
}

void loop() {
  if(digitalRead(IRslot) == LOW && complete == false){
    detect = true;
    digitalWrite(conCCW, LOW);
    digitalWrite(conCW, HIGH);
    digitalWrite(BarR, LOW);
//    delay(1000);
//    digitalWrite(BarR, HIGH);
    Serial.println("forward");
  }
  if(digitalRead(IRslot2) == LOW && detect == true){
    detect = false;
    digitalWrite(conCCW, LOW);
    digitalWrite(conCW, LOW);
    Serial.println("stop");
    delay(100);
    digitalWrite(BarR, HIGH);
        delay(100);
    digitalWrite(BarR, LOW);
    delay(1500);
    digitalWrite(BarR, HIGH);
    complete = true;
    scan = true;
    delay(1000); //adjust to kain time
  }
  if(digitalRead(relay) == HIGH){
    go = false;
    Serial.println("fail");
    delay(150);
    }
    if(digitalRead(relay) == LOW ){
    go = true;
    Serial.println("success");
    delay(150);
    }  
  if(scan == true && go == false){
//    delay(3000);
    digitalWrite(conCCW, HIGH);
    digitalWrite(conCW, LOW);
    Serial.println("reverse");
    delay(7000);
    digitalWrite(conCCW, LOW);
    digitalWrite(conCW, LOW); 
    Serial.println("stop");   
    scan = false;
    complete = false;
    
    
  }
 
  if(scan == true && go == true && Rpressed == false){
    delay(100);
     digitalWrite(videokeR, LOW);
  delay(500); 
   digitalWrite(videokeR, HIGH);
   delay(200);
    digitalWrite(conCCW, LOW);
    digitalWrite(conCW, HIGH);
    Serial.println("forwardSuccess");
//    Rpressed = true;
    delay(9000);
        digitalWrite(conCCW, LOW);
    digitalWrite(conCW, LOW);  
    Serial.println("stop");
    go = false;
    scan = false;
    complete = false;
    Rpressed = true;
  }
//
//  
//  if(digitalRead(relay) == LOW && Rpressed == false){
//    Rpressed = true;
//  digitalWrite(led, HIGH);
////     servo();
//  delay(150);
//  }
  if(Rpressed == true){
    

    Rpressed = false;
  }
}
