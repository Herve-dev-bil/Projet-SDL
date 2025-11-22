#include "Graphics/Window.h"
#include <iostream> // pour std::cout et std::cerr

namespace Ecosystem {
namespace Graphics {

// 🏗 CONSTRUCTEUR
Window::Window(const std::string& title, float width, float height)
    : mTitle(title), mWidth(width), mHeight(height),
      mWindow(nullptr), mRenderer(nullptr), mIsInitialized(false) {}

// 🗑 DESTRUCTEUR
Window::~Window() {
    Shutdown();
}

// ⚙ INITIALISATION
bool Window::Initialize() {
    // Initialisation du sous-système Vidéo de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "❌ Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

    // Création de la fenêtre
    // Correction : ajout de <int> dans les static_cast
    mWindow = SDL_CreateWindow(mTitle.c_str(),
                              static_cast<int>(mWidth),
                              static_cast<int>(mHeight),
                              0); // 0 pour les flags par défaut

    if (!mWindow) {
        std::cerr << "❌ Erreur création fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Création du renderer (le moteur de dessin)
    // Note : SDL_CreateRenderer prend la fenêtre et le nom du driver (NULL pour auto)
    mRenderer = SDL_CreateRenderer(mWindow, NULL);

    if (!mRenderer) {
        // Correction : Ligne rétablie (point-virgule et endl ajoutés)
        std::cerr << "❌ Erreur création renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    mIsInitialized = true;
    // Correction : Ligne rétablie (fermeture des guillemets et affichage complet)
    std::cout << "✅ Fenêtre initialisée: " << mTitle << " (" << mWidth << "x" << mHeight << ")" << std::endl;
    return true;
}

// 🔄 FERMETURE
void Window::Shutdown() {
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    // Quitter proprement SDL
    SDL_Quit();
    mIsInitialized = false;
    std::cout << "🔄 Fenêtre fermée" << std::endl;
}

// 🧹 NETTOYAGE DE L'ÉCRAN
void Window::Clear(const Core::Color& color) {
    if (mRenderer) {
        // Définir la couleur d'arrière-plan
        SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
        // Remplir l'écran avec cette couleur
        SDL_RenderClear(mRenderer);
    }
}

// 🎨 AFFICHAGE (Swap Buffers)
void Window::Present() {
    if (mRenderer) {
        // Afficher ce qu'on vient de dessiner
        SDL_RenderPresent(mRenderer);
    }
}

} // namespace Graphics
} // namespace Ecosystem