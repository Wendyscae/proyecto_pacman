// PROYECTO PACMAN
//cambia la posicion de inicio del pacman, va despues de 
int dir=4;
int px=30*14,py=30*17;
//PARA PONER COMIDA TENEMOS QUE PONER o ADENTRO DEL MAPA CHAR
//A LOS BITMAPS LE AGREGO EL DE LA COMIDA
BITMAP *comida;

void dibujar_mapa(){
	//despues del if(mapa[row][col]==X.. NO ADENTRO
	else if(mapa[row][col]=='o'){
		draw_sprite(buffer,comida,col*30,row*30);
	    if(py/30==row && px/30==col){
	    	mapa[row][col]=' ';
		}
	}
}


int main(){
	//abajo de pacman=create_bitmap...
	comida=load_bitmap("Comida.bmp",NULL);
	//cambio aqui una parte de la tecla de escape para que salga cuando se active la funcion game over tmb
	while(!key[KEY_ESCAPE]&&game_over()){
		//...
	}
	//cambio la rutina del pacman creo?? para agregar los muros
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
		if(mapa[(py-30)/30][(px/30]!='X')
		py-=30;
		else dir=4;
	}
	if(dir==3){
		if(mapa[(py+30)/30][(px/30]!='X')
		py+=30;
		else dir=4;
	}
	//conectamos rutina para que salga por el otro lado del atajo
	if(px<=-30){
		px=870;
	}else if(px>=870){
		px=-30;
	}
	
	
}

//funcion para que cuando se coma todas las bolitas sea game over
bool game_over(){
	int row,col;
	
	for(row=0;row<MAXFILAS;row++){
		for(col=0;col<MALXCOL;col++){
			if(mapa[row][col]=='o'){
				return true;
			}
			
		}
	}
	return false;
}