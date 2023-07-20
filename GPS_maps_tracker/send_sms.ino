void send_co_ordinates(String message)
{
  gsm_module.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  gsm_module.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 gsm_module.println("AT+CMGS=\"+256770777605\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  gsm_module.print(message); //text content
  updateSerial();
  gsm_module.write(26);
}