#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    // Initialize the SDL video mode
    SDL_Init(SDL_INIT_VIDEO);

    // Create a new window with undefined position and a size of (640, 480) in pixels
    SDL_Window *window = SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0
    );

    // Render a black screen (color is R: 0, G: 0, B: 0)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Wait for 3000 milliseconds
    SDL_Delay(3000);

    // Destroy the window (free the memory) and exit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}