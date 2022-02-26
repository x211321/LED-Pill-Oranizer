#define max_connection_time 10

const char *ap_ssid = "PillBox";
const char *ap_pass = "";
const char *ap_host = "pillbox";


void init_network()
{
  int connection_time = 0;
  bool connection_failed  = false;
  
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  delay(100);
  
  if (get_setting("wifiSSID").length()) {
    debug("Connecting to " + get_setting("wifiSSID"));
    debug(" ...");

    WiFi.hostname(ap_host);
    WiFi.begin(get_setting("wifiSSID"), get_setting("wifiPass"));
  
    while (WiFi.status() != WL_CONNECTED && !connection_failed) {
      delay(1000);
      debug(".", true);

      connection_time++;

      if (connection_time == max_connection_time) {
        connection_failed = true;
      }
    }

    debug("");
  }

  if (get_setting("wifiSSID").length() && !connection_failed) {
    debug("Connection established!");
    debug("IP address: " + String(WiFi.localIP()[0]) + "." + 
                           String(WiFi.localIP()[1]) + "." + 
                           String(WiFi.localIP()[2]) + "." + 
                           String(WiFi.localIP()[3]));
  }else{
    debug("Could not connect to WiFi");
    debug("Switching to access point mode");
    network_access_point_mode();
  }
}


void network_access_point_mode() {
  WiFi.disconnect();

  IPAddress ap_ip(192,168,1,1);
  IPAddress ap_gateway(1,2,3,1);
  IPAddress ap_subnet(255,255,255,0);

  WiFi.softAPConfig(ap_ip, ap_gateway, ap_subnet);
  WiFi.softAP(ap_ssid, ap_pass);

  debug("Access Point " + String(ap_ssid) + " started");
  debug("IP address: " + String(WiFi.softAPIP()[0]) + "." + 
                         String(WiFi.softAPIP()[1]) + "." + 
                         String(WiFi.softAPIP()[2]) + "." + 
                         String(WiFi.softAPIP()[3]));
}
