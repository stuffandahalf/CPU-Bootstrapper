#define LED_PIN 13

#define PEEK 0
#define POKE 1

void setup() {
    pinMode(LED_PIN, OUTPUT);
    //digitalWrite(LED_PIN, LOW);
    Serial.begin(9600);
}

void loop() {
    byte mode = Serial.read();
    switch {
    case PEEK:
        break;
    case POKE:
        break;
    }
    if (mode != 255) {
        //Serial.println(mode);
        digitalWrite(LED_PIN, mode);
    }
}
