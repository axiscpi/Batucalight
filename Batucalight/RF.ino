// Structure pour associer nom de menu et fonction
struct MenuEntry {
  const char* nom;
  void (*fonction)();
};

// Tableau de correspondance nom/fonction - Doit être identique aux menus du MASTER
MenuEntry menuTable[] = {
  {"TWINKLE", TWINKLE},
  {"SOLID", SOLID},
  {"WAVE", WAVE},
  {"CHENILLARD", CHENILLARD},
  {"ROUE", ROUE},
  {"SPECTRE", SPECTRE}
};

const int nombreMenus = sizeof(menuTable) / sizeof(menuTable[0]);

// Structure pour associer nom de palette et palette
struct PaletteEntry {
  const char* nom;
  CRGBPalette16 palette;
};

// Tableau de correspondance nom/palette - Doit être identique aux palettes du MASTER et palettes disponibles.
PaletteEntry paletteTable[] = {
  {"BTKDRAINBOW", BTKDRAINBOW},
  {"BTKDBLEUJAUNE", BTKDBLEUJAUNE},
  {"BTKDORANGBLEU", BTKDORANGBLEU},
  {"Rainbow", Rainbow},
  {"Tukafac", Tukafac}
};

const int nombrePalettes = sizeof(paletteTable) / sizeof(paletteTable[0]);

// Fonction vide utilisée lorsqu'aucun menu n'est reçu
void VIDE() {
  for(int dot = 0; dot < NUMLEDS; dot++) { 
    leds[dot] = CRGB::Black;
  }
  FastLED.show();
  delay(50);
}

void testRF(){
    if (radio.available()) {
    radio.read(&message, sizeof(message));                        // Si un message vient d'arriver, on le charge dans la variable "message"...
    byte Menu = message.MenuMaster;
    byte Palette = message.PalMaster;
    byte Luminosite = message.LumMaster;
    byte Parametre = message.ParaMaster;
    Compare();                                                    // ... et on met à jour les données en cours.
  }
}

void RF(){
  radio.stopListening(); // Necessaire ? A verifier...
  radio.startListening();
  testRF();
// Recherche Palette
  if (strlen(message.PalMaster) > 0) {
    for(int i = 0; i < nombrePalettes; i++) {
      if(strcmp(message.PalMaster, paletteTable[i].nom) == 0) {
        currentPalette = paletteTable[i].palette;
        strcpy(DonneesEC.Palette, message.PalMaster);
        break;
      }
    }
  }
  IntRF = false;
  PointeurMenuRF = VIDE;
  
// Recherche menu
  for(int i = 0; i < nombreMenus; i++) {
    if(strcmp(DonneesEC.Menu, menuTable[i].nom) == 0) {
      PointeurMenuRF = menuTable[i].fonction;
      break;
    }
  }
  PointeurMenuRF();
  if (EtatInt == 1 ) loop() ;
}

/************************************************************
Compare les données en cours, avec les données recues.
Si données différentes, 
*************************************************************/
void Compare() {
  if (strcmp(DonneesEC.Menu, message.MenuMaster) == 0) {
  }
  else {
    strcpy(DonneesEC.Menu, message.MenuMaster);
    IntRF = 1;
  }
  
  if (strcmp(DonneesEC.Palette, message.PalMaster) == 0) {
  }
  else {
    strcpy(DonneesEC.Palette, message.PalMaster);
    for(int i = 0; i < nombrePalettes; i++) {
      if(strcmp(DonneesEC.Palette, paletteTable[i].nom) == 0) {
        currentPalette = paletteTable[i].palette;
        break;
      }
    }
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