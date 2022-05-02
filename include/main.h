#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
bool g_bRunning = false;

SDL_Texture* m_pTexture; 
// 원본 사각형
SDL_Rect m_sourceRectangle;	 
// 대상 사각형
SDL_Rect m_destinationRectangle;