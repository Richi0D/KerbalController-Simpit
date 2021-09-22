
//check if it is time to send a control packet
void send_control_packet() {
  now = millis();
  controlTime = now - controlTimeOld;
  motorfader(); //call motorfader if button pressed
  Buttons_Switches(); //press buttons and switches
  
  if (controlTime > CONTROLREFRESH) {
    controlTimeOld = now;
    joystick_control();   //send joystick inputs
  }
}

void joystick_control() {
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

    int deadzone = 35;
    int deadzonethrottle = 25;
    float precisionfactor = 0.5;
    // Translation and steering is reversed!
    // for rovers we want also wheel throttle on pitch if we dont use throttle slider so we can go reverse

    switch(flymode){
    case 0:
      if (analogRead(pTHROTTLE)>= deadzonethrottle && analogRead(pTHROTTLE)<= 1023-deadzonethrottle){
        throttle_value = map(analogRead(pTHROTTLE),0,1023,0,INT16_MAX); wheelMsg.throttle = throttle_value;}
      else if (analogRead(pTHROTTLE)>= 1023-deadzonethrottle){
        throttle_value = INT16_MAX; wheelMsg.throttle = throttle_value;}
      else {throttle_value = 0; wheelMsg.throttle = 0;}
      
      if(analogRead(pRX) >= 512+deadzone || analogRead(pRX) <= 512-deadzone) {
        rotationMsg.yaw = map(analogRead(pRX),0,1023,INT16_MIN,INT16_MAX);
        wheelMsg.steer = map(analogRead(pRX),0,1023,INT16_MAX,INT16_MIN);}
      else {rotationMsg.yaw = 0; wheelMsg.steer = 0;}
      if(analogRead(pRY) >= 512+deadzone || analogRead(pRY)<= 512-deadzone) {
        rotationMsg.pitch = map(analogRead(pRY),0,1023,INT16_MIN,INT16_MAX);
        if (throttle_value == 0){wheelMsg.throttle = map(analogRead(pRY),0,1023,INT16_MAX,INT16_MIN);}
        }
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRZ) >= 512+deadzone || analogRead(pRZ)<= 512-deadzone) {
        rotationMsg.roll = map(analogRead(pRZ),0,1023,INT16_MIN,INT16_MAX);}
      else {rotationMsg.roll = 0;}

      if(analogRead(pTX) >= 512+deadzone || analogRead(pTX) <= 512-deadzone) {
        translationMsg.X = map(analogRead(pTX),0,1023,INT16_MAX,INT16_MIN);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone || analogRead(pTY)<= 512-deadzone) {
        translationMsg.Y = map(analogRead(pTY),0,1023,INT16_MAX,INT16_MIN);}
      else {translationMsg.Y= 0;}
      if(analogRead(pTZ) >= 512+deadzone || analogRead(pTZ)<= 512-deadzone) {
        translationMsg.Z = map(analogRead(pTZ),0,1023,INT16_MAX,INT16_MIN);}
      else {translationMsg.Z = 0;}

      break;
    case 1:
      if (analogRead(pTHROTTLE)>= deadzonethrottle && analogRead(pTHROTTLE)<= 1023-deadzonethrottle){
        throttle_value = map(analogRead(pTHROTTLE),0,1023,0,INT16_MAX); wheelMsg.throttle = throttle_value;}
      else if (analogRead(pTHROTTLE)>= 1023-deadzonethrottle){
        throttle_value = INT16_MAX; wheelMsg.throttle = throttle_value;}
      else {throttle_value = 0; wheelMsg.throttle = 0;}
      
      if(analogRead(pRZ) >= 512+deadzone || analogRead(pRZ) <= 512-deadzone) {
        rotationMsg.yaw = map(analogRead(pRZ),0,1023,INT16_MIN,INT16_MAX); 
        wheelMsg.steer = map(analogRead(pRZ),0,1023,INT16_MAX,INT16_MIN);}
      else {rotationMsg.yaw = 0; wheelMsg.steer = 0;}
      if(analogRead(pRY) >= 512+deadzone || analogRead(pRY)<= 512-deadzone) {
        rotationMsg.pitch = map(analogRead(pRY),0,1023,INT16_MIN,INT16_MAX);
        if (throttle_value == 0){wheelMsg.throttle = map(analogRead(pRY),0,1023,INT16_MAX,INT16_MIN);}
        }
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRX) >= 512+deadzone || analogRead(pRX)<= 512-deadzone) {
        rotationMsg.roll = map(analogRead(pRX),0,1023,INT16_MIN,INT16_MAX);}
      else {rotationMsg.roll = 0;}

      if(analogRead(pTX) >= 512+deadzone || analogRead(pTX) <= 512-deadzone) {
        translationMsg.X = map(analogRead(pTX),0,1023,INT16_MAX,INT16_MIN);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone || analogRead(pTY)<= 512-deadzone) {
        translationMsg.Y = map(analogRead(pTY),0,1023,INT16_MAX,INT16_MIN);}
      else {translationMsg.Y= 0;}
      if(analogRead(pTZ) >= 512+deadzone || analogRead(pTZ)<= 512-deadzone) {
        translationMsg.Z = map(analogRead(pTZ),0,1023,INT16_MAX,INT16_MIN);}
      else {translationMsg.Z = 0;}
    
      break;
    case 2:
      if (analogRead(pTHROTTLE)>= deadzonethrottle && analogRead(pTHROTTLE)<= 1023-deadzonethrottle){
        throttle_value = map(analogRead(pTHROTTLE),0,1023,0,INT16_MAX); wheelMsg.throttle = throttle_value;}
      else if (analogRead(pTHROTTLE)>= 1023-deadzonethrottle){
        throttle_value = INT16_MAX; wheelMsg.throttle = throttle_value;}
      else {throttle_value = 0; wheelMsg.throttle = 0;}
      
      if(analogRead(pRX) >= 512+deadzone || analogRead(pRX) <= 512-deadzone) {
        rotationMsg.yaw = map(analogRead(pRX),0,1023,INT16_MIN*precisionfactor,INT16_MAX*precisionfactor);
        wheelMsg.steer = map(analogRead(pRX),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {rotationMsg.yaw = 0; wheelMsg.steer = 0;}
      if(analogRead(pRY) >= 512+deadzone || analogRead(pRY)<= 512-deadzone) {
        rotationMsg.pitch = map(analogRead(pRY),0,1023,INT16_MIN*precisionfactor,INT16_MAX*precisionfactor);
        if (throttle_value == 0){wheelMsg.throttle = map(analogRead(pRY),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
        }
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRZ) >= 512+deadzone || analogRead(pRZ)<= 512-deadzone) {
        rotationMsg.roll = map(analogRead(pRZ),0,1023,INT16_MIN*precisionfactor,INT16_MAX*precisionfactor);}
      else {rotationMsg.roll = 0;}

      if(analogRead(pTX) >= 512+deadzone || analogRead(pTX) <= 512-deadzone) {
        translationMsg.X = map(analogRead(pTX),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone || analogRead(pTY)<= 512-deadzone) {
        translationMsg.Y = map(analogRead(pTY),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {translationMsg.Y= 0;}
      if(analogRead(pTZ) >= 512+deadzone || analogRead(pTZ)<= 512-deadzone) {
        translationMsg.Z = map(analogRead(pTZ),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {translationMsg.Z = 0;}
    
      break;
    case 3:
      if (analogRead(pTHROTTLE)>= deadzonethrottle && analogRead(pTHROTTLE)<= 1023-deadzonethrottle){
        throttle_value = map(analogRead(pTHROTTLE),0,1023,0,INT16_MAX); wheelMsg.throttle = throttle_value;}
      else if (analogRead(pTHROTTLE)>= 1023-deadzonethrottle){
        throttle_value = INT16_MAX; wheelMsg.throttle = throttle_value;}
      else {throttle_value = 0; wheelMsg.throttle = 0;}
      
      if(analogRead(pRZ) >= 512+deadzone || analogRead(pRZ) <= 512-deadzone) {
        rotationMsg.yaw = map(analogRead(pRZ),0,1023,INT16_MIN*precisionfactor,INT16_MAX*precisionfactor);
        wheelMsg.steer = map(analogRead(pRZ),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {rotationMsg.yaw = 0; wheelMsg.steer = 0;}
      if(analogRead(pRY) >= 512+deadzone || analogRead(pRY)<= 512-deadzone) {
        rotationMsg.pitch = map(analogRead(pRY),0,1023,INT16_MIN*precisionfactor,INT16_MAX*precisionfactor);
        if (throttle_value == 0){wheelMsg.throttle = map(analogRead(pRY),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
        }
      else {rotationMsg.pitch = 0;}
      if(analogRead(pRX) >= 512+deadzone || analogRead(pRX)<= 512-deadzone) {
        rotationMsg.roll = map(analogRead(pRX),0,1023,INT16_MIN*precisionfactor,INT16_MAX*precisionfactor);}
      else {rotationMsg.roll = 0;}

      if(analogRead(pTX) >= 512+deadzone || analogRead(pTX) <= 512-deadzone) {
        translationMsg.X = map(analogRead(pTX),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {translationMsg.X = 0;}
      if(analogRead(pTY) >= 512+deadzone || analogRead(pTY)<= 512-deadzone) {
        translationMsg.Y = map(analogRead(pTY),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {translationMsg.Y= 0;}
      if(analogRead(pTZ) >= 512+deadzone || analogRead(pTZ)<= 512-deadzone) {
        translationMsg.Z = map(analogRead(pTZ),0,1023,INT16_MAX*precisionfactor,INT16_MIN*precisionfactor);}
      else {translationMsg.Z = 0;}
    
      break;
    }
    //send the joystick control packet to the Simpit plugin
    mySimpit.send(THROTTLE_MESSAGE, throttle_value);     
    mySimpit.send(WHEEL_MESSAGE, wheelMsg);
    mySimpit.send(ROTATION_MESSAGE,rotationMsg);
    mySimpit.send(TRANSLATION_MESSAGE,translationMsg);    
}

void Buttons_Switches(){
    //toggle switches
    //SAS
    if(!digitalRead(pSAS) && !SAS_on){
      mySimpit.activateAction(SAS_ACTION);} 
    else if(digitalRead(pSAS) && SAS_on){
      mySimpit.deactivateAction(SAS_ACTION);}    
    //RCS
    if(!digitalRead(pRCS) && !RCS_on){
      mySimpit.activateAction(RCS_ACTION);}  
    else if(digitalRead(pRCS) && RCS_on){
      mySimpit.deactivateAction(RCS_ACTION);}     
    //Abort
    if(digitalRead(pABORT) && !Abort_on){
      mySimpit.activateAction(ABORT_ACTION);}
    else if(!digitalRead(pABORT) && Abort_on){
      mySimpit.deactivateAction(ABORT_ACTION);}
    
    //Set SAS Mode
    if(!digitalRead(pSAS)&& SAS_on && SASvalOld != SASval){
      SASvalOld = SASval;
      refreshSASDisplay = true;
      mySimpit.setSASMode(SASval);
    }

    //Parking Brakes
    if(debouncerBrakes.pressed()){mySimpit.toggleAction(BRAKES_ACTION);}

    //momentary stage button
    if(debouncerStage.pressed() && digitalRead(pARM)){Keyboard.write(32);}
  
    //toggle buttons
    if(debouncerLights.pressed()){Keyboard.write('U');}
    if(debouncerGears.pressed()){Keyboard.write('G');}
    if(debouncerA1.pressed()){Keyboard.write('1');}
    if(debouncerA2.pressed()){Keyboard.write('2');}
    if(debouncerA3.pressed()){Keyboard.write('3');}
    if(debouncerA4.pressed()){Keyboard.write('4');}
    if(debouncerA5.pressed()){Keyboard.write('5');} 
    if(debouncerA6.pressed()){Keyboard.write('6');}      
    if(debouncerLadder.pressed()){Keyboard.write('7');}
    if(debouncerChutes.pressed()){Keyboard.write('8');}    
    if(debouncerSolar.pressed()){Keyboard.write('9');}   

    //update button LEDs based on in-game status
    digitalWrite(pLIGHTSLED, lights_on); 
    digitalWrite(pGEARSLED, gears_on);
    digitalWrite(pBRAKESLED, brakes_on);
    digitalWrite(pACTION1LED, action1_on);
    digitalWrite(pACTION2LED, action2_on);
    digitalWrite(pACTION3LED, action3_on);
    digitalWrite(pACTION4LED, action4_on);
    digitalWrite(pACTION5LED, action5_on);
    digitalWrite(pACTION6LED, action6_on);    
    digitalWrite(pLADDERLED, ladder_on);
    digitalWrite(pSOLARLED, solar_on);
    digitalWrite(pCHUTESLED, chutes_on);     
}


//Control of motorfader
void motorfader() {
    if(!digitalRead(maxthrottle)){
      throttletarget = 1023;
      digitalWrite(motoron, HIGH);
        if (analogRead(pTHROTTLE) < (throttletarget - theThreshold) ) {
          analogWrite(motordown, 0);
          analogWrite(motorup, 255);     
        }
        else {
          analogWrite(motordown, 0);
          analogWrite(motorup, 0);                 
        } 
    }
    else if(!digitalRead(minthrottle)){
      throttletarget = 0;
      digitalWrite(motoron, HIGH);
        if (analogRead(pTHROTTLE) > (throttletarget + theThreshold) ) {
          analogWrite(motordown, 255);
          analogWrite(motorup, 0);
          }
        else {
          analogWrite(motordown, 0);
          analogWrite(motorup, 0);                 
        }  
      }
    else {
      throttletarget = pTHROTTLE;
      digitalWrite(motoron, LOW);
    }
}
