/***************************************
Roue : 6 couleurs tournants en face à face
****************************************/

void ROUE() {
  SETPARALUM(); 
  for(int dot = 0; dot < NUMLEDS; dot++) {
    if (EtatInt == 1 || IntRF == 1) break ;

    index = 0 ;
    leds(dot,dot+(NUMLEDS/6)-1) = ColorFromPalette(currentPalette, index) ;
    if ((dot+(NUMLEDS/6)) > NUMLEDS) {
      index = 0 ;
      leds[dot+(NUMLEDS/6)-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 16 ;
    leds(dot+(NUMLEDS/6),dot+(NUMLEDS/3)-1) = ColorFromPalette(currentPalette, index) ;
    if ((dot+(NUMLEDS/3)) > NUMLEDS) {
      index = 16 ;
      leds[dot+(NUMLEDS/3)-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 32 ;
    leds(dot+(NUMLEDS/3),dot+(NUMLEDS*3/6)-1) = ColorFromPalette(currentPalette, index);
    if ((dot+(NUMLEDS*3/6)) > NUMLEDS) {
      index = 32 ;
      leds[dot+(NUMLEDS*3/6)-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 48 ;
    leds(dot+(NUMLEDS*3/6),dot+(NUMLEDS*4/6)-1) = ColorFromPalette(currentPalette, index);
    if ((dot+(NUMLEDS*4/6)) > NUMLEDS) {
      index = 48 ;
      leds[dot+(NUMLEDS*4/6)-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 64 ;
    leds(dot+(NUMLEDS*4/6),dot+(NUMLEDS*5/6)-1) = ColorFromPalette(currentPalette, index);
    if ((dot+(NUMLEDS*5/6)) > NUMLEDS) {
      index = 64 ;
      leds[dot+(NUMLEDS*5/6)-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 80 ;
    leds(dot+(NUMLEDS*5/6),dot+NUMLEDS-1) = ColorFromPalette(currentPalette, index);
    if ((dot+NUMLEDS) > NUMLEDS) {
      index = 80 ;
      leds[dot+NUMLEDS-1-NUMLEDS] = ColorFromPalette(currentPalette, index) ;
    }
    SETPARALUM();
    FastLED.setBrightness(LUMINOSITE);
    FastLED.show();
    index = 0 ;
    delay((PARAMETRE/2)+15);
  }
}