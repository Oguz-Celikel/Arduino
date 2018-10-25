#include <SoftwareSerial.h>

SoftwareSerial BlueSelin(10, 11);

const int flexpin1 = A0;
const int flexpin2 = A1;
int flex[2];
int high = 8; 
int high2 = 9;
int button = 7;
int state;
int distance;

void setup() {
  pinMode(high, OUTPUT);
  digitalWrite(high, HIGH);
  pinMode(high2, OUTPUT);
  digitalWrite(high2, HIGH);
  pinMode(button, INPUT);
  //pinMode(6,HIGH);
  //pinMode(5,LOW);
  Serial.begin(9600);
  BlueSelin.begin(9600);
}

void loop() {
  //Analog reading
  flex[0] = analogRead(flexpin1);
  flex[1] = analogRead(flexpin2);
  state = digitalRead(button);

  //Mapping sensor values in range of 0-255 for PWM
  flex[0] = map(flex[0], 830, 950, 0, 255);
  flex[1] = map(flex[1], 800, 950, 0, 255);

  //Arranging stop position of fingers
  if ( flex[0] < 50 && flex[0] > -50) {
    flex[0] = 0;
  }
  if ( flex[1] < 50 && flex[1] > -50) {
    flex[1] = 0;
  }

  //Serial Printing the sensor values
  Serial.print(flex[0]);
  Serial.print("     ");
  Serial.println(flex[1]);

  //Bluetooth transmitting the sensor values to the car
  BlueSelin.write(flex[0]);
  Serial.print("Tx ");
  Serial.print(flex[0]);
  BlueSelin.write(flex[1]);
  Serial.print("-----");
  Serial.print(flex[1]);
  BlueSelin.write(state);
  Serial.print("-----");
  Serial.println(state);
  delay(20);
  
/*
  //Receving distance value from the car.
  if (BlueSelin.available() > 0) {
    distance = BlueSelin.read();
    Serial.print("Received: ");
    Serial.print(distance);
  }

  //Blinking led according to the distance value
  if (distance < 5) {
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
  else if (distance >= 5 && distance < 10) {
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
  else if (distance >= 10 && distance < 20) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
  else if (distance >= 20) {
    digitalWrite(led, HIGH);
  }
 */
}


