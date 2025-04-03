#include <avr/io.h>
#include <util/delay.h>


#define NE555_PIN 8 // Utilisation de la broche numérique 8 sur Arduino
#define Blue_buton 10
#define White_buton 9




void enableNE555() {
    digitalWrite(NE555_PIN, HIGH); // NE555 actif
}


void disableNE555() {
    digitalWrite(NE555_PIN, LOW);  // NE555 désactivé
}


void sendBit(uint8_t bit) {
    enableNE555();
    delayMicroseconds(560); // Pulse de 562.5 µs

    disableNE555();
    if (bit) {
        delayMicroseconds(1687); // Bit "1" : 1687.5 µs LOW
    } else {
        delayMicroseconds(562);  // Bit "0" : 562.5 µs LOW
    }
}


void sendNECCommand(uint16_t address, uint8_t command) {
    // Start Pulse
    enableNE555();
    delayMicroseconds(9000); // 9 ms HIGH
    disableNE555();
    delayMicroseconds(4500); // 4.5 ms LOW

    // Envoi de l'adresse (MSB en premier)
    for (int8_t i = 15; i >= 0; i--) {
        sendBit((address >> i) & 1);
    }
    
    // Envoi de la commande (MSB en premier)
    for (int8_t i = 7; i >= 0; i--) {
        sendBit((command >> i) & 1);
    }

    // Pulse de stop
    enableNE555();
    delayMicroseconds(560);
    disableNE555();
}


void setup() {
    pinMode(NE555_PIN, OUTPUT);
    pinMode(Blue_buton,INPUT);
    pinMode(White_buton,INPUT);
}


void loop() {
    if(digitalRead(Blue_buton)==1){
      sendNECCommand(0x0FFFF, 0x0); // Exemple d'adresse et de commande
      delay(100);
    }
    else if(digitalRead(White_buton)==1){
      sendNECCommand(0x00, 0xFF); // Exemple d'adresse et de commande
      delay(100); // Pause entre les commandes
    }
    else{
      sendNECCommand(0x00, 0x0);
      delay(100);
    }
    
    //sendNECCommand(0x01, 0x0);
    //delay(100);
    

}





