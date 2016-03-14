const int nTrial = 300;
const int nPulse = 20;
const unsigned long pulseDuration = 1000;
int iTrial = 0;
int iPulse = 0;

unsigned long times = 0;
unsigned long timeStart = 0;
unsigned long duration[4] = {pulseDuration, 1000000/nPulse-pulseDuration, 1000000};

int state = 9;
int select = 0;

void setup() {
    Serial.begin(9600);

    // Pin setup
    DDRC = B11000000;
    PORTC &= B00111111;
}

void loop() {
    if (state==9) {
        if (Serial.available() > 0) {
            select = Serial.read();

            if (select == 's') {
                state = 2;
                Serial.println("Start");
            }
        }
    }

    if (state < 9) {
        times = micros();

        if (times >= timeStart+duration[state]) {
            timeStart = times;

            if (state==0) {
                PORTC &= B00111111;
                if (iPulse >= nPulse) {
                    state = 2;
                    iPulse = 0;
                }                    
                else {
                    state = 1;  
                }
                
            }
            else if (state==1) {
                PORTC |= B11000000;
                ++iPulse;
                state = 0;
            }
            else if (state==2) {
                ++iTrial;
                if (iTrial > nTrial) {
                    state = 9;
                    iTrial = 0;
                    iPulse = 0;
                    Serial.println("End");
                }
                else {
                    state = 1;
                    Serial.println(iTrial);
                }
            }
        }
        else if (Serial.available() > 0) {
            select = Serial.read();

            if (select == 'e') {
                state = 9;
                iTrial = 0;
                iPulse = 0;
                Serial.println("End");
            }
        }
    }
}

