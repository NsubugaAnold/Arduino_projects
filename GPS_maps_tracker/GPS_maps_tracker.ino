#include <HardwareSerial.h>
HardwareSerial neogps(1);
HardwareSerial gsm_module(2);
#include <TinyGPS++.h>

TinyGPSPlus gps;
String location = "www.google.com/maps/dir/";
int co_ordinates; 



void setup()

 {
  Serial.begin(115200);
  gsm_module.begin(9600,SERIAL_8N1,16,17);
  neogps.begin(9600,SERIAL_8N1,27,26);
  
  Serial.println("Initializing..."); 
  delay(1000);

}

void loop() 

{ 
  send_sms(); 
  delay(5000);
}


