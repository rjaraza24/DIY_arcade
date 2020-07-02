 /*
Using 2 7-segment displays with the 74HC595 shift registers
CC by-sa-nc 3.0
http://tronixstuff.wordpress.com
*/



/*
 * ORDER : MOTORDRIVER - WHTE(12V) - BLACK(GND) - GREEN (IN1 Motor) - BLUE(IN2 motor)
 *         GREEN(12V Motor) - BLUE(GND MOTOR) 
 *         GREEN(STOPPER OPEN PIN1) - BLK(GND STOPPER) - BLUE(STOPPER CLOSE PIN4)
 *         BLK(GND OF RED LED BUTTON - wHT(12V button lED) - GREEN(BUTTON PIN18) - BLACK(GND SHORTED TO GND STOPEER) - BLUE(RASPBERRY BUTTON PIN19)
 *         
 */


#include <Servo.h>
boolean interrupt = false;
int z         = 0;
int u         = 45 ;
int dw        = 130;
int motor_close = 18; //positive blue //2 sa uno //3 //'595 PIN27
int motor_open = 19; //negative yellow //3 sa uno //2 atmega //'595 PIN28
int button    =  9; //LED Red Button//'595 PIN15
int led       = 15; // LED red NPN//'595 PIN24
int relay     = 10; //from Rpi ///12-c  19-b 19-A//'595 PIN16
int stop_close = 4; //pagtaas stopper //5 uno //1 atmega//'595 PIN6
int stop_open = 3; //pagbaba stopper //'595 PIN5
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 20000;  

int latchpin  = 7; // connect to pin 12 on the '595 //'595 PIN7
int clockpin  = 8; // connect to pin 11 on the '595//'595 PIN8
int datapin   = 6; // 14//'595 PIN6


enum {OPEN, CLOSED, OPENING, CLOSING, UNKNOWN};
byte get_roof_status()
{
    if (digitalRead(stop_close) == LOW) return CLOSED; //pagtaas
    else if (digitalRead(stop_open) == LOW) return OPEN; // pagbaba
    else if (digitalRead(motor_open) == HIGH) return OPENING;
    else if (digitalRead(motor_close) == HIGH) return CLOSING;
    return UNKNOWN;
}

float b       = 0;
int   c       = 0;  
float d       = 0;
int   e       = 0;
int   speed   = 500; // used to control speed of counting
int   segdisp[10] = { 3,159,37,13,153,73,65,27,1,9 };

boolean Bpressed = false;
boolean Rpressed;
//boolean setup = true;
Servo myservo;   


void open_roof() {
//    digitalWrite(alarm, HIGH);
//    digitalWrite(enable_motor, HIGH);
    digitalWrite(motor_close, LOW);
    digitalWrite(motor_open, HIGH);
    // Loop until roof is open
    while (OPEN != get_roof_status()) /* NULL */;
    stop();
}
void close_roof() {
//    digitalWrite(alarm, HIGH);
//    digitalWrite(enable_motor, HIGH);
    digitalWrite(motor_open, LOW);
    digitalWrite(motor_close, HIGH);
    // Loop until roof is closed
    while (CLOSED != get_roof_status()) /* NULL */;
    stop();
}
void stop() {
//    digitalWrite(alarm, LOW);
//    digitalWrite(enable_motor, LOW);
    digitalWrite(motor_open, LOW);
    digitalWrite(motor_close, LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(relay, INPUT_PULLUP);
  pinMode(motor_open, OUTPUT);
  pinMode(motor_close, OUTPUT);
  pinMode(stop_close, INPUT_PULLUP);
  pinMode(stop_open, INPUT_PULLUP);
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  digitalWrite(led, LOW);
//  scorer();
//  close_roof();
  delay(2000);
  close_roof();
  delay(1000);
//  open_roof();
  timer0();
  delay(40000);
  Rpressed = false;
//  rises(300);
}

void loop() {
  
  if(digitalRead(relay) == LOW && Rpressed == false){
    Rpressed = true;
  digitalWrite(led, HIGH);  
//     servo();
  delay(150);
  }
  if(digitalRead(button) == LOW && Rpressed == true){
      Bpressed = true;
  delay(150);    
  }

  if(Bpressed == true) { 
      digitalWrite(led, LOW);
      delay(100);
    open_roof();
      delay(500);   
    timer(60); /////////////////////////////////change this for time
      delay(1000);
   close_roof();
         Bpressed = false;
      Rpressed = false;
        }
  }


void timer0() {
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, LSBFIRST, segdisp[0]); // clears the right display
    shiftOut(datapin, clockpin, LSBFIRST, segdisp[0]); // clears the left display
    digitalWrite(latchpin, HIGH);
}

void timer(int t) {
  
  for (int z=t; z>=0; z--)
  {
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, LSBFIRST, 255); // clears the right display
    shiftOut(datapin, clockpin, LSBFIRST, 255); // clears the left display
    digitalWrite(latchpin, HIGH);

//    counted = false;

    if (z<10)
    {
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, segdisp[z]); // sends the digit down the serial path
      shiftOut(datapin, clockpin, LSBFIRST, 255); // sends a blank down the serial path to push the digit to the right
      digitalWrite(latchpin, HIGH);
    }
    if (z==0){
      Bpressed = false;
      Rpressed = false;
      return;
    }
    else if (z>=10)
    {
      d = z%10; // find the remainder of dividing z by 10, this will be the right-hand digit
      c = int(d); // make it an integer, c is the right hand digit
      b = z/10; // divide z by 10 - the whole number value will be the left-hand digit
      e = int(b); // e is the left hand digit
      digitalWrite(latchpin, LOW); // send the digits down to the shift registers!
      shiftOut(datapin, clockpin, LSBFIRST, segdisp[c]); 
      shiftOut(datapin, clockpin, LSBFIRST, segdisp[e]); 
      digitalWrite(latchpin, HIGH);
    }
    else{
      delay(speed);
    }

    delay(1000);
  }
}
