#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "../Core/Structs.h"

namespace Ecosystem {
namespace Graphics {

    class Window {
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        float mWidth, mHeight;
        std::string mTitle;
        bool mIsInitialized;

    public:
        Window(const std::string& title, float width, float height);
        ~Window();
        bool Initialize();
        void Shutdown();
        void Clear(const Core::Color& color = Core::Color(30, 30, 30));
        void Present();
        SDL_Renderer* GetRenderer() const { return mRenderer; }
    };
}
}