const int motion_pin = 2;
const int light_pin = 3;
const int Led_pin1 = 12;
const int Led_pin2 = 13;

void Motion(){
    Serial.println("Motion Detected");
    digitalWrite(Led_pin1, HIGH);
}
void Light(){
    Serial.println("Light detected");
    digitalWrite(Led_pin2, HIGH);
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(motion_pin, INPUT);
  pinMode(light_pin, INPUT);
  pinMode(Led_pin1, OUTPUT);
  pinMode(Led_pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motion_pin), Motion, HIGH);
  attachInterrupt(digitalPinToInterrupt(light_pin), Light, HIGH);
}

void loop() {
  // reads the input on analog pin A0 (value between 0 and 1023)
  if(digitalRead(motion_pin)==LOW){
    Serial.println("No Motion");
    digitalWrite(Led_pin1, LOW);
  } 
  if(digitalRead(light_pin)==LOW){
    Serial.println("No Light");
    digitalWrite(Led_pin2, LOW);
  } 
  delay(500);
}
