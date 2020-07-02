/*
Using 2 7-segment displays with the 74HC595 shift registers
CC by-sa-nc 3.0
http://tronixstuff.wordpress.com
*/
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 70000 ;      

int y         = 0;
int sensor    = 3; //'595 PIN5
int sensor2   = 4; //'595 PIN6
int button    = 19; //'595 PIN28
int latchpin2 = 7; // connect to pin 12 on the '595 //'595 PIN7
int clockpin2 = 8; // connect to pin 11 on the '595 //'595 PIN8
int datapin2  = 6;// connect to pin 14 on the '595 //'595 PIN6
int scoreDelay = 300;

float b       = 0;
int   c       = 0;  
float d       = 0;
int   e       = 0;
int   speed   = 2000; // used to control speed of counting
int   segdisp[10] = { 3,159,37,13,153,73,65,27,1,9 };

boolean Bpressed = false;  
boolean scoretiming = false;
void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(latchpin2, OUTPUT);
  pinMode(clockpin2, OUTPUT);
  pinMode(datapin2, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(sensor2, INPUT);
//  scorer();
  timer0();
  delay(3000);
}

void loop() {
//delay(50);

// 
  if(digitalRead(button) == HIGH && scoretiming == false) {   //////////LOW(if always off); HIGH( if always ON)
  Bpressed = true;   
  y = 0;
  scorer();
  scoretiming = true;
  delay(150);
  
  }
//
//  if(scoretiming==true){
//    delay(30000);
//    scoretiming = false;
//    }

unsigned long currentMillis = millis();
       
  if (currentMillis - previousMillis >= interval && scoretiming == true) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (scoretiming == false) {
      scoretiming = true;
    } else {
      scoretiming = false;
    
    }
    return;
    }
  


    // set the LED with the ledState of the variable:
//    digitalWrite(ledPin, ledState); 
  
   if( digitalRead(sensor) == LOW && digitalRead(sensor2) == LOW && Bpressed == true ) {      
      y = (y < 99) ? y+1 : 0;
      scorer();  
      delay(scoreDelay);
          
      if(y>99){
          Bpressed = false;
          return; 
      }
    }

}
void timer0() {
    digitalWrite(latchpin2, LOW);
    shiftOut(datapin2, clockpin2, LSBFIRST, segdisp[0]); // clears the right display
    shiftOut(datapin2, clockpin2, LSBFIRST, segdisp[0]); // clears the left display
    digitalWrite(latchpin2, HIGH);
}

void scorer() {


  digitalWrite(latchpin2, LOW);
  shiftOut(datapin2, clockpin2, LSBFIRST, segdisp[y % 10]);  // ones digit
  shiftOut(datapin2, clockpin2, LSBFIRST, segdisp[y / 10]);  // tens digit
  digitalWrite(latchpin2, HIGH);

  return ;
} 
