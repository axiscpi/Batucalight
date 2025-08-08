/***************************************
CHENILLARD_XXX_YYY : Chenillard XXX sur fond YYY
Utilise les 2 premières couleurs de la palette
****************************************/

void CHENILLARD() {
  for(int dot = 0; dot < NUMLEDS; dot++) {
    if (EtatInt == 1 ) break ;
    index = 16 ;
    leds(dot,dot+LongChen-1) = ColorFromPalette(currentPalette, index) ;
    if ((dot+LongChen) > NUMLEDS) {
      index = 16 ;
      leds[dot+LongChen-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    SETPARALUM();
    FastLED.setBrightness(LUMINOSITE);
    FastLED.show();
    index = 0 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;                  // clear this led for the next time around the loop
    delay((PARAMETRE/2)+15);
  }
}