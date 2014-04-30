#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <ncurses.h>

#define T .1
#define X 5

struct TCoordenadas{
double x;
double y;
};

struct TFisica{

    struct TCoordenadas punto;
    struct TCoordenadas velocidad;
    struct TCoordenadas aceleracion;
};

struct TTanque{
    struct TCoordenadas dimension[X];
};

void rellenar_tanque(struct TTanque *tanque){

    for(int fila=0; fila < X; fila++){
	   tanque->dimension[fila].y = 20;
	   tanque->dimension[fila].x = 27 + fila;
    }

}

void pintar_tanque(struct TTanque *tanque){

    attron(COLOR_PAIR(1));
    for(int fila=0; fila < X; fila++)
	mvprintw(tanque->dimension[fila].y, tanque->dimension[fila].x, "@");

    attroff(COLOR_PAIR(1));
    }

    int main(int argc, char *argv[]){

	struct TFisica disparo;
	struct TTanque tanque;

	disparo.punto.x = 30;
	disparo.punto.y =  0;

	disparo.aceleracion.x =   0;
	disparo.aceleracion.y = -10;

	rellenar_tanque(&tanque);

	initscr();
	curs_set(0);
	start_color();

	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	do{

	    disparo.velocidad.x += disparo.aceleracion.x * T;
	    disparo.velocidad.y += disparo.aceleracion.y * T;

	    disparo.punto.x += disparo.velocidad.x * T;
	    disparo.punto.y += disparo.velocidad.y * T;

	    pintar_tanque(&tanque);

	    mvprintw(25,0, "Introduce velocidad:\nx: ");

	    __fpurge(stdin);
	    scanw(" %lf", &disparo.velocidad.x);
	    printw("y: ");
	    __fpurge(stdin);
	    scanw(" %lf", &disparo.velocidad.y);

	    mvprintw(20 - disparo.punto.y, disparo.punto.x, "*");

	    refresh();

	}while(disparo.punto.y >= 0);

	getch();
	endwin();

	return EXIT_SUCCESS;
    }
