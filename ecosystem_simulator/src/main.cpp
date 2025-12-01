// src/main.cpp

// Inclusions requises
#include "Core/GameEngine.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{

    // 🎲 Initialisation de l'aléatoire (pour les positions et directions)
    // Utilise l'heure actuelle comme graine
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "🎮 Démarrage du Simulateur d'Écosystème" << std::endl;
    std::cout << "=======================================" << std::endl;

    // 🏗 Création du moteur de jeu
    // Le constructeur est appelé ici, ce qui appelle les constructeurs de Window et Ecosystem
    Ecosystem::Core::GameEngine engine("Simulateur d'Écosystème Intelligent", 1200.0f, 800.0f);

    // ⚙ Initialisation
    if (!engine.Initialize())
    {
        // Correction de la ligne coupée
        std::cerr << "❌ Erreur: Impossible d'initialiser le moteur de jeu" << std::endl;
        return -1;
    }

    std::cout << "✅ Moteur initialisé avec succès" << std::endl;
    std::cout << "🎯 Lancement de la simulation..." << std::endl;

    // Affichage des contrôles pour l'utilisateur
    std::cout << "=== CONTRÔLES ===" << std::endl;
    std::cout << "ESPACE: Pause/Reprise" << std::endl;
    std::cout << "R: Reset simulation" << std::endl;
    std::cout << "F: Ajouter nourriture" << std::endl;
    std::cout << "FLÈCHES HAUT/BAS: Vitesse simulation" << std::endl;
    std::cout << "ÉCHAP: Quitter" << std::endl;

    // ▶️ Boucle principale
    engine.Run();

    // 🛑 Arrêt propre
    // Le destructeur de 'engine' est appelé automatiquement à la fin de 'main'
    engine.Shutdown();

    std::cout << "👋 Simulation terminée. Au revoir !" << std::endl;
    return 0;
}