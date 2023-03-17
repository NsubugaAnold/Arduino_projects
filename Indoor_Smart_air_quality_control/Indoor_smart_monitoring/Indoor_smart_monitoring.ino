

void setup() {
Serial.begin(115200);
attachInterrupt(0,set_AC,HIGH);
}

void loop() {

}

void set_AC(){
  /* check for t variable in EEPROM: if the variable == 0... define user input 
  if the user presses the reset button: that variable in eeprom will be cleared to zero
  */
  #ifdef user_input 
  while(!Serial.available());
  while(Serial.avaiable()){
    int AC_model = Serial.readInt();
    // save the received variable in EEPROM
// depending on the number.. write the name of the AC
    if (AC_model == 0){   
      Serial.println("Safe evironment is a health priority"); 
    }   
  }
  #endif
}
/*
Write an interrupt session that automatically puts the device in reset mode when 
reset button is pressed
*/