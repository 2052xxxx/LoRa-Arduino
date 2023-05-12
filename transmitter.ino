#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"
#define DHTPIN A0    //Define DHT11 pin: A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int hum;
int analog;
int vMoist;
int moist;
float temp; //Stores temperature value
int output_value ;
int relayPin = 5;
 
void setup() {    
  Serial.begin(9600); // Default Baud rate
  dht.begin();
  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { //433MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode (relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}
void loop()
{
  temp = dht.readTemperature(); // đọc input
  hum = dht.readHumidity();
  analog = analogRead(A1); //ADC value, dao dong tu 0 den 1023
  vMoist = map(analog, 0, 1023, 0, 100); /*Giá trị cần chuyển đổi là analog, 0 và 1023 là min, max của thang đo hiện tại (8 bits), 0 và 100 là min max của thang đo cần chuyển tới*/
  moist = 100 - vMoist; // chuyển về đơn vị %
 
  Serial.println("Sending packet: ");
  // send packet
  LoRa.beginPacket();
/*Gọi thao tác gửi của LoRa, gán các giá trị cần gửi (hum, temp, moist)*/
  LoRa.print("Humidity: ");
  LoRa.print(hum);
  LoRa.print("%");
  LoRa.print(" Temperature: ");
  LoRa.print(temp);
  LoRa.print("C");
  LoRa.print(" Soil-Moisture: ~");
  LoRa.print(moist);
  LoRa.print("%");
 
/*Hiện các giá trị được gửi của LoRa lên màn hình để kiểm soát*/
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.print(" Temperature: ");
  Serial.print(temp);
  Serial.print("C");
  Serial.print(" Soil-Moisture: ~");
  Serial.print(moist);
  Serial.println("%");
  Serial.println("");


  LoRa.endPacket();
/*Đặt điều kiện kích hoạt relay để tưới nước*/
  if (moist <= 18){
    digitalWrite (relayPin, HIGH); //output
    //độ ẩm đất dưới hoặc bằng 18% => kích hoạt relay
  }
  else
  {
    digitalWrite (relayPin, LOW);
    //độ ẩm đất trên 18% => relay tắt
  }
  delay(1500);
}
