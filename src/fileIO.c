#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#include "leerArchivo.h"
#include "re.h"
#define ARCHIVO_DEFAULT "agenda.ics"

//////////////prueba///////////////////////
struct pendiente { //formato de un solo pendiente
  int hora; //hora del pendiente en formato 24h
  int minuto;
  int completado; //si ya esta completada, sera 1
  char contenido[];
};
//////////////prueba///////////////////////

//regex to match field
// /([field]:.+?)(?=\W[A-Z]+:)/gs

void cargarArchivo(char* nombreDelArchivo, char** buffer){
  FILE *fp;
  int tamanoDelArchivo = 0;

  //si no se dio un nombre, usar el valor default
  nombreDelArchivo = nombreDelArchivo[0] == '\0' ? ARCHIVO_DEFAULT : nombreDelArchivo;

  fp = fopen(nombreDelArchivo, "r");

  if(fp == NULL){
    printf("Ocurrio un error al intentar abrir el archivo\n");
    exit(1);
  } else {
    //consigue el tamaño del archivo
    fseek(fp, 0L, SEEK_END);
    tamanoDelArchivo = ftell(fp);
    rewind(fp);

    *buffer = (char*) malloc(tamanoDelArchivo);
    if(buffer == NULL){
      printf("Ocurrio un error al cargar el archivo [malloc]\n");
    } else {

      fread(*buffer, 1, tamanoDelArchivo, fp)  ;
    }//fin error check malloc
  }//fin error check al abrir archivo
  fclose(fp);
}//fin cargarArchivo

struct pendiente *conseguirPendientesPorDia(int dia, int mes, int year){
  char *buffer = NULL;
  char *fechaConFormato;
  sprintf(fechaConFormato,"%i%i%i", year, mes, dia);
  cargarArchivo("", &buffer);


}

/////////TODO DEBAJO DE AQUI ES PARA FINES DE PRUBEA, SE DEBERA BORRAR AL FINAL
int main() {
  char *buffer = NULL;
  cargarArchivo("icalexport.ics", &buffer);

  printf("%s\n", buffer);

  free(buffer);
  return 0;
}
