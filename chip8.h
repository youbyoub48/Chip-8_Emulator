#ifndef CHIP8_H 
#define CHIP8_H 

#include <SDL2/SDL.h>

#define TAILLEMEMOIRE 4096 
#define ADRESSEDEBUT 512 

#define NOIR  0 
#define BLANC 1 
#define l 64
#define L 32
#define DIMPIXEL 8
#define WIDTH   l*DIMPIXEL
#define HEIGHT  L*DIMPIXEL

struct PIXEL
{
    SDL_Rect pixel;
    Uint8 couleur;
};


class Chip8{
    private:
        Uint8 memoire[TAILLEMEMOIRE];
        Uint16 pc;
        Uint8 V[16];
        Uint16 I;
        Uint16 saut[16];
        Uint8 nbrsaut;
        Uint8 compteurJeu;
        Uint8 compteurSon;
        PIXEL ecran[l][L];
        SDL_Window* pWindow{ nullptr };
        SDL_Renderer* pRenderer{ nullptr };
    public:
        Chip8();
        ~Chip8();
        void decompter();
        void initialiserEcran();
        void initialiserPixel();
        void dessinerPixel(PIXEL pixel);
        void effacerEcran();
        void updateEcran();
};

#endif