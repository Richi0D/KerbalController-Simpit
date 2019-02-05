//input variables
float DataAP;
float DataPE;
long DataAPTime;
long DataPETime;
float DataAlt; 
float DataRAlt;
float Vsurf;
float VVI;
float VOrbit;
float MachNumber;
long DataTargetDist;
float TargetV;     
String strSOINumber;

void get_vessel_data() {
    now = millis();
    deadtime = now - deadtimeOld; 
    if (deadtime > IDLETIMER){
      receivedata = false;
    }
            
    if (receivedata){
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
      displayTime = now - displayTimeOld;
      if (displayTime > DISPLAYREFRESH) {
        displayTimeOld = now;
        define_vessel_data_display();   //define what to do with the data below
      }
    }
    else  { //if no message received for a while, go idle
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

//define what to do with the vessel data here, e.g. turn on LED's, display text on the LCD
void define_vessel_data_display() {

//AtmosphereGauge(VData.Density);   //call Atmosphere gauge

//Orbit Data Page2
  if (PageDisplay1==2){
//Apoapsis
    String strApo = "";
    //float DataAP = myApsides.apoapsis; 
    if (DataAP < 1000000 && DataAP > -1000000) {
      strApo += String(DataAP,0);
      strApo += "m";
    } else if ((DataAP >= 1000000 && DataAP < 1000000000) || (DataAP <= -1000000 && DataAP > -1000000000)) {
      strApo += String((DataAP / 1000),0);
      strApo += "km";
    } else if ((DataAP >= 1000000000 && DataAP < 1000000000000) || (DataAP <= -1000000000 && DataAP > -1000000000000)) {
      strApo += String((DataAP / 1000000),0);
      strApo += "Mm";
    } else {
      strApo += String((DataAP / 1000000000),0);
      strApo += "Gm";
    }
    sendToDisplay1(String("APHV.txt=\"") + String(strApo)+String("\""));
    
//Periapsis
    String strPeri = "";
    //float DataPE = myApsides.periapsis;
    if (DataPE < 1000000 && DataPE > -1000000) {
      strPeri += String(DataPE,0);
      strPeri += "m";
    } else if ((DataPE >= 1000000 && DataPE < 1000000000) || (DataPE <= -1000000 && DataPE > -1000000000)) {
      strPeri += String((DataPE / 1000),0);
      strPeri += "km";
    } else if ((DataPE >= 1000000000 && DataPE < 1000000000000) || (DataPE <= -1000000000 && DataPE > -1000000000000)) {
      strPeri += String((DataPE / 1000000),0);
      strPeri += "Mm";
    } else {
      strPeri += String((DataPE / 1000000000),0);
      strPeri += "Gm";
    }
    sendToDisplay1(String("PEHV.txt=\"") + String(strPeri)+String("\""));
// Time to Apoapsis
    String strApotime = "";
    long secondsAP=0;
    long minutesAP=0;
    long hoursAP=0;
    if (DataAPTime < 60 && DataAPTime > -60){
      strApotime += String(DataAPTime); 
      strApotime += "s";
    } else if ((DataAPTime >= 60 && DataAPTime < 3600) || (DataAPTime <= -60 && DataAPTime > -3600)) {
      secondsAP = DataAPTime % 60;
      minutesAP = DataAPTime / 60;
      strApotime += String(minutesAP);
      strApotime += "m";
      strApotime += String(secondsAP);
      strApotime += "s";
    } else {
      secondsAP = DataAPTime % 60;
      minutesAP = DataAPTime /60;
      hoursAP = minutesAP / 60;
      minutesAP = minutesAP % 60;
      strApotime += String(hoursAP);
      strApotime += "h";     
      strApotime += String(minutesAP);
      strApotime += "m";
      strApotime += String(secondsAP);
      strApotime += "s";
    }
    sendToDisplay1(String("APTV.txt=\"") + String(strApotime)+String("\""));
// Time to Periapsis
    String strPeritime = "";
    long secondsPE=0;
    long minutesPE=0;
    long hoursPE=0;
    if (DataPETime < 60 && DataPETime > -60){
      strPeritime += String(DataPETime); 
      strPeritime += "s";
    } else if ((DataPETime >= 60 && DataPETime < 3600) || (DataPETime <= -60 && DataPETime > -3600)) {
      secondsPE = DataPETime % 60;
      minutesPE = DataPETime / 60;
      strPeritime += String(minutesPE);
      strPeritime += "m";
      strPeritime += String(secondsPE);
      strPeritime += "s";
    } else {
      secondsPE = DataPETime % 60;
      minutesPE = DataPETime /60;
      hoursPE = minutesPE / 60;
      minutesPE = minutesPE % 60;
      strPeritime += String(hoursPE);
      strPeritime += "h";     
      strPeritime += String(minutesPE);
      strPeritime += "m";
      strPeritime += String(secondsPE);
      strPeritime += "s";
    }
    sendToDisplay1(String("PETV.txt=\"") + String(strPeritime)+String("\""));
// Orbital Speed
    String strOrbitalSpeed = "";
    strOrbitalSpeed += String(VOrbit);
    strOrbitalSpeed += "m/s"; 
    sendToDisplay1(String("ORSV.txt=\"") + String(strOrbitalSpeed)+String("\""));         
 }
 
//Surface Data Page3
  if (PageDisplay1==3){
//Altidude Sealevel
    String strAltSea = "";
    if (DataAlt < 1000000 && DataAlt > -1000000) {
      strAltSea += String(DataAlt);
      strAltSea += "m";
    } else if ((DataAlt >= 1000000 && DataAlt < 1000000000) || (DataAlt <= -1000000 && DataAlt > -1000000000)) {
      strAltSea += String((DataAlt / 1000.0));
      strAltSea += "km";
    } else if ((DataAlt >= 1000000000 && DataAlt < 1000000000000) || (DataAlt <= -1000000000 && DataAlt > -1000000000000)) {
      strAltSea += String((DataAlt / 1000000.0));
      strAltSea += "Mm";
    } else {
      strAltSea += String((DataAlt / 1000000000.0));
      strAltSea += "Gm";
    }
    sendToDisplay1(String("ALSV.txt=\"") + String(strAltSea)+String("\""));

//Altidude Terrain
    String strAltTerrain = "";
    if (DataRAlt < 1000000 && DataRAlt > -1000000) {
      strAltTerrain += String(DataRAlt);
      strAltTerrain += "m";
    } else if ((DataRAlt >= 1000000 && DataRAlt < 1000000000) || (DataRAlt <= -1000000 && DataRAlt > -1000000000)) {
      strAltTerrain += String((DataRAlt / 1000.0));
      strAltTerrain += "km";
    } else if ((DataRAlt >= 1000000000 && DataRAlt < 1000000000000) || (DataRAlt <= -1000000000 && DataRAlt > -1000000000000)) {
      strAltTerrain += String((DataRAlt / 1000000.0));
      strAltTerrain += "Mm";
    } else {
      strAltTerrain += String((DataRAlt / 1000000000.0));
      strAltTerrain += "Gm";
    }
    sendToDisplay1(String("ALTV.txt=\"") + String(strAltTerrain)+String("\""));
    
// Surface Speed
    String strSurfaceSpeed = "";
    strSurfaceSpeed += String(Vsurf,0);
    strSurfaceSpeed += "m/s"; 
    sendToDisplay1(String("SUSV.txt=\"") + String(strSurfaceSpeed)+String("\"")); 

// Vertical Speed
    String strVerticalSpeed = "";
    strVerticalSpeed += String(VVI,0);
    strVerticalSpeed += "m/s"; 
    sendToDisplay1(String("VESV.txt=\"") + String(strVerticalSpeed)+String("\""));    

// Horizontal Speed
    String strHorizontalSpeed = "";
    long hV = sqrt((pow(Vsurf,2) - pow(VVI,2)));
    strHorizontalSpeed += String(hV);
    strHorizontalSpeed += "m/s"; 
    sendToDisplay1(String("HOSV.txt=\"") + String(strHorizontalSpeed)+String("\"")); 

// Mach Number
    String strMach = "";
    strMach += String(MachNumber);
    strMach += ""; 
    sendToDisplay1(String("MACV.txt=\"") + String(strMach)+String("\"")); 
  }
  
//Target/Node Data Page4
  if (PageDisplay1==4){
// Distance to targeted vessel
    String strDistanceVessel = "";
    if (DataTargetDist < 1000000 && DataTargetDist > -1000000) {
      strDistanceVessel += String(DataTargetDist);
      strDistanceVessel += "m";
    } else if ((DataTargetDist >= 1000000 && DataTargetDist < 1000000000) || (DataTargetDist <= -1000000 && DataTargetDist > -1000000000)) {
      strDistanceVessel += String((DataTargetDist / 1000.0));
      strDistanceVessel += "km";
    } else if ((DataTargetDist >= 1000000000 && DataTargetDist < 1000000000000) || (DataTargetDist <= -1000000000 && DataTargetDist > -1000000000000)) {
      strDistanceVessel += String((DataTargetDist / 1000000.0));
      strDistanceVessel += "Mm";
    } else {
      strDistanceVessel += String((DataTargetDist / 1000000000.0));
      strDistanceVessel += "Gm";
    }
    sendToDisplay1(String("DITV.txt=\"") + String(strDistanceVessel)+String("\""));

// Target relative Speed
    String strTargetSpeed = "";
    strTargetSpeed += String(TargetV,0);
    strTargetSpeed += "m/s"; 
    sendToDisplay1(String("RESV.txt=\"") + String(strTargetSpeed)+String("\""));  
  }
  
//Body Data Page5
  if (PageDisplay1==5){
// SOI Number
    //100 = KERBOL
    //110 = MOHO
    //120 = EVE
    //121 = GILLY
    //130 = KERBIN
    //131 = MUN
    //132 = MINMUS
    //140 = DUNA
    //141 = IKE
    //150 = DRES
    //160 = JOOL
    //161 = LAYTHE
    //162 = VALL
    //163 = TYLO
    //164 = BOP
    //165 = POL
    //170 = EELOO
    String strSafeAltidude = "-";
    String strHighAtmosphere = "-";
    String strLowSpace = "-";
    String strHighSpace = "-";
    String strSynchrounousAlt = "-";
    String strSOIAlt = "-";
    String strRotationPeriod = "-";
    String strEscapeVelocity = "-";
    String strBody = "-";  
if (strSOINumber == "Kerbin"){strSOINumber = "130";}

    if (strSOINumber == "100"){
     strSafeAltidude = "2065Mm";
     strHighAtmosphere = "18000m";
     strLowSpace = "600000m";
     strHighSpace = "1000Mm";
     strSynchrounousAlt = "1508Mm";
     strSOIAlt = "-";
     strRotationPeriod = "20d0h0m0s";
     strEscapeVelocity = "94672m/s";
     strBody = "KERBOL";
    }
    else if (strSOINumber == "110"){
     strSafeAltidude = "8000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "80000m";
     strSynchrounousAlt = "18173km";
     strSOIAlt = "9647km";
     strRotationPeriod = "56d0h6m40s";
     strEscapeVelocity = "1161m/s";
     strBody = "MOHO";      
    }
    else if (strSOINumber == "120"){
     strSafeAltidude = "90000m";
     strHighAtmosphere = "22000m";
     strLowSpace = "90000m";
     strHighSpace = "400000m";
     strSynchrounousAlt = "10328km";
     strSOIAlt = "85109km";
     strRotationPeriod = "3d4h21m40s";
     strEscapeVelocity = "4832m/s";
     strBody = "EVE";      
    }
    else if (strSOINumber == "121"){
     strSafeAltidude = "7000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "6000m";
     strSynchrounousAlt = "42138m";
     strSOIAlt = "126123m";
     strRotationPeriod = "1d1h50m55s";
     strEscapeVelocity = "36m/s";
     strBody = "GILLY";      
    }
    else if (strSOINumber == "130"){
     strSafeAltidude = "70000m";
     strHighAtmosphere = "18000m";
     strLowSpace = "70000m";
     strHighSpace = "250000m";
     strSynchrounousAlt = "2863km";
     strSOIAlt = "84159km";
     strRotationPeriod = "5h59m9s";
     strEscapeVelocity = "3431m/s";
     strBody = "KERBIN";      
    }
    else if (strSOINumber == "131"){
     strSafeAltidude = "8000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "60000m";
     strSynchrounousAlt = "2971km";
     strSOIAlt = "2430km";
     strRotationPeriod = "6d2h36m24s";
     strEscapeVelocity = "807m/s";
     strBody = "MUN";      
    }
    else if (strSOINumber == "132"){
     strSafeAltidude = "6000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "30000m";
     strSynchrounousAlt = "357941m";
     strSOIAlt = "2247km";
     strRotationPeriod = "1d5h13m20s";
     strEscapeVelocity = "243m/s";
     strBody = "MINMUS";      
    }
    else if (strSOINumber == "140"){
     strSafeAltidude = "50000m";
     strHighAtmosphere = "12000m";
     strLowSpace = "50000m";
     strHighSpace = "140000m";
     strSynchrounousAlt = "2880km";
     strSOIAlt = "47922km";
     strRotationPeriod = "3d0h11m58s";
     strEscapeVelocity = "1372m/s";
     strBody = "DUNA";      
    }
    else if (strSOINumber == "141"){
     strSafeAltidude = "14000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "50000m";
     strSynchrounousAlt = "1134km";
     strSOIAlt = "1050km";
     strRotationPeriod = "3d0h11m58s";
     strEscapeVelocity = "534m/s";
     strBody = "IKE";      
    }
    else if (strSOINumber == "150"){
     strSafeAltidude = "6000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "25000m";
     strSynchrounousAlt = "732244m";
     strSOIAlt = "32833km";
     strRotationPeriod = "1d3h40m0s";
     strEscapeVelocity = "558m/s";
     strBody = "DRES";      
    }
    else if (strSOINumber == "160"){
     strSafeAltidude = "200000m";
     strHighAtmosphere = "120000m";
     strLowSpace = "200000m";
     strHighSpace = "4000km";
     strSynchrounousAlt = "15011km";
     strSOIAlt = "2456Mm";
     strRotationPeriod = "1d4h0m0s";
     strEscapeVelocity = "9704m/s";
     strBody = "JOOL";      
    }
    else if (strSOINumber == "161"){
     strSafeAltidude = "50000m";
     strHighAtmosphere = "10000m";
     strLowSpace = "50000m";
     strHighSpace = "200000m";
     strSynchrounousAlt = "4686km";
     strSOIAlt = "3724km";
     strRotationPeriod = "2d2h43m1s";
     strEscapeVelocity = "2801m/s";
     strBody = "LAYTHE";      
    }
    else if (strSOINumber == "162"){
     strSafeAltidude = "9000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "90000m";
     strSynchrounousAlt = "3593km";
     strSOIAlt = "2406km";
     strRotationPeriod = "4d5h26m2s";
     strEscapeVelocity = "1176m/s";
     strBody = "VALL";      
    }
    else if (strSOINumber == "163"){
     strSafeAltidude = "12000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "250000m";
     strSynchrounousAlt = "14158km";
     strSOIAlt = "10857km";
     strRotationPeriod = "9d4h52m6s";
     strEscapeVelocity = "3069m/s";
     strBody = "TYLO";      
    }
    else if (strSOINumber == "164"){
     strSafeAltidude = "23000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "25000m";
     strSynchrounousAlt = "2588km";
     strSOIAlt = "1221km";
     strRotationPeriod = "25d1h15m7s";
     strEscapeVelocity = "246m/s";
     strBody = "BOP";      
    }
    else if (strSOINumber == "165"){
     strSafeAltidude = "6000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "22000m";
     strSynchrounousAlt = "2415km";
     strSOIAlt = "1042km";
     strRotationPeriod = "41d4h31m";
     strEscapeVelocity = "181m/s";
     strBody = "POL";      
    }
    else if (strSOINumber == "170"){
     strSafeAltidude = "5000m";
     strHighAtmosphere = "-";
     strLowSpace = "0m";
     strHighSpace = "60000m";
     strSynchrounousAlt = "683691m";
     strSOIAlt = "119083km";
     strRotationPeriod = "5h24m20s";
     strEscapeVelocity = "842m/s";
     strBody = "EELOO";      
    }
    else {
     strSafeAltidude = "-";
     strHighAtmosphere = "-";
     strLowSpace = "-";
     strHighSpace = "-";
     strSynchrounousAlt = "-";
     strSOIAlt = "-";
     strRotationPeriod = "-";
     strEscapeVelocity = "-";
     strBody = "-";      
    }                                           
    sendToDisplay1(String("SAAV.txt=\"") + String(strSafeAltidude)+String("\"")); 
    sendToDisplay1(String("HATV.txt=\"") + String(strHighAtmosphere)+String("\"")); 
    sendToDisplay1(String("LOSV.txt=\"") + String(strLowSpace)+String("\"")); 
    sendToDisplay1(String("HISV.txt=\"") + String(strHighSpace)+String("\"")); 
    sendToDisplay1(String("SYAV.txt=\"") + String(strSynchrounousAlt)+String("\"")); 
    sendToDisplay1(String("SOAV.txt=\"") + String(strSOIAlt)+String("\"")); 
    sendToDisplay1(String("ROPV.txt=\"") + String(strRotationPeriod)+String("\"")); 
    sendToDisplay1(String("ESVV.txt=\"") + String(strEscapeVelocity)+String("\"")); 
    sendToDisplay1(String("BODYV.txt=\"") + String(strBody)+String("\""));      
  }
       
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
