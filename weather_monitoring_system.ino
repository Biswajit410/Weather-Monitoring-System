#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// for the LCD

// declaring the  OUTPUTS
int wLED = 9;  // LED for LDR
int rLED = 6;  // LED for TMP
int bLED = 7;  // LED for TMP
int gLED = 8;  // LED for TM
int pLED = 13; // LED for PRR
int piezo=10;  // piezo for sound/alarm

// declaring the sensor
int LDR = A0;    // for light sensor
int LsensorValue = 0;

int TMP = A1; // for temprature sesnor
int TsensorValue=0;

int GAS = A2; // for gas sensor
int GsensorValue = 0;

int PRS = A3; // for pressure sensor
int PsensorValue = 0;

void setup() 
{
  Serial.begin(9600);
  lcd.begin (16, 2);
  pinMode(wLED, OUTPUT);
  pinMode(rLED, OUTPUT);
  pinMode(bLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(pLED, OUTPUT);
  
}

void loop() 
{
  
  //for printing the Temprature value
  TsensorValue = analogRead(TMP);
  
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = TsensorValue * 5.0;
  voltage /= 1024.0; 
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
  Serial.print("The temperature is=");
  Serial.print(temperatureC); 
  Serial.println(" degrees C");
  lcd.setCursor(0,1);
  lcd.print(temperatureC);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (temperatureC < 2)
  {
    digitalWrite(bLED, HIGH);
    digitalWrite(rLED, LOW);
    lcd.print("Cold temp");
    tone(10, 300);
  } 
  else 
    if (temperatureC >= 2 && temperatureC < 45 )
  {
    digitalWrite(bLED, LOW);
    digitalWrite(rLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Normal temp");
    noTone(10);
  } 
  else 
  {
    digitalWrite(rLED, HIGH);
    digitalWrite(bLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Hot temp");
    tone(10, 300);
  }
 
  // if  convert to Fahrenheit
  //float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  //Serial.print(temperatureF); Serial.println(" degrees F");
 
  //for printing the light value
  LsensorValue = analogRead(LDR);  
  Serial.print("The light value is= ");
  Serial.println(LsensorValue); 
  
   if (LsensorValue < 50)
   {
    digitalWrite(wLED, HIGH);
     lcd.setCursor(0, 1);
     lcd.print("Dark");
  } 
  
    else if(LsensorValue>=50 && LsensorValue<250)
  {
    digitalWrite(wLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("cloudy");
  }
  else  
  {
    digitalWrite(wLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("sunny");
  }
  
  //for printing the gas value
  GsensorValue = analogRead(GAS);
  Serial.print("Gas Sensor Value= ");
  Serial.println(GsensorValue, DEC);
  if (GsensorValue > 100)
  {
     tone(10,700);
    lcd.setCursor(6,1);
     lcd.print("& polluted");
  }
  
  //for printing the pressure value
  PsensorValue = analogRead(PRS);
  Serial.print("pressure Sensor Value= ");
  Serial.println(PsensorValue, DEC);
  if (PsensorValue > 100)
  {
    digitalWrite(pLED, HIGH);
    Serial.println("air pressure is high");  
  }
  else 
  {
    digitalWrite(pLED, LOW);
  }
  
  Serial.println();
  Serial.println();
  Serial.println();
    
  delay (5000);
  
}