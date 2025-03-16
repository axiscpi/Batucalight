/***************************************
Programme de test
****************************************/

void TEST() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::White;
  }

  FastLED.setBrightness(analogRead(POT)/4) ;
  FastLED.show();
  
  Serial.println(analogRead(POT)/4);
  delay (5) ;
}


/***************************************
"COULEUR" : Couleur solide du nom du programme
****************************************/

void BLEU() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::DeepSkyBlue;
  }
  FastLED.show();
}

void GOLD() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Gold;
  }
  FastLED.show();
}

/***************************************
CHENILLARD_XXX_YYY : Chenillard XXX sur fond YYY
****************************************/

void CHENILLARD_JAUNE_BLEU() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::DeepSkyBlue;
  }  
  FastLED.show();

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    leds(dot,dot+LongChen-1) = CRGB::Gold;
    if ((dot+LongChen) > NUM_LEDS) {
      leds[dot+LongChen-1-NUM_LEDS] = CRGB::Gold ;
    }
    FastLED.show();
    leds[dot] = CRGB::DeepSkyBlue ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*10)+10);
  }
}

void CHENILLARD_BLEU_JAUNE() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Gold;
  }  
  FastLED.show();

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    leds(dot,dot+LongChen-1) = CRGB::DeepSkyBlue;
    if ((dot+LongChen) > NUM_LEDS) {
      leds[dot+LongChen-1-NUM_LEDS] = CRGB::DeepSkyBlue ;
    }
    FastLED.show();
    leds[dot] = CRGB::Gold ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
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
 FastLED.show();
  for(int dot = NUM_LEDS-1; dot >= 0; dot--) {
   if (EtatInt == 1 ) break ;
   leds(dot,dot+LongChen-1) = CRGB::Green;
   if ((dot+LongChen) > NUM_LEDS) {
     leds(0,dot+LongChen-1-NUM_LEDS) = CRGB::Green;
   }
   FastLED.show();
   leds[dot+LongChen-1] = CRGB::Red ;                  // clear this led for the next time around the loop
   if ((dot+LongChen) > NUM_LEDS) {
      leds(0,dot+LongChen-1-NUM_LEDS) = CRGB::Red;
   }
   SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
   delay(SpeedWAVE*8);
  }
}

/***************************************
FACE_A_FACE : 2 demi cercles tournants face à face
****************************************/
void FACE_A_FACE() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Gold;
  }  
  FastLED.show();

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    leds(dot,dot+(NUM_LEDS/2)-1) = CRGB::DeepSkyBlue;
    if ((dot+(NUM_LEDS/2)) > NUM_LEDS) {
      leds[dot+(NUM_LEDS/2)-1-NUM_LEDS] = CRGB::DeepSkyBlue ;
    }
    FastLED.show();
    leds[dot] = CRGB::Gold ;                  // clear this led for the next time around the loop
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*12+10));
  }
}

/***************************************
WAVE : Battement entre 2 couleurs solides
****************************************/
void WAVE() {
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::DeepSkyBlue;
  }
  for(int Brightness = 0; Brightness < 100; Brightness++) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show();
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
  for(int Brightness = 100; Brightness > 0; Brightness--) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }

  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Gold;
  }
  for(int Brightness = 0; Brightness < 100; Brightness++) {
    if (EtatInt == 1 ) break ; 
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
  for(int Brightness = 100; Brightness > 0; Brightness--) { 
    if (EtatInt == 1 ) break ;
    FastLED.setBrightness(Brightness);
    FastLED.show(); 
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*4)+10);
  }
}

/***************************************
SPECTRE : Choix d'une couleur HUE solide selon potard
****************************************/
void SPECTRE() {
  SpectreColor = (analogRead(POT)/4) ;
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot].setHue(SpectreColor) ;
  }
  FastLED.show();
  delay(5);
}

/***************************************
QUATRE_QUARTS : 4 quarts de cercles tournants en face à face
****************************************/
void QUATRE_QUARTS() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    if (EtatInt == 1 ) break ;
    leds(dot,dot+(NUM_LEDS/4)-1) = CRGB::DeepSkyBlue;
    if ((dot+(NUM_LEDS/4)) > NUM_LEDS) {
      leds[dot+(NUM_LEDS/4)-1-NUM_LEDS] = CRGB::DeepSkyBlue ;
    }
    leds(dot+(NUM_LEDS/4),dot+(NUM_LEDS/2)-1) = CRGB::Gold;
    if ((dot+(NUM_LEDS/2)) > NUM_LEDS) {
      leds[dot+(NUM_LEDS/2)-1-NUM_LEDS] = CRGB::Gold ;
    }
    leds(dot+(NUM_LEDS/2),dot+(NUM_LEDS*3/4)-1) = CRGB::DeepSkyBlue;
    if ((dot+(NUM_LEDS*3/4)) > NUM_LEDS) {
      leds[dot+(NUM_LEDS*3/4)-1-NUM_LEDS] = CRGB::DeepSkyBlue ;
    }
    leds(dot+(NUM_LEDS*3/4),dot+NUM_LEDS-1) = CRGB::Gold;
    if ((dot+NUM_LEDS) > NUM_LEDS) {
      leds[dot+NUM_LEDS-1-NUM_LEDS] = CRGB::Gold ;
    }
    FastLED.show();
    SpeedWAVE = (analogRead(POT) * 15 / 1024) ;
    delay((SpeedWAVE*12+10));
  }
}
