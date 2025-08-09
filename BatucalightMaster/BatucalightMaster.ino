/***********************************************************
____  _  ___  _ _  __   _   _    _  __  _ _  ___ 
| o )/ \|_ _|| | |/ _| / \ | |  | |/ _|| U ||_ _|
| o \ o || | | U ( (_ | o || |_ | ( |_n|   | | | 
|___/_n_||_| |___|\__||_n_||___||_|\__/|_n_| |_| 

Eclairages des intruments BATUK'A DUNES
Conception et Réalisation Matthieu DELANEF

BATUCALIGHT MASTER V0.5 - 09/08/2025
- Gestion des menu et palettes par leur nom et plus par numéro pour permettre au boitier d'harmoniser les instruments même si les menus ou palettes indépendament de l'ordre des menus/palettes.

************************************************************/

#include <SPI.h>
#include <RF24.h>     //RF24 1.4.11
#include <printf.h>

#define pinBP1 3
#define pinBP2 2
#define POTFUNC A2 // Pin potard Fonction
#define POTLUM A1 // Pin potard Luminosité

#define MENUMAX 6   // Nombre de menu des Batucalight Slave - 1
#define PALETTEMAX 3 // Nombre de palettes identiques au Batucalight Slave.

#define pinCE 10            // On associe la broche "CE" du NRF24L01 à la sortie digitale DX de l'arduino
#define pinCSN 9             // On associe la broche "CSN" du NRF24L01 à la sortie digitale DX de l'arduino
#define tunnel "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;               // Mise au format "byte array" du nom du tunnel
bool EtatInt = false ;
const unsigned long dureeAntiRebond = 200;
byte NumMenu = 1 ;
byte NumPal = 1 ;

struct Donnees {            // MAXIMUM 32 Octets
	char MenuMaster[15];      // 14 caractères utiles + '\0' -> 15 Octets
  char PalMaster[15];       // 14 caractères utiles + '\0' -> 15 Octets
  byte LumMaster;           // val 0-255 -> 1 Octet
  byte ParaMaster;          // val 0-255 -> 1 Octet 
};
Donnees message;

void setup() {
  // Init Debug
  Serial.begin(9600);   // Si debug
  printf_begin();       // Si debug, pour le print PrettyDetails
  
  //Init boutons
  pinMode(pinBP1, INPUT_PULLUP);
  pinMode(pinBP2, INPUT_PULLUP);

  // Init NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MAX);      // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, ou RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS);	  // en remplaçant « xxx » par RF24_250KBPS, RF24_1MBPS, ou encore, RF24_2MBPS
  radio.setChannel(120); 		          // en remplaçant « x » par une valeur comprise entre 0 et 125
  radio.setAutoAck(false);            // N'attend pas d'accusé reception du message du recepteur
  radio.stopListening();              // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
  
  radio.printPrettyDetails();         // Si Debug
  Serial.print("Chip Connection Status: "); // Si Debug
  Serial.println(radio.isChipConnected()); // Si Debug

  attachInterrupt(digitalPinToInterrupt(pinBP1), ISRMENU, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinBP2), ISRPALETTE, FALLING);
  
  //message.MenuMaster = 1;
  //message.PalMaster = 1;
  //message.LumMaster = 1;
  //message.ParaMaster = 1;
}

void loop() {
  // Défintion des menus - ATTENTION : 14 CARACTERE MAXIMUM POUR LE NOM DU MENU
  if (NumMenu == 1) message.MenuMaster = TWINKLE ;
  if (NumMenu == 2) message.MenuMaster = SOLID ;
  if (NumMenu == 3) message.MenuMaster = WAVE;
  if (NumMenu == 4) message.MenuMaster = CHENILLARD;
  if (NumMenu == 5) message.MenuMaster = ROUE;
  if (NumMenu == 6) message.MenuMaster = SPECTRE;

  // Défintion des palettes - ATTENTION : 14 CARACTERE MAXIMUM POUR LE NOM DE LA PALETTE
  if (NumPal == 1) message.PalMaster = Batukadune ;
  if (NumPal == 2) message.PalMaster = BTKD2 ;
  if (NumPal == 3) message.PalMaster = Rainbow ;

  // Défintion ParaLum
  message.ParaMaster = (analogRead(POTFUNC)/4);
  message.LumMaster = (255-(analogRead(POTLUM)/4));

  // Envoi du message
  radio.write(&message, sizeof(message));     // Envoi de notre message
  delay(150);
}

void ISRMENU() {
  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
    if (NumMenu < MENUMAX) {
    NumMenu++ ;
    }
  else {
    NumMenu = 1 ;
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
    if (NumPal < PALETTEMAX) {
    NumPal++ ;
    }
  else {
    NumPal = 1 ;
  }
    dateDernierChangement = date;
    EtatInt = 1 ;
    delay(10);
  }

}
