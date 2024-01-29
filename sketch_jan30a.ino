const int motion_pin = 2;
const int Led_pin = 13;
const int hold = 3000;
void setup()
{
  Serial.begin(9600);
  pinMode(motion_pin, INPUT);
  pinMode(Led_pin, OUTPUT);
}
void loop()
{
  // Detect motion
  int motion_status = digitalRead(motion_pin);
  // Process the detection
  if (motion_status == HIGH)
  {
    Serial.println("Motion Detected!!!");
    digitalWrite(Led_pin, HIGH);
    delay(hold);
  }
  else
  {
    Serial.println("No Motion");
    digitalWrite(Led_pin, LOW);
  }
  delay(500);
}