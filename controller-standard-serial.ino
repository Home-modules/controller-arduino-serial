#define CMD_PIN_MODE 0
#define CMD_DIGITAL_WRITE 1
#define CMD_DIGITAL_READ 2
#define CMD_ANALOG_WRITE 3
#define CMD_ANALOG_READ 4

void setup() {
    Serial.begin(9600);
    Serial.write(0); // Notify the hub that the connection is ready.
}

void loop() {
    if(Serial.available() >= 2) { // The smallest command is 2 bytes
        byte command= Serial.read();
        byte param1= Serial.read(); 

        if(command==CMD_PIN_MODE) { // Init pin
            while(Serial.available() == 0); // Wait for the third command byte
            byte param2= Serial.read();
            pinMode(param1, param2);
            return;
        }

        if(command==CMD_DIGITAL_WRITE) { // Digital write
            while(Serial.available() == 0); // Wait for the third command byte
            byte param2= Serial.read();
            digitalWrite(param1, param2);
            return;
        }

        if(command==CMD_ANALOG_WRITE) { // Analog write
            while(Serial.available() == 0); // Wait for the third command byte
            byte param2= Serial.read();
            analogWrite(param1, param2);
            return;
        }

        if(command==CMD_DIGITAL_READ) { // Digital read
            Serial.write(digitalRead(param1));
            return;
        }

        if(command==CMD_ANALOG_READ) {
            Serial.write(analogRead(param1));
            return;
        }
    }
}
