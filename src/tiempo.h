#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <time.h>
#include <string.h>

struct tm *conseguirStructTmActual(void);
void conseguirDiaDeLaSemana(char[]);
void conseguirMesString(char[]);
int conseguirDiaDelMes();
int conseguirMesNumero();
int conseguirAnio();

#endif
