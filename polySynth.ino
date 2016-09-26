
#include <MIDI.h>

#include <avr/interrupt.h> // Use timer interrupt library


void flash(){
  digitalWrite(13, !digitalRead(13));
  delay(10);
  digitalWrite(13, !digitalRead(13));
}

void error(int i){
  while(true){
    for(int j = 0; j < i; j++){
      flash();
      delay(100);
    }
    delay(400);
  }
}

void swap (unsigned int *a, unsigned int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
/*
void randomize ( unsigned int arr[], int n ){
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = random(i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}
*/

#define NOTECOUNT 127
unsigned int period[NOTECOUNT];


#define REFPD 2273
#define REFIX 57
#define TUNING 1.05946309436

void generate_period(){
  for(int i = 0; i < NOTECOUNT; i++){
    period[i] = REFPD * pow(TUNING, REFIX - i);
  }
  
  //randomize(period + 40, 60);
}


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

//  /******** Set up timer2 to call ISR ********/
//  TCCR2A = 0; // No options in control register A
//  TCCR2B = (1 << CS21); // Set prescaler to divide by 8
//  TIMSK2 = (1 << OCIE2A); // Call ISR when TCNT2 = OCRA2
//  OCR2A = 255; // Set frequency of wave updates
//  //freq = 16MHz / prescaler / OCR2A = 62.5 kHz
  
  generate_period();
  
//  sei(); // Enable interrupts to generate waveform!
  
  
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






//ISR(TIMER0_COMPA_vect){
//  flash();
//  static unsigned long now = micros();
//  
//  for(int i = 0; i < VOICECOUNT; i++){
//    if(voices[i].vel == 0 && voices[i].lastvel == 0)
//      continue;
//    
//    if(now > voices[i].time){
//      voices[i].time = now + period[voices[i].note];
//      if(voices[i].lastvel == 0){
//        OCR1AL += voices[i].vel;
//        voices[i].lastvel = voices[i].vel;
//      } else {
//        OCR1AL -= voices[i].lastvel;
//        voices[i].lastvel == 0;
//      }
//    }
//  }
//  flash();  
//}


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
