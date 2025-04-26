/***********************************************************
BATUCALIGHT V0.2
25/03/2025
- Ajout Palettes (Nouveau bouton, renommage menus, ajout des palettes dans les menus)
- Nettoyage du code de certains menus
- Wave passe à 4 premières couleurs de la palette

************************************************************
Eclairages des intruments BATUK'A DUNES
Conception et Réalisation Matthieu DELANEF
************************************************************/

/***********************************************************
Ajout d'un menu : 
- MENUMAX +1
- Ajout d'un void XXXX() ;
- Ajout du menu dans le void loop()
- Description du programme du menu.
*************************************************************/

/************************************************************
Infos perso instruments :
Timba Pauline : 32 Leds à 30 leds par metre ou 64 à 60 leds par metre.
Consomation Blanc 100% : 1.1A

Surdo 22" Matthieu : 52 Leds à 30 leds par metre.
Consomation Blanc 100% : XXX

Repinique XX" Uli : XX Leds à 30 leds par metre
Consomation Blanc 100% : XXX

*************************************************************/

#include <FastLED.h>

#define NUM_LEDS 52 // Nombre total de led du bandeau
#define DATA_PIN 4 // Pin signal bandeau
#define MENUMAX 8 // Nombre de menu disponibles
#define PALETTEMAX 3 // Nombre de palettes disponibles
#define pinBP1 2 // MENU Pin BP1 - ATTENTION, doit être une pin INTERRUPT (NANO -> Pin D2 ou D3)
#define pinBP2 3 // PALETTE Pin BP2 - ATTENTION, doit être une pin INTERRUPT (NANO -> Pin D2 ou D3)
#define POTFUNC A2 // Pin potard Fonction
#define POTLUM A1 // Pin potard Luminosité
#define LongChen NUM_LEDS/5 // Nombre de leds du chenillard simple 

// Défintion des menus
void TEST() ;
void SOLID1() ;
void SOLID2() ;
void WAVE() ;
void CHENILLARD() ;
void CHENILLARD_INV() ;
void SPECTRE() ;
void FACE_A_FACE() ;
void QUATRE_QUARTS() ;

// Défintion du programme d'interruption ISR
void ISRMENU() ;
void ISRPALETTE() ;

// Défintion des constantes-variables
volatile byte MENU = 1 ;
volatile byte PALETTE = 1 ;
bool EtatInt = false ;
const unsigned long dureeAntiRebond = 200;
byte Brightness = 1 ;
byte SpeedWAVE = 5 ;
int SpectreColor = 0 ;
uint8_t index = 0 ;

//CRGB leds[NUM_LEDS] ;
CRGBArray<NUM_LEDS> leds ;
CRGBPalette16 currentPalette;
extern CRGBPalette16 Batukadune;
extern CRGBPalette16 Tukafac;
extern CRGBPalette16 Police;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(pinBP1, INPUT_PULLUP);
  pinMode(pinBP2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinBP1), ISRMENU, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinBP2), ISRPALETTE, FALLING);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,2500);
  currentPalette = Batukadune ;
  //Serial.begin(9600); // Pour le debug
}

void loop() { 
  FastLED.setBrightness(255) ;
  EtatInt = 0 ;
  if (PALETTE == 1) currentPalette = Batukadune ;
  if (PALETTE == 2) currentPalette = Tukafac ;
  if (PALETTE == 3) currentPalette = Police ;

  //if (MENU == 1) TEST() ;
  if (MENU == 1) SOLID1() ;
  //if (MENU == 1) SPECTRE() ;
  if (MENU == 2) SOLID2() ;
  if (MENU == 3) WAVE() ;
  if (MENU == 4) CHENILLARD() ;
  if (MENU == 5) CHENILLARD_INV() ;
  if (MENU == 6) QUATRE_QUARTS() ;
  if (MENU == 7) FACE_A_FACE() ;
  if (MENU == 8) SPECTRE() ;
}

// Menu d'interruption ISR permet de changer le menu au clic du bouton.
// Attention, ne termine pas l'effet visuel en cours,
// il faut vérifier EtatInt=1 et break la boucle for pour repartir dans le loop()

void ISRMENU() {
  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
    if (MENU < MENUMAX) {
    MENU++ ;
    }
  else {
    MENU = 1 ;
  }
    dateDernierChangement = date;
    EtatInt = 1 ;
    delay(10);
  }
}


void ISRPALETTE() {
  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
    if (PALETTE < PALETTEMAX) {
    PALETTE++ ;
    }
  else {
    PALETTE = 1 ;
  }
    dateDernierChangement = date;
    EtatInt = 1 ;
    delay(10);
  }

}

