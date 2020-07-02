int slotR1 = 8;
int slotR2 = 11;


int b1 = 3;
int b2 = 6;

//D2(grn)+GND(blk) = 0.5m
//D3(grn)+GND(blk) = 1m
//D6(blu)+GND(blk) = 1m
//D8(blu)+D9(grn)+5v(wht)+GND(blk) = .2m
//D11(blu)+D12(grn)+5v(wht)+GND(blk) = .2m

//12v(wht) --->Normally Open ng IN2 Relay1 hinang sa baba
//12v(wht) --->Normally Open ng IN2 Relay2 hinangg sa baba

int led1 = 9;
int led2 = 12;



int button1;
int button2;

int fromConveyor;
int fromConv = 2;

boolean readyB = false;
boolean charge = false;
boolean charge1 = false;


void setup() {
   Serial.begin(9600);
   pinMode(slotR1, OUTPUT);
   pinMode(slotR2, OUTPUT);

   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);

   pinMode(b1, INPUT_PULLUP);
   pinMode(b2, INPUT_PULLUP);

   pinMode(fromConv, INPUT_PULLUP);

delay(100);
  digitalWrite(slotR1, HIGH);
  digitalWrite(slotR2, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
delay(1000);

}

void loop() {

 button1 = digitalRead(b1);
 button2 = digitalRead(b2);
 fromConveyor = digitalRead(fromConv);

 if( fromConveyor == LOW ){
digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
//digitalWrite(led3, HIGH);
//digitalWrite(led4, HIGH);
  Serial.println("waiting for specific slot...");

  readyB = true;
 }
 if( button1 == LOW & readyB == true ) {
  digitalWrite(slotR1, LOW);
//  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
//  digitalWrite(led3, LOW);
//  digitalWrite(led4, LOW);
  delay(1500);
  digitalWrite(slotR1, HIGH);
  digitalWrite(led1, HIGH);
  readyB = false;
    Serial.println("Charging SLOT 1");

 }
 
 else if( button2 == LOW & readyB == true ) {
  digitalWrite(slotR2, LOW);
  digitalWrite(led1, HIGH);
  delay(1500);
  digitalWrite(slotR2, HIGH);
  digitalWrite(led2, HIGH);
  readyB = false;
  
    Serial.println("Charging SLOT 2");
 }
 
 
 else {
  digitalWrite(slotR1, HIGH);
  digitalWrite(slotR2, HIGH);


 }


}
