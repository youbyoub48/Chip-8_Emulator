#include "chip8.h"

void initialiserSDL();
void pause();

int main(int argc, char* argv[])
{
    Chip8 chip8;

    initialiserSDL();
    chip8.initialiserEcran();
    chip8.initialiserPixel();

    chip8.updateEcran();

    pause();


    return EXIT_SUCCESS;
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

    Uint8 continuer = 1;
    SDL_Event event;

    do
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            continuer = 0;
            break;
        default: break;
        }
    } while (continuer == 1);

}