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
	   tanque->dimension[fila].x = 10 + fila;
	   tanque->dimension[fila].y = 3 + fila;
    }

    mvprintw(tanque->dimension[fila].x, tanque->dimension[fila].y, "1");

}

int main(int argc, char *argv[]){

    struct TFisica disparo;
    struct TTanque tanque;

    printf("Introduce velocidad:\nx: ");
    __fpurge(stdin);
    scanf(" %lf", &disparo.velocidad.x);
    printf("y: ");
    __fpurge(stdin);
    scanf(" %lf", &disparo.velocidad.y);

    disparo.punto.x = 40;
    disparo.punto.y = 0;

    disparo.aceleracion.x =   0;
    disparo.aceleracion.y = -10;

    rellenar_tanque(&tanque);

    initscr();
    curs_set(0);

    do{

	disparo.velocidad.x += disparo.aceleracion.x * T;
	disparo.velocidad.y += disparo.aceleracion.y * T;

	disparo.punto.x += disparo.velocidad.x * T;
	disparo.punto.y += disparo.velocidad.y * T;

	mvprintw(20 - disparo.punto.y, disparo.punto.x, "*");

	refresh();

    }while(disparo.punto.y >= 0);

    getch();
    endwin();

    return EXIT_SUCCESS;
}
