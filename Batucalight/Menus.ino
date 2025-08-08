/***************************************
Programme de test
****************************************/
void TEST() {  
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  
  FastLED.show();
}