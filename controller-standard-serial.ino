#define CMD_PIN_MODE 0
#define CMD_DIGITAL_WRITE 1
#define CMD_DIGITAL_READ 2
#define CMD_ANALOG_WRITE 3
#define CMD_ANALOG_READ 4
#define CMD_DHT11 50
#define CMD_DHT21 51
#define CMD_DHT22 52

#include <dht.h>
dht DHT;

void setup() {
    Serial.begin(9600);
    Serial.write(0); // Notify the hub that the connection is ready.
}

void loop() {
    if(Serial.available() >= 3) { // All commands are three bytes
        byte command= Serial.read();
        byte pin= Serial.read(); 

        if(command==CMD_PIN_MODE) {
            byte mode= Serial.read();
            pinMode(pin, mode);
            return;
        }

        if(command==CMD_DIGITAL_WRITE) {
            byte state= Serial.read();
            digitalWrite(pin, state);
            return;
        }

        if(command==CMD_ANALOG_WRITE) {
            byte value= Serial.read();
            analogWrite(pin, value);
            return;
        }

        if(command==CMD_DIGITAL_READ) {
            byte id= Serial.read(); // ID helps the hub match the command and its response.
            Serial.write(id);
            Serial.write(digitalRead(pin));
            Serial.println();
            return;
        }

        if(command==CMD_ANALOG_READ) {
            byte id= Serial.read();
            Serial.write(id);
            Serial.write(analogRead(pin));
            Serial.println();
            return;
        }

        if(command==CMD_DHT11) {
            byte id= Serial.read();
            Serial.write(id);
            DHT.read11(pin);
            float temp = DHT.temperature; // Convert to float (32-bit), because on Arduino Due a double is 64-bit.
            float humi = DHT.humidity;
            Serial.write((byte *) &temp, 4);
            Serial.write((byte *) &humi, 4);
            Serial.println();
        }
        if(command==CMD_DHT21) {
            byte id= Serial.read();
            Serial.write(id);
            DHT.read21(pin);
            float temp = DHT.temperature; // Convert to float (32-bit), because on Arduino Due a double is 64-bit.
            float humi = DHT.humidity;
            Serial.write((byte *) &temp, 4);
            Serial.write((byte *) &humi, 4);
            Serial.println();
        }
        if(command==CMD_DHT22) {
            byte id= Serial.read();
            Serial.write(id);
            DHT.read22(pin);
            float temp = DHT.temperature; // Convert to float (32-bit), because on Arduino Due a double is 64-bit.
            float humi = DHT.humidity;
            Serial.write((byte *) &temp, 4);
            Serial.write((byte *) &humi, 4);
            Serial.println();
        }
    }
}
