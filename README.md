# 🎵 BATUCALIGHT

> Système d'éclairage LED synchronisé pour instruments de percussion - BATUK'A DUNE

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![FastLED](https://img.shields.io/badge/FastLED-FF6B35?style=for-the-badge)
![RF24](https://img.shields.io/badge/RF24-4CAF50?style=for-the-badge)

## 📖 Description

BATUCALIGHT est un système d'éclairage intelligent conçu pour sublimer les performances du groupe de percussion **BATUK'A DUNE**. Chaque instrument peut être équipé de bandeaux LED programmables offrant des effets visuels synchronisés et personnalisables.

### ✨ Caractéristiques principales

- **Plusieurs modes d'éclairage** distincts avec effets dynamiques
- **Plusieurs palettes de couleurs** personnalisées 
- **Communication sans fil RF24** pour synchronisation maître/esclave
- **Contrôle en temps réel** via potentiomètres (luminosité, paramètres)
- **Architecture modulaire** et extensible

## 🎯 Modes d'éclairage

| Mode | Description | Animation |
|------|-------------|-----------|
| **TWINKLE** | Scintillement aléatoire des LEDs | ✨ Dynamique |
| **SOLID** | Couleur unie sélectionnable parmis les couleurs de la palette | 🎨 Statique |
| **WAVE** | Battement/fade entre les couleurs de la palette | 🌊 Dynamique |
| **CHENILLARD** | Section de points lumineux mobile (parmis les deux premières couleurs de la palette) | ➡️ Dynamique |
| **ROUE** | Sections colorées en rotation selon les 6 premières couleurs de la palette | 🎡 Dynamique |
| **SPECTRE** | Spectre de couleur complet réglable | 🌈 Statique |
| **RF** | Mode réception sans fil, pilotage par boitier Master | 📡 Synchronisé |

## 🔧 Matériel requis

### Composants principaux
- **Arduino RF-Nano** (ou Arduino Nano + module NRF24L01)
- **Bandeau LED WS2812B** (Nombre de leds à définir par instrument)
- **2 boutons poussoirs ou tactils** (menu/palette)
- **2 potentiomètres** (luminosité/paramètre)
- **1 Boitier** (comprenant une alimentation 5V)

## 🚀 Installation

### 1. Bibliothèques requises
```cpp
#include <FastLED.h>    // Version 3.4.0
#include <RF24.h>       // Version 1.4.11
```

### 2. Configuration
Ajustez ces paramètres dans `Batucalight.ino` :
```cpp
#define NUMLEDS 31      // Nombre de LEDs
#define MENUMAX 7       // Nombre de menus
#define PALETTEMAX 4    // Nombre de palettes
```

### 3. Upload
1. Connecter l'Arduino
2. Sélectionner le bon port série
3. Téléverser le code
4. Profiter du spectacle ! 🎉

## 🎛️ Utilisation

### Contrôles physiques
- **Potard 1** : Régler la luminosité
- **Potard 2** : Ajuster les paramètres d'effet
- **Bouton 1** : Changer de mode d'éclairage
- **Bouton 2** : Changer de palette (sauf en mode RF)

### Mode RF (Synchronisation)
Le mode RF permet de synchroniser plusieurs instruments :
- Un boitier **maître** contrôle les instruments
- Les instruments **esclaves** reçoivent les commandes
- Synchronisation automatique des effets et des palettes

## 🎵 Contexte artistique

BATUCALIGHT a été conçu spécifiquement pour **BATUK'A DUNE**, la Batucada du bassin d'Arcachon. Le système permet de :
- Créer une **identité visuelle** unique lors des performances
- Offrir une **expérience immersive** au public
- **Personnaliser** l'ambiance selon les morceaux

## 👨‍💻 Auteur

**BATUCALIGHT**
- Conception et réalisation : Matthieu DELANEF
- PCB : Philippe DELANEF
- Développement pour BATUK'A DUNE

## 📄 Licence

L’ensemble du projet est publié sous licence **Creative Commons Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes Conditions 4.0 International (CC BY-NC-SA 4.0)**.

👉 En clair :
- ✅ Vous pouvez utiliser, modifier et partager le projet librement, en particulier dans le cadre associatif de votre orchestre ou batucada.
- ✅ Vous devez créditer l’auteur original.
- ⛔ Vous **ne pouvez pas** l’utiliser à des fins commerciales.
- ✅ Les modifications doivent être partagées sous la même licence.

Texte complet de la licence : [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)

---

⭐ **Si ce projet vous plaît, n'hésitez pas à lui donner une étoile !**

*Fait avec ❤️ pour la musique et les arts de la scène*
