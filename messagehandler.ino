void registerInputchannel()   // Send a message to the plugin registering to channel messages
{
  mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);
  mySimpit.registerChannel(CAGSTATUS_MESSAGE);
  mySimpit.registerChannel(SAS_MODE_INFO_MESSAGE);  
  mySimpit.registerChannel(FLIGHT_STATUS_MESSAGE); 
  mySimpit.registerChannel(ALTITUDE_MESSAGE);
  mySimpit.registerChannel(SOI_MESSAGE); 
  mySimpit.registerChannel(ELECTRIC_MESSAGE);   
  mySimpit.registerChannel(MONO_MESSAGE); 
  mySimpit.registerChannel(LF_MESSAGE); 
  mySimpit.registerChannel(OX_MESSAGE); 
  mySimpit.registerChannel(SF_MESSAGE); 
  mySimpit.registerChannel(XENON_GAS_MESSAGE);
  mySimpit.registerChannel(CUSTOM_RESOURCE_1_MESSAGE);              
}   

void messageHandler(byte messageType, byte msg[], byte msgSize) {
      switch(messageType){
      case ACTIONSTATUS_MESSAGE:
        if (msgSize == 1){
          gears_on = msg[0] & GEAR_ACTION;
          brakes_on = msg[0] & BRAKES_ACTION;
          lights_on = msg[0] & LIGHT_ACTION;
          RCS_on = msg[0] & RCS_ACTION;
          SAS_on = msg[0] & SAS_ACTION;
          Abort_on = msg[0] & ABORT_ACTION;
        }                 
        break;
      case CAGSTATUS_MESSAGE:
        if (msgSize == sizeof(cagStatusMessage)) {
          cagStatusMessage cagStatus;
          cagStatus = parseCAGStatusMessage(msg);
          action1_on = cagStatus.is_action_activated(1);
          action2_on = cagStatus.is_action_activated(2);
          action3_on = cagStatus.is_action_activated(3);
          action4_on = cagStatus.is_action_activated(4);
          action5_on = cagStatus.is_action_activated(5);
          action6_on = cagStatus.is_action_activated(6);
          ladder_on = cagStatus.is_action_activated(7);
          chutes_on = cagStatus.is_action_activated(8);
          solar_on = cagStatus.is_action_activated(9);
        }
        break;
      case SAS_MODE_INFO_MESSAGE:
        if (msgSize == sizeof(SASInfoMessage)) {
          SASInfoMessage sasMode;
          sasMode = parseSASInfoMessage(msg);
          SASval = sasMode.currentSASMode;
        }
        break;
      case FLIGHT_STATUS_MESSAGE:
        if (msgSize == sizeof(flightStatusMessage)) {
          flightStatusMessage flightStatus;
          flightStatus = parseFlightStatusMessage(msg);
          inflight = flightStatus.isInFligth();
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
      case SOI_MESSAGE:
        strSOI = (char *)msg;   
        break;
      case ELECTRIC_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {     
          resourceMessage myElectric;                 
          myElectric = parseResource(msg);
          ECharge = myElectric.available;
          EChargeTot = myElectric.total;
        }        
        break;  
      case MONO_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {     
          resourceMessage myMono;                 
          myMono = parseResource(msg);
          MonoProp = myMono.available;
          MonoPropTot = myMono.total;
        }        
        break;    
      case LF_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {     
          resourceMessage myLF;                 
          myLF = parseResource(msg);
          LiquidFuel = myLF.available;
          LiquidFuelTot = myLF.total;
        }        
        break;
      case OX_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {     
          resourceMessage myOX;                 
          myOX = parseResource(msg);
          Oxidizer = myOX.available;
          OxidizerTot = myOX.total;
        }        
        break;  
      case SF_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {     
          resourceMessage mySF;                 
          mySF = parseResource(msg);
          SolidFuel = mySF.available;
          SolidFuelTot = mySF.total;
        }        
        break;
     case XENON_GAS_MESSAGE:
        if (msgSize == sizeof(resourceMessage)) {     
          resourceMessage myXenon;                 
          myXenon = parseResource(msg);
          XenonGas = myXenon.available;
          XenonGasTot = myXenon.total;
        }        
        break;  
     case CUSTOM_RESOURCE_1_MESSAGE:
        if (msgSize == sizeof(CustomResourceMessage)) {     
          CustomResourceMessage myCustom1;                 
          myCustom1 = parseCustomResource(msg);
          IntakeAir = myCustom1.currentResource1;
          IntakeAirTot = myCustom1.maxResource1;
        }        
        break;                                          
   }                          
}
