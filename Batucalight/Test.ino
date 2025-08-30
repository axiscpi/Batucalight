/***************************************
Programme de test
****************************************/
void TEST() {
  index=0;
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  FastLED.setBrightness(LUMINOSITE);
  for (index = 0; index <= 80 ; index = index + 16) {
    for(int dot = 0; dot < NUMLEDS; dot++) {
      if (EtatInt == 1 || IntRF == 1 ) break ;
      //index = 16 ;
      leds(dot,dot+LongChen-1) = ColorFromPalette(currentPalette, index) ;
      //if ((dot+LongChen) > NUMLEDS) {
      //  index = 16 ;
      //  leds[dot+LongChen-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
      //}
      SETPARALUM();
      FastLED.setBrightness(LUMINOSITE);
      FastLED.show();
      //index = 0 ;
      leds[dot] = ColorFromPalette(currentPalette, index+16) ;                  // clear this led for the next time around the loop
      delay((PARAMETRE/2)+15);
    }
  }
}