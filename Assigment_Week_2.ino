#include "Display.h";
const int BUZZER = 3;
const int LDR = A2;
const int LEDYW = 7;
const int LEDRD = 4;
const int LEDGR = 5;
const int LEDBL = 6;
double TEMP = A1;
int brightness = analogRead(LDR);
int btnbrightness = 8;
int btntemperature = 9;
const int DARK_THRESHOLD = 400;
const int LIGHT_THRESHOLD = 800;
int track = 0;
const int NTC_R25 = 10000; 
const int NTC_MATERIAL_CONSTANT = 3950;
const int PIN_NTC = 15;
const int lowtemp = 26.00;
const int hightemp = 29.00;
bool toggle = false;
int lastButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
pinMode(LDR, INPUT);
pinMode(LEDYW, OUTPUT);
pinMode(LEDRD, OUTPUT);
pinMode(LEDBL, OUTPUT);
pinMode(LEDGR, OUTPUT);
pinMode(BUZZER, OUTPUT);
pinMode(TEMP, INPUT);
pinMode(btnbrightness, INPUT_PULLUP);
pinMode(btntemperature, INPUT_PULLUP);
Serial.begin(9600);
}

void bright() 
 {
  digitalWrite(LEDBL, LOW);
int val = analogRead(LDR);
Serial.print("brightness value: " );
Serial.println(val);
Display.show(val);
delay(1000);
if (val < DARK_THRESHOLD)
    {
      digitalWrite(LEDRD, HIGH);
      delay(20);
          digitalWrite(LEDRD, LOW);
          delay(20);
      tone(BUZZER, 200, 600);
      delay(20);
      tone(BUZZER, 200, 600);
      delay(70);
      digitalWrite(LEDGR, LOW);
      digitalWrite(LEDYW, HIGH);
      
    }
      if (val > LIGHT_THRESHOLD)
        {
          digitalWrite(LEDRD, HIGH);
          delay(20);
          digitalWrite(LEDRD, LOW);
          delay(20);
          tone(BUZZER, 200, 600);
      delay(20);
      tone(BUZZER, 200, 600);
      delay(70);
      digitalWrite(LEDGR, LOW);
      digitalWrite(LEDYW, HIGH);
        }
        else 
          if (val >= DARK_THRESHOLD && val <= LIGHT_THRESHOLD)
          {
            digitalWrite(LEDRD, LOW);
            digitalWrite(LEDYW, HIGH);
            digitalWrite(LEDGR, HIGH);
            }
}


void temp()
{
    digitalWrite(LEDYW, LOW);
    float celcius;
    celcius = get_temperature();
    Serial.print("temp value: ");
    Serial.println(celcius);
    delay(1000);
    Display.show(celcius);
      if(celcius < lowtemp) 
      {
        digitalWrite(LEDRD, HIGH);
      delay(20);
          digitalWrite(LEDRD, LOW);
          delay(20);
      tone(BUZZER, 200, 600);
      delay(20);
      tone(BUZZER, 200, 600);
      delay(70);
      digitalWrite(LEDGR, LOW);
      digitalWrite(LEDBL, HIGH);
        }
        if (celcius > hightemp) 
        {
        digitalWrite(LEDRD, HIGH);
      delay(20);
          digitalWrite(LEDRD, LOW);
          delay(20);
      tone(BUZZER, 200, 600);
      delay(20);
      tone(BUZZER, 200, 600);
      delay(70);
      digitalWrite(LEDGR, LOW);
      digitalWrite(LEDBL, HIGH);
      }
      else if (celcius > lowtemp && celcius < hightemp)
      {
            digitalWrite(LEDRD, LOW);
            digitalWrite(LEDBL, HIGH);
            digitalWrite(LEDGR, HIGH);
            }
      
    }

void unstarted()
{
  digitalWrite(LEDGR, HIGH);
  Display.show("----");
  digitalWrite(LEDYW, LOW);
  digitalWrite(LEDBL, LOW);
  }    
    
float get_temperature()
{
    float temperature,resistance;
    int value;
    value = analogRead(PIN_NTC);
    resistance   = (float)value * NTC_R25/(1024 - value); // Calculate resistance
    /* Calculate the temperature according to the following formula. */
    temperature  = 1/(log(resistance/NTC_R25)/NTC_MATERIAL_CONSTANT+1/298.15)-273.15;
    return temperature;
}

void loop() {
  // put your main code here, to run repeatedly:
int btnbright = digitalRead(btnbrightness);
int btntemp = digitalRead(btntemperature);

if (btnbright == LOW) 
{
  delay (50);
  btnbright = digitalRead(btnbrightness);
  
if (btnbright == LOW)
  if (track == 0) 
  {
    unstarted();
    track = 1;
  } else {
    bright();
    track = 0;
    } 
  }
  delay(200);
if (track == 1) {bright();}
if (track == 0) {unstarted();}
///////////////////////////////////
if (btntemp == LOW) 
  {
    delay(50);
    btntemp = digitalRead(btntemperature);
if (btntemp == LOW)
  if(track == 0)
    {
      unstarted();
      track = 2;
      }
      else
      if (track == 1)
      {
        bright();
        track = 2;
        }
        if(track == 2)
          {
            temp();
            track = 0;
            }
  }
  delay(200);
  if (track == 2) {temp();}
if (track == 0) {unstarted();}
    }
