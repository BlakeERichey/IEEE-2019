void setup(){
  Serial.begin(9600);
}

void loop(){
  sendId(1);
  res = receiveData();
  Serial.println(res);
}

String receiveData(){
  String msg = "";
  if (Serial.available() > 0) {    // is a character available?
    char rx_byte = Serial.read();       // get the character
    
    // check if a number was received
    if ((rx_byte >= 'A') /*&& (rx_byte <= '9')*/) {
      Serial.print("Msg received: ");
      Serial.println(rx_byte);
      //do something with data
      msg = String(rx_byte);
    }
  } // end: if (Serial.available() > 0)
  return msg;
}

void sendData(int val){
  Serial.print("Sending msg: ");
  Serial.println(val);
}

void sendId(int id){
  sendData(id);
}
