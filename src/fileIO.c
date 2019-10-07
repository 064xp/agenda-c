#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#include "leerArchivo.h"
#define ARCHIVO_DEFAULT "test.ics"

//regex to match field
// /([field]:.+?)(?=\W[A-Z]+:)/gs

void cargarArchivo(char* nombreDelArchivo, char** buffer){
  FILE *fp;
  int tamanoDelArchivo = 0;

  //si no se dio un nombre, usar el valor default
  nombreDelArchivo = nombreDelArchivo[0] == '\0' ? ARCHIVO_DEFAULT : nombreDelArchivo;

  fp = fopen(nombreDelArchivo, "r");

  if(fp == NULL){
    perror("Ocurrio un error al intentar abrir el archivo\n");
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

int main() {
  char *buffer = NULL;
  cargarArchivo("icalexport.ics", &buffer);

  printf("%s\n", buffer);

  free(buffer);
  return 0;
}
