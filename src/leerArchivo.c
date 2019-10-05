#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <lib/pcre3.h>
#include <pcre3.h>

struct pendiente {
  int fecha;
  char titulo[];
};

int main() {
  struct pendiente pendiente;
  char c;
  char strBuff[77];
  FILE *fp;

  fp = fopen("test.ics", "r+");

  if(fp == NULL){
    perror("hubo un error al abrir el archivo...");
  } else {
    while((c = fgetc(fp)) != EOF){
      strBuff[strlen(strBuff)-1] = c;
      strBuff[strlen(strBuff)] = '\0';
    }//end while != EOF
    // printf("%s\n", strBuff);
  }
  fclose(fp);
  return 0;
}
