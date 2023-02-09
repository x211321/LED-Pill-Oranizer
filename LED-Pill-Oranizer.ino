#define debug_output true

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
#include <ESP_Mail_Client.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "pitches.h"

void setup()
{
  // Prepare serial communication
  init_serial();

  // Prepare file system
  init_file_system();

  // Load settings
  settings_load();

  // Init date time
  init_date_time();

  // Connect to network
  init_network();

  // Init notifications
  init_notification();

  // Start web server
  init_web_server();

  // Play melody
  sound_play_melody();

  // Init LEDs
  init_led();

  // Init Button
  init_button();

  // Init schedule
  init_schedule();
}



void loop()
{
  // Handle web server requests
  web_server_handle_client();

  // Handle intake schedule
  schedule_handle_intake();

  //Serial.println(ESP.getFreeHeap());

  delay(100);
}
