#include "Core/GameEngine.h"
#include <iostream>
#include <thread> // Pour std::this_thread::sleep_for (optionnel mais mieux que SDL_Delay)

namespace Ecosystem
{
    namespace Core
    {

        // 🏗 CONSTRUCTEUR
        GameEngine::GameEngine(const std::string &title, float width, float height)
            : mWindow(title, width, height),
              mEcosystem(width, height, 500), // Max 500 entités par défaut
              mIsRunning(false),
              mIsPaused(false),
              mTimeScale(1.0f),
              mAccumulatedTime(0.0f)
        {
        }

        // ⚙ INITIALISATION
        bool GameEngine::Initialize()
        {
            if (!mWindow.Initialize())
            {
                return false;
            }

            // Configuration initiale : 20 herbivores, 5 carnivores, 30 plantes
            mEcosystem.Initialize(20, 5, 30);

            mIsRunning = true;
            mLastUpdateTime = std::chrono::high_resolution_clock::now();

            std::cout << "✅ Moteur de jeu initialisé" << std::endl;
            return true;
        }

        // 🔄 BOUCLE PRINCIPALE
        void GameEngine::Run()
        {
            std::cout << "🎯 Démarrage de la boucle de jeu..." << std::endl;

            while (mIsRunning)
            {
                // Calcul du Delta Time (temps écoulé depuis la dernière image)
                auto currentTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float> elapsed = currentTime - mLastUpdateTime;
                mLastUpdateTime = currentTime;

                float deltaTime = elapsed.count();

                // Gestion des événements (clavier/souris)
                HandleEvents();

                // Mise à jour de la logique (si pas en pause)
                if (!mIsPaused)
                {
                    // On multiplie par mTimeScale pour accélérer/ralentir le temps
                    Update(deltaTime * mTimeScale);
                }

                // Dessin
                Render();

                // Limitation à ~60 FPS pour ne pas surchauffer le CPU
                SDL_Delay(16);
            }
        }

        // 🛑 FERMETURE
        void GameEngine::Shutdown()
        {
            mIsRunning = false;
            mWindow.Shutdown(); // Fermeture explicite de la fenêtre
            std::cout << "🔄 Moteur de jeu arrêté" << std::endl;
        }

        // 🎮 GESTION DES ÉVÉNEMENTS
        void GameEngine::HandleEvents()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_EVENT_QUIT:
                    mIsRunning = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    HandleInput(event.key.key);
                    break;
                }
            }
        }

        // ⌨ GESTION DES TOUCHES
        void GameEngine::HandleInput(SDL_Keycode key)
        {
            switch (key)
            {
            case SDLK_ESCAPE:
                mIsRunning = false;
                break;
            case SDLK_SPACE:
                mIsPaused = !mIsPaused;
                std::cout << (mIsPaused ? "⏸ Simulation en pause" : "▶ Simulation reprise") << std::endl;
                break;
            case SDLK_R:
                mEcosystem.Initialize(20, 5, 30);
                std::cout << "🔄 Simulation réinitialisée" << std::endl;
                break;
            case SDLK_F:
                mEcosystem.SpawnFood(10);
                std::cout << "🍎 Nourriture ajoutée" << std::endl;
                break;
            case SDLK_UP:
                mTimeScale *= 1.5f;
                std::cout << "⏩ Vitesse: " << mTimeScale << "x" << std::endl;
                break;
            case SDLK_DOWN:
                mTimeScale /= 1.5f;
                if (mTimeScale < 0.1f)
                    mTimeScale = 0.1f;
                std::cout << "⏪ Vitesse: " << mTimeScale << "x" << std::endl;
                break;
            }
        }

        // 🔄 MISE À JOUR
        void GameEngine::Update(float deltaTime)
        {
            mEcosystem.Update(deltaTime);

            // Affichage occasionnel des statistiques (toutes les 2 secondes)
            static float statsTimer = 0.0f;
            statsTimer += deltaTime;

            if (statsTimer >= 2.0f)
            {
                auto stats = mEcosystem.GetStatistics();
                std::cout << "📊 Stats - Herbivores: " << stats.totalHerbivores
                          << ", Carnivores: " << stats.totalCarnivores
                          << ", Plantes: " << stats.totalPlants
                          << ", Naissances: " << stats.birthsToday
                          << ", Morts: " << stats.deathsToday << std::endl;
                statsTimer = 0.0f;
            }
        }

        // 🎨 RENDU
        void GameEngine::Render()
        {
            // 1. Effacer l'écran
            mWindow.Clear();

            // 2. Dessiner l'écosystème
            mEcosystem.Render(mWindow.GetRenderer());

            // 3. Dessiner l'interface (UI)
            RenderUI();

            // 4. Afficher le résultat
            mWindow.Present();
        }

        // 🖥 INTERFACE UTILISATEUR
        void GameEngine::RenderUI()
        {
            // Pour l'instant vide (Bonus : afficher du texte avec SDL_ttf ici)
        }

    } // namespace Core
} // namespace Ecosystem