void gsm_setup(){
if(!modem.init()){
        Serial.println("Failed to initialise modem.");
      return; 
      }
    String modem_name = modem.getModemName(); 
    Serial.print("modem_name is: ");
    Serial.println(modem_name);
    String modem_information = modem.getModemInfo(); 
    Serial.print("modem information:  "); 
    Serial.println(modem_information);
    Serial.println("Modem now waiting for network"); 
    if(!modem.waitForNetwork(600000L,true)){delay(6000);return;}
    if(modem.isNetworkConnected()){Serial.println("modem connected to the network");}
    if(!modem.gprsConnect(apn)){
      Serial.println("failed to connect to the apn"); 
      delay(1000); 
      return;
    }
    Serial.println("check point 2");
   if(modem.isGprsConnected()){
      Serial.println("gprs is connected"); 
   } 
    else{Serial.println("No gprs connection");}  
}