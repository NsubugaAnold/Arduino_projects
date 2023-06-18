#include <MQUnifiedsensor.h>
#define         Board                   "ESP-32"
#define         Pin                      35  
#define         Type                     "MQ-135" 
#define         Voltage_Resolution       3.3 
#define         ADC_Bit_Resolution       12 
#define         RatioMQ2CleanAir         9.83
#define         RatioMQ135CleanAir       3.6
MQUnifiedsensor MQ135(Board,Voltage_Resolution,ADC_Bit_Resolution,Pin,Type);
// follow link to understand the connection https://www.researchgate.net/publication/340412980_User_Manual 
// operate the sensor in fresh air for some good time before the actual readings for your project 

void setup() {
  Serial.begin(115200);
  MQ135.serialDebug(true);
  MQ135.setRegressionMethod(1);
  MQ135.setA(110.47);
  MQ135.setB(-2.862);
  MQ135.setRL(1);
  MQ135.init();
  MQ_calibration();
}

void loop() {
  MQ135.serialDebug();
  MQ135.update();
  String d = "carbondioxide";
  double CO2 = MQ135.readSensor();
  //double CO2 = _adc;
  delay(2000);
    Serial.println(d+" " +CO2); 
}

// calibration for the carbondioxide sensor 
 void MQ_calibration(){
            Serial.println(F("calibration on -going-wait"));
            float calcR0 = 0;
            for (int i =1;i<=10;i++){
                MQ135.update(); // update data: esp32 will read wth esp32
                calcR0 += MQ135.calibrate(RatioMQ135CleanAir);       
            }
            delay(6000);
            MQ135.setR0(calcR0/10);
              Serial.println("calibration done"); 
            if(isinf(calcR0)){
                    Serial.println(F("R0 is infinite, check wiring"));
                    while(1);}  
            if(calcR0==0){
                    Serial.println(F("R0 is zero, check wiring"));
                    while(1);} 
            MQ135.serialDebug(false);
 }
