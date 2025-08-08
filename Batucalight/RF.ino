void testRF(){
  //Serial.print("Test RF en cours");         // Si debug
  //Serial.println(radio.isChipConnected());  // Si debug
    if (radio.available()) {
    radio.read(&message, sizeof(message));                        // Si un message vient d'arriver, on le charge dans la variable "message"...
//A verifier si necessaire...
    byte Menu = message.MenuMaster;
    byte Palette = message.PalMaster;
    byte Luminosite = message.LumMaster;
    byte Parametre = message.ParaMaster;
// ...jusqu'ici.
    Compare();                                                    // ... et on met à jour les données en cours.
  }
}

void RF(){
  radio.stopListening(); // Necessaire ? A verifier...
  radio.startListening();
  testRF();
 /*Si debug
  Serial.print("Chip Connection Status: "); 
  Serial.println(radio.isChipConnected());     
  Serial.print("Menu Recu: ");                  
  Serial.print(message.MenuMaster);             
  Serial.print(", ");                           
  Serial.print("Menu EC: "); 
  Serial.print(DonneesEC.Menu);
  Serial.print(", ");
  Serial.print("Palette : "); 
  Serial.print(PALETTE);
  Serial.print(", ");
  //Serial.print("Luminosite : "); 
  //Serial.print(Luminosite);
  //Serial.print(", ");
  //Serial.print("Parametre : "); 
  //Serial.print(Parametre);
  //Serial.print(". ");
  Serial.println(millis()/1000);
  //delay(1000);
//...si debug.
*/
  IntRF = false;
  if (DonneesEC.Menu == 1) TWINKLE() ; // OK RF
  if (DonneesEC.Menu == 2) SOLID() ; // OK RF
  if (DonneesEC.Menu == 3) WAVE(); // OK RF
  if (DonneesEC.Menu == 4) CHENILLARD(); // OK RF
  if (DonneesEC.Menu == 5) ROUE(); // OK RF
  if (DonneesEC.Menu == 6) SPECTRE(); // OK RF
  if (EtatInt == 1 ) loop() ;
}

/************************************************************
Compare les données en cours, avec les données recues.
Si données différentes, 
*************************************************************/
void Compare() {
  if ((DonneesEC.Menu) == (message.MenuMaster)) {
    //Serial.print("Menu identique. ");
  }
  else {
    DonneesEC.Menu = message.MenuMaster;
    IntRF = 1;
    //Serial.print("Menu modifié ! ");
  }
  if ((DonneesEC.Palette) == (message.PalMaster)) {
    //Serial.print("Palette identique. ");
  }
  else {
    DonneesEC.Palette = message.PalMaster;
    PALETTE = DonneesEC.Palette;
    CHANGEPALETTE();
    //Serial.print("Pallette Modifiée ! ");
  }
}

void CLIGNORF() {
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = CRGB::Black;
  }
  FastLED.setBrightness(LUMINOSITE);  
  FastLED.show();
  delay(200);

  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = CRGB::Blue;
  }
  FastLED.setBrightness(LUMINOSITE);  
  FastLED.show();
  delay(200);

  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = CRGB::Black;
  }
  FastLED.setBrightness(LUMINOSITE);  
  FastLED.show();
  delay(200);
  
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = CRGB::Blue;
  }
  FastLED.setBrightness(LUMINOSITE);  
  FastLED.show();
  delay(200);

  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = CRGB::Black;
  }
  FastLED.setBrightness(LUMINOSITE);  
  FastLED.show();
  delay(500);
}