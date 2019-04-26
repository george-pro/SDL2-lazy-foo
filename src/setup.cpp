#include <SDL.h>
#include <setup.h>
#include <iostream>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

bool gRepeat = true;

void openWindow(const char* title, const int width, const int height) {
    int init_status = SDL_Init(SDL_INIT_VIDEO);

    if (init_status == -1) {
        abort("SDL_Init Error");
        return;
    }

    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        abort("SDL_CreateWindow Error");
        return;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
}

void closeWindow() {
    if (gWindow != NULL) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }

    SDL_Quit();
}

void abort(const char* message) {
    std::cout << message << std::endl << SDL_GetError() << std::endl;

    gRepeat = false;
}

SDL_Surface* loadBitmap(const char* path) {
    SDL_Surface* bitmap = SDL_LoadBMP(path);

    if (bitmap == NULL) {
        abort("SDL_LoadBMP Error");
        return NULL;
    }

    SDL_Surface* optimized_image = SDL_ConvertSurface(bitmap, gScreenSurface->format, 0);
    SDL_FreeSurface(bitmap);
    bitmap = NULL;

    return optimized_image;
}
