#include "chip8.h"

void initialiserSDL();
void pause();

int main(int argc, char* argv[])
{
    Chip8 chip8;

    initialiserSDL();
    chip8.initialiserEcran();
    chip8.initialiserPixel();

    bool continuer=true; 

    do 
    {   
        chip8.updateEcran() ; 
        SDL_Delay(FPS);
    }while(continuer); 

    pause();


    return 0;
}


void initialiserSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }


}

void pause()
{

    bool continuer = true;
    SDL_Event event;

    do
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            continuer = false;
            break;
        case SDL_KEYDOWN:
            continuer = false;
            break;
        default: break;
        }
    } while (continuer);

}