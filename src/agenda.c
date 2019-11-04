#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

typedef struct pendiente { //formato de un solo pendiente
  int hora; //hora del pendiente en formato 24h
  int minuto;
  int completado; //si ya esta completada, sera 1
  char contenido[60];
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
int escribirArchivo(pendiente *, int);
pendiente *leerArchivo(int *, char *);

void generarPendientes(pendiente pendientesDeHoy[]);

int main(){
  fecha fechaDeHoy;
  char opcion[30] = ""; //cuando el usuario indique que quiere salir, este sera "-1"
  fijarFecha(&fechaDeHoy);
  pendiente *pendientesDeHoy;
  int cantidadDePendientes;

  pendientesDeHoy = leerArchivo(&cantidadDePendientes, "");
  if(pendientesDeHoy == NULL){
    printf("Ocurrio un error al intentar abrir el archivo\n");
    exit(1);
  }

  system("mode con: cols=100 lines=30"); //establecer dimensiones de la ventana
  // loop central del programa
  while(strcmp(opcion, "-1") != 0){
    menuPrincipal(pendientesDeHoy, cantidadDePendientes, opcion, fechaDeHoy);
  }
  free(pendientesDeHoy);
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

//funcion de prueba para fines de desarrollo
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

int escribirArchivo(pendiente *pendientes, int cantidadDePendientes){
  FILE *fp;
  fp = fopen("agenda.dat", "wb");
  if(fp != NULL){
    fwrite(pendientes, sizeof(pendiente), cantidadDePendientes, fp);
    fclose(fp);
    return 0;
  } else {
    return 1;
  }
}

pendiente *leerArchivo(int *cantidadDePendientes, char *nombreDelArchivo){
  FILE *fp;
  int tamanoDelArchivo;
  pendiente *buffer;
  nombreDelArchivo = nombreDelArchivo[0] == '\0' ? "agenda.dat" : nombreDelArchivo;

  fp = fopen(nombreDelArchivo, "rb");
  if(fp != NULL){
    fseek(fp, 0L, SEEK_END);
    tamanoDelArchivo = ftell(fp);
    *cantidadDePendientes = tamanoDelArchivo / sizeof(pendiente);
    rewind(fp);
    buffer = malloc(tamanoDelArchivo);
    fread(buffer, sizeof(pendiente), *cantidadDePendientes, fp);
    fclose(fp);
  } else {
    return NULL;
  }
  return buffer;
}
