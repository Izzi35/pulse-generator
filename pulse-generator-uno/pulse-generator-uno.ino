int nPulse = 200;
unsigned long Hz = 2;
unsigned long pulseDuration = 1000; // in microseconds
int iPulse = 0;

unsigned long times = 0;
unsigned long timeStart = 0;
unsigned long duration[2] = {pulseDuration, 1000000/Hz-pulseDuration};

int state = 9;
int select = 0;

void setup() {
    Serial.begin(9600);

    // Pin setup
    DDRB = B00111111;
    PORTB &= B11000000;

    Serial.println("=== Pulse Generator for Arduino Uno by Dohoung Kim (Oct, 2016) ===");
    Serial.println("");
    Serial.println("s: start, h: Hz, n: pulse number, p: pulse duration, e: termination");
    Serial.println("e.g. h10 for 10 Hz, n200 for 200 pulse");
    Serial.println("");    
    Serial.print("nPulse = ");
    Serial.print(nPulse);
    Serial.print(", Hz = ");
    Serial.print(Hz);
    Serial.print(", Pulse duration = ");
    Serial.print(pulseDuration);
    Serial.println(" (us)");
}

void loop() {
    if (state==9) {
        if (Serial.available() > 0) {
            select = Serial.read();

            if (select == 's') {
                nPulse = Serial.parseInt();
                if (nPulse <=0) {
                    nPulse = 200;
                }
                Serial.print("nPulse = ");
                Serial.print(nPulse);
                Serial.print(", Hz = ");
                Serial.print(Hz);
                Serial.print(", Pulse duration = ");
                Serial.print(pulseDuration);
                Serial.println(" (us)");
                Serial.println("");
                Serial.println("Start");
                state = 1;
            }

            else if (select == 'h') {
                Hz = Serial.parseFloat();
                if (Hz <= 0) {
                  Hz = 1;
                }
                Serial.print("nPulse = ");
                Serial.print(nPulse);
                Serial.print(", Hz = ");
                Serial.print(Hz);
                Serial.print(", Pulse duration = ");
                Serial.print(pulseDuration);
                Serial.println(" (us)");
            }

            else if (select == 'n') {
                nPulse = Serial.parseInt();
                if (nPulse <=0) {
                    nPulse = 200;
                }
                Serial.print("nPulse = ");
                Serial.print(nPulse);
                Serial.print(", Hz = ");
                Serial.print(Hz);
                Serial.print(", Pulse duration = ");
                Serial.print(pulseDuration);
                Serial.println(" (us)");
            }

            else if (select == 'p') {
                pulseDuration = Serial.parseInt();
                if (pulseDuration <= 0) {
                    pulseDuration = 1000;
                }
                Serial.print("nPulse = ");
                Serial.print(nPulse);
                Serial.print(", Hz = ");
                Serial.print(Hz);
                Serial.print(", Pulse duration = ");
                Serial.print(pulseDuration);
                Serial.println(" (us)");
            }

            else {
                Serial.println("");
                Serial.println("s: start, h: Hz, n: pulse number, p: pulse duration, e: termination");
                Serial.print("nPulse = ");
                Serial.print(nPulse);
                Serial.print(", Hz = ");
                Serial.print(Hz);
                Serial.print(", Pulse duration = ");
                Serial.print(pulseDuration);
                Serial.println(" (us)");
                Serial.println("");
            }
            
        }
    }

    if (state < 9) {
        times = micros();

        if (times >= timeStart+duration[state]) {
            timeStart = times;

            if (state==0) {
                PORTB &= B11000000;
                if (iPulse < nPulse) {
                    state = 1;  
                }                    
                else {
                    state = 9;
                    iPulse = 0;
                    Serial.println("End");
                    Serial.println("");
                    Serial.println("s: start, h: Hz, n: pulse number, p: pulse duration, e: termination");
                    Serial.println("");
                    Serial.print("nPulse = ");
                    Serial.print(nPulse);
                    Serial.print(", Hz = ");
                    Serial.print(Hz);
                    Serial.print(", Pulse duration = ");
                    Serial.print(pulseDuration);
                    Serial.println(" (us)");
                }
            }
            else if (state==1) {
                PORTB |= B00111111;
                ++iPulse;
                state = 0;
                Serial.println(iPulse);
            }
        }
        else if (Serial.available() > 0) {
            select = Serial.read();

            if (select == 'e') {
                state = 9;
                iPulse = 0;
                Serial.println("End");
                Serial.println("");
                Serial.println("s: start, h: Hz, n: pulse number, p: pulse duration, e: termination");
                Serial.println("");
                Serial.print("nPulse = ");
                Serial.print(nPulse);
                Serial.print(", Hz = ");
                Serial.print(Hz);
                Serial.print(", Pulse duration = ");
                Serial.print(pulseDuration);
                Serial.println(" (us)");
            }
        }
    }
}

