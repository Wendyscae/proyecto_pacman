
/* parte 5 de pac man */
#include <allegro.h>
#include <cstdlib>

#define MAXFILAS 21
#define MAXCOLS 30

BITMAP *buffer;
BITMAP *roca;
BITMAP *comida;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *muertebmp;
BITMAP *enemigobmp;
BITMAP *enemigo;
SAMPLE *musica;
SAMPLE *bolita;
SAMPLE *caminando;
SAMPLE *gameover;


struct Fantasma{// en el video lo hace con una clase, pero como es de c++ lo cambie a un struct pero si voy a tener que adaptar unas cositas


    int dir;
    int x;
	int y; //x es la coordenada del fantasma

};
struct Fantasma fantasmaA;
struct Fantasma fantasmaB;

int dir=4;
int px=30*14,py=30*17;

int anteriorpx,anteriorpy;                    

char mapa[MAXFILAS][MAXCOLS] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "Xo o |o o o XXXXX o o o| o oX",//
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "XoXXX XXXXX XXXXX XXXXX XXXoX",//
    "X      o|o o o o o o|o      X",
    "XoXXXoXX XXXXXXXXXXX XXoXXXoX",
    "X     XX     XXX    XX      X",
    "XoXXXoXXXXXX XXX XXXXXXoXXXoX",
    "X XXXoXX ooo|ooo|ooo XXoXXX X",
    "  o  |XX XXXXXXXXXXX XX|  o  ",
    "X XXXoXX XXXXXXXXXXX XXoXXX X",
    "XoXXXoXX oo |ooo|ooo XXoXXXoX", //
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "Xo    XX     XXX     XX    oX",
    "X XXXoXX XXXXXXXXXXX XXoXXX X",
    "XoXXX| o| o o o o o |o  XXX X",//
    "X XXXoXXXX XXXXXXXX XXX XXX X",
    "XoXXXoXXXX  o o o   XXX XXXoX",
    "X  o |o o  XXXXXXXX o o|o   X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

void dibujar_mapa() {
    int row, col;

    for (row = 0; row < MAXFILAS; row++) {
        // Recorremos hasta 29 para procesar solo los caracteres visibles del laberinto
        for (col = 0; col < MAXCOLS; col++) { 
            if (mapa[row][col] == 'X') { 
                draw_sprite(buffer, roca, col * 30, row * 30);
            }else if(mapa[row][col]=='o'){
		        draw_sprite(buffer,comida,col*30,row*30);
	            if(py/30==row && px/30==col){
	    	        play_sample(bolita,350,150,1000,0);
					mapa[row][col]=' ';
                } 
		    }
	    }// <- Aqui cierra el for de las columnas (col)
    } // <- Aqui cierra el for de las filas (row)
} // <- Aqui cierra la función dibujar_mapa

void pantalla(){
	blit(buffer, screen, 0,0,0,0,880,600);
	
}

void dibujar_personaje() {
    blit(pacbmp,pacman,dir*33,0,0,0,33,33);
    draw_sprite(buffer,pacman,px,py);
}
//funcion para que cuando se coma todas las bolitas sea game over
bool game_over(){
	int row,col;
	
	for(row=0;row<MAXFILAS;row++){
		for(col=0;col<MAXCOLS;col++){
			if(mapa[row][col]=='o'){
				return true;
			}
			
		}
	}
	return false;
}



//inincializar fantasma
void inicializarF(struct Fantasma *f, int x, int y){
	f->x=x;
	f->y=y;
	f->dir=rand()%4;
}


void dibujar_fantasma(struct Fantasma *f){
    blit(enemigobmp,enemigo,0,0,0,0,30,30);
    draw_sprite(buffer,enemigo,f->x,f->y);
}

void choque_pacman(struct Fantasma *f){
	
	    if(py == f->y && px == f->x){
		
		play_sample(gameover,200,150,1000,0);
		
		for(int j=0; j<=5;j++){
			clear(pacman);
			clear(buffer);
			dibujar_mapa();
			
			blit(muertebmp,pacman,j*33,0,0,0,33,33);
			draw_sprite(buffer,pacman,px,py);
			
			pantalla();
			rest(80);
		}
		px = 30*14;
		py = 30*17;
		dir = 4;
	}
}


void mover_fantasma(struct Fantasma *f){

    dibujar_fantasma(f);
    choque_pacman(f);

    if(mapa[f->y/30][(f->x-30)/30] == '|'){
        f->dir = rand()%4;
    }

    if(f->dir == 0){
        if(mapa[f->y/30][(f->x-30)/30] != 'X')
            f->x -= 30;
        else
            f->dir = rand()%4;
    }

    if(f->dir == 1){
        if(mapa[f->y/30][(f->x+30)/30] != 'X')
            f->x += 30;
        else
            f->dir = rand()%4;
    }

    if(f->dir == 2){
        if(mapa[(f->y-30)/30][f->x/30] != 'X')
            f->y -= 30;
        else
            f->dir = rand()%4;
    }

    if(f->dir == 3){
        if(mapa[(f->y+30)/30][f->x/30] != 'X')
            f->y += 30;
        else
            f->dir = rand()%4;
    }
//atajos
    if(f->x <= -30)
        f->x = 870;
    else if(f->x >= 870)
        f->x = -30;
}

int main(){
	allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,880,600,0,0);
	
	//inicializar audio en allegro
	 if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       return 1;
    }
    //ajustar volumen
    set_volume(70,70);
    
    musica=load_wav("musicaf.wav");
    bolita=load_wav("comida.wav");
    caminando=load_wav("sonidoP.wav");
    gameover=load_wav("gameover.wav");
	
	enemigo = create_bitmap(30,30);
	enemigobmp = load_bitmap("enemigo.bmp",NULL);
	buffer= create_bitmap(880, 600);
	roca = load_bitmap("roca.bmp",NULL);
	pacbmp = load_bitmap("pacman.bmp",NULL);
	pacman = create_bitmap(33,33);
	muertebmp = load_bitmap("muerte.bmp",NULL);
	comida = load_bitmap("comida.bmp", NULL);
	
	play_sample(musica,300,150,1000,1);
	
	inicializarF(&fantasmaA, 30*2, 30*3);
	inicializarF(&fantasmaB, 30*15, 30*15);
	
	while(!key[KEY_ESC]&&game_over()){
		
		if(dir!=4){
			play_sample(caminando,100,150,1000,0);
		}
		
		anteriorpx = px;
		anteriorpy = py;
		
		if(key[KEY_RIGHT]) dir = 1;  
		else if(key[KEY_LEFT]) dir = 0;
		else if(key[KEY_UP]) dir = 2;
		else if(key[KEY_DOWN]) dir = 3;

    if(dir==0){
		if(mapa[py/30][(px-30)/30]!='X')
		px-=30;
		else dir=4;
	}
	if(dir==1){
		if(mapa[py/30][(px+30)/30]!='X')
		px+=30;
		else dir=4;
	}
	if(dir==2){
		if(mapa[(py-30)/30][px/30]!='X')
		py-=30;
		else dir=4;
	}
	if(dir==3){
		if(mapa[(py+30)/30][px/30]!='X')
		py+=30;
		else dir=4;
	} 
    //conectamos rutina para que salga por el otro lado del atajo
	if(px<=-30){
		px=870;
	}else if(px>=870){
		px=-30;
	}
	
        clear(buffer);
        dibujar_mapa();
        dibujar_personaje();
        mover_fantasma(&fantasmaA);
        mover_fantasma(&fantasmaB);

		pantalla();
        rest(70);
        
        clear(pacman);
        blit(pacbmp,pacman,4*33,0,0,0,333,333);
        draw_sprite(buffer,pacman,px,py);
        pantalla();
        rest(90);
	}
	
	
	
}
END_OF_MAIN();
