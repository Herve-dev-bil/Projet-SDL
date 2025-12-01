# Simulateur d'Écosystème Intelligent

## 📖 Description

Ce projet est une simulation d'écosystème virtuel développée en C++ (standard C++17) en utilisant les principes fondamentaux de la **Programmation Orientée Objet (POO)** et la bibliothèque graphique **SDL3**.

L'objectif est d'observer l'évolution d'entités (Herbivores, Carnivores, Plantes) qui interagissent, se nourrissent, et se reproduisent. Le code est structuré professionnellement pour garantir la clarté, la sécurité et la bonne gestion des ressources.

---

## 🏗️ Architecture et Rôle des Composants

Le projet est organisé en trois grandes catégories : `Core` (Logique du jeu), `Graphics` (Rendu SDL), et `main.cpp` (Point d'entrée).

### 1. Organisation du Code (Namespaces et Structs)

* **Namespaces** : Le code est séparé en `Ecosystem::Core` pour la logique de simulation et `Ecosystem::Graphics` pour le rendu. Cela prévient les **conflits de noms** et structure le projet[cite: 27, 28, 29].
* **Structs (`include/Core/Structs.hpp`)** : Utilisées pour les conteneurs de données simples qui n'ont pas besoin d'une protection ou d'une logique complexe, comme `Vector2D`, `Color`, et `Food`[cite: 340, 341, 342].

### 2. Le Cœur du Programme (Classes et Fonctions/Méthodes)

#### A. Classe `Entity` (Être Vivant)

La classe `Entity` représente tout objet capable d'interagir dans l'écosystème.

| Composant | Utilité / Fonctionnement |
| :--- | :--- |
| **Données Privées (`m...`)** | **Encapsulation** : `mEnergy`, `mMaxAge`, `mIsAlive` sont protégées. L'accès direct est impossible, garantissant l'intégrité des données. |
| **Constructeur (`Entity(...)`)** | **Initialisation** : Définit l'état initial (énergie, taille, couleur) basé sur le `EntityType` (Herbivore, Carnivore, Plant). |
| **Méthode `Update(float deltaTime)`** | **Logique de Vie** : Appelle les méthodes privées comme `ConsumeEnergy()`, `Age()`, et `Move()`. C'est le cycle de vie de l'entité. |
| **Méthode `Reproduce()`** |**Comportement** : Crée une nouvelle entité (un enfant) en utilisant le **constructeur de copie** et en débitant l'énergie du parent. |
| **Méthode `GetEnergy()`, `IsAlive()`** |**Interface Publique** : Permettent à d'autres classes (comme `Ecosystem`) de consulter l'état privé de l'entité de manière contrôlée (Getters)[cite: 521, 532, 1039]. |

#### B. Classe `Ecosystem` (Gestionnaire de Monde)

La classe `Ecosystem` gère l'état global de la simulation.

| Composant | Utilité / Fonctionnement |
| :--- | :--- |
| **Membres `std::unique_ptr<Entity>`** | **Gestion Mémoire** : Utilisation de pointeurs intelligents pour s'assurer que lorsqu'une entité meurt ou que l'écosystème est détruit, la mémoire associée est **automatiquement libérée** sans fuite. |
| **Méthode `Update(float deltaTime)`** | **Mise à jour globale** : Appelle l'`Update()` de chaque entité et gère les interactions inter-entités (`HandleEating`, `HandleReproduction`). |
| **Méthode `RemoveDeadEntities()`** | **Nettoyage** : Supprime les entités pour lesquelles `IsAlive()` est faux. C'est ici que les destructeurs sont appelés et que la mémoire est libérée. |

#### C. Classe `GameEngine` (Moteur Principal)

Cette classe orchestre la boucle de jeu et l'interaction avec l'utilisateur.

| Composant | Utilité / Fonctionnement |
| :--- | :--- |
| **Membres `mWindow`, `mEcosystem`** | **Agrégation (RAII)** : L'Engine possède la Fenêtre et l'Écosystème. Lorsque l'`GameEngine` est détruit, ses destructeurs sont appelés, arrêtant proprement SDL et nettoyant toutes les entités. |
| **Méthode `Run()`** | **Boucle de Jeu** : La fonction principale qui tourne en continu, gérant le temps (`deltaTime`), les événements utilisateurs (`HandleEvents()`), la mise à jour de la simulation (`Update()`), et le rendu (`Render()`). |
| **Méthode `HandleInput(SDL_Keycode key)`** | **Contrôles Utilisateur** : Interprète les touches pressées pour des actions comme `Pause`, `Reset` ou changer l'échelle de temps. |

---

## 🛠️ Compilation et Exécution

Ce projet nécessite un compilateur supportant le standard C++17 (ou plus) et la bibliothèque SDL3.

### 1. Compilation

Utilisez l'une des commandes suivantes depuis le répertoire racine du projet :

**Avec g++ :**
```bash
g++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp $(sdl3-config --cflags --libs)
```
**Avec clang++ :**
```bash
clang++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp $(sdl3-config --cflags --libs)
```
**Execution:**
```bash
./ecosystem
```