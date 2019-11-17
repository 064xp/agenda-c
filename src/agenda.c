#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

#define TAMANO_MAXIMO 250

typedef struct pendiente { //formato de un solo pendiente
  int hora; //hora del pendiente en formato 24h
  int minuto;
  int dia;
  int mes;
  int tiempo;
  char contenido[TAMANO_MAXIMO];
} pendiente;

typedef struct fecha { //fecha del dia actual
  char fechaString[30];
  int dia;
  int mes;
  int anio;
} fecha;

//prototipos
int menuPrincipal(pendiente **, int *, fecha);
void imprimirPendientesDelDia(struct pendiente[], int);
void fijarFecha(fecha*);
void gotoxy(int, int);
int escribirArchivo(pendiente *, int);
pendiente *leerArchivo(int *);
void interpretarComando(char *, pendiente **, int *);
int agregarPendiente(pendiente, pendiente **, int *);
int borrarPendiente(int, pendiente **, int *);

void generarPendientes(pendiente pendientes[]);

int main(){
  fecha fechaDeHoy;
  int salir = 0;
  pendiente *pendientes;
  fijarFecha(&fechaDeHoy);
  int cantidadDePendientes;

  pendientes = leerArchivo(&cantidadDePendientes);
  if(pendientes == NULL){
    printf("No tienes pendientes...\n");
    cantidadDePendientes = 0;
  }

  system("mode con: cols=100 lines=30"); //establecer dimensiones de la ventana
  // loop central del programa
  while(!salir){
    salir = menuPrincipal(&pendientes, &cantidadDePendientes, fechaDeHoy);
  }
  free(pendientes);
  return 0;
}

int menuPrincipal(pendiente **pendientes, int *cantidadDePendientes, fecha fechaDeHoy){
  char opcion[TAMANO_MAXIMO];
  gotoxy(65, 1);
  printf("%s", fechaDeHoy.fechaString);
  gotoxy(0, 3);
  imprimirPendientesDelDia(*pendientes, *cantidadDePendientes);

  fgets(opcion, TAMANO_MAXIMO, stdin);

  if(opcion[0] == 's' || opcion[0] == 'S'){
    return 1;
  }

  interpretarComando(opcion, pendientes, cantidadDePendientes);
  system("cls");
  return 0;
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

void imprimirPendientesDelDia(pendiente pendientes[], int cantidadDePendientes){
  int i;
  char completado;
  if(cantidadDePendientes == 0){
    printf("\tNo tienes pendientes...\n");
    return;
  }

  for(int i=0; i<cantidadDePendientes; i++){
    printf("   [%i] %s (%i:%i)\n\n", i, pendientes[i].contenido, pendientes[i].hora, pendientes[i].minuto);
  }
}

void gotoxy(int x, int y){
	printf("\033[%d;%dH", y, x);
}

int escribirArchivo(pendiente *pendientes, int cantidadDePendientes){
  FILE *fp;
  fp = fopen("agenda.dat", "wb");
  if(fp != NULL){
    if(cantidadDePendientes == 0){
      return 0;
    }
    fwrite(pendientes, sizeof(pendiente), cantidadDePendientes, fp);
    fclose(fp);
    return 0  ;
  } else {
    return 1;
  }
}

pendiente *leerArchivo(int *cantidadDePendientes){
  FILE *fp;
  int tamanoDelArchivo;
  pendiente *buffer;

  fp = fopen("agenda.dat", "rb");
  if(fp != NULL){
    fseek(fp, 0L, SEEK_END);
    tamanoDelArchivo = ftell(fp);
    *cantidadDePendientes = tamanoDelArchivo / sizeof(pendiente);
    rewind(fp);
    buffer = (pendiente*) malloc(tamanoDelArchivo);
    fread(buffer, sizeof(pendiente), *cantidadDePendientes, fp);
    return buffer;
  } else {
    fclose(fp);
    fp = fopen("agenda.dat", "wb");//si no existe el archivo, crearlo
    fclose(fp);
    return NULL;
  }
  fclose(fp);
}

void interpretarComando(char *opcion, pendiente **pendientes, int *cantidadDePendientes)
{
	int indice;
	char buffer[TAMANO_MAXIMO];
  pendiente pendienteBuffer;

  strcpy(pendienteBuffer.contenido, "");

	switch(opcion[0])
	{
    case 'a':
		case 'A':
      opcion[strcspn(opcion, "\r\n")] = 0; //quitar la nueva linea del input
      strcpy(pendienteBuffer.contenido, (opcion+2));
      pendienteBuffer.hora = 12;
      pendienteBuffer.minuto = 2;

      agregarPendiente(pendienteBuffer, pendientes, cantidadDePendientes);
			break;
		case 'b':
		case 'B':
		  substr(buffer, opcion, 1, strlen(opcion)-1);
      indice = atoi(buffer);
      borrarPendiente(indice, pendientes, cantidadDePendientes);
		  break;
    default:
      printf("No se reconocio la opcion dada, intente de nuevo\n");//notification
      fflush(stdin);
      getchar();
	}
}

int agregarPendiente(pendiente nuevoPendiente, pendiente **pendientes, int *cantidadDePendientes){
  pendiente *temp;

  *cantidadDePendientes+=1;
  temp  = (pendiente*) realloc(*pendientes, sizeof(pendiente) * *cantidadDePendientes);
  if(temp == NULL){
    printf("Ocurrio un error al agregar el pendiente\n");
    return 1;
  }
  temp[*cantidadDePendientes-1] = nuevoPendiente;
  *pendientes = temp;
  if(escribirArchivo(*pendientes, *cantidadDePendientes) != 0){
    printf("Ocurrio un error al guardar el pendiente\n");
    return 1;
  }
  return 0;
}

int borrarPendiente(int indice, pendiente **pendientes, int *cantidadDePendientes){
  int repeticion = *cantidadDePendientes - (indice + 1); //numero de veces que se debe repetir el ciclo
  int i;
  pendiente *temp = *pendientes;
  if(indice <= *cantidadDePendientes || *cantidadDePendientes <= 0){
    for(i=0; i<repeticion; i++){
      temp[indice + i] = temp[indice + i + 1];
    }

    *cantidadDePendientes -= 1;
    temp  = (pendiente*) realloc(*pendientes, sizeof(pendiente) * *cantidadDePendientes);

    if(temp == NULL && *cantidadDePendientes != 0){ //Si borramos el ultimo pendiente, realloc regresara NULL, pero no queremos que regrese la funcion aun
      return 1;
    } else {
      *pendientes = temp;
    }
  }
  escribirArchivo(*pendientes, *cantidadDePendientes);
  return 0;
}
