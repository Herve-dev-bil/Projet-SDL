#include "Core/GameEngine.h"
#include <iostream>
#include <cstdlib> // Pour std::srand
#include <ctime>   // Pour std::time

// Sous Windows, SDL remplace parfois le main. 
// Si vous avez une erreur de linker "undefined reference to WinMain", 
// ajoutez #define SDL_MAIN_HANDLED avant l'include SDL dans Window.hpp 
// ou utilisez int main(int argc, char* argv[]) comme ci-dessous.

int main(int argc, char* argv[]) {
    // Initialisation de l'aléatoire (important pour que la simulation change à chaque fois)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    std::cout << "🎮 Démarrage du Simulateur d'Écosystème" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    // 🏗 Création du moteur de jeu
    // J'ai rétabli les valeurs 1200 et 800 qui étaient coupées
    Ecosystem::Core::GameEngine engine("Simulateur d'Écosystème Intelligent", 1200.0f, 800.0f);
    
    // ⚙ Initialisation
    if (!engine.Initialize()) {
        std::cerr << "❌ Erreur: Impossible d'initialiser le moteur de jeu" << std::endl;
        return -1;
    }
    
    std::cout << "✅ Moteur initialisé avec succès" << std::endl;
    std::cout << "🎯 Lancement de la simulation..." << std::endl;
    std::cout << "=== CONTRÔLES ===" << std::endl;
    std::cout << "ESPACE : Pause/Reprise" << std::endl;
    std::cout << "R      : Reset simulation" << std::endl;
    std::cout << "F      : Ajouter nourriture" << std::endl;
    std::cout << "FLÈCHES: Vitesse simulation" << std::endl;
    std::cout << "ÉCHAP  : Quitter" << std::endl;
    
    // 🔄 Boucle principale
    engine.Run();
    
    // 🛑 Arrêt propre
    engine.Shutdown();
    
    std::cout << "👋 Simulation terminée. Au revoir !" << std::endl;
    return 0;
}