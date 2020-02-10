//check if it is time to send a control packet
void send_control_packet() {
  now = millis();
  controlTime = now - controlTimeOld;
  if (controlTime > CONTROLREFRESH) {
    controlTimeOld = now;
    define_control_packet();
    motorfader(); //call motorfader if button pressed
  }
}

void define_control_packet() {
    //create structs and masks
    rotationMessage rotationMsg;
    rotationMsg.mask=1|2|4;
    translationMessage translationMsg;
    translationMsg.mask=1|2|4;    
    wheelMessage wheelMsg;
    wheelMsg.mask=1|2; 

    //check flymode 
     if((digitalRead(pprecision)) and (!digitalRead(pmodeswitch))){
       flymode = 0;} // rocket mode
     else if((digitalRead(pprecision)) and (digitalRead(pmodeswitch))){
       flymode = 1;} // plane mode
     else if((!digitalRead(pprecision)) and (!digitalRead(pmodeswitch))){
       flymode = 2;} // rocket mode + precision      
     else if((!digitalRead(pprecision)) and (digitalRead(pmodeswitch))){
       flymode = 3;} // plane mode + precision
     else {flymode = 0;}

    int deadzone = 50;
    int deadzonethrottle = 25;

    switch(flymode){
    case 0:
      throttle_value = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      wheelMsg.throttle = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      
      if(analogRead(pRX) >= 512+deadzone){rotationMsg.yaw = constrain(map(analogRead(pRX),512+deadzone,1023,0,32767),0,32767);
      wheelMsg.steer = constrain(map(analogRead(pRX),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pRX) <= 450){rotationMsg.yaw = constrain(map(analogRead(pRX),0,512-deadzone,-32767,0),-32767,0);
      wheelMsg.steer = constrain(map(analogRead(pRX),512-deadzone,0,0,32767),0,32767);}
      else {rotationMsg.yaw = 0;
      wheelMsg.steer = 0;}
      if(analogRead(pRY) >= 512+deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),512+deadzone,1023,0,32767),0,32767);}
      else if(analogRead(pRY) <= 512-deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),0,512-deadzone,-32767,0),-32767,0);}
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRZ) >= 512+deadzone){rotationMsg.roll = constrain(map(analogRead(pRZ),512+deadzone,1023,0,32767),0,32767);}
      else if(analogRead(pRZ) <= 512-deadzone){rotationMsg.roll = constrain(map(analogRead(pRZ),0,512-deadzone,-32767,0),-32767,0);}
      else {rotationMsg.roll = 0;}

      if(analogRead(pTX) >= 512+deadzone){translationMsg.X = constrain(map(analogRead(pTX),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pTX) <= 512-deadzone){translationMsg.X = constrain(map(analogRead(pTX),512-deadzone,0,0,32767),0,32767);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone){translationMsg.Y = constrain(map(analogRead(pTY),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pTY) <= 512-deadzone){translationMsg.Y = constrain(map(analogRead(pTY),512-deadzone,0,0,32767),0,32767);}
      else {translationMsg.Y = 0;}
      if(analogRead(pTZ) >= 512+deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pTZ) <= 512-deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),512-deadzone,0,0,32767),0,32767);}
      else {translationMsg.Z = 0;}

      break;
    case 1:
      throttle_value = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      wheelMsg.throttle = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      
      if(analogRead(pRX) >= 512+deadzone){rotationMsg.roll = constrain(map(analogRead(pRX),512+deadzone,1023,0,32767),0,32767);}
      else if(analogRead(pRX) <= 512-deadzone){rotationMsg.roll = constrain(map(analogRead(pRX),0,512-deadzone,-32767,0),-32767,0);}
      else {rotationMsg.roll = 0;}
      if(analogRead(pRY) >= 512+deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),512+deadzone,1023,0,32767),0,32767);}
      else if(analogRead(pRY) <= 512-deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),0,512-deadzone,-32767,0),-32767,0);}
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRZ) >= 512+deadzone){rotationMsg.yaw = constrain(map(analogRead(pRZ),512+deadzone,1023,0,32767),0,32767);
      wheelMsg.steer = constrain(map(analogRead(pRZ),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pRZ) <= 512-deadzone){rotationMsg.yaw = constrain(map(analogRead(pRZ),0,512-deadzone,-32767,0),-32767,0);
      wheelMsg.steer = constrain(map(analogRead(pRZ),512-deadzone,0,0,32767),0,32767);}
      else {rotationMsg.yaw = 0;
      wheelMsg.steer = 0;}

      if(analogRead(pTX) >= 512+deadzone){translationMsg.X = constrain(map(analogRead(pTX),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pTX) <= 512-deadzone){translationMsg.X = constrain(map(analogRead(pTX),512-deadzone,0,0,32767),0,32767);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone){translationMsg.Y = constrain(map(analogRead(pTY),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pTY) <= 512-deadzone){translationMsg.Y = constrain(map(analogRead(pTY),512-deadzone,0,0,32767),0,32767);}
      else {translationMsg.Y = 0;}
      if(analogRead(pTZ) >= 512+deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),1023,512+deadzone,-32767,0),-32767,0);}
      else if(analogRead(pTZ) <= 512-deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),512-deadzone,0,0,32767),0,32767);}
      else {translationMsg.Z = 0;}
    
      break;
    case 2:
      throttle_value = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      wheelMsg.throttle = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      
      if(analogRead(pRX) >= 512+deadzone){rotationMsg.yaw = constrain(map(analogRead(pRX),512+deadzone,1023,0,8192),0,8192);
      wheelMsg.steer = constrain(map(analogRead(pRX),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pRX) <= 512-deadzone){rotationMsg.yaw = constrain(map(analogRead(pRX),0,512-deadzone,-8192,0),-8192,0);
      wheelMsg.steer = constrain(map(analogRead(pRX),512-deadzone,0,0,8192),0,8192);}
      else {rotationMsg.yaw = 0;
      wheelMsg.steer = 0;}
      if(analogRead(pRY) >= 512+deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),512+deadzone,1023,0,8192),0,8192);}
      else if(analogRead(pRY) <= 512-deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),0,512-deadzone,-8192,0),-8192,0);}
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRZ) >= 512+deadzone){rotationMsg.roll = constrain(map(analogRead(pRZ),512+deadzone,1023,0,8192),0,8192);}
      else if(analogRead(pRZ) <= 512-deadzone){rotationMsg.roll = constrain(map(analogRead(pRZ),0,512-deadzone,-8192,0),-8192,0);}
      else {rotationMsg.roll = 0;}

      if(analogRead(pTX) >= 512+deadzone){translationMsg.X = constrain(map(analogRead(pTX),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pTX) <= 512-deadzone){translationMsg.X = constrain(map(analogRead(pTX),512-deadzone,0,0,8192),0,8192);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone){translationMsg.Y = constrain(map(analogRead(pTY),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pTY) <= 512-deadzone){translationMsg.Y = constrain(map(analogRead(pTY),512-deadzone,0,0,8192),0,8192);}
      else {translationMsg.Y = 0;}
      if(analogRead(pTZ) >= 512+deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pTZ) <= 512-deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),512-deadzone,0,0,8192),0,8192);}
      else {translationMsg.Z = 0;}
    
      break;
    case 3:
      throttle_value = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      wheelMsg.throttle = constrain(map(analogRead(pTHROTTLE),1023-deadzonethrottle,0+deadzonethrottle,0,32767),0,32767);
      
      if(analogRead(pRX) >= 512+deadzone){rotationMsg.roll = constrain(map(analogRead(pRX),512+deadzone,1023,0,8192),0,8192);}
      else if(analogRead(pRX) <= 512-deadzone){rotationMsg.roll = constrain(map(analogRead(pRX),0,512-deadzone,-8192,0),-8192,0);}
      else {rotationMsg.roll = 0;}
      if(analogRead(pRY) >= 512+deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),512+deadzone,1023,0,8192),0,8192);}
      else if(analogRead(pRY) <= 512-deadzone){rotationMsg.pitch = constrain(map(analogRead(pRY),0,512-deadzone,-8192,0),-8192,0);}
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRZ) >= 512+deadzone){rotationMsg.yaw = constrain(map(analogRead(pRZ),512+deadzone,1023,0,8192),0,8192);
      wheelMsg.steer = constrain(map(analogRead(pRZ),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pRZ) <= 512-deadzone){rotationMsg.yaw = constrain(map(analogRead(pRZ),0,512-deadzone,-8192,0),-8192,0);
      wheelMsg.steer = constrain(map(analogRead(pRZ),512-deadzone,0,0,8192),0,8192);}
      else {rotationMsg.yaw = 0;
      wheelMsg.steer = 0;}

      if(analogRead(pTX) >= 512+deadzone){translationMsg.X = constrain(map(analogRead(pTX),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pTX) <= 512-deadzone){translationMsg.X = constrain(map(analogRead(pTX),512-deadzone,0,0,8192),0,8192);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone){translationMsg.Y = constrain(map(analogRead(pTY),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pTY) <= 512-deadzone){translationMsg.Y = constrain(map(analogRead(pTY),512-deadzone,0,0,8192),0,8192);}
      else {translationMsg.Y = 0;}
      if(analogRead(pTZ) >= 512+deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),1023,512+deadzone,-8192,0),-8192,0);}
      else if(analogRead(pTZ) <= 512-deadzone){translationMsg.Z = constrain(map(analogRead(pTZ),512-deadzone,0,0,8192),0,8192);}
      else {translationMsg.Z = 0;}
    
      break;
    }
    //send the control packet to the Simpit plugin
    mySimpit.send(THROTTLE_MESSAGE, throttle_value);     
    mySimpit.send(WHEEL_MESSAGE, wheelMsg);
    mySimpit.send(ROTATION_MESSAGE,rotationMsg);
    mySimpit.send(TRANSLATION_MESSAGE,translationMsg);

    //toggle switches
    if(!digitalRead(pSAS)){
      if(!SAS_on){mySimpit.activateAction(SAS_ACTION);SAS_on=true;}} 
    else {
      if(SAS_on){mySimpit.deactivateAction(SAS_ACTION);SAS_on=false;}}

    if(!digitalRead(pRCS)){
      if(!RCS_on){mySimpit.activateAction(RCS_ACTION);RCS_on=true;}}  
    else {
      if (RCS_on){mySimpit.deactivateAction(RCS_ACTION);RCS_on=false;}}     

    if(digitalRead(pABORT)){
      if(!Abort_on){mySimpit.activateAction(ABORT_ACTION);Abort_on=true;}}
    else {
      if (Abort_on){mySimpit.deactivateAction(ABORT_ACTION);Abort_on=false;}}   

    //momentary stage button
    if(debouncerStage.pressed() && digitalRead(pARM)){mySimpit.activateAction(STAGE_ACTION);}
    //toggle buttons
    if(debouncerLights.pressed()){mySimpit.toggleAction(LIGHT_ACTION);}
    if(debouncerBrakes.pressed()){mySimpit.toggleAction(BRAKES_ACTION);}
    if(debouncerGears.pressed()){mySimpit.toggleAction(GEAR_ACTION);}
    if(debouncerSolar.pressed()){mySimpit.toggleCAG(9);}
    if(debouncerChutes.pressed()){mySimpit.toggleCAG(8);}
    if(debouncerLadder.pressed()){mySimpit.toggleCAG(7);}
    if(debouncerA6.pressed()){mySimpit.toggleCAG(6);}
    if(debouncerA5.pressed()){mySimpit.toggleCAG(5);}
    if(debouncerA4.pressed()){mySimpit.toggleCAG(4);}
    if(debouncerA3.pressed()){mySimpit.toggleCAG(3);}
    if(debouncerA2.pressed()){mySimpit.toggleCAG(2);}
    if(debouncerA1.pressed()){mySimpit.toggleCAG(1);}       
}

void motorfader() {
if(!digitalRead(maxthrottle)){
  throttletarget = 0;
  digitalWrite(motoron, HIGH);
  }
else if(!digitalRead(minthrottle)){
  throttletarget = 1020;
  digitalWrite(motoron, HIGH);
  }
else {
  throttletarget = pTHROTTLE;
  digitalWrite(motoron, LOW);
  }
  
    if (analogRead(pTHROTTLE) > (throttletarget + theThreshold) ) {
      analogWrite(motordown, 0);
      analogWrite(motorup, 255);
    }
    else if (analogRead(pTHROTTLE) < (throttletarget - theThreshold) ) {
      analogWrite(motordown, 255);
      analogWrite(motorup, 0);     
    }
    else {
      analogWrite(motordown, 0);
      analogWrite(motorup, 0);
    }
}
