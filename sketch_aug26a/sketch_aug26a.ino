#include <SoftwareSerial.h>
const int echoPin =2 ; // Echo Pin of Ultrasonic Sensor
const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin2=9;
const int pingPin2=10;
const int buzz =5;
const int buzz1 =6;
//const int buttonA=7;
//const int buttonB=8;

void setup() {
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT); // initialising pin 3 as output
  pinMode(echoPin, INPUT); // initialising pin 2 as input
  pinMode(buzz,OUTPUT);
  pinMode(pingPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(buzz1,OUTPUT);
  //pinMode(buttonA, INPUT);
  //pinMode(buttonB, INPUT);

}

void loop() {
  long duration,cm;
  long duration2,cm2;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);    //For starting the Ultrasonic sensor 1
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);   // Calculate the duration  pulseIn build in fn
  cm = microsecondsToCentimeters(duration);   

  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin2, HIGH);     //For starting the Ultrasonic sensor 2
  delayMicroseconds(10);
  
  digitalWrite(pingPin2, LOW);
  
  duration2 = pulseIn(echoPin2, HIGH); // using pulsin function to determine total time
  cm2 = microsecondsToCentimeters(duration2);

  ultrasonic(cm);     
  ultrasonic2(cm2);
  //remote();

}


long microsecondsToCentimeters(long microseconds) // method to covert microsec to centimeters
{
   return microseconds *0.034 / 2;
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


void ultrasonic2(long cm2)
{
  long b=cm2;
  Serial.println(b);
  delay(100);
  if(b<=20)
  {
    digitalWrite(buzz1,HIGH);

  }
  else
  {
    digitalWrite(buzz1,LOW);
  }
}



/*void remote()
{
  if(digitalRead(buttonA)== 1){
    //Serial.println("DAJKLJLKDA");
    tone(buzz, 700, 5000);
    delay(500);
  }
  if(digitalRead(buttonB)== 1){
    print_result();
    delay(500);
  }
}*/
