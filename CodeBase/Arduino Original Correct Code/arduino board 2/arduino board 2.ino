#define irdoorf 3
#define irdoorb 4
#define irwindowf 5 
#define irwindowf2 6 
#define buzzgar 2
void setup() {
  // put your setup code here, to run once:
pinMode(irdoorf,INPUT);
pinMode(irdoorb,INPUT);
pinMode(irwindowf,INPUT);
pinMode(irwindowf2,INPUT);
pinMode(buzzgar,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(50);
if(digitalRead(irwindowf) == HIGH){
  digitalWrite(buzzgar,HIGH);
}
else{
  digitalWrite(buzzgar,LOW);
}
delay(100);
 if(digitalRead(irdoorb) == HIGH){
    digitalWrite(buzzgar,HIGH);
  }
  else{
  digitalWrite(buzzgar,LOW);
}
delay(100);
   if(digitalRead(irdoorf) == HIGH){
    digitalWrite(buzzgar,HIGH);
  }
  else{
  digitalWrite(buzzgar,LOW);
}
delay(100);
   if (digitalRead(irwindowf2) == HIGH){
    digitalWrite(buzzgar,HIGH);
  }
else{
  digitalWrite(buzzgar,LOW);
}
}
