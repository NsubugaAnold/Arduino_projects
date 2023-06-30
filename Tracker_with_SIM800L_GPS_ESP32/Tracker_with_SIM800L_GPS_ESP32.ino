String location = "www.google.com/maps/dir/"; 
double latitude,longitude; 
int co_ordinates; 

const size_t BUFSIZE = 300;
char f_buffer[BUFSIZE];
float *f_buf = (float*)f_buffer;
//----------------------------------------------------------
#define SMS_TARGET  "+256763437494"
#define TINY_GSM_MODEM_SIM800      // Modem is SIM800
#define TINY_GSM_RX_BUFFER   1024  // Set RX buffer to 1Kb
#include <TinyGsmClient.h>
#define SerialMon Serial
#define SerialAT  Serial2
//-----------------------------------------------------------------
#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif
//--------------------------------------------------------------
#include <TinyGPS++.h>
HardwareSerial neogps(1); 
TinyGPSPlus gps;
// -------------------------------------------------------------
void send_gps_data();


void setup() {
  SerialMon.begin(115200); 
  SerialAT.begin(115200, SERIAL_8N1,16,17);
  neogps.begin(9600, SERIAL_8N1,25,26);
  delay(3000);
  SerialMon.println("Initializing modem...");
  modem.restart();
}

void loop() {
  // put your main code here, to run repeatedly:
  send_gps_data();
  delay(3000);

}


void send_gps_data(){
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;){
    while (neogps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
      }
    }
  }
  if(newData == true){
    newData = false;
    SerialMon.println(gps.satellites.value());
  }
  else{SerialMon.println("No data from gps");}
  if(gps.location.lat() == 0 || gps.location.lng() == 0){
    SerialMon.println("Zero recorded as readings");
    return;
  }
  co_ordinates++; 
  SerialMon.print("latitude(deg): ");
  f_buf[co_ordinates] = gps.location.lat(); 
  Serial.println( f_buf[co_ordinates]);
  f_buf[co_ordinates + 1] = gps.location.lng();
  SerialMon.println(f_buf[co_ordinates + 1]);
  SerialMon.println(co_ordinates);
  SerialMon.println();
  location += String(gps.location.lat(),6);
  location += ",";
  location += String(gps.location.lng(),6);
  location +="/"; 
  SerialMon.println(location);
  if(co_ordinates >= 3){
    co_ordinates =0;
    if(modem.sendSMS(SMS_TARGET,location)){SerialMon.println(location);}
    else{SerialMon.println("SMS failed to send");}
    location = "www.google.com/maps/dir/";
  }

  delay(3000);
}