#include "main.h"
#include <stdio.h>


SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
bool g_bRunning = false;

SDL_Texture* m_pTexture; 
// 원본 사각형
SDL_Rect m_sourceRectangle;	 
// 대상 사각형
SDL_Rect m_destinationRectangle;

SDL_Texture* text_texture;
SDL_Rect r;
//#include <iostream>
bool init(const char* title, int xpos, int ypos, 
          int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {

        g_pWindow = SDL_CreateWindow( title, 
                                      xpos, ypos, 
                                      height, width, flags);

        if (g_pWindow != 0)
        {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }

    }
    else
    {
        return false;
    }

    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

  SDL_Surface* pTempSurface = IMG_Load("./assets/animate-alpha.png");
  m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);

  m_sourceRectangle.w = 128;
  m_sourceRectangle.h = 82;

  m_destinationRectangle.w = m_sourceRectangle.w;
  m_destinationRectangle.h = m_sourceRectangle.h;

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
		
TTF_Font* m_pFont;
	
	  if (TTF_Init() < 0) { printf("오류: 폰트를 초기화할 수 없습니다. (%s)\n", TTF_GetError()); return false; }
  m_pFont = TTF_OpenFont("./assets/NanumGothic.ttf", 20);
  if (m_pFont == NULL) { printf("오류: 폰트를 열 수 없습니다. (%s)\n", TTF_GetError()); return false; }

	  SDL_Color color_Black = { 0, 0, 0 };
    SDL_Color color_Blue = { 0, 0, 255 };
	  SDL_Color color_White = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(m_pFont, "한글 한글", color_White,color_Black ); 
    text_texture = SDL_CreateTextureFromSurface(g_pRenderer, surface);
    r = { 0, 0, surface->w, surface->h };
    SDL_FreeSurface(surface);

	
    return true;
}

void render()
{
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	
    SDL_RenderClear(g_pRenderer);

    SDL_RenderCopy(g_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderCopy(g_pRenderer, text_texture, &r, &r);

    filledCircleColor(g_pRenderer, 300, 300, 50, 0xFFFF0000); 

/*
	    // SDL TTF



*/
	
    SDL_RenderPresent(g_pRenderer);
}

int main(int argc, char* argv[])
{
    if (init("Breaking Up HelloSDL", 
              SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED, 
              640, 480,
              SDL_WINDOW_SHOWN))
    {
        g_bRunning = true;
    }
    else
    {
        return 1; // something's wrong
    }
//std::cout << "CPP TEST " << std::endl;
    while (g_bRunning)
    {
        // handle input - update - render
        render();
    }

    SDL_Quit();
    return 0;
}