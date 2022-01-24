/*
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: FERNANDO AÑÓN BLANCO LOGIN 2: fernando.anon.blanco
* GROUP: 2.5
* DATE: 01/12/2020
*/

#include "P4_10.h"

/**UMBRAL = 10*/

void OrdenarAux10 (int v[], int izq, int der){
    int x, pivote, i, j;
    if ((izq + 10) <= der){
        x = (rand() % (der - izq + 1)) + izq;
        pivote = v[x];
        intercambiar(izq, x);
        i = izq + 1;
        j = der;
        while (i <= j){
            while (i <= der && v[i] < pivote){
                i++;
            }
            while (v[j] > pivote){
                j--;
            }
            if (i <= j){
                intercambiar(v[i], v[j]);
                i++;
                j--;
            }
        }
        intercambiar(izq, j);
        OrdenarAux10(v, izq, j-1);
        OrdenarAux10(v, j+1, der);
    }
}

void ord_ins10 (int v [], int n) {
    int i, j, x;

    for (i = 1; i < n; i++){
        x = v[i];
        j = i - 1;
        while(j >= 0 && v[j] > x){
            v[j+1] = v[j];
            j = j - 1;
        }
        v[j+1] = x;
    }
}

void ord_rapida10(int v[], int n) {
    OrdenarAux10(v, 0, n-1);
    ord_ins10(v, n);
}