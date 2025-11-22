#pragma once
#include "../Graphics/Window.h"
#include "Ecosystem.h"
#include <chrono>       // Pour le chronomètre
#include <string>       // Pour std::string
#include <SDL3/SDL.h>   // Pour SDL_Keycode

namespace Ecosystem {
namespace Core {

class GameEngine {
private:
    // ÉTAT DU MOTEUR
    Graphics::Window mWindow;
    Ecosystem mEcosystem;
    bool mIsRunning;
    bool mIsPaused;
    float mTimeScale;
    
    // ⏱ CHRONOMÉTRE
    // time_point stocke un instant précis dans le temps
    std::chrono::high_resolution_clock::time_point mLastUpdateTime;
    float mAccumulatedTime;

public:
    // 🏗 CONSTRUCTEUR
    GameEngine(const std::string& title, float width, float height);
    
    // ⚙ MÉTHODES PRINCIPALES
    bool Initialize();
    void Run();
    void Shutdown();
    
    // 🎮 GESTION D'ÉVÉNEMENTS
    void HandleEvents();
    void HandleInput(SDL_Keycode key);

private:
    // MÉTHODES INTERNES
    void Update(float deltaTime);
    void Render();
    void RenderUI();
};

} // namespace Core
} // namespace Ecosystem