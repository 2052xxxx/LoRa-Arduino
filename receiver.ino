#include <SPI.h>
#include <LoRa.h>
//#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPLxtEu0oXC"  
#define BLYNK_DEVICE_NAME "Smart Agriculture"
#define BLYNK_AUTH_TOKEN "OzedxYGASq9ZrRO6CyKL8t7nYMhtyTX5"
char auth[] = "OzedxYGASq9ZrRO6CyKL8t7nYMhtyTX5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Giangneeee";
char pass[] = "88888888";
void setup()
{
  Serial.begin(9600);
//Blynk.begin(auth, ssid, pass);
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { //433 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
 
void loop() {
  // try to parse packet
  //Serial.println("test");
 // Blynk.run();


  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // Nhận gói tin
    Serial.println("");
    Serial.println("...................................");
    Serial.println("Received packet: ");
   
    // Đọc gói tin
    while (LoRa.available()) { 
      char incoming = (char)LoRa.read(); //đọc dữ liệu nhận từ Lora gán
      if (incoming == 'c')
      {
        Serial.print("Error");
      }
      else
      {
        Serial.print(incoming); // in ra Serial
      }
    }
  }
}
