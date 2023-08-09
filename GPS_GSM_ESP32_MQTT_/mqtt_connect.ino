   void mqttConnect() {
      while ( !mqtt.connected() ){
        Serial.println("Attempting mqtt connection"); 
        if ( mqtt.connect(clientID,mqttUserName,mqttpassword) ) {
          Serial.print( "MQTT connection successful " );
         // mqttPublish(1651527,(String("&field1=")+String(30))); 

        } 
        else {
          Serial.println( "mqtt connection failure" );
          Serial.println( mqtt.state() );
          delay(1000 );
        }
      }
          Serial.println( "MQTT connection successful");    
           mqttPublish(XXXXX,(String("&field1=")+String(gps.location.lat())+String("&field2=")+String(gps.location.lng())));
   }