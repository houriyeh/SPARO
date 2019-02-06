#include <Wire.h>
#include <SparkFun_MMA8452Q.h>

MMA8452Q accel;

const int trigPin = 13;
const int echoPin = 12;
double duration = 0;
double distance = 0;

int flexPin = A1;
int flex = 0;

int potPin = A0;
int state = 0;



void setup() {
  accel.init();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  checkState();
  switch(state) {
    case 0:
      accel.read();
      printAccel();
      break;
    case 1:
      findRange(); 
      printRange();
      break;
    case 2:
      flex = analogRead(flexPin);
      printFlex();
      break;
  }
}

void findRange() {
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}

void checkState() {
  int pot = analogRead(potPin);
  if (pot < 342) { state = 0; }
  else if (pot >= 342 && pot < 684 ) { state = 1; }
  else { state = 2; }
}

void printAccel() {
  Serial.print("X:");
  Serial.print(accel.cx);
  Serial.print(", Y: ");
  Serial.print(accel.cy);
  Serial.print(", Z: ");
  Serial.println(accel.cz);
}

void printRange(){
  if (distance < 2.5) {  
    Serial.println("Too Close");
  }
  
  if (distance >= 300){
    Serial.println("Too Far");
  }
  else {
    Serial.print(distance);
    Serial.println("cm");
  }
}

void printFlex() {
  if(flex < 600) { Serial.println("UP"); }
  else if (flex >= 600 && flex < 700) { Serial.println("NEUTRAL"); }
  else { Serial.println("DOWN"); }
}
