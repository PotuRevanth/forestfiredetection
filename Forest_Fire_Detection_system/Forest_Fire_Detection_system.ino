#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


#define voltage_sensor A0

#define MQ A4
#define Fire 2
#define buzzer 7

void beep()
{
  digitalWrite(buzzer, LOW);delay(1500);digitalWrite(buzzer, HIGH);delay(200);
}

float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

int sti = 0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
unsigned char rcv, gchr = 'x', gchr1 = 'x', robos = 's';


void okcheck()
{
  unsigned char rcr;
  do {
    rcr = Serial.read();
  } while (rcr != 'K');
}

int voltage()
{
  value = analogRead(voltage_sensor);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2/(R1+R2));

  lcd.setCursor(0,0);
  lcd.print("Voltage:");
  lcd.setCursor(8,0);
  lcd.print(vin);
  lcd.setCursor(13,0);
  lcd.print("V");
  return vin;
}

void setup()
{
 
  pinMode(MQ, INPUT);
 pinMode(Fire, INPUT);
  pinMode(buzzer, OUTPUT);
  
  
  digitalWrite(buzzer, HIGH);
  
  Serial.begin(115200);
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO THE");
  lcd.setCursor(4, 1);
  lcd.print("PROJECT");
  delay(1500);
  lcd.clear();
 
  lcd.clear();

  lcd.print("Wifi init");

  Serial.write("AT\r\n");         delay(500); okcheck();
  Serial.write("ATE0\r\n");         okcheck();
  Serial.write("AT+CWMODE=3\r\n"); delay(500);
  Serial.write("AT+CIPMUX=1\r\n"); delay(500);         okcheck();
  Serial.write("AT+CIPSERVER=1,23\r\n");      okcheck();


  lcd.clear();
  lcd.print("Waiting For");
  lcd.setCursor(0, 1);
  lcd.print("Connection");
  do {
    rcv = Serial.read();
  } while (rcv != 'C');


  lcd.clear();
  lcd.print("Connected");
  delay(2000);
  lcd.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MQ:"); //5,0
  lcd.setCursor(0, 1);
  lcd.print("F:"); //5,0
  
}

void loop()
{     
  if(digitalRead(MQ) == LOW)
    {
       lcd.setCursor(4,0);lcd.print("ON  ");
       beep();
         
                  Serial.write("AT+CIPSEND=0,41\r\n");delay(2000);
                  Serial.write(" Smoke Detected at @ 17.3911°N,78.3221°E \r\n");delay(3000);
                  

    }  
  if(digitalRead(MQ) == HIGH)
    {
       lcd.setCursor(4,0);lcd.print("OFF ");               
    }    
   
  
  if(digitalRead(Fire) == HIGH)
    {
       lcd.setCursor(2,1);lcd.print("ON  ");
       digitalWrite(buzzer, LOW);
         
                  Serial.write("AT+CIPSEND=0,40\r\n");delay(2000);
                  Serial.write(" Fire Detected at @ 17.3911°N,78.3221°E \r\n");delay(3000);
                  

    }  
  if(digitalRead(Fire) == LOW)
    {
       lcd.setCursor(2,1);lcd.print("OFF");
              digitalWrite(buzzer, HIGH);               
    }     

   
}
