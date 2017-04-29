/*
Important Notices:

Before starting this application, the Bluetooth-Modul (HC-05) has to be coupled to the Smartphone.In the special case of the HC-05 the default PinCode for initiating the Coupling-Process is "1234".

Wiring: GND of HC-05 to GND Arduino, VCC of HC-05 to VCC Arduino, TX HC-05 to Arduino Pin 10 (RX) RX HC-05 to Arduino Pin 11 (TX) 

if (currentvalue!= oldvalue)
{
 Serial.print (currentvalue); // send this value
oldvalue=currentvalue; // remember that we have sent this value
}

*/
#include <SoftwareSerial.h>

SoftwareSerial BTserial(13, 12); // RX | TX

#include <DHT.h>
#define DHTPIN 10     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

int Buzzer = 2;
int tones[] = {261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493, 523 , 554};
const int redLED = 6;
const int receiverPin = 7;
const int receiverPin_2 = 8;
const int yellowLED =  5;
const int fiveVolt =  3;
const int greenLED = 4;
const int blueLED = 9;
int receiverState = 0;
int receiverState_2 = 0;
int dhtstate = 0;
int secLaser=0;
int earthLaser=0;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(fiveVolt, OUTPUT);
  pinMode(receiverPin, INPUT);
  pinMode(receiverPin_2, INPUT);
  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("DHT11 test!");

  dht.begin();
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);
  for (int i = 0; i < Buzzer; i++) {}
}
void loop() {
  receiverState = digitalRead(receiverPin);
  receiverState_2 = digitalRead(receiverPin_2);
  BTserial.print(secLaser);
  BTserial.print(",");
  BTserial.print(earthLaser);
  BTserial.print(",");
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    } else {
      BTserial.print(h);
      BTserial.print(",");
      BTserial.print(t);
      BTserial.print(";");
    Serial.print("  Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    if (h < 25) {
      dhtstate = 0;
    } else {}

    if (dhtstate == 0) {
      Serial.println("low humidity");
      digitalWrite(fiveVolt, HIGH);
      Serial.println("Motor Activated!");
    }
    else {}
    if (h < 40 && h > 30) {
      dhtstate = 1;
      digitalWrite(fiveVolt, LOW);
      Serial.println("Motor Deactivated!");
    }
  }
  if (receiverState == HIGH) {
    secLaser=1;
    digitalWrite(greenLED, HIGH);
    Serial.println(receiverState + "    Safe");
  }
  else {
    secLaser=0;
    Serial.println(receiverState + "    Laser Not Recieved!");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(Buzzer, HIGH); // here the Buzzer is set high in order to make a sound.
    tone(Buzzer, tones[13]); //here we set the tone by choosing from number 1 to 14
    delay (100);
    digitalWrite(yellowLED, LOW);
    digitalWrite(Buzzer, LOW); // here we set the buzzer low and next we set noTone for the buzzer to make a break.
    noTone(Buzzer);
    delay (100);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(Buzzer, HIGH);
    tone(Buzzer, tones[12]);
    delay (100);
    digitalWrite(yellowLED, LOW);
    digitalWrite(Buzzer, LOW);
    noTone(Buzzer);
    digitalWrite(Buzzer, HIGH);
  }
  if (receiverState_2 == HIGH) {
    earthLaser=1;
    Serial.println("No Earthquake!");
    digitalWrite(blueLED, LOW);
  } else {
    Serial.println("Earthquake Detected!");
    digitalWrite(blueLED, HIGH);
  }
}

