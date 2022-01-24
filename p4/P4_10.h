/*
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: FERNANDO AÑÓN BLANCO LOGIN 2: fernando.anon.blanco
* GROUP: 2.5
* DATE: 01/12/2020
*/

#ifndef P4_P4_10_H
#define P4_P4_10_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define intercambiar(x, y) {typeof(x) temp = x; x = y; y = temp;}

void OrdenarAux10 (int v[], int izq, int der);
void ord_ins10 (int v [], int n);
void ord_rapida10(int v[], int n);

#endif //P4_P4_10_H
