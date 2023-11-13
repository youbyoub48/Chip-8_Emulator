#include "chip8.h"
#include <cstdlib>
#include <ctime>

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
    opcode.masque[10]= 0xF00F; opcode.id[10]=0x8000;        /* 8XY0 */ 
    opcode.masque[11]= 0xF00F; opcode.id[11]=0x8001;        /* 8XY1 */ 
    opcode.masque[12]= 0xF00F; opcode.id[12]=0x8002;        /* 8XY2 */ 
    opcode.masque[13]= 0xF00F; opcode.id[13]=0x8003;        /* BXY3 */ 
    opcode.masque[14]= 0xF00F; opcode.id[14]=0x8004;        /* 8XY4 */ 
    opcode.masque[15]= 0xF00F; opcode.id[15]=0x8005;        /* 8XY5 */ 
    opcode.masque[16]= 0xF00F; opcode.id[16]=0x8006;        /* 8XY6 */ 
    opcode.masque[17]= 0xF00F; opcode.id[17]=0x8007;        /* 8XY7 */ 
    opcode.masque[18]= 0xF00F; opcode.id[18]=0x800E;        /* 8XYE */ 
    opcode.masque[19]= 0xF00F; opcode.id[19]=0x9000;        /* 9XY0 */ 
    opcode.masque[20]= 0xF000; opcode.id[20]=0xA000;        /* ANNN */ 
    opcode.masque[21]= 0xF000; opcode.id[21]=0xB000;        /* BNNN */ 
    opcode.masque[22]= 0xF000; opcode.id[22]=0xC000;        /* CXNN */ 
    opcode.masque[23]= 0xF000; opcode.id[23]=0xD000;        /* DXYN */ 
    opcode.masque[24]= 0xF0FF; opcode.id[24]=0xE09E;        /* EX9E */ 
    opcode.masque[25]= 0xF0FF; opcode.id[25]=0xE0A1;        /* EXA1 */ 
    opcode.masque[26]= 0xF0FF; opcode.id[26]=0xF007;        /* FX07 */ 
    opcode.masque[27]= 0xF0FF; opcode.id[27]=0xF00A;        /* FX0A */ 
    opcode.masque[28]= 0xF0FF; opcode.id[28]=0xF015;        /* FX15 */ 
    opcode.masque[29]= 0xF0FF; opcode.id[29]=0xF018;        /* FX18 */ 
    opcode.masque[30]= 0xF0FF; opcode.id[30]=0xF01E;        /* FX1E */ 
    opcode.masque[31]= 0xF0FF; opcode.id[31]=0xF029;        /* FX29 */ 
    opcode.masque[32]= 0xF0FF; opcode.id[32]=0xF033;        /* FX33 */ 
    opcode.masque[33]= 0xF0FF; opcode.id[33]=0xF055;        /* FX55 */ 
    opcode.masque[34]= 0xF0FF; opcode.id[34]=0xF065;        /* FX65 */ 

    memoire[0]=0xF0;memoire[1]=0x90;memoire[2]=0x90;memoire[3]=0x90; memoire[4]=0xF0; // O 

    memoire[5]=0x20;memoire[6]=0x60;memoire[7]=0x20;memoire[8]=0x20;memoire[9]=0x70; // 1 

    memoire[10]=0xF0;memoire[11]=0x10;memoire[12]=0xF0;memoire[13]=0x80; memoire[14]=0xF0; // 2 

    memoire[15]=0xF0;memoire[16]=0x10;memoire[17]=0xF0;memoire[18]=0x10;memoire[19]=0xF0; // 3 

    memoire[20]=0x90;memoire[21]=0x90;memoire[22]=0xF0;memoire[23]=0x10;memoire[24]=0x10; // 4 

    memoire[25]=0xF0;memoire[26]=0x80;memoire[27]=0xF0;memoire[28]=0x10;memoire[29]=0xF0; // 5 

    memoire[30]=0xF0;memoire[31]=0x80;memoire[32]=0xF0;memoire[33]=0x90;memoire[34]=0xF0; // 6 

    memoire[35]=0xF0;memoire[36]=0x10;memoire[37]=0x20;memoire[38]=0x40;memoire[39]=0x40; // 7 

    memoire[40]=0xF0;memoire[41]=0x90;memoire[42]=0xF0;memoire[43]=0x90;memoire[44]=0xF0; // 8 

    memoire[45]=0xF0;memoire[46]=0x90;memoire[47]=0xF0;memoire[48]=0x10;memoire[49]=0xF0; // 9 

    memoire[50]=0xF0;memoire[51]=0x90;memoire[52]=0xF0;memoire[53]=0x90;memoire[54]=0x90; // A 

    memoire[55]=0xE0;memoire[56]=0x90;memoire[57]=0xE0;memoire[58]=0x90;memoire[59]=0xE0; // B 

    memoire[60]=0xF0;memoire[61]=0x80;memoire[62]=0x80;memoire[63]=0x80;memoire[64]=0xF0; // C 

    memoire[65]=0xE0;memoire[66]=0x90;memoire[67]=0x90;memoire[68]=0x90;memoire[69]=0xE0; // D 

    memoire[70]=0xF0;memoire[71]=0x80;memoire[72]=0xF0;memoire[73]=0x80;memoire[74]=0xF0; // E 

    memoire[75]=0xF0;memoire[76]=0x80;memoire[77]=0xF0;memoire[78]=0x80;memoire[79]=0x80; // F 

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

Uint16 Chip8::recupererOpcode()
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


void Chip8::dessinerEcran(Uint8 b1,Uint8 b2, Uint8 b3) 
{ 
    Uint8 x=0,y=0,k=0,codage=0,j=0,decalage=0; 
    V[0xF]=0; 

     for(k=0;k<b1;k++) 
        { 
            codage=memoire[I+k];

            y=(V[b2]+k)%L;

            for(j=0,decalage=7;j<8;j++,decalage--) 
             { 
                x=(V[b3]+j)%l;

                        if(((codage)&(0x1<<decalage))!=0)
                        {   //si c'est blanc 
                            if( ecran[x][y].couleur==BLANC) 
                            { 
                                ecran[x][y].couleur=NOIR; 
                                V[0xF]=1;

                            } 
                            else
                            { 
                                 ecran[x][y].couleur=BLANC;
                            } 


                        } 

            } 
        } 

}

void Chip8::interpreterOpcode(Uint16 opcode){
    Uint8 action,b3,b2,b1; 

    b3=(opcode&(0x0F00))>>8;
    b2=(opcode&(0x00F0))>>4;
    b1=(opcode&(0x000F));

    action = recupererAction(opcode);

    switch(action){
        case 0: //0NNN
            break;

        case 1: //00E0
            effacerEcran();
            break;
        
        case 2: //00EE
            if(nbrsaut>0) { 
                nbrsaut--; 
                pc=saut[nbrsaut]; 
            } 
            break;
        
        case 3: //1NNN
            pc=(b3<<8)+(b2<<4)+b1;
            pc -= 2;
            break;
        
        case 4: //2NNN
            saut[nbrsaut]=pc; //on reste là où on était 

            if(nbrsaut<15) nbrsaut++; 
                        
            pc=(b3<<8)+(b2<<4)+b1;
            pc-=2;
            break;
        
        case 5: //3XNN
            if(V[b3] == ((b2<<4)+b1)) pc+=2; 
            break;
        
        case 6: //4XNN
            if(V[b3] != ((b2<<4)+b1)) pc+=2; 
            break;

        case 7: //5XY0
            if(V[b3] == V[b2]) pc+=2;
            break;
        
        case 8: //6XNN
            V[b3] = (b2<<4)+b1;
            break;
        
        case 9: //7XNN
            V[b3] += (b2<<4)+b1;
            break;
        
        case 10: //8XY0
            V[b3]=V[b2];
            break;
        
        case 11: //8XY1
            V[b3] = V[b3]|V[b2];
            break;
        
        case 12: //8XY2
            V[b3] = V[b3]&V[b2];
            break;
        
        case 13: //8XY3
            V[b3] = V[b3]^V[b2];
            break;
        
        case 14: //8XY4
            if((V[b3]+V[b2])>255) V[0xF]=1;
            else V[0xF]=0;
            V[b3]+=V[b2];
            break;
        
        case 15: //8XY5
            if((V[b3]<V[b2])) V[0xF]=0;
            else V[0xF]=1;

            V[b3]=V[b3]-V[b2];
            break;
        
        case 16: //8XY6
            V[0xF] = V[b3]&(0x01);
            V[b3] = V[b3]>>1;
            break;

        case 17: //8XY7
            if((V[b2]<V[b3])) V[0xF]=0;
            else V[0xF]=1;

            V[b3]=V[b2]-V[b3];
            break;

        case 18: //8XYE
            V[0xF] = V[b3]>>7;
            V[b3] = V[b3]<<1;
            break;

        case 19: //9XY0
            if(V[b3] != V[b2]) pc+=2;
            break;

        case 20: //ANNN
            I = (b3<<8)+(b2<<4)+b1;
            break;

        case 21: //BNNN
            pc = ((b3<<8)+(b2<<4)+b1)+V[0];
            pc-=2;
            break;

        case 22: //CXNN
            srand(time(NULL));
            V[b3]=(rand())%((b2<<4)+b1+1);
            break;

        case 23: //DXYN
            dessinerEcran(b1,b2,b3);
            break;

        case 24: //EX9E
            break;
        
        case 25: //EXA1
            break;
        
        case 26: //FX07
            V[b3] = compteurJeu;
            break;
        
        case 27: //FX0A
            break;
        
        case 28: //FX15
            compteurJeu = V[b3];
            break;
        
        case 29: //FX18
            compteurSon = V[b3];
            break;

        case 30: //FX1E
            if(I+V[b3] > 0xFFF) V[0xF] = 1;
            else V[0xF] = 0;

            I += V[b3];
            break;

        case 31: //FX29
            I =5*V[b3];
            break;

        case 32: //FX33
            memoire[I]=(V[b3]-V[b3]%100)/100;
            memoire[I+1]=(((V[b3]-V[b3]%10)/10)%10);
            memoire[I+2]=V[b3]-memoire[I]*100-memoire[I+1]*10;
            break;

        case 33: //FX55
            for(Uint8 i=0;i<b3;i++){
                memoire[I+i] = V[i];
            }
            break;
        
        case 34: //FX65
            for(Uint8 i=0;i<b3;i++){
                V[i] = memoire[I+i];
            }
            break;
    }

    pc += 2;
}