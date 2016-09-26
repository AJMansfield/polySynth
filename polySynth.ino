#include <Arduino.h>
#include <MIDI.h>
#include <avr/interrupt.h> // Use timer interrupt library


#include "error.h"


#include "noteData.cpp"

#define NOTECOUNT 127
unsigned int period[NOTECOUNT];

#define VOICECOUNT 8
struct voice{
  unsigned long time;
  unsigned int period;
  byte note;
  boolean on : 1;
  boolean up : 1;
};

voice voices[VOICECOUNT];




MIDI_CREATE_DEFAULT_INSTANCE();

void setup(){
  
  pinMode(13, OUTPUT); //debug LED

  MIDI.begin();
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  
  /****Set timer1 for 8-bit fast PWM output ****/
  pinMode(9, OUTPUT); // Make timer’s PWM pin an output
  TCCR1B = (1 << CS10); // Set prescaler to full 16MHz
  TCCR1A |= (1 << COM1A1); // Pin low when TCNT1=OCR1A
  TCCR1A |= (1 << WGM10); // Use 8-bit fast PWM mode
  TCCR1B |= (1 << WGM12);
  //write to OCR1AL to adjust voltage
  
  equal_tempered::generate_scale(period, period+NOTECOUNT);
  
}

void loop(){
  unsigned long now = micros();
  
  byte von = 0;
  byte vup = 0;
  
  for(int i = 0; i<VOICECOUNT; i++){
    if(voices[i].on){
      von++;
    } else {
      continue;
    }
    
    if(now > voices[i].time){
      voices[i].time += voices[i].period;
      voices[i].up = !voices[i].up;
    }
    if(voices[i].up){
      vup++;
    }
  }
  
  OCR1AL = 255 / von * vup;
}




void serialEvent(){
  MIDI.read();
}


void HandleNoteOff (byte channel, byte note, byte velocity){
  //flash();
  static byte lastOff = 128;
  
  for(int i = 0; i < VOICECOUNT; i++){
    if(voices[i].note == note){
      /*if(lastOff >= 128){
        lastOff = note;
      } else {
        swap(&period[note], &period[lastOff]);
        lastOff = 128;
      }*/
      voices[i].on = false;
    }
  }
}

void HandleNoteOn (byte channel, byte note, byte velocity){
  //flash();
  if(velocity == 0){
    HandleNoteOff(channel,note,velocity);
    return;
  }
  
  for(int i = 0; i < VOICECOUNT; i++){
    if(voices[i].on == 0){
      voices[i] = {micros(), period[note], note, true, false};
      break;
    }
  }
}
