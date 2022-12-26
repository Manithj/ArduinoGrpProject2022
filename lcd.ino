#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Keypad.h>
#include <LCD_I2C.h>
#define Password_Length 8 

int signalPin = 12;
int red=11;
int green=10;
char Data[Password_Length]; 
char Master[Password_Length] = "123A456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup(){
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
}

void loop(){
  digitalWrite(green,HIGH);
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    digitalWrite(green,HIGH);
    digitalWrite(red,LOW);
    lcd.clear();
    if(!strcmp(Data, Master)){
      lcd.print("Correct");
      lcd.setCursor(0,1);
      lcd.print("welcome");
      delay(9000);
      digitalWrite(signalPin, HIGH);
      digitalWrite(signalPin, LOW);
      
      }
    else{
      lcd.print("Incorrect");
      lcd.setCursor(0,1);
      lcd.print("Try Again");
      delay(9000);
      } 
     
        lcd.clear();
    clearData();
  }
  else{
      digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
     }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
