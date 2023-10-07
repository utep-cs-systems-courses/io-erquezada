#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

void melody(int counter) {
  // Specific pitch numbers
  int notes[] = {880, 784, 1047, 1175, 880, 659, 659, 1175};
  int numNotes = sizeof(notes) / sizeof(notes[0]); // Array size
  
  // Play each note twice simultaneously
  for (int i = 0; i < numNotes; i++) {
    // Turn on green LED and turn off red LED
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    buzzer_set_period(notes[i]);
    __delay_cycles(1000000); // Delay between notes
    
    // Turn on red LED and turn off green LED
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    buzzer_set_period(notes[i]);
    __delay_cycles(1000000); // Delay between notes
  }
  
  // Turn off both LEDs after playing the melody
  P1OUT &= ~LED_RED;
  P1OUT &= ~LED_GREEN;
  
  // If counter is less than 3, repeat the melody (recursive call)
  if (counter < 3) {
    melody(counter + 1); // Increment the counter for recursion
  }
}

int main() {
  configureClocks(); // Configure clocks
  buzzer_init();     // Initialize the buzzer
  P1DIR |= LEDS;     // Set LEDs as output
  melody(0);         // Start playing the melody
  or_sr(0x18);       // CPU off, GIE on
}
