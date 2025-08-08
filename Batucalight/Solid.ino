/***************************************
"SOLID" : Couleur fixe
Utilise les 6 premières couleurs de la palette
****************************************/

void SOLID() {
  SETPARALUM();
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    if (PARAMETRE >= 0 && PARAMETRE < 43) index = 0 ;
    if (PARAMETRE >= 43 && PARAMETRE < 85) index = 16 ;
    if (PARAMETRE >= 85 && PARAMETRE < 128) index = 32 ;
    if (PARAMETRE >= 128 && PARAMETRE < 170) index = 48 ;
    if (PARAMETRE >= 170 && PARAMETRE < 213) index = 64 ;
    if (PARAMETRE >= 213 && PARAMETRE < 256) index = 80 ;
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  FastLED.setBrightness(LUMINOSITE);
  FastLED.show();
}