
#include "ESP8266WiFi.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm

const int displayEnc=1;// set to 1 to display Encryption or 0 not to display

void setup() {
  Serial.begin(115200);
  Serial.println("Robojax Wifi Signal Scan");
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);

  Serial.println("Setup done");
}

void loop() {

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("0 0");
  } else {
    char *ret;
    const char *tmp = "incz2137_";
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found

      char a[10];
      int len_ssid=sizeof(WiFi.SSID(i));
  
      for(int j=0;j<len_ssid;j++){
        a[j]=WiFi.SSID(i)[j];
      }

    ret = strstr(a, tmp);
    if (ret){
    
      Serial.print(WiFi.SSID(i));
      Serial.print(": ");
      Serial.print(WiFi.RSSI(i));
      if(WiFi.RSSI(i)>-10)
      Serial.print(" ");
      Serial.print("\n");
    }
      delay(10);
    }

  }
  // Wait a bit before scanning again
  delay(500);
  WiFi.scanDelete();  
}// loop
