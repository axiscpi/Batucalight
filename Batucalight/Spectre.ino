/***************************************
SPECTRE : Choix d'une couleur HUE solide selon potard
****************************************/

void SPECTRE() {
  SETPARALUM();
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot].setHue(PARAMETRE) ;
  }
  FastLED.setBrightness(LUMINOSITE);
  FastLED.show();
  delay(5);

}
