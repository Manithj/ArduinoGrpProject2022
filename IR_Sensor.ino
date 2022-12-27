#include <SimpleTimer.h>
const int ledPin = 12;
const int ldrPin = A2;
int irdoor=2;
int irwindow=4;
int buzz=3;
SimpleTimer timer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(irdoor,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(irwindow,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrStatus = analogRead(ldrPin);
 if (ldrStatus >450  || (digitalRead(irdoor)==1 && digitalRead(irwindow)==1 )) {
  digitalWrite(buzz,HIGH);
  Serial.println(ldrStatus);
}
 else if(ldrStatus <400 ||(digitalRead(irdoor)==1 && digitalRead(irwindow)==1 )){
     digitalWrite(buzz,LOW);
     Serial.println(ldrStatus);
} 
 
}
