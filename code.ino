#include <avr/sleep.h>

void setup() {
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);

  TCCR0A = _BV(COM0A1);                // Clear OC0A on Compare Match, set OCR0A at BOTTOM
  TCCR0A |= _BV(WGM01) | _BV(WGM00);   // Fast PWM
  TCCR0B = _BV(CS01) | _BV(CS00);      // CLKi/o / 64 (From prescaler)
  OCR0A = 255;

  TCCR1A = 0;
  TCCR1B = _BV(CS10);                   // No prescaling
  TIMSK1 |= _BV(TOIE1);                 // Unmask overflow

  ADMUX = _BV(ADLAR);                   // Left-adjust result (8-bit precision)
  ADMUX |= _BV(REFS0);

  ADCSRA = _BV(ADEN);                   // Enable ADC
  ADCSRA |= _BV(ADATE);                 // Auto trigger enable
  ADCSRA |= _BV(ADIE);                  // ADC Interrupt enable
  ADCSRB = _BV(ADTS2) | _BV(ADTS1);     // Timer/Counter1 Overflow
  ADCSRA |= _BV(ADSC);                  // Start a conversion.

  sei();
}

void loop() {
  // TODO: idle sleep
}

ISR(ADC_vect)
{
  OCR0A = ADCH;
}

ISR(TIMER1_OVF_vect)
{
  // Empty so the flag is automatically cleared.
}
