#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
int red_light_pin= A2;
int green_light_pin = A3;
int blue_light_pin = A4;
const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  
  Serial.begin(9600); 
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  lcd.begin(16, 2);
}
void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "9A 9A 77 15") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    RGB_color(0, 0, 255); // Red
  delay(1000);
    lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Hi Kantharuban !!");
  lcd.setCursor(0,1);
   lcd.print("entry permitted!");
    delay(1000);
  }
 
 else   {
    Serial.println(" Access denied");
    RGB_color(255, 0, 0); // Red
  delay(1000);
    lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("person unknown!");
  lcd.setCursor(0,1);
   lcd.print("Entry denied");
    delay(1000);
  }
  
}
  void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
