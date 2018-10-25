#include <SoftwareSerial.h>

SoftwareSerial BlueSelin(10, 11);

int flex[2];
int state;

int trigPin = 3;
int echoPin = 4;
long duration;
long distance;

const int Renable = 5;
const int Lenable = 6;
const int Rbackward = 8;
const int Rforward = 9;
const int Lforward = 12;
const int Lbackward = 13;

// Movement Function
void movement(int speed1, int speed2) {
  analogWrite(Renable, speed1 );
  digitalWrite(Rforward, HIGH);
  digitalWrite(Rbackward, LOW);

  analogWrite(Lenable, speed2 );
  digitalWrite(Lforward, HIGH);
  digitalWrite(Lbackward, LOW);
}

void Rmovement(int speed1, int speed2) {
  analogWrite(Renable, speed1 );
  digitalWrite(Rforward, LOW);
  digitalWrite(Rbackward, HIGH);

  analogWrite(Lenable, speed2 );
  digitalWrite(Lforward, LOW);
  digitalWrite(Lbackward, HIGH);
}

void ultrasonic() {
  digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */
  duration = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  distance = (duration / 2) / 29.1; /* ölçülen sure uzaklığa çevriliyor */
  if (distance > 30) {
    distance = 30;
  }
  Serial.print("Distance ");
  Serial.print(distance);
  Serial.println(" cm");
  //delay(500);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Rforward, OUTPUT);
  pinMode(Rbackward, OUTPUT);
  pinMode(Lforward, OUTPUT);
  pinMode(Lbackward, OUTPUT);
  pinMode(Renable, OUTPUT);
  pinMode(Lenable, OUTPUT);
  Serial.begin(9600);
  BlueSelin.begin(9600);
}

void loop() {
  // Receiving sensor values
  if (BlueSelin.available() > 0) {
    flex[0] = BlueSelin.read();
    Serial.print("Received: ");
    Serial.print(flex[0]);
  }

  if (BlueSelin.available() > 0) {
    flex[1] = BlueSelin.read();
    Serial.print("-----");
    Serial.println(flex[1]);
  }

  if (BlueSelin.available() > 0) {
    state = BlueSelin.read();
    Serial.print("-----");
    Serial.println(state);
  }

  //Apply sensor values to movement function
  if (state) {
    movement(flex[0], flex[1]);
    delay(20);
  }
  else {
    Rmovement(flex[0], flex[1]);
    delay(20);
  }
  /*
    //Calculating ultrasonic by its function defined above
    ultrasonic();

    //Bluetooth transmitting the sensor value to the glove
    BlueSelin.write(distance);
    Serial.print("Transmitted: ");
    Serial.print(distance);
    delay(20);
  */
}


