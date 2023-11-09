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

    opcode.masque[0]= 0x0000; opcode.id[0]=0x0FFF;          /* 0NNN */ 
    opcode.masque[1]= 0xFFFF; opcode.id[1]=0x00E0;          /* 00E0 */ 
    opcode.masque[2]= 0xFFFF; opcode.id[2]=0x00EE;          /* 00EE */ 
    opcode.masque[3]= 0xF000; opcode.id[3]=0x1000;          /* 1NNN */ 
    opcode.masque[4]= 0xF000; opcode.id[4]=0x2000;          /* 2NNN */ 
    opcode.masque[5]= 0xF000; opcode.id[5]=0x3000;          /* 3XNN */ 
    opcode.masque[6]= 0xF000; opcode.id[6]=0x4000;          /* 4XNN */ 
    opcode.masque[7]= 0xF00F; opcode.id[7]=0x5000;          /* 5XY0 */ 
    opcode.masque[8]= 0xF000; opcode.id[8]=0x6000;          /* 6XNN */ 
    opcode.masque[9]= 0xF000; opcode.id[9]=0x7000;          /* 7XNN */ 
    opcode.masque[10]= 0xF00F; opcode.id[10]=0x8000;          /* 8XY0 */ 
    opcode.masque[11]= 0xF00F; opcode.id[11]=0x8001;          /* 8XY1 */ 
    opcode.masque[12]= 0xF00F; opcode.id[12]=0x8002;          /* 8XY2 */ 
    opcode.masque[13]= 0xF00F; opcode.id[13]=0x8003;          /* BXY3 */ 
    opcode.masque[14]= 0xF00F; opcode.id[14]=0x8004;          /* 8XY4 */ 
    opcode.masque[15]= 0xF00F; opcode.id[15]=0x8005;          /* 8XY5 */ 
    opcode.masque[16]= 0xF00F; opcode.id[16]=0x8006;          /* 8XY6 */ 
    opcode.masque[17]= 0xF00F; opcode.id[17]=0x8007;          /* 8XY7 */ 
    opcode.masque[18]= 0xF00F; opcode.id[18]=0x800E;          /* 8XYE */ 
    opcode.masque[19]= 0xF00F; opcode.id[19]=0x9000;          /* 9XY0 */ 
    opcode.masque[20]= 0xF000; opcode.id[20]=0xA000;          /* ANNN */ 
    opcode.masque[21]= 0xF000; opcode.id[21]=0xB000;          /* BNNN */ 
    opcode.masque[22]= 0xF000; opcode.id[22]=0xC000;          /* CXNN */ 
    opcode.masque[23]= 0xF000; opcode.id[23]=0xD000;          /* DXYN */ 
    opcode.masque[24]= 0xF0FF; opcode.id[24]=0xE09E;          /* EX9E */ 
    opcode.masque[25]= 0xF0FF; opcode.id[25]=0xE0A1;          /* EXA1 */ 
    opcode.masque[26]= 0xF0FF; opcode.id[26]=0xF007;          /* FX07 */ 
    opcode.masque[27]= 0xF0FF; opcode.id[27]=0xF00A;          /* FX0A */ 
    opcode.masque[28]= 0xF0FF; opcode.id[28]=0xF015;          /* FX15 */ 
    opcode.masque[29]= 0xF0FF; opcode.id[29]=0xF018;          /* FX18 */ 
    opcode.masque[30]= 0xF0FF; opcode.id[30]=0xF01E;          /* FX1E */ 
    opcode.masque[31]= 0xF0FF; opcode.id[31]=0xF029;          /* FX29 */ 
    opcode.masque[32]= 0xF0FF; opcode.id[32]=0xF033;          /* FX33 */ 
    opcode.masque[33]= 0xF0FF; opcode.id[33]=0xF055;          /* FX55 */ 
    opcode.masque[34]= 0xF0FF; opcode.id[34]=0xF065;          /* FX65 */ 
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

Uint16 Chip8::recupererOpcode()   //dans cpu.c 
{  
    return (memoire[pc]<<8)+memoire[pc+1]; 
}

Uint8 Chip8::recupererAction(Uint16 opcode) 
{ 
    Uint8 action; 
    Uint16 resultat; 

    for(action=0;action<NBROPCODE;action++) 
    { 
        resultat= (this->opcode.masque[action]&opcode);

        if(resultat == this->opcode.id[action])
           break;
    } 

    return action;
}

void Chip8::interpreterOpcode(Uint16 opcode){
    Uint8 action,b3,b2,b1; 

    b3=(opcode&(0x0F00))>>8;
    b2=(opcode&(0x00F0))>>4;
    b1=(opcode&(0x000F));

    action = recupererAction(opcode);

    switch(action){
        case 0:
            break;

        case 1:
            break;
        
        case 2:
            break;
        
        case 3:
            break;
        
        case 4:
            break;
        
        case 5:
            break;
        
        case 6:
            break;

        case 7:
            break;
        
        case 8:
            break;
        
        case 9:
            break;
        
        case 10:
            break;
        
        case 11:
            break;
        
        case 12:
            break;
        
        case 13:
            break;
        
        case 14:
            break;
        
        case 15:
            break;
        
        case 16:
            break;

        case 17:
            break;

        case 18:
            break;

        case 19:
            break;

        case 20:
            break;

        case 21:
            break;

        case 22:
            break;

        case 23:
            break;

        case 24:
            break;
        
        case 25:
            break;
        
        case 26:
            break;
        
        case 27:
            break;
        
        case 28:
            break;
        
        case 29:
            break;

        case 30:
            break;

        case 31:
            break;

        case 32:
            break;

        case 33:
            break;
        
        case 34:
            break;
    }
}