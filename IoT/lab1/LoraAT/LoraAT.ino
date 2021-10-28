void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
    Serial.println("Test!");

    Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

    Serial.println("Enter:");
    while (!Serial.available());
    Serial1.println(Serial.read());

    delay(1000);
    
    reply_length =Serial1.available();
  
    while (reply_length--) {
      reply = Serial1.read();
      Serial.print(reply);
    }
}
