const int motion_pin = 2;
const int Led_pin = 13;
const int hold = 3000;

void interruptOn(){
    Serial.println("Motion Detected");
    digitalWrite(Led_pin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(motion_pin, INPUT);
  pinMode(Led_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motion_pin), interruptOn, HIGH);

}
void loop()
{
  if(digitalRead(motion_pin)==LOW){
    Serial.println("No Motion");
    digitalWrite(Led_pin, LOW);
  }
  delay(500);
} 