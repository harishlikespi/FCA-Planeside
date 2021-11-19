#include <Wire.h>
#include <SparkFun_Ublox_Arduino_Library.h> //http://librarymanager/All#SparkFun_Ublox_GPS

// GPS object
SFE_UBLOX_GPS myGPS; 

void setup() {

  Serial.begin(115200);

  // waiting for Serial to connect
  while(!Serial) yield(); 
  
  Wire.begin();

  // in the case that GPS fails to initialize
  if (myGPS.begin() == false) {
    Serial.println("No GPS detected.");
    while(1) delay(1000);      
  }

  myGPS.setI2COutput(COM_TYPE_UBX); 
  myGPS.saveConfiguration(); 

}

void loop() {

    if (myGPS.begin() == true) {

      float latitude = myGPS.getLatitude();
      latitude = latitude / 10000000;
      Serial.println("Latitude: ");
      Serial.print(latitude);

      float longitude = myGPS.getLongitude();
      longitude = longitude / 10000000;
      Serial.println("Longitude: ");
      Serial.print(longitude);

      float altitude = myGPS.getAltitude();
      Serial.println("Altitude: ");
      Serial.print(altitude);

      float speed = myGPS.getGroundSpeed();
      Serial.println("Speed (mm/s): ");
      Serial.print(speed);

      float time = myGPS.getTimeValid();
      Serial.println("Time: ");
      Serial.print(time);   

    }
}
