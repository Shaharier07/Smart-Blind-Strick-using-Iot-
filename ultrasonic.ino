#include <SoftwareSerial.h>
#include <TinyGPS++.h>

const int echoPin =2 ; // Echo Pin of Ultrasonic Sensor
const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int buzz =5;
const int buzz1 =6;
const int buttonA=7;
const int buttonB=8;
int water = A0;
int RXPin = 12;
int TXPin = 13;

int GPSBaud = 9600;
// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);
SoftwareSerial mySerial(12, 13); //A6 Tx & Rx is connected to Arduino #3 & #2
double lt,ln,g;
String loct;           
void setup() 
{
  Serial.begin(9600); // Starting Serial Communication
  pinMode(pingPin, OUTPUT); // initialising pin 3 as output
  pinMode(echoPin, INPUT); // initialising pin 2 as input
  pinMode(buzz,OUTPUT);
  pinMode(buzz1,OUTPUT);
  pinMode(water, INPUT);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  gpsSerial.begin(GPSBaud);
}
void loop()
{
  long duration,cm;
  int wt;
  
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // using pulsin function to determine total time
  cm = microsecondsToCentimeters(duration);
  wt =  analogRead(water);// calling method
  ultrasonic(cm);
  watersensor(wt);
  gps();
  remote();
  
}

long microsecondsToCentimeters(long microseconds) // method to covert microsec to centimeters
{
   return microseconds *0.034 / 2;
}

void watersensor(int wt)
{
  int b=wt;
  Serial.println(b);
  if(b>=150) {
      tone(buzz1, 3000, 500);
      delay(1000);
   }
   else {
      digitalWrite(buzz1,LOW);
   }
}

void ultrasonic(long cm)
{
  long a=cm;
  Serial.println(a);
  delay(100);

  if(a<=30)
  {
    digitalWrite(buzz,HIGH);
  }
  else
  {
    digitalWrite(buzz,LOW);
  }
}

void remote()
{
  if(digitalRead(buttonA)== 1){
    tone(buzz1, 1000, 5000);
    delay(500);
  }
  if(digitalRead(buttonA)== 3){
    gsm();
    delay(500);
  }
}

void gps()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  

  Serial.println();
  Serial.println();
  delay(1000);
}

void gsm()
{
  //String s="https://www.google.com/maps/@";
  //String lt="23.818366",ln="90.354706";
  //23.818366827285, 90.35470627765231
  //String ss=",";
  //String z="14.00z";
  //String msg=lt+ss+ln;
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+8801854378284\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  //mySerial.print("https://www.google.com/maps/@");
      //mySerial.print(lt, 6);
     // mySerial.print(",");
     // mySerial.print(ln, 6);
     //Serial.println(msg);
  updateSerial();
  mySerial.print(loct); //text content
  updateSerial();
  mySerial.write((char)26);
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
