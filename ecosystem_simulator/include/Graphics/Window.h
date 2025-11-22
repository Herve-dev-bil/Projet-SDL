#pragma once
#include <SDL3/SDL.h> // pour SDL_Window et SDL_Renderer
#include <string>     // qpour std::string
#include "Core/Structs.h" // Pour utiliser Core::Color

namespace Ecosystem {
namespace Graphics {

class Window {
private:
    // RESSOURCES SDL
    // Ce sont des pointeurs bruts (C-style) fournis par SDL.
    // Nous devons les gérer manuellement (créer dans Initialize, détruire dans Shutdown).
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    float mWidth;
    float mHeight;
    bool mIsInitialized;
    std::string mTitle;

public:
    // 🏗 CONSTRUCTEUR/DESTRUCTEUR
    Window(const std::string& title, float width, float height);
    ~Window();

    // ⚙ INITIALISATION
    bool Initialize();
    void Shutdown();
    
    // 🎨 RENDU
    // Efface l'écran avec une couleur gris foncé par défaut (30, 30, 30)
    void Clear(const Core::Color& color = Core::Color(30, 30, 30));
    
    // Affiche ce qui a été dessiné (Swap buffers)
    void Present();
    
    // 🔍 GETTERS
    SDL_Renderer* GetRenderer() const { return mRenderer; }
    bool IsInitialized() const { return mIsInitialized; }
    float GetWidth() const { return mWidth; }
    float GetHeight() const { return mHeight; }
    std::string GetTitle() const { return mTitle; }
};

} // namespace Graphics
} // namespace Ecosystem