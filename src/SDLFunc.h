#ifndef H_SDL_Func
#define H_SDL_Func
#include <iostream>
#include <SDL2/SDL.h>
#include <string>


void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
SDL_Texture* loadTextureAlpha(const std::string &file, SDL_Renderer *ren, int r, int g, int b);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void initRect(SDL_Rect* rect);
#endif
