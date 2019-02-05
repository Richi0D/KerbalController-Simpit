void sendToDisplay1(String command)   //send Data to Display 1
{
  Serial1.print(command);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
} 

void sendToDisplay2(String command)   //send Data to Display 2
{
  Serial2.print(command);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
} 

void AtmosphereGauge (float DataAtmo){
//Atmosphere gauge

 //prepare the shift register
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW); 
  
  int vA = (12 - 6*log10(1 + 99*(DataAtmo / 6)));
  vA = (vA < 12) ? vA : 11;
  int powvA = 0.1+pow(2,vA);
    shiftOut(dataPin, clockPin, LSBFIRST, powvA<<4);
    shiftOut(dataPin, clockPin, LSBFIRST, powvA>>4);

  //latch the values in when done shifting
  digitalWrite(latchPin, HIGH); 
}
