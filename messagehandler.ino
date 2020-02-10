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
      switch(messageType){
      case ACTIONSTATUS_MESSAGE:
        if (msg[0] & GEAR_ACTION) {gears_on = HIGH;}
        else {gears_on = LOW;}
        if (msg[0] & BRAKES_ACTION) {brakes_on = HIGH;}
        else {brakes_on = LOW;}
        if (msg[0] & LIGHT_ACTION) {lights_on = HIGH;}
        else {lights_on = LOW;} 
        if (msg[0] & RCS_ACTION) {RCS_on = HIGH;}
        else {RCS_on = LOW;}    
        if (msg[0] & SAS_ACTION) {SAS_on = HIGH;}
        else {SAS_on = LOW;} 
        if (msg[0] & ABORT_ACTION) {Abort_on = HIGH;}
        else {Abort_on = LOW;}                      
        break;
      case APSIDES_MESSAGE:
        if (msgSize == sizeof(apsidesMessage)) {     
        apsidesMessage myApsides;                 
        myApsides = parseApsides(msg);
        DataAP = myApsides.apoapsis;
        DataPE = myApsides.periapsis;
        }        
        break;
      case APSIDESTIME_MESSAGE:
        if (msgSize == sizeof(apsidesTimeMessage)) {     
        apsidesTimeMessage myApsidestime;                 
        myApsidestime = parseApsidesTime(msg);
        DataAPTime = myApsidestime.apoapsis;
        DataPETime = myApsidestime.periapsis;
        }        
        break;
      case ALTITUDE_MESSAGE:
        if (msgSize == sizeof(altitudeMessage)) {     
        altitudeMessage myAltitude;                 
        myAltitude = parseAltitude(msg);
        DataAlt = myAltitude.sealevel;
        DataRAlt = myAltitude.surface;
        }        
        break;
      case VELOCITY_MESSAGE:
        if (msgSize == sizeof(velocityMessage)) {     
        velocityMessage myVelocity;                 
        myVelocity = parseVelocity(msg);
        Vsurf = myVelocity.surface;
        VVI = myVelocity.vertical;
        VOrbit = myVelocity.orbital;
        }        
        break;           
      case AIRSPEED_MESSAGE:
        if (msgSize == sizeof(airspeedMessage)) {     
        airspeedMessage myAirspeed;                 
        myAirspeed = parseAirspeed(msg);
        MachNumber = myAirspeed.mach;
        }        
        break;
      case TARGETINFO_MESSAGE:
        if (msgSize == sizeof(targetMessage)) {     
        targetMessage myTarget;                 
        myTarget = parseTarget(msg);
        DataTargetDist = myTarget.distance;
        TargetV = myTarget.velocity;       
        }        
        break;
      case SOI_MESSAGE:
        strSOINumber = msg;   
        break;  
   }                          
}
