
#include "main.h"

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
		

    return true;
}

void render()
{
		SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	
    SDL_RenderClear(g_pRenderer);

	  SDL_RenderCopy(g_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

		filledCircleColor(g_pRenderer, 200, 200, 100, 0xFFFFFF00); 
	
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

    while (g_bRunning)
    {
        // handle input - update - render
        render();
    }

    SDL_Quit();
    return 0;
}