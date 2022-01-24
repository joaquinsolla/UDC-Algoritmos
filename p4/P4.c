/*
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: FERNANDO AÑÓN BLANCO LOGIN 2: fernando.anon.blanco
* GROUP: 2.5
* DATE: 01/12/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "P4_1.h"
#include "P4_10.h"
#include "P4_100.h"

double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);

}

void inicializar_semilla () {
    srand(time(NULL));
}

void aleatorio (int v [], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
}

void ascendente (int v [], int n) {
    int i;
    for (i=0; i < n; i++) {
        v[i] = i;
    }
}

void descendente (int v [], int n) {
    int i;
    for (i=0; i < n; i++){
        v[i] = n-i;
    }
}

void checkOrdenado (int v[], int n) {
    int i = 1;
    while (i < n) {
        if (v[i] < v[i-1]) break;
        else i++;
    }
    if (i == n) printf("ordenado? 1\n");    //1 para ordenado = verdadero
    else printf("ordenado? 0\n");           //0 para ordenado = falso

    printf("\n");
}

void print_vector (int v[], int n){
    int i;
    for (i = 0; i < n; i++) {
        printf("%4d", v[i]);
    }
    printf("\n");
}

void test(){
    int v[10];

    printf("################# TEST #################\n");
    aleatorio(v, 10);
    printf("Vector desordenado:\n");
    print_vector(v, 10);
    checkOrdenado(v, 10);
    ord_rapida1(v, 10);
    printf("Vector ordenado con umbral 1:\n");
    print_vector(v, 10);
    checkOrdenado(v, 10);

    aleatorio(v, 10);
    printf("Vector desordenado:\n");
    print_vector(v, 10);
    checkOrdenado(v, 10);
    ord_rapida10(v, 10);
    printf("Vector ordenado con umbral 10:\n");
    print_vector(v, 10);
    checkOrdenado(v, 10);

    aleatorio(v, 10);
    printf("Vector desordenado:\n");
    print_vector(v, 10);
    checkOrdenado(v, 10);
    ord_rapida100(v, 10);
    printf("Vector ordenado con umbral 100:\n");
    print_vector(v, 10);
    checkOrdenado(v, 10);
}

void medirTiempos(void iVector (int [], int), bool print,
                  void metodoOrdenacion (int [], int),
                  double cInf, double cAj, double cSup) {
    int i, j, n = 500, v[32000];
    double t1, t2, t, t1r, t2r;
    if (print) printf("%10s%15s%9s%.3f%s%9s%.3f%s%9s%.3f%s\n", "n", "t(n)",
                      "t/(n^", cInf, ")*log(n)", "t/(n^", cAj, ")*log(n)",
                      "t/(n^", cSup, ")*log(n)");
    while (n <= 32000) {
        iVector (v, n);                         //Inicializamos el vector
        t1 = microsegundos();
        metodoOrdenacion (v, n);                //Se ordena el vector con el
        t2 = microsegundos();                   //método indicado
        t = t2 - t1;
        if (t < 500) {                          //SI EL TIEMPO ES INFERIOR A
            t1 = microsegundos();               //500 MICROSEGUNDOS:
            for (i = 0; i < 1000; i++) {
                iVector (v, n);                 //Inicializamos los vectores
                metodoOrdenacion (v, n);        //desordenados de nuevo
            } t2 = microsegundos();             //y los volvemos a ordenar
            t1r = t2 - t1;
            t1 = microsegundos();
            for (j = 0; j < 1000; j++) {
                iVector (v, n);
            } t2 = microsegundos();             //Eliminamos el tiempo empleado
            t2r = t2 - t1;                      //en inicializar los vectores
            t = (t1r-t2r)/1000;
            if (print) {
                    printf("%5s%5i%15.3f%22.7f%22.7f%22.7f\t%s\n", "", n, t,
                           t/(pow(n, cInf)*log(n)), t/(pow(n, cAj)*log(n)),
                           t/(pow(n, cSup)*log(n)), "(*)");}}
        else {
            if (print) {
                    printf("%5s%5i%15.3f%22.7f%22.7f%22.7f\n", "", n, t,
                           t/(pow(n, cInf)*log(n)), t/(pow(n, cAj)*log(n)),
                           t/(pow(n, cSup)*log(n)));}
        } n = n*2;                              //Incrementamos n
    } if (print) printf("\n"); }

void printTiempos (void iVector (int [], int),
                   double cInf, double cAj, double cSup) {
    int i;

    for (i = 0; i < 2; i++) {
        if (i==1){
            printf("UMBRAL 1:\n");
            medirTiempos(iVector, true, ord_rapida1,cInf, cAj, cSup);
            printf("UMBRAL 10:\n");
            medirTiempos(iVector, true, ord_rapida10,cInf, cAj, cSup);
            printf("UMBRAL 100:\n");
            medirTiempos(iVector, true, ord_rapida100,cInf, cAj, cSup);
        }else {
            medirTiempos(iVector, false, ord_rapida1, cInf, cAj, cSup);
            medirTiempos(iVector, false, ord_rapida10, cInf, cAj, cSup);
            medirTiempos(iVector, false, ord_rapida100, cInf, cAj, cSup);
        }
    }
}

void results(){
    /** n=500 */

    double cInfR = 1.6, cAjR = 1.825, cSupR = 2,
            cInfD = 1.6, cAjD = 1.875, cSupD = 2.1,
            cInfA = 0.7, cAjA = 0.86, cSupA = 1;
    printf("############### TIEMPOS: ###############\n");
    printf("Ordenación con inicializacion aleatoria\n");
    printTiempos(aleatorio, cInfR, cAjR, cSupR);
    printf("Ordenación con inicializacion descendente\n");
    printTiempos(descendente, cInfD, cAjD, cSupD);
    printf("Ordenación con inicializacion ascendente\n");
    printTiempos(ascendente, cInfA, cAjA, cSupA);
}

int main() {

    inicializar_semilla();
    test();
    results();

    return 0;
}