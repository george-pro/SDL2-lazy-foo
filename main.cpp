#include <SDL.h>
#include <setup.h>

enum keyPressEnum {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const char* imagePathArray[KEY_PRESS_SURFACE_TOTAL] = {
    "bitmap/default.bmp",
    "bitmap/up.bmp",
    "bitmap/down.bmp",
    "bitmap/left.bmp",
    "bitmap/right.bmp"
};

SDL_Surface* gKeyPressSurfaceArray[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

SDL_Event event;


void handleInput() {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            abort("SDL_QUIT");
            break;
        }

        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                gCurrentSurface = gKeyPressSurfaceArray[KEY_PRESS_SURFACE_UP];
                break;
                case SDLK_DOWN:
                gCurrentSurface = gKeyPressSurfaceArray[KEY_PRESS_SURFACE_DOWN];
                break;
                case SDLK_LEFT:
                gCurrentSurface = gKeyPressSurfaceArray[KEY_PRESS_SURFACE_LEFT];
                break;
                case SDLK_RIGHT:
                gCurrentSurface = gKeyPressSurfaceArray[KEY_PRESS_SURFACE_RIGHT];
                break;
                default:
                gCurrentSurface = gKeyPressSurfaceArray[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
        }
    }
}

void render() {
    SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);
}

int main(int argc, char* args[]) {
    // Open Window
    openWindow("SDL2 Tetris", 640, 480);

    // Load Bitmaps
    for (int index = KEY_PRESS_SURFACE_DEFAULT; index != KEY_PRESS_SURFACE_TOTAL; index++) {
        gKeyPressSurfaceArray[index] = loadBitmap(imagePathArray[index]);
    }
    gCurrentSurface = gKeyPressSurfaceArray[KEY_PRESS_SURFACE_DEFAULT];

    // Looping...
    while (gRepeat) {
        handleInput();
        render();
    }

    // Release Surfaces
    for (int index = KEY_PRESS_SURFACE_DEFAULT; index != KEY_PRESS_SURFACE_TOTAL; index++) {
        SDL_FreeSurface(gKeyPressSurfaceArray[index]);
        gKeyPressSurfaceArray[index] = NULL;
    }
    gCurrentSurface = NULL;

    // Close Window
    closeWindow();

    // Exit Application
    return 0;
}
