#include <IRremoteESP8266.h> 
#include <IRac.h> 
#include <IRutils.h> 

/*
Sketch works for the following Air conditioning brands 
1.GREE 2.LG 3.ARGO 4.DAIKIN 5.KELVINATOR 6.JVC 7.MITSUBISHI 8.TROTEC 9.PANASONIC 10.SAMSUNG


*/
#define serial_prints

const uint16_t Ir_send_pin = 4; 
IRac air_conditioner(Ir_send_pin);

void setup() {
  Serial.begin(115200);
  delay(200);
  
  air_conditioner.next.protocol = decode_type_t ::SAMSUNG; // specify the AC brand you are working with here 
}

void loop() {
  for (int i = 1; i < kLastDecodeType; i++) {
    decode_type_t protocol = (decode_type_t)i;
    if(air_conditioner.isProtocolSupported(protocol)){
      #ifdef serial_prints
           Serial.println("This protocal is supported");
           delay(2000);
      #endif  
      air_conditioner.next.protocol = protocol;     
    }
  }  
}

void on_ac(){
      air_conditioner.next.power = true;
      air_conditioner.sendAc();
      #ifdef serial_prints
           Serial.println("AC on");
      #endif
       delay(2000);  
}

void off_ac(){
      air_conditioner.next.power = false; 
      air_conditioner.sendAc();
      #ifdef serial_prints
           Serial.println("AC off");
      #endif 
     delay(2000); 
}

void swing_off(){
  air_conditioner.next.swingv = stdAc::swingv_t::kOff;  // Don't swing the fan up or down.
  air_conditioner.next.swingh = stdAc::swingh_t::kOff;  // Don't swing the fan left or right.
  air_conditioner.sendAc();
      #ifdef serial_prints
           Serial.println("swing off");
      #endif 
  delay(2000);
}

