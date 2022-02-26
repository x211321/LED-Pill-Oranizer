#define LED_PIN D8
#define LED_COUNT 28

Adafruit_NeoPixel led_strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN);

void init_led() 
{
  byte brightness = get_setting("ledBrightness").toInt();

  if (brightness == 0) {
    brightness = 30;
  }
  
  led_strip.begin();
  led_set_brightness(brightness);
  led_reset();
}


void led_show()
{
  led_strip.show();
}


void led_set_brightness(byte brightness)
{
  led_strip.setBrightness(brightness);
  led_show();
}


void led_reset()
{
  led_set_all(0, 0, 0);
}


void led_set_all(byte r, byte g, byte b)
{
  for (int i = 0; i < LED_COUNT; i++) {
    led_set_pixel(i, r, g, b);
  }
}


void led_set_all(String hexColor)
{
  led_set_all(led_get_r_from_hex_string(hexColor),
              led_get_g_from_hex_string(hexColor),
              led_get_b_from_hex_string(hexColor));
}


void led_set_pixel(int pixel, byte r, byte g, byte b)
{
  led_strip.setPixelColor(pixel, led_strip.Color(r, g, b));
}


void led_set_pixel(int pixel, String hexColor)
{
  led_set_pixel(pixel,
                led_get_r_from_hex_string(hexColor),
                led_get_g_from_hex_string(hexColor),
                led_get_b_from_hex_string(hexColor));
}


byte led_get_r_from_hex_string(String hexString)
{
  return strtoul(("0x" + led_get_section_from_hex_string(hexString, 0, 2)).c_str(), NULL, 0);
}


byte led_get_g_from_hex_string(String hexString)
{
  return strtoul(("0x" + led_get_section_from_hex_string(hexString, 2, 4)).c_str(), NULL, 0);
}


byte led_get_b_from_hex_string(String hexString)
{
  return strtoul(("0x" + led_get_section_from_hex_string(hexString, 4, 6)).c_str(), NULL, 0);
}


String led_get_section_from_hex_string(String hexString, int sectionStart, int sectionEnd)
{
  int offset = 0;
  
  if (hexString.length() >= 6) {
    if (hexString.substring(0, 1) == "#") {
      offset = 1;
    }

    return hexString.substring(sectionStart+offset, sectionEnd+offset);
  }
}

void led_chase_animation()
{
  while (true) {
    for (int i = 0; i <= LED_COUNT; i++) {
      led_set_pixel(i, 255, 0, 0);
      led_set_pixel(i-1, 0, 255, 0);
      led_set_pixel(i-2, 0, 0, 255);
      led_set_pixel(i-3, 0, 0, 0);
  
      led_show();
  
      delay(100);
    }
  
    for (int i = LED_COUNT; i >= 0; i--) {
      led_set_pixel(i, 255, 0, 0);
      led_set_pixel(i+1, 0, 255, 0);
      led_set_pixel(i+2, 0, 0, 255);
      led_set_pixel(i+3, 0, 0, 0);
  
      led_show();
  
      delay(100);
    }
  }
}
