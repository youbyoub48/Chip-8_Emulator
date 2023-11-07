#include "chip8.h"

Chip8::Chip8(){
    Uint16 i=0; 

    for(i=0;i<TAILLEMEMOIRE;i++)
    { 
        memoire[i]=0; 
    } 

     for(i=0;i<16;i++) 
     { 
        V[i]=0; 
        saut[i]=0; 
     } 

    pc=ADRESSEDEBUT; 
    nbrsaut=0; 
    compteurJeu=0; 
    compteurSon=0; 
    I=0;
}

void Chip8::decompter() 
{ 
    if(compteurJeu>0) compteurJeu--; 

    if(compteurSon>0) compteurSon--; 
}

void Chip8::initialiserPixel()
{
    Uint8 x = 0, y = 0;

    for (x = 0; x < l; x++)
    {
        for (y = 0; y < L; y++)
        {
            ecran[x][y].pixel.x = x * DIMPIXEL;
            ecran[x][y].pixel.y = y * DIMPIXEL;
            ecran[x][y].pixel.w = DIMPIXEL;
            ecran[x][y].pixel.y = DIMPIXEL;
            ecran[x][y].couleur = NOIR;
        }
    }

}

void Chip8::initialiserEcran() {
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowTitle(pWindow, "Chip_8 Emulator");
}

void Chip8::dessinerPixel(PIXEL pixel) {
    if(pixel.couleur == NOIR) SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    if(pixel.couleur == BLANC) SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    SDL_RenderFillRect(pRenderer, &pixel.pixel);
}

void Chip8::effacerEcran()
{
    Uint8 x = 0, y = 0;
    for (x = 0; x < l; x++)
    {
        for (y = 0; y < L; y++)
        {
            ecran[x][y].couleur = NOIR;
        }
    }

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
}

void Chip8::updateEcran()
{
    Uint8 x = 0, y = 0;

    for (x = 0; x < l; x++)
    {
        for (y = 0; y < L; y++)
        {
            dessinerPixel(ecran[x][y]);
        }
    }

    SDL_RenderPresent(pRenderer); 
}

Chip8::~Chip8() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}