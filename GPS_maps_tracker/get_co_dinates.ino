void send_sms()

{  
    double latitude; 
    double longitude; 
    const size_t BUFSIZE = 300; 
    char f_buffer[BUFSIZE];
    float *f_buf = (float*)f_buffer; 
    String SMS_target = "+256770777605"; 
    
    boolean newdata = false;
    for(unsigned long start = millis(); millis()-start<1000;)
        while(neogps.available())
          if(gps.encode(neogps.read()))
            newdata = true; 

    if(newdata = true)
    {
      newdata = false;
      Serial.println(gps.satellites.value());
    }

    else 
    {
      Serial.println("No data from gps"); 
    }

    if(gps.location.lat() == 0 || gps.location.lng()==0)
    {
      Serial.println("Zero readngs recorded"); 
      return; 
    }

    co_ordinates++; 
  Serial.print("latitude(deg): ");
  f_buf[co_ordinates] = gps.location.lat(); 
  Serial.println( f_buf[co_ordinates]);
  f_buf[co_ordinates + 1] = gps.location.lng();
  Serial.println(f_buf[co_ordinates + 1]);
  Serial.println(co_ordinates);
  Serial.println();
  location += String(gps.location.lat(),6);
  location += ",";
  location += String(gps.location.lng(),6);
  location +="/"; 
  Serial.println(location);
    if(co_ordinates == 40)
    {
            co_ordinates =0; 
            Serial.println(location); 
            Serial.println("sending sms");
            send_co_ordinates(location);
            send_co_ordinates("sending a bigger sms");
            location = "www.google.com/maps/dir/";
    }


delay(3000); 
}