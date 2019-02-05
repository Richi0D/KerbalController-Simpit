void registerOutputchannel()   // Send a message to the plugin registering to channel messages
{
  mySimpit.registerChannel(THROTTLE_MESSAGE);
  mySimpit.registerChannel(WHEEL_MESSAGE);
  mySimpit.registerChannel(ROTATION_MESSAGE);
  mySimpit.registerChannel(TRANSLATION_MESSAGE);
 
}  

void registerInputchannel()   // Send a message to the plugin registering to channel messages
{
  //mySimpit.registerChannel(SCENE_CHANGE_MESSAGE);   // not working! getting no data
  mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);  
  mySimpit.registerChannel(ALTITUDE_MESSAGE);
  mySimpit.registerChannel(APSIDES_MESSAGE);
  mySimpit.registerChannel(APSIDESTIME_MESSAGE);
  mySimpit.registerChannel(ALTITUDE_MESSAGE); 
  mySimpit.registerChannel(VELOCITY_MESSAGE);
  mySimpit.registerChannel(AIRSPEED_MESSAGE);   
  mySimpit.registerChannel(TARGETINFO_MESSAGE);  
  mySimpit.registerChannel(SOI_MESSAGE);      
}   

void messageHandler(byte messageType, byte msg[], byte msgSize) {
        receivedata = true;  //if any data get received, messagehandler get called
        deadtimeOld = now;   //reset idle timer
      if (messageType==ACTIONSTATUS_MESSAGE){
        byte actions = msg[0];  // actions now contains the action group message
        if (actions & GEAR_ACTION) {gears_on = HIGH;}
        else {gears_on = LOW;}
        if (actions & BRAKES_ACTION) {brakes_on = HIGH;}
        else {brakes_on = LOW;}
        if (actions & LIGHT_ACTION) {lights_on = HIGH;}
        else {lights_on = LOW;} 
        }
      if (messageType==APSIDES_MESSAGE){
        if (msgSize == sizeof(apsidesMessage)) {     
        apsidesMessage myApsides;                 
        myApsides = parseApsides(msg);
        DataAP = myApsides.apoapsis;
        DataPE = myApsides.periapsis;
        }        
      }
      if (messageType==APSIDESTIME_MESSAGE){
        if (msgSize == sizeof(apsidesTimeMessage)) {     
        apsidesTimeMessage myApsidestime;                 
        myApsidestime = parseApsidesTime(msg);
        DataAPTime = myApsidestime.apoapsis;
        DataPETime = myApsidestime.periapsis;
        }        
      }
      if (messageType==ALTITUDE_MESSAGE){
        if (msgSize == sizeof(altitudeMessage)) {     
        altitudeMessage myAltitude;                 
        myAltitude = parseAltitude(msg);
        DataAlt = myAltitude.sealevel;
        DataRAlt = myAltitude.surface;
        }        
      }
      if (messageType==VELOCITY_MESSAGE){
        if (msgSize == sizeof(velocityMessage)) {     
        velocityMessage myVelocity;                 
        myVelocity = parseVelocity(msg);
        Vsurf = myVelocity.surface;
        VVI = myVelocity.vertical;
        VOrbit = myVelocity.orbital;
        }        
      }              
      if (messageType==AIRSPEED_MESSAGE){
        if (msgSize == sizeof(airspeedMessage)) {     
        airspeedMessage myAirspeed;                 
        myAirspeed = parseAirspeed(msg);
        MachNumber = myAirspeed.mach;
        }        
      }  
      if (messageType==TARGETINFO_MESSAGE){
        if (msgSize == sizeof(targetMessage)) {     
        targetMessage myTarget;                 
        myTarget = parseTarget(msg);
        DataTargetDist = myTarget.distance;
        TargetV = myTarget.velocity;       
        }        
      }  
      if (messageType==SOI_MESSAGE){
        strSOINumber = msg;     
        }        
                   
}
