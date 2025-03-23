/*
TO DO LIST :
- FAIRE UN CHENILLARD DOUBLE EN SENS CONTRAIRE 
- Pilotage bluetooth Boitier MASTER / SLAVE (nRF24L01)
*/


/***********************************************************
BATUCALIGHT V1.0
08/09/2023
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

Surdo 22" Matthieu : 54 Leds à 30 leds par metre.
Consomation Blanc 100% : XXX

Repinique XX" Uli : XX Leds à 30 leds par metre
Consomation Blanc 100% : XXX

*************************************************************/

#include <FastLED.h>

#define NUM_LEDS 54 // Nombre total de led du bandeau
#define DATA_PIN 4 // Pin signal bandeau
#define MENUMAX 8 // Nombre de menu disponibles
#define pinBP1 2 // Pin BP1 - ATTENTION, doit être une pin INTERRUPT (NANO -> Pin D2 ou D3)
#define pinBP2 3 // Pin BP2 - ATTENTION, doit être une pin INTERRUPT (NANO -> Pin D2 iu D3)
#define POTFUNC A2 // Pin potard Fonction
#define POTLUM A1 // Pin potard Luminosité
#define LongChen NUM_LEDS/6 // Nombre de leds du chenillard simple 

// Défintion des menus
void TEST() ;
void BLEU() ;
void GOLD() ;
void WAVE() ;
void CHENILLARD_JAUNE_BLEU() ;
void CHENILLARD_BLEU_JAUNE() ;
void SPECTRE() ;
void FACE_A_FACE() ;
void QUATRE_QUARTS() ;

// Défintion du programme d'interruption ISR
void ISRMENU() ;

// Défintion des constantes-variables
volatile byte MENU = 1 ;
bool EtatInt = false ;
const unsigned long dureeAntiRebond = 150;
byte Brightness = 1 ;
byte SpeedWAVE = 5 ;
int SpectreColor = 0 ;

//CRGB leds[NUM_LEDS] ;
CRGBArray<NUM_LEDS> leds ;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(pinBP1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinBP1), ISRMENU, FALLING);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,2500);
  //Serial.begin(9600);
}

void loop() { 
  FastLED.setBrightness(255) ;
  EtatInt = 0 ;
  //if (MENU == 1) TEST() ;
  //if (MENU == 1) GOLD() ;
  if (MENU == 1) SPECTRE() ;
  if (MENU == 2) BLEU() ;
  if (MENU == 3) WAVE() ;
  if (MENU == 4) CHENILLARD_JAUNE_BLEU() ;
  if (MENU == 5) CHENILLARD_BLEU_JAUNE() ;
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

