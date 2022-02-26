void init_serial()
{
  Serial.begin(115200);
  delay(500);
  debug("");
  debug("Startup");
}
