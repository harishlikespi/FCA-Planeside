#include <Wire.h> //Needed for I2C to GNSS

#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS
SFE_UBLOX_GNSS myGNSS;

long lastTime = 0; //Simple local timer. Limits amount if I2C traffic to u-blox module.

void setup()
{
  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal

  Wire.begin();

  if (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

   myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  //myGNSS.saveConfiguration();        //Optional: Save the current settings to flash and BBR
}

void loop()
{
  //Query module only every second. Doing it more often will just cause I2C traffic.
  //The module only responds when a new position is available
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    
    long latitude = myGNSS.getLatitude();
    Serial.print(F("{latDeg: "));
    Serial.print(latitude/1000000);

    long longitude = myGNSS.getLongitude();
    Serial.print(F(", lonDeg: "));
    Serial.print(longitude/1000000);
    Serial.println(F("}"));

    long speed = myGNSS.getGroundSpeed();
    Serial.print(F("{Speed: "));
    Serial.print(speed);
    Serial.println(F(" (mm/s)}"));

    long heading = myGNSS.getHeading();
    Serial.print(F("{Heading: "));
    Serial.print(heading);
    Serial.println(F(" (degrees * 10^-5)}"));

    long altitude = myGNSS.getAltitude();
    Serial.print(F("{Alt: "));
    Serial.print(altitude);
    Serial.println(F(" (mm)}"));

    Serial.print(F("{Date: "));
    Serial.print(myGNSS.getYear());
    Serial.print("-");
    Serial.print(myGNSS.getMonth());
    Serial.print("-");
    Serial.print(myGNSS.getDay());
    Serial.println(F("}"));
    Serial.print(F("{Time: "));
    Serial.print(myGNSS.getHour());
    Serial.print(":");
    Serial.print(myGNSS.getMinute());
    Serial.print(":");
    Serial.print(myGNSS.getSecond());
    Serial.println(F("}"));

    Serial.print(F("Time is "));
    if (myGNSS.getTimeValid() == false)
    {
      Serial.print(F("not "));
    }
    Serial.print(F("valid. Date is "));
    if (myGNSS.getDateValid() == false)
    {
      Serial.print(F("not "));
    }
    Serial.print(F("valid."));

    Serial.println();
  }
}
