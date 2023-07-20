
void receive_sms()
{
  String message; 
  int messageLength; 
  if(gsm_module.available()>0)
    message = gsm_module.readString();
    messageLength = message.length();
  if(messageLength > 0)
    send_sms(); 
}