// C++ code

const byte LED_PIN = 13;
const byte METER_PIN = A4;

void startTimer();

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  
  startTimer();
}

void loop()
{ 
}

void startTimer(){
  noInterrupts();

  TCCR1A = 0; // Set entire TCCR1A register to 0
  TCCR1B = 0; // Same for TCCR1B
  TCNT1 = 0; // Initialize counter value to 0
  // Set compare match register for 0.5Hz increments (2 seconds)
  OCR1A = 31249; // = (16*10^6) / (0.5*1024) - 1 (must be <65536)
  // Turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

ISR(TIMER1_COMPA_vect){
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}
