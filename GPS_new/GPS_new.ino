#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).

   Adapted from https://github.com/mikalhart/TinyGPSPlus/blob/master/examples/FullExample/FullExample.ino.
   All baud rates have been changed to 9600 where applicable.
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  //Serial.println(F("FullExample.ino"));
  //Serial.println(F("An extensive example of many interesting TinyGPS++ features"));
  //Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  //Serial.println(F("by Mikal Hart"));
  //Serial.println();
  //Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
  //Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
  //Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));
}

void loop()
{
  Serial.print("|GPS|");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.println();
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec) //Value, validity, length of supposed string (or asterisk placeholder), precision.
{
  if (!valid)
  {
    Serial.print(F("NO_ENCODE|"));
    //Serial.print(val, prec);
    //Serial.print(F("|"));
  }
  else
  {
    Serial.print(val, prec);
    Serial.print(F("|"));
  }
  smartDelay(0);
}
