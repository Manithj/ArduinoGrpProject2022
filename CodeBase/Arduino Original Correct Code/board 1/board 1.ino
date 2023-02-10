#include <SoftwareSerial.h>
SoftwareSerial mySerial(22,23); 
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <LCD_I2C.h>
#include <EEPROM.h>
#define Password_Length 8 
#define mdriver1 34
#define mdriver2 35 
#define relay 33
#define trigrb 4
#define echorb 5
#define triglb 2
#define echolb 3
#define triglf 12
#define echolf 13
#define trigrf 8
#define echorf 9
#define buzz1 7
char val;
int time;
int distance;
const int ldrPin = A0;
const int led = 22;
char Data[Password_Length]; 
char Master[Password_Length] = "123A456"; 
byte data_count = 0, master_count = 0;
int Attempt = 1;
bool Pass_is_good;
char customKey;
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'D','#','0','*'},
{'C','9','8','7'},
{'B','6','5','4'},
{'A','3','2','1'}
};

byte rowPins[ROWS] = {46, 47, 48, 49};
byte colPins[COLS] = {50, 51, 52, 53};
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int red = 11;
int green = 10;
int blue = 6;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
 lcd.init();
 lcd.backlight();
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(mdriver1, OUTPUT);
pinMode(mdriver2, OUTPUT);
pinMode(relay, OUTPUT);
pinMode(trigrb, OUTPUT);
pinMode(echorb,INPUT);
pinMode(triglb,OUTPUT);
pinMode(echolb,INPUT);
pinMode(triglf,OUTPUT);
pinMode(echolf,INPUT);
pinMode(trigrf,OUTPUT);
pinMode(echorf,INPUT);
pinMode(buzz1,OUTPUT);
mySerial.begin(9600);
Serial.begin(9600);
}

void loop(){

 if (Serial.available()){
     val = Serial.read();
     Serial.println(val);
  }
  if (val == '1'){
    analogWrite(mdriver2,200);
    delay(1500);
    val='0';
  }
  else if(val=='0'){
    digitalWrite(mdriver2,LOW);
  }
  else if (val=='2'){
    analogWrite(mdriver1,200);
    delay(1500);
    val='3';
  }
  else if(val=='3'){
    digitalWrite(mdriver1,LOW);
  }
  digitalWrite(trigrb,HIGH);
    delayMicroseconds (10);
    digitalWrite (trigrb, LOW);
    time = pulseIn (echorb, HIGH);
    distance = (time * 0.034) / 2;
  if (distance > 55) 
  { 
    sendMessage();
  digitalWrite(buzz1,HIGH);
    delay(50);
  }
  else {
    digitalWrite(buzz1,LOW);
    delay(50);
  }
   digitalWrite(triglb,HIGH);
    delayMicroseconds (10);
    digitalWrite (triglb, LOW);
    time = pulseIn (echolb, HIGH);
    distance = time * 0.034 / 2;
  if (distance > 65) 
  { 
    digitalWrite(buzz1,HIGH);
    sendMessage();
    delay(50);
  }
  else {
    digitalWrite(buzz1,LOW);
    delay(50);
  }
   digitalWrite(triglf,HIGH);
    delayMicroseconds (10);
    digitalWrite (triglf, LOW);
    time = pulseIn (echolf, HIGH);
    distance = time * 0.034 / 2;
  if (distance >53) 
  { 
    digitalWrite(buzz1,HIGH);
    sendMessage();
    delay(50);
  }
  else {
    digitalWrite(buzz1,LOW);
    delay(50);
  }
  digitalWrite(trigrf,HIGH);
    delayMicroseconds (10);
    digitalWrite (trigrf, LOW);
    time = pulseIn (echorf, HIGH);
    distance = (time * 0.034) / 2;
  if (distance > 65) 
  { 
    digitalWrite(buzz1,HIGH);
    sendMessage();
    delay(50);
  }
  else {
    digitalWrite(buzz1,LOW);
    delay(50);
  }
  lcd.setCursor(0,0);
  lcd.print("Enter Password:"); 
  customKey = customKeypad.getKey();
  if (customKey){
    digitalWrite(blue,HIGH);
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }
  if(data_count == Password_Length-1){ 
    lcd.clear();
    if(!strcmp(Data, Master)){
      digitalWrite(red,LOW);
      digitalWrite(green,HIGH);
      delay(3000);
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      lcd.print("Access Granted");
      lcd.setCursor(0,1);
      lcd.print("Gate Open");
       digitalWrite(relay,HIGH);
     delay(3000);
     digitalWrite(relay,LOW);  
      analogWrite(mdriver1,255);
      delay(3000);
      digitalWrite(mdriver1,LOW);  
      }
      else{
      digitalWrite(red,HIGH);
      delay(3000);
      digitalWrite(red,LOW);
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      lcd.print("Incorrect");
      lcd.setCursor(0,1);
      lcd.print("Try Again");
      digitalWrite(relay,LOW);
      delay(5000);
      }
        lcd.clear();
    clearData(); 
  }
}
void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
void sendMessage(){
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+94770334480\"\r");
  delay(1000);
  mySerial.println("Please check the Graden");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}

