#include <SoftwareSerial.h>

/* PACKET DOCUMENTATION

C2S packets:

    SendInstructions: 01 AA AB BB CC CD DD
        AA A: Motor 1 angle in degrees, 12 bit uint
        B BB: Motor 2 angle in degrees, 12 bit uint
        CC C: Motor 3 angle in degrees, 12 bit uint
        D DD: Motor 4 angle in degrees, 12 bit uint

*/

enum C2S {
    SendInstructions = 1
};

int targetAngles[] = { 0, 0, 0, 0 };

// the tooth is blue
#define rxPin 0
#define txPin 1
SoftwareSerial BlueTooth (rxPin, txPin);

// put your setup code here, to run once:
void setup() {
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    BlueTooth.begin(9600);

    //pinMode(LED_BUILTIN, OUTPUT);
}

void ReceiveInstructions() {
    char buffer[6];
    for (int i = 0; i < 6; i++) {
        buffer[i] = BlueTooth.read();
    }
}

// put your main code here, to run repeatedly:
void loop() {
    if (BlueTooth.available() == 0) return;
    switch (BlueTooth.read()) {
        case C2S.SendInstructions:
            ReceiveInstructions();
            break;
    }

    // for (int i = 0; i < 100; i++) {
    //     digitalWrite(LED_BUILTIN, i & 1 ? LOW : HIGH);
    //     delay(1000 / (i + 1));
    // }
}