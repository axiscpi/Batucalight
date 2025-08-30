/***************************************
WAVE : Battement entre les couleurs de la palette
Utilise la totalité des couleurs de la palette
****************************************/

void WAVE() {
  SETPARALUM();
  for (index = 0; index <= 80 ; index = index + 16) {
    if (EtatInt == 1 || IntRF == 1) break ;
    for(int dot = 0; dot < NUMLEDS; dot++) { 
      leds[dot] = ColorFromPalette(currentPalette, index);
    }
    if (EtatInt == 1 || IntRF == 1) break ;
    SETPARALUM();
    for(int Cycle = 0; Cycle < 254 ; Cycle++) { 
     FastLED.setBrightness(Cycle*LUMINOSITE/255);
      SETPARALUM();
    if (EtatInt == 1 || IntRF == 1) break ;
     FastLED.show();
     delay(PARAMETRE/25);
    }
    if (EtatInt == 1 || IntRF == 1) break ;
    SETPARALUM();
    for(int Cycle = 255; Cycle > 0 ; Cycle--) { 
      FastLED.setBrightness(Cycle*LUMINOSITE/255);
      SETPARALUM();
    if (EtatInt == 1 || IntRF == 1) break ;
      FastLED.show();
      delay(PARAMETRE/25);
    }
  }
}