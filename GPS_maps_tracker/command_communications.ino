
void updateSerial()

{
  delay(500);
  while (Serial.available()) 
  {
    gsm_module.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gsm_module.available()) 
  {
    Serial.write(gsm_module.read());//Forward what Software Serial received to Serial Port
  }
}