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

    // Game loop
    int should_continue = 1;
    do {
        // There is a list of all events received by SQL
        // An event can be a key press, a mouse click, a click on the window exit button, etc.
        // We need to "poll" all events from that list and manage all of them (that's why there is a while loop)
        // If the event "SDL_QUIT" is sent (i.e. the user wants to leave the application), then we stop the game loop
        SDL_Event event;
        while(SDL_PollEvent(&event)) {  // While there are events to manage, we store them in the "event" variable
            switch (event.type) {
                case SDL_QUIT:      // If the user is quitting
                    should_continue = 0;
                    break;
                case SDL_KEYDOWN:   // If the user is pressing a key
                    if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        // If this key is "ESCAPE"
                        should_continue = 0;
                    }
                    break;
            }
        }

        // It's in the game loop that we render the scene
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    } while(should_continue);


    // Destroy the window (free the memory) and exit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}