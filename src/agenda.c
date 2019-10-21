#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

typedef struct pendiente { //formato de un solo pendiente
  int hora; //hora del pendiente en formato 24h
  int minuto;
  int completado; //si ya esta completada, sera 1
  char contenido[40];
} pendiente;

typedef struct fecha { //fecha del dia actual
  char fechaString[30];
  int dia;
  int mes;
  int anio;
} fecha;

//prototipos
void menuPrincipal(pendiente[], int, char[], fecha);
void imprimirPendientesDelDia(struct pendiente[], int);
void fijarFecha(fecha*);
void gotoxy(int, int);

void generarPendientes(pendiente pendientesDeHoy[]);

int main(){
  fecha fechaDeHoy;
  char opcion[30] = ""; //cuando el usuario indique que quiere salir, este sera "-1"
  fijarFecha(&fechaDeHoy);
  pendiente pendientesDeHoy[5];
  int cantidadDePendientes = 5;
  generarPendientes(pendientesDeHoy);

  system("mode con: cols=100 lines=30"); //establecer dimensiones de la ventana
  // loop central del programa
  while(strcmp(opcion, "-1") != 0){
    menuPrincipal(pendientesDeHoy, cantidadDePendientes, opcion, fechaDeHoy);
  }
  return 0;
}

void menuPrincipal(pendiente pendientesDeHoy[], int cantidadDePendientes, char opcion[], fecha fechaDeHoy){
  gotoxy(65, 1);
  printf("%s", fechaDeHoy.fechaString);
  gotoxy(0, 3);
  imprimirPendientesDelDia(pendientesDeHoy, cantidadDePendientes);
  scanf("%s", opcion); //no usamos & ya que los arrays se pasan por referencia por default
  system("cls");
}

void fijarFecha(fecha *fechaActual){
  char diaSemana[15];
  int dia = conseguirDiaDelMes();
  char mesString[15];
  int mes = conseguirMesNumero();
  int anio = conseguirAnio();
  conseguirDiaDeLaSemana(diaSemana);
  conseguirMesString(mesString);

  fechaActual->dia = dia;
  fechaActual->mes = mes;
  fechaActual->anio = anio;
  sprintf(fechaActual->fechaString, "%s %i de %s del %i", diaSemana, dia, mesString, anio);
}

void imprimirPendientesDelDia(pendiente pendientesDeHoy[], int cantidadDePendientes){
  int i;
  char completado;
  for(int i=0; i<cantidadDePendientes; i++){
    if(pendientesDeHoy[i].completado == 1){
      completado = 'X';
    } else {
      completado = ' ';
    }
    printf("   [%c] %s (%i:%i)\n\n", completado, pendientesDeHoy[i].contenido, pendientesDeHoy[i].hora, pendientesDeHoy[i].minuto);
  }
}

void gotoxy(int x, int y){
	printf("\033[%d;%dH", y, x);
}

//esta funcion es solo para prueba durante el desarrollo
void generarPendientes(pendiente pendientesDeHoy[]){
  int i;
  for(i=0; i<5; i++){
    pendientesDeHoy[i].hora = i + 15;
    pendientesDeHoy[i].minuto = i*2 + 20;
    if(i == 2 || i == 4){
      pendientesDeHoy[i].completado = 1;
    } else{
      pendientesDeHoy[i].completado = 0;
    }
    sprintf(pendientesDeHoy[i].contenido, "Pendiente de prueba no. #%i", i);
  }
}
