#include <stdio.h>
#include <stdlib.h>
#include <time.h>//librería
#include <string.h>

struct tm *conseguirStructTmActual(void);
void conseguirDiaDeLaSemana(char[]);
void conseguirMesString(char[]);
int conseguirDiaDelMes();
int conseguirMesNumero();
int conseguirAnio();

int main()
{
	// int dia, anio; //declaramos las variables necesarias para imprimir la fecha
	// anio=(tiempo->tm_year)+1900;
	// printf("Hoy es: %s %d de %s de %d\n", diaSemana, dia, mesSemana, anio);
	char diaDeLaSemana[15];
	char mes[15];
	int diaDelMes = conseguirDiaDelMes();
	int anio = conseguirAnio();

	conseguirDiaDeLaSemana(diaDeLaSemana);
	conseguirMesString(mes);
	printf("%s %i de %s del %i\n", diaDeLaSemana, diaDelMes, mes, anio);

	return 0;
}

void conseguirDiaDeLaSemana(char buffer[]) //asigna al parametro el dia de la semana en string (Lunes, Martes, ...)
{
	char diasDeLaSemana[7][10] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
	struct tm *tiempo = conseguirStructTmActual();
	strcpy(buffer, diasDeLaSemana[0]);
}

int conseguirDiaDelMes() //regresa dia del mes en numero (1-31)
{
	struct tm *tiempo = conseguirStructTmActual();
	return tiempo->tm_mday;
}

int conseguirMesNumero() //regresa numero del mes actual (0-11)
{
	struct tm *tiempo = conseguirStructTmActual();
	return tiempo->tm_mon;
}

void conseguirMesString(char buffer[]) //asigna al parametro el mes en forma de string (Enero, Febrero, ...)
{
	char meses[12][15] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
	strcpy(buffer, meses[conseguirMesNumero()]);
}

int conseguirAnio()
{
	struct tm *tiempo = conseguirStructTmActual();
	return (tiempo->tm_year)+1900;
}

struct tm *conseguirStructTmActual()
{
	time_t tiempoDelSistema;
	struct tm *tiempo;
	time(&tiempoDelSistema);
	tiempo = localtime(&tiempoDelSistema);
	return tiempo;
}
