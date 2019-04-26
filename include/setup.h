#include <SDL.h>

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;

extern bool gRepeat;

void openWindow(const char* title, const int width, const int height);
void closeWindow();

void abort(const char* message);

SDL_Surface* loadBitmap(const char* path);
