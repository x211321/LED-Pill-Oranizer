DynamicJsonDocument settings(1024);

void settings_save()
{
  String settings_json;
  serializeJson(settings, settings_json);
  
  if (file_write("/settings.json", settings_json)) {
    debug("Settings save OK");
    debug(settings_json);

    // Apply new Settings
    schedule_set_leds();
    led_set_brightness(get_setting("ledBrightness").toInt());
  }else{
    debug("Settings save FAILED");
  }
}


void settings_load()
{
  String settings_json;

  settings_json = file_read("/settings.json");

  if (settings_json.length() > 0) {
    debug("Settings load OK");
    debug(settings_json);
  }else{
    debug("Settings load FAILED");
  }

  deserializeJson(settings, settings_json);
}

String get_setting(String key)
{
  if (settings.containsKey(key)) {
    return String(settings[key]);
  }else{
    return "";
  }
}

void set_setting(String key, String value)
{
  settings[key] = value;
}

void settings_reset()
{
  settings.clear();
}
