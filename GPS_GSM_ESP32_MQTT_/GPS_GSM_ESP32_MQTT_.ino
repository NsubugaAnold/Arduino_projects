#include <HardwareSerial.h>
#define TINY_GSM_MODEM_SIM800

#include <PubSubClient.h> 
#include <TinyGsmClient.h> 
#include <TinyGPS++.h>

#define Serialgsm Serial1

const char apn[] = "internet"; // apn for uganda 
const char* broker = "mqtt3.thingspeak.com"; 
const char clientID[] = "XXXXXXX"; 
const char mqttUserName[] = "XXXXXXXX"; 
const char mqttpassword[] = "XXXXXXXXXXX"; 
double latitude,longitude; 

uint32_t lastReconnectAttempt = 0; 

TinyGsm modem(Serialgsm); 
TinyGsmClientSecure client(modem); 
PubSubClient mqtt(client);
HardwareSerial neogps(1); 
TinyGPSPlus gps;

void setup(){
    Serial.begin(115200);
    Serialgsm.begin(9600,SERIAL_8N1,16,17);
    gsm_setup(); 
    mqtt.setServer(broker,8883);
    mqtt.setCallback(mymqttcallback); 
    mqtt.setBufferSize(2048);
    delay(2000); 
    neogps.begin(9600, SERIAL_8N1,27,26);
    
}

void loop(){
  // assure internet is still connected 
  boolean newData = false;
    for (unsigned long start = millis(); millis() - start > 1000;){
    while (neogps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
      }
    }
  }
    if(newData == true){
    newData = false;
    Serial.println(gps.satellites.value());
  }
  //-----------------------------------------------------------------
  else{Serial.println("No data from gps");}
    if(gps.location.lat() == 0 || gps.location.lng() == 0){
    Serial.println("Zero recorded as readings");
    return;
  }
  //------------------------------------------------------------------------
    if (!modem.isGprsConnected()) {
      if (!modem.gprsConnect(apn)) {
        Serial.println(" fail");
        delay(10000);
        return;
      }
      if (modem.isGprsConnected()) { Serial.println("GPRS reconnected"); }
    }
    mqttConnect();
      mqtt.loop();
  }


    void mymqttcallback(char* topic, byte* payload, unsigned int length){
      // handle received message
      Serial.print("Message on topic: ");
      Serial.print(topic);
      Serial.println(" received"); 
    }

    void mqttSubscribe(long pubChannelID){
      String topicString =  "channels/"+ String(pubChannelID) + "/subscribe"; 
      mqtt.subscribe(topicString.c_str());
    }

    // publish to a channel 
    void mqttPublish(long pubChannelID, String message){ 
      String topicString = "channels/"+ String(pubChannelID) + "/publish"; 
      mqtt.publish(topicString.c_str(),message.c_str()); 
    }


