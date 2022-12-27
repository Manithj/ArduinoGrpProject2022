
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <LCD_I2C.h>
#include <EEPROM.h>
#define Password_Length 8 

char Data[Password_Length]; 
char Master[Password_Length] = "123A456"; 
byte data_count = 0, master_count = 0;
int Attempt=1;
bool Pass_is_good;
char customKey;
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int red = 11;
int green = 10;
int blue =12;
int buzz=13;
int i=1;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
 lcd.init();
 lcd.backlight();
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue,OUTPUT);
pinMode(buzz,OUTPUT);
}

void loop(){
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
      digitalWrite(blue,LOW);
      lcd.print("Access Granted");
      lcd.setCursor(0,1);
      lcd.print("Gate Open");
      delay(5000);
      
      }
    else{
      for(i=1;i<4;i++){
      if(!strcmp(Data, Master)){
        digitalWrite(red,LOW);
      digitalWrite(green,HIGH);
      digitalWrite(blue,LOW);
      lcd.print("Access Granted");
      lcd.setCursor(0,1);
      lcd.print("Gate Open");
      }
      else{
      digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      lcd.print("Incorrect");
      lcd.setCursor(0,1);
      lcd.print("Try Again");
      delay(5000);
      }
      }
      }
      if(i>4){
      digitalWrite(buzz,HIGH); 
      }
      else{
        digitalWrite(buzz,LOW);
      }
      Serial.print(i);
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
