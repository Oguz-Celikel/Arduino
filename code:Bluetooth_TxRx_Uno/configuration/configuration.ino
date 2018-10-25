/*
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
 
void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT); 
  digitalWrite(9,HIGH);
  Serial.println("Enter AT commands:");
  mySerial.begin(38400);
}
 
void loop()
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
String isim = "Glove";
int sifre = 4321;
String uart = "9600,0,0";
int role = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("HC-05 Modul Ayarlaniyor...");
  Serial.println("Lutfen 5 sn icinde HC-05 modulun uzerindeki butona basili tutarak baglanti yapiniz.");
  mySerial.begin(38400);
  delay(5000);
  mySerial.print("AT+NAME=");
  mySerial.println(isim);
  Serial.print("Isim ayarlandi: ");
  Serial.println(isim);
  delay(1000);
  mySerial.print("AT+PSWD=");
  mySerial.println(sifre);
  Serial.print("Sifre ayarlandi: ");
  Serial.println(sifre);
  delay(1000);
   mySerial.print("AT+ROLE=");
  mySerial.println(role);
  Serial.print("Master ayarlandi: ");
  Serial.println(role);
  delay(1000);
  mySerial.print("AT+UART=");
  mySerial.println(uart);
  Serial.print("Baud rate ayarlandi: ");
  Serial.println(uart);
  delay(2000);
  Serial.println("Islem tamamlandi.");
}

void loop()

{

}

