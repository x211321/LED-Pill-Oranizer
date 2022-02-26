HTTPClient http;
WiFiClient wifiClient;

String http_get(String url)
{
  int statusCode = 0;

  url.replace(" ", "+");

  http.begin(wifiClient, url.c_str());

  debug("HTTP GET: " + url);

  statusCode = http.GET();

  if (statusCode == 200) {
    debug("HTTP GET OK");
    debug("Payload: ");
    debug(http.getString());

    return http.getString();
  }else{
    debug("HTTP GET FAILED");
  }

  http.end();
}
