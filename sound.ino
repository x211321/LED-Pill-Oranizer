#define SOUND_PIN D7

void sound_play_melody() {
  // notes in the melody:
  int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, NOTE_END
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

  for (int currentNote = 0; melody[currentNote] != NOTE_END; currentNote++) {
    int noteDuration = 1000 / noteDurations[currentNote];
    
    tone(SOUND_PIN, melody[currentNote], noteDuration);
    delay(noteDuration * 1.30);
    noTone(SOUND_PIN);
  }
}
