// ESP32 code that sends the message to the arduino uno

#include <HardwareSerial.h>

void setup() {
  Serial.begin(9600, SERIAL_8N1, 16, 17);
  delay(100);
}

void loop()
{
    int mssage = 0;

    Serial.write("U");
    delay(500);
}
