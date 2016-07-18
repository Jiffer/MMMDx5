/* / **************************************
sustain 

Variable lowNote - determines motor channel
MIDI velocity is mapped to PWM rate to control motor power

Jiffer Harriman - modular-muse.com
************************************** */

// use PWM pins 3, 4, 6, 9, 10
int pins[] = {3, 4, 6, 9, 10};
#define numNotes 5

int lowNote = 60; // MIDI note 16 (E-2) // change to use different note triggers

void OnNoteOn(byte channel, byte note, byte velocity);
void OnNoteOff(byte channel, byte note, byte velocity);


void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
}


void loop() {
  while (usbMIDI.read()) {
  }

}

void OnNoteOn(byte channel, byte note, byte velocity) {
  if (note >= lowNote && note < lowNote + 5) {

    note = note - lowNote;
    // linear map from MIDI's 7 bits of resolution to Teensy's 12
    analogWrite(pins[note], velocity << 5 ); 
  }

}

void OnNoteOff(byte channel, byte note, byte velocity) {
  if (note >= lowNote && note < lowNote + 5) {
    note = note - lowNote; // offset
    analogWrite(pins[note], 0);
  }

}





