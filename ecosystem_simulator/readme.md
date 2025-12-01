# Simulateur d'Écosystème Intelligent

## Description

[cite_start]Ce projet est une simulation d'écosystème virtuel développée en C++ en utilisant les principes de la **Programmation Orientée Objet (POO)** avancée et la bibliothèque graphique **SDL3**[cite: 1802].

[cite_start]L'objectif est d'observer l'évolution d'entités (Herbivores, Carnivores, Plantes) qui interagissent selon des règles biologiques simples[cite: 905]. [cite_start]Le code est organisé de manière professionnelle en utilisant les concepts de *Namespaces*, de *Structs* et de *Classes* avec une gestion mémoire par **RAII** (`std::unique_ptr`)[cite: 898, 899, 900, 902].

## Architecture et Concepts Clés

| Concept | Utilisation |
| :--- | :--- |
| **Namespaces** | [cite_start]Organisation du code (Ecosystem::Core, Ecosystem::Graphics)[cite: 898]. |
| **Structs** | [cite_start]Conteneurs de données simples (Vector2D, Color, Food)[cite: 899]. |
| **Classes** | [cite_start]Entités complexes avec logique (Entity, Ecosystem, GameEngine)[cite: 900]. |
| **Encapsulation** | [cite_start]Protection des données internes (membres privés m...)[cite: 901]. |
| **Gestion Mémoire** | [cite_start]Utilisation des destructeurs et de std::unique_ptr (RAII) pour éviter les fuites[cite: 902]. |

## Compilation et Exécution

[cite_start]Ce projet nécessite un compilateur supportant le standard C++17 (ou plus) et la bibliothèque SDL3[cite: 1845, 1849].

### 1. Compilation

[cite_start]Utilisez l'une des commandes suivantes depuis le répertoire racine du projet[cite: 1806, 1808]:

**Avec g++ :**
```bash
g++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp $(sdl3-config --cflags --libs)

clang++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp $(sdl3-config --cflags --libs)

**Execution**
./ecosystem

Contrôles de la Simulation
Une fois l'application lancée, vous pouvez interagir avec le moteur de jeu:




ESPACE : Pause/Reprise de la simulation.



R : Reset de la simulation.



F : Ajouter de la nourriture.



FLÈCHES HAUT/BAS : Ajuster la vitesse de la simulation.



ÉCHAP : Quitter l'application.