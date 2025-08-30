/***********************************************************
____  _  ___  _ _  __   _   _    _  __  _ _  ___ 
| o )/ \|_ _|| | |/ _| / \ | |  | |/ _|| U ||_ _|
| o \ o || | | U ( (_ | o || |_ | ( |_n|   | | | 
|___/_n_||_| |___|\__||_n_||___||_|\__/|_n_| |_| 

Eclairages des intruments BATUK'A DUNES
Conception et Réalisation : Matthieu DELANEF

BATUCALIGHT V0.5 - 09/08/2025
- Gestion des menu et palettes par leur nom et plus par numéro pour permettre au boitier d'harmoniser les instruments même si les menus ou palettes indépendament de l'ordre des menus/palettes.
- Correction Chenillard.ino (ajout de IntRF manquant)
- Modification de l'effet Chenillard pour gerer les 6 couleurs de la palette.
- Correction RF.ino (Vérification Palette à chanque lancement du menu RF)
************************************************************/

/************************************************************
Libraries :
*************************************************************/
#include <FastLED.h>        //FastLED 3.4.0
#include <SPI.h>
#include <RF24.h>           //RF24 1.4.11
#include <printf.h>         //Si debug, pour le print PrettyDetails

/***********************************************************
Configuration de l'instrument :
************************************************************/
#define NUMLEDS 52 // Nombre total de led du bandeau
#define MENUMAX 7 // Nombre de menu disponibles
#define PALETTEMAX 3 // Nombre de palettes disponibles
#define MENURF MENUMAX // Numéro du menu RF (MENUMAX si le menu RF est le dernier.)

/***********************************************************
Configuration globale :
************************************************************/
#define pinBP1 2 // MENU Pin BP1 - ATTENTION, doit être une pin INTERRUPT (NANO -> Pin D2 ou D3)
#define pinBP2 3 // PALETTE Pin BP2 - ATTENTION, doit être une pin INTERRUPT (NANO -> Pin D2 ou D3)
#define pinCE 10  // On associe la broche "CE" du NRF24L01 à la sortie digitale D9 de l'arduino
#define pinCSN 9 // On associe la broche "CSN" du NRF24L01 à la sortie digitale D10 de l'arduino
#define POTFUNC A2 // Pin potard Fonction
#define POTLUM A1 // Pin potard Luminosité
#define DATA_PIN 4 // Pin signal bandeau
#define LongChen NUMLEDS/5 // Nombre de leds du chenillard simple 

/***********************************************************
RF24
***********************************************************/
#define tunnel  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01
const byte adresse[6] = tunnel;    // Mise au format "byte array" du nom du tunnel

struct message {
	char MenuMaster[15];
  char PalMaster[15];
  byte LumMaster;
  byte ParaMaster; 
};
message message;

struct DonneesEC {
	char Menu[15];
  char Palette[15];
  byte Luminosite;
  byte Parametre;  
};
DonneesEC DonneesEC;

/***********************************************************
Défintion des menus

Ajout d'un menu : 
- MENUMAX +1
- Ajout d'un void XXXX() ;
- Ajout du menu dans le void loop() ET dans le void RF()
- Description du programme du menu.

***********************************************************/
// ATTENTION : 14 CARACTERE MAXIMUM POUR LE NOM DU MENU
void TEST() ;
void SOLID() ;
void WAVE() ;
void CHENILLARD() ;
void SPECTRE() ;
void ROUE() ;
void TWINKLE() ;
void RF() ;

void(*PointeurMenu)();
void(*PointeurMenuRF)();

/***********************************************************
Programmes divers
***********************************************************/
void testRF();
void Compare();
void CLIGNORF();

/***********************************************************
Défintion du programme d'interruption ISR
***********************************************************/
void ISRMENU() ;
void ISRPALETTE() ;

/***********************************************************
Défintion des variables
***********************************************************/
volatile byte MENU = 1 ;
volatile byte PALETTE = 1 ;
bool EtatInt = false ;
bool IntRF = false ;
const unsigned long dureeAntiRebond = 200;
byte LUMINOSITE = 128 ;
byte PARAMETRE = 128 ;
byte index = 0 ;
// Défintion des variables RF
byte Luminosite = 255 ; // Nécéssaire ?
byte Parametre = 255 ;  // Nécéssaire ?
byte NumMenu = 1 ;
byte NumPal = 1 ;

//CRGB leds[NUMLEDS] ;
// ATTENTION : 14 CARACTERE MAXIMUM POUR LE NOM DE LA PALETTE
CRGBArray<NUMLEDS*2> leds ;
CRGBPalette16 currentPalette;
extern CRGBPalette16 BTKDBLEUJAUNE;
extern CRGBPalette16 BTKDRAINBOW;
extern CRGBPalette16 BTKDORANGBLEU;
extern CRGBPalette16 Tukafac;
extern CRGBPalette16 Rainbow; 

/***********************************************************
SETUP
***********************************************************/
void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUMLEDS);
  pinMode(pinBP1, INPUT_PULLUP);
  pinMode(pinBP2, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinBP1), ISRMENU, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinBP2), ISRPALETTE, FALLING);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,2500);
  //Serial.begin(9600);     // Si debug
  //printf_begin();         // Si debug, pour le print PrettyDetails
  radio.begin();          // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);	// RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, ou RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS);	// en remplaçant « xxx » par RF24_250KBPS, RF24_1MBPS, ou encore, RF24_2MBPS
  radio.setChannel(120); 		// en remplaçant « x » par une valeur comprise entre 0 et 125
  radio.setAutoAck(false);
  radio.startListening();		// permet de pouvoir utiliser la fonction « read » par la suite
}

/***********************************************************
LOOP
***********************************************************/
void loop() { 
  if ((MENU == MENURF) && (EtatInt == 1)) {    // Clignotement au menu RF.
      CLIGNORF();
  }
  EtatInt = 0 ;
  CHANGEMENU();
  CHANGEPALETTE();
  PointeurMenu();
}

/***********************************************************
Changement du menu
***********************************************************/
void CHANGEMENU() {
  if (MENU == 1) PointeurMenu = TWINKLE ;
  if (MENU == 2) PointeurMenu = SOLID ;
  if (MENU == 3) PointeurMenu = WAVE ;
  if (MENU == 4) PointeurMenu = CHENILLARD ;
  if (MENU == 5) PointeurMenu = ROUE ;
  if (MENU == 6) PointeurMenu = SPECTRE ;
  if (MENU == 7) PointeurMenu = RF ; // TOUJOURS LE DERNIER sinon modifier le #define MENURF
}

/***********************************************************
Changement de palette
***********************************************************/
void CHANGEPALETTE() {
  if (MENU != MENURF) {
    if (PALETTE == 1) currentPalette = BTKDBLEUJAUNE ;   
    if (PALETTE == 2) currentPalette = BTKDORANGBLEU ;
    if (PALETTE == 3) currentPalette = BTKDRAINBOW ;
  }
}

/***********************************************************
Menu de défintion du paramètre et de la luminosité
***********************************************************/
void SETPARALUM() {
// Set Paramètre
  if (MENU == MENURF) {
    testRF();
    PARAMETRE = message.ParaMaster ;
  }
  else {
    PARAMETRE = map(analogRead(POTFUNC),0,1023,0,255) ;
  }
// Set Luminosité
  if (MENU == MENURF) {
    testRF();
    if (message.LumMaster < 5) {
      LUMINOSITE = 0 ;
    }
    else {
      LUMINOSITE = message.LumMaster ;
    }
  }
  else {
    if (map(analogRead(POTLUM),0,1023,255,0) < 5) {
      LUMINOSITE = 0 ;
    }
    else {
    LUMINOSITE = map(analogRead(POTLUM),0,1023,255,0) ;
    }
  }
}

/***********************************************************
Menu d'interruption ISR permet de changer le menu / palette au clic du bouton.
Attention, ne termine pas l'effet visuel en cours si boucle FOR,
il faut vérifier EtatInt=1 et break la boucle FOR pour repartir dans le loop()
***********************************************************/
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
  if (MENU != MENURF) {
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
} 

