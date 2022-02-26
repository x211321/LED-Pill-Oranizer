
void debug(String debugstring, bool noLineBreak = false) {
  if (debug_output) {
    if (!noLineBreak) {
      Serial.println(debugstring);
    }else{
      Serial.print(debugstring);
    }
  }
}
