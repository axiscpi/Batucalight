/***************************************
Programme de test
****************************************/

void TEST() {
  /*for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index);
  } 
  FastLED.setBrightness(analogRead(POTLUM)/4); 
  FastLED.show();
*/
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    index = 0 ;
    leds(dot,dot+LongChen-1) = ColorFromPalette(currentPalette, index);
    if ((dot+LongChen) > NUM_LEDS) {
      index = 0 ;
      leds[dot+LongChen-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    FastLED.setBrightness(analogRead(POTLUM)/4);
    FastLED.show();
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*10)+10);
  }

  FastLED.setBrightness(analogRead(POTLUM)/4) ;
  FastLED.show();
  
  //Serial.println(analogRead(POTLUM)/4); // Debug
  //Serial.println(PALETTE) ;             // Debug
  //delay (5) ;                           // Debug
}


/***************************************
"SOLIDX" : Couleur fixe
****************************************/

void SOLID1() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 0 ;   // Couleur 1 de la palette en cours
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  FastLED.setBrightness(analogRead(POTLUM)/4);
  FastLED.show();
}

void SOLID2() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 16 ;  // Couleur 2 de la palette en cours
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  FastLED.setBrightness(analogRead(POTLUM)/4);
  FastLED.show();
}

/***************************************
CHENILLARD_XXX_YYY : Chenillard XXX sur fond YYY
****************************************/

void CHENILLARD() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {               // A verifier si necessaire jusqu'à ...
    index = 0 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;
  } 
  FastLED.setBrightness(analogRead(POTLUM)/4); 
  FastLED.show();                                         //...ici.

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    index = 16 ;
    leds(dot,dot+LongChen-1) = ColorFromPalette(currentPalette, index) ;
    if ((dot+LongChen) > NUM_LEDS) {
      index = 16 ;
      leds[dot+LongChen-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    FastLED.setBrightness(analogRead(POTLUM)/4);
    FastLED.show();
    index = 0 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*10)+10);
  }
}

void CHENILLARD_INV() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Gold;
  } 
  FastLED.setBrightness(analogRead(POTLUM)/4); 
  FastLED.show();

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    index = 0 ;
    leds(dot,dot+LongChen-1) = ColorFromPalette(currentPalette, index);
    if ((dot+LongChen) > NUM_LEDS) {
      index = 0 ;
      leds[dot+LongChen-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    FastLED.setBrightness(analogRead(POTLUM)/4);
    FastLED.show();
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*10)+10);
  }
}

/***************************************
CONTRECHENILLARD : Chenillard dans l'autre sens
****************************************/

void CONTRECHENILLARD() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
   leds[dot] = CRGB::Red;
 }  
 FastLED.setBrightness(analogRead(POTLUM)/4);
 FastLED.show();
  for(int dot = NUM_LEDS-1; dot >= 0; dot--) {
   if (EtatInt == 1 ) break ;
   leds(dot,dot+LongChen-1) = CRGB::Green;
   if ((dot+LongChen) > NUM_LEDS) {
     leds(0,dot+LongChen-1-NUM_LEDS) = CRGB::Green;
   }
   FastLED.setBrightness(analogRead(POTLUM)/4);
   FastLED.show();
   leds[dot+LongChen-1] = CRGB::Red ;                  // clear this led for the next time around the loop
   if ((dot+LongChen) > NUM_LEDS) {
      leds(0,dot+LongChen-1-NUM_LEDS) = CRGB::Red;
   }
   SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
   delay(SpeedWAVE*8);
  }
}

/***************************************
FACE_A_FACE : 2 demi cercles tournants face à face
****************************************/
void FACE_A_FACE() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  FastLED.setBrightness(analogRead(POTLUM)/4);  
  FastLED.show();

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    index = 0 ;
    leds(dot,dot+(NUM_LEDS/2)-1) = ColorFromPalette(currentPalette, index) ;
    if ((dot+(NUM_LEDS/2)) > NUM_LEDS) {
      index = 0 ;
      leds[dot+(NUM_LEDS/2)-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    FastLED.setBrightness(analogRead(POTLUM)/4);
    FastLED.show();
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*12+10));
  }
}

/***************************************
WAVE : Battement entre les couleurs de la palette
****************************************/
void WAVE() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 0 ;
    leds[dot] = ColorFromPalette(currentPalette, index);
  }
  for(int Brightness = 0; Brightness < 100; Brightness++) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show();
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
  for(int Brightness = 100; Brightness > 0; Brightness--) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }

  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 16 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;
  }
  for(int Brightness = 0; Brightness < 100; Brightness++) {
    if (EtatInt == 1 ) break ; 
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
  for(int Brightness = 100; Brightness > 0; Brightness--) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }

  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 32 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;
  }
  for(int Brightness = 0; Brightness < 100; Brightness++) {
    if (EtatInt == 1 ) break ; 
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
  for(int Brightness = 100; Brightness > 0; Brightness--) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }

  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    index = 48 ;
    leds[dot] = ColorFromPalette(currentPalette, index) ;
  }
  for(int Brightness = 0; Brightness < 100; Brightness++) {
    if (EtatInt == 1 ) break ; 
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
  for(int Brightness = 100; Brightness > 0; Brightness--) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
}

/***************************************
SPECTRE : Choix d'une couleur HUE solide selon potard
****************************************/
void SPECTRE() {
  SpectreColor = (analogRead(POTFUNC)/4) ;
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot].setHue(SpectreColor) ;
  }
  FastLED.setBrightness(analogRead(POTLUM)/4);
  FastLED.show();
  delay(5);
}

/***************************************
QUATRE_QUARTS : 4 quarts de cercles tournants en face à face
****************************************/
void QUATRE_QUARTS() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    index = 0 ;
    leds(dot,dot+(NUM_LEDS/4)-1) = ColorFromPalette(currentPalette, index);
    if ((dot+(NUM_LEDS/4)) > NUM_LEDS) {
      index = 0 ;
      leds[dot+(NUM_LEDS/4)-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 16 ;
    leds(dot+(NUM_LEDS/4),dot+(NUM_LEDS/2)-1) = ColorFromPalette(currentPalette, index) ;
    if ((dot+(NUM_LEDS/2)) > NUM_LEDS) {
      index = 16 ;
      leds[dot+(NUM_LEDS/2)-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 32 ;
    leds(dot+(NUM_LEDS/2),dot+(NUM_LEDS*3/4)-1) = ColorFromPalette(currentPalette, index);
    if ((dot+(NUM_LEDS*3/4)) > NUM_LEDS) {
      index = 32 ;
      leds[dot+(NUM_LEDS*3/4)-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    index = 48 ;
    leds(dot+(NUM_LEDS*3/4),dot+NUM_LEDS-1) = ColorFromPalette(currentPalette, index);
    if ((dot+NUM_LEDS) > NUM_LEDS) {
      index = 48 ;
      leds[dot+NUM_LEDS-1-NUM_LEDS] = ColorFromPalette(currentPalette, index) ;
    }
    FastLED.setBrightness(analogRead(POTLUM)/4);
    FastLED.show();
    SpeedWAVE = (analogRead(POTFUNC) * 15 / 1024) ;
    delay((SpeedWAVE*12+10));
  }
}
