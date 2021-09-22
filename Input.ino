//input variables
float DataAlt; 
float DataRAlt;   
String strSOI;
float ECharge;
float EChargeTot;
float MonoProp;
float MonoPropTot;
float LiquidFuel;
float LiquidFuelTot;
float Oxidizer;
float OxidizerTot;
float SolidFuel;
float SolidFuelTot;
float XenonGas;
float XenonGasTot;
float IntakeAir;
float IntakeAirTot;


void get_vessel_data() {
    now = millis();

    if (inflight){
      //we are in flight. Update Displays
      deadtimeOld = now;                
        displayTime = now - displayTimeOld;
        if (displayTime > DISPLAYREFRESH) {
          displayTimeOld = now;

          //data is being received
        if (!digitalRead(pswitch1) && PageDisplay1 != 2) {
          PageDisplay1 = 2;
          sendToDisplay1(String("page ") + String(PageDisplay1)); 
        }
        else if (!digitalRead(pswitch2) && PageDisplay1 != 3) {
          PageDisplay1 = 3;
          sendToDisplay1(String("page ") + String(PageDisplay1)); 
        }
        else if (!digitalRead(pswitch3) && PageDisplay1 != 4) {
          PageDisplay1 = 4;
          sendToDisplay1(String("page ") + String(PageDisplay1)); 
        }
        else if (!digitalRead(pswitch4) && PageDisplay1 != 5) {
          PageDisplay1 = 5;
          sendToDisplay1(String("page ") + String(PageDisplay1)); 
        }     
        if (PageDisplay2 !=2) {
          PageDisplay2 = 2;
          sendToDisplay2(String("page ") + String(PageDisplay2));   
        }
          
          define_vessel_data_display();   //define what to do with the data below
        }
      }
      else  { //if not in flight, go idle
      deadtime = now - deadtimeOld; 
      if (deadtime > IDLETIMER){
        if (PageDisplay1 !=1){
          PageDisplay1 = 1;
          sendToDisplay1(String("page ") + String(PageDisplay1));}
        if (PageDisplay2 !=1){
          PageDisplay2 = 1;
          sendToDisplay2(String("page ") + String(PageDisplay2));}
        AtmosphereGauge(10);   //Atmosphere gauge off     
        //turn off Leds
        digitalWrite(pLIGHTSLED, LOW); 
        digitalWrite(pGEARSLED, LOW);
        digitalWrite(pBRAKESLED, LOW);
        digitalWrite(pACTION1LED, LOW);
        digitalWrite(pACTION2LED, LOW);
        digitalWrite(pACTION3LED, LOW);
        digitalWrite(pACTION4LED, LOW);
        digitalWrite(pACTION5LED, LOW);
        digitalWrite(pACTION6LED, LOW);    
        digitalWrite(pLADDERLED, LOW);
        digitalWrite(pSOLARLED, LOW);
        digitalWrite(pCHUTESLED, LOW);
      }
    }    
  } 

//define what to do with the vessel data here, e.g. turn on LED's, display text on the LCD
void define_vessel_data_display() {

//AtmosphereGauge(VData.Density);   //call Atmosphere gauge, missing density message in simpit

  //update SAS buttons based on in-game status
  switch (PageDisplay1){
    case 4:  // update SAS Buttons
      // only update if old value is different
     if(SASvalOld != SASval || refreshSASDisplay){
      SASvalOld = SASval;
      refreshSASDisplay = false;
      switch (SASval){
        case 255: //SMOFF
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;        
        case AP_STABILITYASSIST: //SMSAS
          sendToDisplay1(String("dsoff.val=") + String(1));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
        case AP_PROGRADE: //SMPrograde
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(1));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
        case AP_RETROGRADE: //SMRetroGrade
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(1));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
        case AP_NORMAL: //SMNormal
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(1));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
         case AP_ANTINORMAL: //SMAntinormal
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(1));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
         case AP_RADIALIN: //SMRadialIn
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(1));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
        case AP_RADIALOUT: //SMRadialOut
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(1));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
         case AP_TARGET: //SMTarget
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(1));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;
         case AP_ANTITARGET: //SMAntiTarget
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(0));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(1));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;  
         case AP_MANEUVER: //SMManeuverNode
          sendToDisplay1(String("dsoff.val=") + String(0));
          sendToDisplay1(String("dsman.val=") + String(1));
          sendToDisplay1(String("dspro.val=") + String(0));
          sendToDisplay1(String("dsret.val=") + String(0));
          sendToDisplay1(String("dsnorm.val=") + String(0));
          sendToDisplay1(String("dsanti.val=") + String(0));
          sendToDisplay1(String("dsradout.val=") + String(0));
          sendToDisplay1(String("dsradin.val=") + String(0));
          sendToDisplay1(String("dstarg.val=") + String(0));
          sendToDisplay1(String("dsrettarg.val=") + String(0));
        break;                                                                       
        }
     }
    break;
    case 5:  // update Wavepage    
      //Altitude
      String strAlt = "";
      if (Altitude < 1000000 && Altitude > -1000000) {
        strAlt += String(Altitude,0);
        strAlt += "m";
      } else if ((Altitude >= 1000000 && Altitude < 1000000000) || (Altitude <= -1000000 && Altitude > -1000000000)) {
        strAlt += String((Altitude / 1000.0),0);
        strAlt += "km";
      } else if ((Altitude >= 1000000000 && Altitude < 1000000000000) || (Altitude <= -1000000000 && Altitude > -1000000000000)) {
        strAlt += String((Altitude / 1000000.0),0);
        strAlt += "Mm";
      } else {
        strAlt += String((Altitude / 1000000000.0),0);
        strAlt += "Gm";
      }      
      sendToDisplay1(String("valh.txt=\"") + String(strAlt)+String("\""));

      //Fly high
      String strflyhigh = "";
      if (flyhigh < 1000000) {
        strflyhigh += String(flyhigh);
        strflyhigh += "m";
      } else if ((flyhigh >= 1000000 && flyhigh < 1000000000)) {
        strflyhigh += String((flyhigh / 1000));
        strflyhigh += "km";
      } else if ((flyhigh >= 1000000000 && flyhigh < 1000000000000)) {
        strflyhigh += String((flyhigh / 1000000));
        strflyhigh += "Mm";
      } else {
        strflyhigh += String((flyhigh / 1000000000));
        strflyhigh += "Gm";
      }       
      sendToDisplay1(String("valfh.txt=\"") + String(strflyhigh)+String("\""));

      //Low space
      String strlowspace = "";
      if (lowspace < 1000000) {
        strlowspace += String(lowspace);
        strlowspace += "m";
      } else if ((lowspace >= 1000000 && lowspace < 1000000000) || (lowspace <= -1000000 && lowspace > -1000000000)) {
        strlowspace += String((lowspace / 1000));
        strlowspace += "km";
      } else if ((lowspace >= 1000000000 && lowspace < 1000000000000) || (lowspace <= -1000000000 && lowspace > -1000000000000)) {
        strlowspace += String((lowspace / 1000000));
        strlowspace += "Mm";
      } else {
        strlowspace += String((lowspace / 1000000000));
        strlowspace += "Gm";
      }       
      sendToDisplay1(String("valls.txt=\"") + String(strlowspace)+String("\""));

      //High space
      String strhighspace = "";
      if (highspace < 1000000) {
        strhighspace += String(highspace);
        strhighspace += "m";
      } else if ((highspace >= 1000000 && highspace < 1000000000) || (highspace <= -1000000 && highspace > -1000000000)) {
        strhighspace += String((highspace / 1000));
        strhighspace += "km";
      } else if ((highspace >= 1000000000 && highspace < 1000000000000) || (highspace <= -1000000000 && highspace > -1000000000000)) {
        strhighspace += String((highspace / 1000000));
        strhighspace += "Mm";
      } else {
        strhighspace += String((highspace / 1000000000));
        strhighspace += "Gm";
      }         
      sendToDisplay1(String("valhs.txt=\"") + String(strhighspace)+String("\""));
    break;    
    }
    
//Get all Data for Wavepage
  Altitude = DataAlt;
 if (strSOI == "Kerbol"){     //100 = SUN
          flyhigh = 18000;
          lowspace = 600000;
          highspace = 1000000000;
  }
  else if (strSOI == "Moho"){     //110 = MOHO
      flyhigh = 0;
      lowspace = 0;
      highspace = 80000;
  }
  else if (strSOI == "Eve"){     //120 = EVE
          flyhigh = 22000;
          lowspace = 90000;
  }
  else if (strSOI == "Gilly"){     //121 = GILLY
          flyhigh = 0;
          lowspace = 0;
          highspace = 6000;
  }
  else if (strSOI == "Kerbin"){     //130 = KERBIN
          flyhigh = 18000;
          lowspace = 70000;
          highspace = 250000;
  }   
  else if (strSOI == "Mun"){     //131 = MUN
          flyhigh = 0;
          lowspace = 0;
          highspace = 60000;
  }  
  else if (strSOI == "Minmus"){     //132 = MINMUS
          flyhigh = 0;
          lowspace = 0;
          highspace = 30000;
  } 
  else if (strSOI == "Duna"){     //140 = DUNA
          flyhigh = 12000;
          lowspace = 50000;
          highspace = 140000;
  }  
  else if (strSOI == "Ike"){     //141 = IKE
          flyhigh = 0;
          lowspace = 0;
          highspace = 50000;
  } 
  else if (strSOI == "Dres"){     //150 = DRES
          flyhigh = 0;
          lowspace = 0;
          highspace = 25000;
  } 
  else if (strSOI == "Jool"){     //160 = JOOL
          flyhigh = 120000;
          lowspace = 200000;
          highspace = 4000000;
  }
  else if (strSOI == "Laythe"){     //161 = LAYTHE
          flyhigh = 10000;
          lowspace = 50000;
          highspace = 200000;
  } 
  else if (strSOI == "Vall"){     //162 = VALL
          flyhigh = 0;
          lowspace = 0;
          highspace = 90000;
  }
  else if (strSOI == "Tylo"){     //163 = TYLO
          flyhigh = 0;
          lowspace = 0;
          highspace = 250000;
  }  
  else if (strSOI == "Bop"){     //164 = BOP
          flyhigh = 0;
          lowspace = 0;
          highspace = 25000;
  }  
  else if (strSOI == "Pol"){     //165 = POL
          flyhigh = 0;
          lowspace = 0;
          highspace = 22000;
  } 
  else if (strSOI == "Eeloo"){     //170 = EELOO
          flyhigh = 0;
          lowspace = 0;
          highspace = 60000;
  } 
  else{
        flyhigh = 0;
        lowspace = 0;
        highspace = 0;
  }   
  
//Ressources Page2 Display2
  if (PageDisplay2==2){
  const unsigned int gaugeColorOK = 29927;           //Color green when full
  const unsigned int gaugeColorAlert = 59169;        //Color yellow when alert
  const unsigned int gaugeColorCritical = 63488;     //Color red when critical

  //Battery
  if (EChargeTot <= 0){
     sendToDisplay2(String("jel.val=") + String(100));
  }else{
      //gauges
      byte vEL = 100-(100 * ECharge / EChargeTot);            //percentage of electric charge remaining
      sendToDisplay2(String("jel.val=") + String(vEL));
      //change color in gauges
      if (vEL >=0 && vEL < 60){
      sendToDisplay2(String("jel.bco=") + String(gaugeColorOK));
      }
      else if (vEL >=60 && vEL <= 90){
      sendToDisplay2(String("jel.bco=") + String(gaugeColorAlert));  
       }
      else {
      sendToDisplay2(String("jel.bco=") + String(gaugeColorCritical));  
      }
      //Numbers
      String strbattery = String(ECharge,0);
      strbattery += "/";
      strbattery += String(EChargeTot,0);
      sendToDisplay2(String("tel.txt=\"") + String(strbattery)+String("\""));
  }
  sendToDisplay2(String("tel.txt=\"") + String(ECharge)+String("\""));
  
  //Monopropellant
  if (MonoPropTot <= 0){
     sendToDisplay2(String("jmp.val=") + String(100));  
  }else{
      //gauges
      byte vMP = 100-(100 * MonoProp / MonoPropTot);          //percentage of monopropellant remaining
      sendToDisplay2(String("jmp.val=") + String(vMP));       
      //change color in gauges  
      if (vMP >=0 && vMP < 60){
      sendToDisplay2(String("jmp.bco=") + String(gaugeColorOK));
      }
      else if (vMP >=60 && vMP <= 90){
      sendToDisplay2(String("jmp.bco=") + String(gaugeColorAlert));  
      }
      else {
      sendToDisplay2(String("jmp.bco=") + String(gaugeColorCritical));  
      }
      //Numbers
      String strMonopropellant = String(MonoProp,0);
      strMonopropellant += "/";
      strMonopropellant += String(MonoPropTot,0);
      sendToDisplay2(String("tmp.txt=\"") + String(strMonopropellant)+String("\""));
  }
  sendToDisplay2(String("tmp.txt=\"") + String(MonoProp)+String("\""));
  
  //Liquid Fuel
  if (LiquidFuelTot <= 0){
     sendToDisplay2(String("jlf.val=") + String(100));  
  }else{
      //gauges
      byte vLF = 100-(100 * LiquidFuel / LiquidFuelTot);    //percentage of liquid fuel remaining in current stage
      sendToDisplay2(String("jlf.val=") + String(vLF));
      //change color in gauges
      if (vLF >=0 && vLF < 60){
      sendToDisplay2(String("jlf.bco=") + String(gaugeColorOK));
      }
      else if (vLF >=60 && vLF <= 90){
      sendToDisplay2(String("jlf.bco=") + String(gaugeColorAlert));  
      }
      else {
      sendToDisplay2(String("jlf.bco=") + String(gaugeColorCritical));  
      }
      //Numbers
      String strLiquidFuel = String(LiquidFuel,0);
      strLiquidFuel += "/";
      strLiquidFuel += String(LiquidFuelTot,0);
      sendToDisplay2(String("tlf.txt=\"") + String(strLiquidFuel)+String("\""));
  }
  //sendToDisplay2(String("tlf.txt=\"") + String(myLF.available)+String("\""));
  
  //Oxidized
  if (OxidizerTot <= 0){
     sendToDisplay2(String("jox.val=") + String(100));
  }else{
      //gauges
      byte vOX = 100-(100 * Oxidizer / OxidizerTot);        //percentage of oxidized remaining in current stage
      sendToDisplay2(String("jox.val=") + String(vOX));

      if (vOX >=0 && vOX < 60){
      sendToDisplay2(String("jox.bco=") + String(gaugeColorOK));
      }
      else if (vOX >=60 && vOX <= 90){
      sendToDisplay2(String("jox.bco=") + String(gaugeColorAlert));  
      }
      else {
      sendToDisplay2(String("jox.bco=") + String(gaugeColorCritical));  
      } 
      //Numbers
      String strOxidized = String(Oxidizer,0);
      strOxidized += "/";
      strOxidized += String(OxidizerTot,0);
      sendToDisplay2(String("tox.txt=\"") + String(strOxidized)+String("\""));              
  }
  //Solid Fuel
  if (SolidFuelTot <= 0){
     sendToDisplay2(String("jsf.val=") + String(100));
  }else{
      //gauges
      byte vSF = 100-(100 * SolidFuel / SolidFuelTot);        //percentage of solid fuel remaining
      sendToDisplay2(String("jsf.val=") + String(vSF));
 
      if (vSF >=0 && vSF < 60){
      sendToDisplay2(String("jsf.bco=") + String(gaugeColorOK));
      }
      else if (vSF >=60 && vSF <= 90){
      sendToDisplay2(String("jsf.bco=") + String(gaugeColorAlert));  
      }
      else {
      sendToDisplay2(String("jsf.bco=") + String(gaugeColorCritical));  
      }  
      //Numbers
      String strSolidFuel = String(SolidFuel,0);
      strSolidFuel += "/";
      strSolidFuel += String(SolidFuelTot,0);
      sendToDisplay2(String("tsf.txt=\"") + String(strSolidFuel)+String("\""));        
  }
  //Xenon Gas
  if (XenonGasTot <= 0){
     sendToDisplay2(String("jxe.val=") + String(100));
  }else{
      //gauges
      byte vXE = 100-(100 * XenonGas / XenonGasTot);          //percentage of xenon gas remaining
      sendToDisplay2(String("jxe.val=") + String(vXE));
      //change color in gauges
      if (vXE >=0 && vXE < 60){
      sendToDisplay2(String("jxe.bco=") + String(gaugeColorOK));
      }
      else if (vXE >=60 && vXE <= 90){
      sendToDisplay2(String("jxe.bco=") + String(gaugeColorAlert));  
      }
      else {
      sendToDisplay2(String("jxe.bco=") + String(gaugeColorCritical));  
      }
      //Numbers
      String strXenonGas = String(XenonGas,0);
      strXenonGas += "/";
      strXenonGas += String(XenonGasTot,0);
      sendToDisplay2(String("txe.txt=\"") + String(strXenonGas)+String("\""));           
  }
  //Intake Air
  if (IntakeAirTot <= 0){
     sendToDisplay2(String("jair.val=") + String(100));
  }else{
      //gauges
      byte vAIR = 100-(100 * IntakeAir / IntakeAirTot);         //percentage of xenon gas remaining
      sendToDisplay2(String("jair.val=") + String(vAIR));  
      //change color in gauges
      if (vAIR >=0 && vAIR < 60){
      sendToDisplay2(String("jair.bco=") + String(gaugeColorOK));
      }
     else if (vAIR >=60 && vAIR <= 90){
      sendToDisplay2(String("jair.bco=") + String(gaugeColorAlert));  
      }
      else {
      sendToDisplay2(String("jair.bco=") + String(gaugeColorCritical));  
      }  
      //Numbers
      String strIntakeAir = String(IntakeAir,0);
      strIntakeAir += "/";
      strIntakeAir += String(IntakeAirTot,0);
      sendToDisplay2(String("tair.txt=\"") + String(strIntakeAir)+String("\""));                   
  }

  sendToDisplay2(String("tair.txt=\"") + String(strSOI)+String("\"")); 
  sendToDisplay2(String("txe.txt=\"") + String(DataAlt)+String("\""));    
  }  
          
}
       
