
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

int inc = 1;
int pressPin = 14 ;
int clearPin = 15 ;
int playPin = 16 ;
int rlyPin = 17;
int value;
int address = 0; 
int memvalue ; 
int value2;
int memadd;
int crdtmx = 6;
int crdt = 0;

int total;


int playtime = 5000;

void clearEEPROM();
void printSachet();
void incSachet();
void lcdfnc();
void play();

 /*
  * Uno, Ethernet  A4 (SDA), A5 (SCL)
    Mega2560  20 (SDA), 21 (SCL)
  */

LiquidCrystal_I2C lcd(0x27,20,4);


void setup() {
    pinMode(pressPin,INPUT_PULLUP) ;
  pinMode(clearPin,INPUT_PULLUP) ;
  pinMode(playPin,INPUT_PULLUP) ;
  pinMode(rlyPin, OUTPUT) ;
//  pinMode(countPin,OUTPUT) ;
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  digitalWrite(rlyPin, HIGH);
delay(500);
  lcd.init();  
//  lcdfnc(0);
//clearEEPROM();
printSachet();
delay(500);
address = memadd;
}

void loop() {
  if(!digitalRead(playPin)){
   play();
  delay(500);
  }

//  total = ((memadd)*10)+memvalue;
  
  if(!digitalRead(pressPin)){
    Serial.println(value2);
    incSachet(memvalue);
    
  delay(500);
  }
  
  if(!digitalRead(clearPin)) //check if erase button is pressed
  {
    clearEEPROM();
    delay(500);
  }
  
}


void clearEEPROM()
{
  for (int j = 0 ; j < EEPROM.length() ; j++) {
    if(EEPROM.read(j) != 0)                     //skip already "empty" addresses
    {
      EEPROM.write(j, 0);
      //write 0 to address i
    
    }
  }
  Serial.println("EEPROM erased");
  memvalue = 0;
  address = 0;   
  value = 0;
  memadd= 0;//reset address counter
  crdt = 0;
      total = ((memadd)*10)+memvalue;
      lcdfnc(total, crdt);
}

void printSachet(){
   for (int j = 0 ; j < EEPROM.length() ; j++) { //EEPROM.length()
     value2 = EEPROM.read(j);   
    if(value2 != 0)                              //skip "empty" addresses
    {
      memvalue = value2;
      memadd = j;
      Serial.print(memadd);
      Serial.print(" ");
      Serial.println(memvalue);
    }
//delay(100);
//      total = ((memadd)*10)+memvalue;
//      lcdfnc(total);
  }
      total = ((memadd)*10)+memvalue;
      lcdfnc(total, crdt);
}
void incSachet(int i){
  if(i==0){
    value++;
    Serial.println("i=0");
    delay(100);

    EEPROM.write(address, value);
    Serial.print("Sensor value stored at address : ");
    Serial.println(address);
    Serial.print("Sensor value stored total: ");
    Serial.println(value);
      total = ((address)*10)+value;
      crdt++;
      lcdfnc(total, crdt);
      if(crdt > 5){
        crdt = 5;
        lcdfnc(total, crdt);
      }
      if(value >= 10 ){
      address++;
      memvalue=1;
      value=1;
      inc=0;
      i=0;
      Serial.println("address added");
   
     }   
  }

  else if(value!=value || i>0){
    
//    value= inc++; 
        value= ((i)+inc);    
   
    Serial.print("i= ");
    Serial.println(value);
    delay(100);
     
     EEPROM.write(address, value); 
  Serial.print("Sensor value stored at address : ");
  Serial.println(address);
    Serial.print("Sensor value stored total: ");
  Serial.println(value);
   inc++;
   crdt++;
     total = ((address)*10)+value;
      lcdfnc(total, crdt);
            if(crdt > 5){
        crdt = 5;
        lcdfnc(total, crdt);
      }
      if(value >= 10 ){
      address++;
      memvalue=1;
      value=1;
      inc=0;
      i=0;
      Serial.println("address added");
   
     }   
  }

  if(address == EEPROM.length())  //check if address counter has reached the end of EEPROM
  {
    address = 0;              //if yes: reset address counter
  }
}


void lcdfnc(int lcdtotal, int crdtval){
 lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Sachet Credits:");
  lcd.setCursor(9,1);
  lcd.print(crdtval);
   lcd.setCursor(1,2);
  lcd.print("Sachets Collected:");
   lcd.setCursor(9,3);
  lcd.print(lcdtotal);
 
}


void play(){
  if ( crdt > 0 && crdt < crdtmx ){
    Serial.println("Playing...");
    digitalWrite(rlyPin, LOW);
    delay(1000);
    digitalWrite(rlyPin, HIGH);
    crdt--;
    lcdfnc(total, crdt);
    delay(playtime);
  }
  else if(crdt==0 ){
    digitalWrite(rlyPin, HIGH);
    Serial.println("No Credits");
  }
}
