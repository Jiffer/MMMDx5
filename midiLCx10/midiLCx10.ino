/* / **************************************
pulse 

Teensy LC with MMMMDx5: https://oshpark.com/shared_projects/uq5EsZsM
uses Teensyduino: https://www.pjrc.com/teensy/teensyduino.html

variable lowNote - determines the starting MIDI note motor channel 
variable onTime - length time motor is pulsed on (in ms) 
MIDI velocity is mapped to PWM rate to control motor power

Jiffer Harriman - modular-muse.com
************************************** */


// use PWM pins 3, 4, 6, 9, 10
int pins[] = {3, 4, 6, 9, 10, 23, 22, 20, 17, 16};   
#define numNotes 10

int lowNote = 60; // MIDI note 16 (E-2)
unsigned int onTime = 20;

void OnNoteOn(byte channel, byte note, byte velocity);
void OnNoteOff(byte channel, byte note, byte velocity);
unsigned long lastHit[numNotes];
bool noteHigh[numNotes];

void setup() {
  for (int i = 0; i < numNotes; i++) {
    pinMode(pins[i], OUTPUT);
  }
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

  // no notes are on to start
  for (int i = 0; i < numNotes; i++) {
    noteHigh[i] = false;
    lastHit[i] = 0;
  }

}


void loop() {
  // flush the MIDI read buffer
  while (usbMIDI.read()) {
  }
  // check if its time to turn a note off
  for (int i = 0; i < numNotes; i++) {
    if (noteHigh[i] && (millis() - lastHit[i] > onTime)) {
      // check if on time has passed and turn off
      noteHigh[i] = false;
      analogWrite(pins[i], 0);
    }
  }
}

void OnNoteOn(byte channel, byte note, byte velocity) {

  if (note >= lowNote && note < lowNote + numNotes 
  ) {
    // adjust fir note # offset
    note = note - lowNote;
    // bit shift 7 bits to 12 
    analogWrite(pins[note], velocity << 5);

    noteHigh[note] = true;
    lastHit[note] = millis();
  }

}

void OnNoteOff(byte channel, byte note, byte velocity) {

}
