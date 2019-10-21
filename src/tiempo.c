#include "tiempo.h"

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
