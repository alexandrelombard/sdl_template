#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define RACKET_W 30
#define RACKET_H 100
#define RACKET_SPEED 10
#define BALL_R 5
#define BALL_SPEED 0.1f

typedef unsigned char bool;
#define true 1
#define false 0

typedef struct {
    float x;
    float y;
} Vector2D;

typedef struct {
    int player1;
    int player2;
    Vector2D ball;
    Vector2D ball_velocity;
} GameState;

// region Game lifecycle
void init(GameState *game_state);
void update(GameState *game_state, float delta_time);
void render(const GameState *game_state, SDL_Renderer *renderer);
// endregion

// region Events
static bool keys[1024];
void on_key_pressed(GameState *game_state);
// endregion

int main(int argc, char *argv[])
{
    int exit_event = 0;

    // Initialize the SDL video mode
    SDL_Init(SDL_INIT_VIDEO);

    // Create a new window with undefined position and a size of (640, 480) in pixels
    SDL_Window *window = SDL_CreateWindow(
            "SDL2 Pong",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
    );

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    // Create a game state
    GameState game_state;

    init(&game_state);

    unsigned int tic = SDL_GetTicks();
    unsigned int toc = SDL_GetTicks();

    do {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        bool key_down = false;
        bool key_up = false;

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit_event = 1;
                    break;
                case SDL_KEYDOWN:
                    keys[event.key.keysym.scancode] = true;
                    key_down = true;
                    break;
                case SDL_KEYUP:
                    keys[event.key.keysym.scancode] = false;
                    key_up = false;
                    break;
            }
        }

        if (key_down) {
            on_key_pressed(&game_state);
        }

        toc = SDL_GetTicks();
        update(&game_state, (toc - tic) / 1000.0f);
        tic = SDL_GetTicks();

        render(&game_state, renderer);
    } while (exit_event == 0);

    // Destroy the window (free the memory) and exit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



void init(GameState *game_state) {
    game_state->player1 = (SCREEN_HEIGHT - RACKET_H) / 2;
    game_state->player2 = (SCREEN_HEIGHT - RACKET_H) / 2;
    game_state->ball.x = (SCREEN_WIDTH - BALL_R) / 2;
    game_state->ball.y = (SCREEN_HEIGHT - BALL_R) / 2;
    game_state->ball_velocity.x = BALL_SPEED;
    game_state->ball_velocity.y = BALL_SPEED;
}

void update(GameState *game_state, float delta_time) {
    game_state->ball.x += game_state->ball_velocity.x;
    game_state->ball.y += game_state->ball_velocity.y;
    if(game_state->ball.x + 2 * BALL_R > SCREEN_WIDTH || game_state->ball.x < 0) {
        game_state->ball_velocity.x = -game_state->ball_velocity.x;
    }
    if(game_state->ball.y + 2 * BALL_R > SCREEN_HEIGHT || game_state->ball.y < 0) {
        game_state->ball_velocity.y = -game_state->ball_velocity.y;
    }
}

void render(const GameState *game_state, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_Rect r1;
    r1.x = 0;
    r1.y = game_state->player1;
    r1.w = RACKET_W;
    r1.h = RACKET_H;
    SDL_RenderFillRect(renderer, &r1);

    SDL_Rect r2;
    r2.x = SCREEN_WIDTH - RACKET_W;
    r2.y = game_state->player2;
    r2.w = RACKET_W;
    r2.h = RACKET_H;
    SDL_RenderFillRect(renderer, &r2);

    SDL_Rect b;
    b.x = game_state->ball.x - BALL_R;
    b.y = game_state->ball.y - BALL_R;
    b.w = BALL_R * 2;
    b.h = BALL_R * 2;
    SDL_RenderFillRect(renderer, &b);
}

void on_key_pressed(GameState *game_state) {
    if(keys[SDL_SCANCODE_S] == true) {
        game_state->player1 += RACKET_SPEED;
    } else if (keys[SDL_SCANCODE_W] == true) {  // Qwerty -> Azerty mapping
        game_state->player1 -= RACKET_SPEED;
    }

    if(keys[SDL_SCANCODE_DOWN] == true) {
        game_state->player2 += RACKET_SPEED;
    } else if (keys[SDL_SCANCODE_UP] == true) {
        game_state->player2 -= RACKET_SPEED;
    }
}