ESP8266WebServer web_server(80);

void init_web_server()
{
  web_server.on("/", web_server_root);
  web_server.on("/apply", web_server_apply);
  web_server.on("/load_settings.js", web_server_load_settings_js);
  web_server.on("/pillbox.js", web_server_pillbox_js);
  web_server.on("/style.css", web_server_style_css);
  web_server.on("/favicon.ico", web_server_favicon_ico);
  web_server.begin();

  debug("Web server started");
}


void web_server_handle_client()
{
  web_server.handleClient();
}


void web_server_root()
{
  String html;

  html = file_read("/web_server/index.html");

  web_server.send(200, "text/html", html);
}


void web_server_apply()
{
  for (int i = 0; i < web_server.args(); i++) {
    debug(String(web_server.argName(i)) + " : " + String(web_server.arg(web_server.argName(i))));
  }

  if (web_server.hasArg("save")) {
    web_server_save_settings();
  }

  if (web_server.hasArg("testMail")) {
    notification_send_mail(get_setting("notifyMail"), "PillBox Test-Mail", "Test der PillBox E-Mail Benachrichtigung erfolgreich!");  
  }

  if (web_server.hasArg("testSignal")) {
    notification_send_signal("Test der PillBox Signal Benachrichtigung erfolgreich!");  
  }

  if (web_server.hasArg("testIntake")) {
    static int testSchedule;

    testSchedule++;
    if (testSchedule > 4){
      testSchedule = 1;
    }

    schedule_update_time();
    schedule_create_new_intake(schedule_get_current_intake_id(), testSchedule);
  }

  if (web_server.hasArg("testFillTime")) {
    schedule_toggle_fill_time();
  }

  if (web_server.hasArg("testConfirm")) {
    schedule_confirm_last_state();
  }

  if (web_server.hasArg("testScheduleLEDs")) {
    schedule_test_leds();
  }
  
  web_server.send(200, "text/html", "");
}


void web_server_pillbox_js() 
{
  web_server_serve_file("/web_server/pillbox.js");
}


void web_server_style_css()
{
  web_server_serve_file("/web_server/style.css");
}


void web_server_favicon_ico()
{
  web_server_serve_file("/web_server/favicon.ico");
}


void web_server_serve_file(String file)
{
  String fileContent;

  fileContent = file_read(file);

  web_server.send(200, "text/css", fileContent);
}


void web_server_load_settings_js()
{
  String js;
  String settings_json;
  String key;
  String value;

  serializeJson(settings, settings_json);
  
  if (settings_json.length() > 0) {
    JsonObject settings_root = settings.as<JsonObject>();

    js += "document.addEventListener('DOMContentLoaded', function(){\n";

    for (JsonPair keyValue: settings_root) {
      key   = String(keyValue.key().c_str());
      value = String(keyValue.value().as<char*>());

      js += "\tvar element_" + key + "   = document.getElementById('" + key + "');\n";
      js += "\telement_" + key + ".value = '" + value + "';\n\n";
    }

    js += "});";
  }

  web_server.send(200, "text/javascript", js);
}


void web_server_save_settings()
{
  bool wifi_change = false;
  
  // Check for WiFi settings change
  if (web_server.hasArg("wifiSSID")) {
    if (web_server.arg("wifiSSID") != get_setting("wifiSSID")) {
      wifi_change = true;
    }
  }

  if (web_server.hasArg("wifiPass")) {
    if (web_server.arg("wifiPass") != get_setting("wifiPass")) {
      wifi_change = true;
    }
  }
  
  settings_reset();
  
  for (int i = 0; i < web_server.args(); i++) {
    set_setting(web_server.argName(i), web_server.arg(web_server.argName(i)));
  }

  settings_save();

  if (wifi_change) {
    init_network();
  }
}
