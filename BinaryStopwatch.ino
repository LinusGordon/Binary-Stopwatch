/* 
 *  Binary Stopwatch w/ Jeopardy Theme 
 *  
 */

#include <PinChangeInt.h>

// Arduino Pins for Shift Register inputs, a button,
// and a piezzo speaker
#define SER 1
#define RCLK 2
#define SRCLK 3
#define BUTTON 4
#define BUZZER 5

// Octave 1
#define B1 61.74

// Octave 2
#define C2 65.41
#define Cs2 69.30
#define Db2 69.30
#define D2 73.42
#define Ds2 77.78
#define Eb2 77.78
#define E2 82.41
#define F2 87.31
#define Fs2 92.50
#define Gb2 92.50
#define G2 98.00
#define Gs2 103.8
#define Ab2 103.8
#define A2 110.0
#define As2 116.5
#define Bb2 116.5
#define B2 123.5

// Octave 3
#define C3 130.8
#define Cs3 138.6
#define Db3 138.6
#define D3 146.8
#define Ds3 155.6
#define Eb3 155.6
#define E3 164.8
#define F3 174.6
#define Fs3 185.0
#define Gb3 185.0
#define G3 196.0
#define Gs3 207.7
#define Ab3 207.7
#define A3 220.0
#define As3 233.1
#define Bb3 233.1
#define B3 246.9

// Octave 4
#define C4 261.6
#define Cs4 277.2
#define Db4 277.2
#define D4 293.7
#define Ds4 311.1
#define Eb4 311.1
#define E4 329.6
#define F4 349.2
#define Fs4 370.0
#define Gb4 370.0
#define G4 392.0
#define Gs4 415.3
#define Ab4 415.3
#define A4 440.0
#define As4 466.2
#define Bb4 466.2
#define B4 493.9

// Octave 5
#define C5 523.3
#define Cs5 554.4
#define Db5 554.4
#define D5 587.3
#define Ds5 622.3
#define Eb5 622.3
#define E5 659.3
#define F5 698.5
#define Fs5 740.0
#define Gb5 740.0
#define G5 784.0
#define Gs5 830.6
#define Ab5 830.6
#define A5 880.0
#define As5 932.3
#define Bb5 932.3
#define B5 987.8

// Octave 6
#define C6 1047
#define Cs6 1109
#define Db6 1109
#define D6 1175
#define Ds6 1245
#define Eb6 1245
#define E6 1319
#define F6 1397
#define Fs6 1480
#define Gb6 1480
#define G6 1568
#define Gs6 1661
#define Ab6 1661
#define A6 1760
#define As6 1865
#define Bb6 1865
#define B6 1976

// Octave 7
#define C7 2093

bool button_pushed = false;

void setup() {
 
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachPinChangeInterrupt(BUTTON, button, FALLING);
}

void loop() {

  // Plays the Jeopardy theme song on the piezzo speaker
  playJeopardy();
  
  if (button_pushed) {
      button_pushed = false;
      for (int num = 0; num < 256; num++) {
         digitalWrite(RCLK, LOW);
         shiftOut(SER, SRCLK, MSBFIRST, num);  
         digitalWrite(RCLK, HIGH);
         delay(1000); // 1000 milliseconds in a second

          // stop timer when pushed again
          if(button_pushed) {
               button_pushed = false;
               break;
          }
      }
  }
}

void button() { // will be called via interrupt when button is pressed
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        // If interrupts come faster than 200ms, assume it's a bounce and ignore
        if ((interrupt_time - last_interrupt_time > 200) and !button_pushed) {
                // button pressed
                if (!button_pushed)
                        button_pushed = true;
        }
        last_interrupt_time = interrupt_time;
}

/*
 *  Plays the Jeopardy theme song on a piezzo speaker
 */
void playJeopardy() {
  
  tone(BUZZER, C2, 500);
  delay(1.3 * 500);
  tone(BUZZER, F3, 500);
  delay(1.3 * 500);
  tone(BUZZER, C3, 500);
  delay(1.3 * 500);
  tone(BUZZER, A2, 500);
  delay(1.3 * 500);

  tone(BUZZER, C3, 500);
  delay(1.3 * 500);
  tone(BUZZER, F3, 500);
  delay(1.3 * 500);
  tone(BUZZER, C3, 1000);
  delay(1.3 * 1000);

  tone(BUZZER, C3, 500);
  delay(1.3 * 500);
  tone(BUZZER, F3, 500);
  delay(1.3 * 500);
  tone(BUZZER, C3, 500);
  delay(1.3 * 500);
  tone(BUZZER, F3, 500);
  delay(1.3 * 500);

  tone(BUZZER, As3, 750);
  delay(1.3 * 750);
  tone(BUZZER, G3, 250);
  delay(1.3 * 250);
  tone(BUZZER, F3, 250);
  delay(1.3 * 250);
  tone(BUZZER, E3, 250);
  delay(1.3 * 250);
  tone(BUZZER, D3, 250);
  delay(1.3 * 250);
  tone(BUZZER, Cs3, 250);
  delay(1.3 * 250);

}

