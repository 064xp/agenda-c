#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//pruebas
//mas pruebas
//ya me enfadé
//estructuras
struct pendiente { //formato de un solo pendiente
  int hora; //hora del pendiente en formato 24h
  int minuto;
  int completado; //si ya esta completada, sera 1
  char contenido[];
};

struct fecha { //fecha del dia actual
  char fechaString[30];
  int dia;
  int mes;
  char diaSemana[12];
};

//prototipos
void menuPrincipal(int *salir);
int obtenerMes(void);
int obtenerDia(void);
const char* obtenerDiaSemana(void);
void mostrarPendientesDelDia(struct pendiente pendientesDeHoy[10]);

int main(){
  /*array con todos los pendientes del dia actual, actualmente esta fijo en 10,
  posteriormente podria ser alocado dinamicamente*/
  struct pendiente pendientesDeHoy[10];
  struct fecha fechaDeHoy;
  int salir = 0; //cuando el usuario indique que quiere salir, este sera 1

  //loop central del programa
  while(salir != 1){
    menuPrincipal(&salir); //pasamos por referencia para que menuPrincipal pueda modificar 'salir'
  }

  return 0;
}

void menuPrincipal(int *salir){
  //mostar opciones
  //registar eleccion
  //si el usuario quiere salir, salir = true
}

int obtenerMes(){
  //regresar numero del mes actual, con ayuda de time.h
}

int obtenerDia(){
  //regresar numero del dia del mes actual, con ayuda de time.h
}

const char* obtenerDiaSemana(){
  //regresar numero del dia de la semana actual como un string ej. 'Jueves', con ayuda de time.h
}

void mostrarPendientesDelDia(struct pendiente pendientesDeHoy[]){
	//loop por cada pendiente y mostrarlo al usuario
	//pedir un numero, que corresponde a un pendiente especifico para ver detalles

}
