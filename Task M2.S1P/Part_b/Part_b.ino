// C++ code

const byte LED_PIN = 13;
const byte METER_PIN = A4;

void startTimer(double timerFrequency);

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  
  // Start timer with frequency 0.5Hz (2 seconds)
  startTimer(0.5);
}

void loop()
{ 
}

void startTimer(double timerFrequency){
  noInterrupts();

  // Calculate the OCRx value based on timer frequency
  uint16_t ocrValue = (uint16_t)((F_CPU / 1024.0 / timerFrequency) - 1);

  // Set the correct TCCRxB bits based on the prescaler value
  byte prescalerBits = 0;
  if (ocrValue < 256) {
    prescalerBits = (1 << CS00);
  } else if (ocrValue < 1024) {
    prescalerBits = (1 << CS01);
  } else {
    prescalerBits = (1 << CS02) | (1 << CS00);
  }

  // Set Timer1 Control Register A and B
  TCCR1A = 0; // Set entire TCCR1A register to 0
  TCCR1B = 0; // Same for TCCR1B
  TCNT1 = 0; // Initialize counter value to 0
  // Set compare match register for the given frequency
  OCR1A = ocrValue;
  // Turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set prescaler bits
  TCCR1B |= prescalerBits;
  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

ISR(TIMER1_COMPA_vect){
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}
