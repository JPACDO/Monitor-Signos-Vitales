

int i = 0;
const int dim = 15; // dimension del array
int ecg[dim];


void setup()
{
  Serial.begin(38400);
  while (Serial.available() == 0) ; //wait until user presses a key
  Serial.read();
}

void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < dim; i++){
   ecg[i]=analogRead(A0); ///dato para ecg
   delay(5);
  }
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print('A');
  for (int i = 0; i < dim; i++){
    Serial.print(',');
    Serial.print(ecg[i]); ///dato para ecg
  }
  Serial.print('\n');
delay(1);

}
