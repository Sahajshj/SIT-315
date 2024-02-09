//defining led pins
const int red_led = 13;// for light sensor 1
const int yellow_led = 12; // for light sensor2
const int green_led = 11; // for motion sensor
const int blue_led = 10; // for timer interrupt

//defining sensor pins
const int motionpin=7;
const int lightpin=6;
const int light2_pin=5;

//creating boolean variables
volatile bool motion_state = LOW;
volatile bool light_state = LOW;
volatile bool light2_state = LOW;
volatile boolean toggle = false;


void setup()
{
  Serial.begin(9600);
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(motionpin, INPUT);
  pinMode(lightpin, INPUT);
  pinMode(light2_pin, INPUT);

  //PCI (using portD)
  PCICR |= B00000100; // activstaing port D
  PCMSK2 |= B11100000; // activating the pins in port D
  
  //For timer interrupts
  // Stop interrupts;
  noInterrupts();

  // Set timer1 interrupt at 0.2Hz (1Hz / 5 seconds)
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Allow interrupts
  interrupts();
}

void loop()
{
  Serial.print("Motion sensor: ");
  Serial.println(digitalRead(motionpin));
  Serial.print("Light sensor I: ");
  Serial.println(digitalRead(lightpin));
  Serial.print("Light sensor II: ");
  Serial.println(digitalRead(light2_pin));
  Serial.println("");
  delay(1000);
  
}

// ISR for PCI
ISR(PCINT2_vect)
{
  if(digitalRead(motionpin) == HIGH)
  {
    motion_state =!motion_state;
    digitalWrite(green_led, motion_state);
  }
  if(digitalRead(lightpin)==HIGH)
  {
    light_state =!light_state;
      digitalWrite(yellow_led, light_state);
  }
  if(digitalRead(light2_pin)==HIGH)
  {
    light2_state=!light2_state;
    digitalWrite(red_led, light2_state);
  }
  
}

//ISR for timer interrupt
ISR(TIMER1_COMPA_vect) { // Timer1 interrupt toggles pin 3 every 5 seconds
  if (toggle) {
    digitalWrite(blue_led, HIGH);
    toggle = false;
  } else {
    digitalWrite(blue_led, LOW);
    toggle = true;
  }
 
}