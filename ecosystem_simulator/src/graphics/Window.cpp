#include "Graphics/Window.h"
#include <iostream>

namespace Ecosystem {
namespace Graphics {

    Window::Window(const std::string& title, float width, float height)
        : mTitle(title), mWidth(width), mHeight(height), mWindow(nullptr), mRenderer(nullptr), mIsInitialized(false) {}

    Window::~Window() { Shutdown(); }

    bool Window::Initialize() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
        
        mWindow = SDL_CreateWindow(mTitle.c_str(), (int)mWidth, (int)mHeight, 0);
        if (!mWindow) return false;

        mRenderer = SDL_CreateRenderer(mWindow, NULL); // SDL3 syntax might differ slightly; for SDL2 use -1, 0
        if (!mRenderer) return false;

        mIsInitialized = true;
        return true;
    }

    void Window::Shutdown() {
        if (mRenderer) SDL_DestroyRenderer(mRenderer);
        if (mWindow) SDL_DestroyWindow(mWindow);
        SDL_Quit();
        mIsInitialized = false;
    }

    void Window::Clear(const Core::Color& color) {
        SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(mRenderer);
    }

    void Window::Present() {
        SDL_RenderPresent(mRenderer);
    }
}
}