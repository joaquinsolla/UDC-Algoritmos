/*
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: FERNANDO AÑÓN BLANCO LOGIN 2: fernando.anon.blanco
* GROUP: 2.5
* DATE: 06/11/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

//IMPLEMENTACIÓN ARBOL

struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

static struct nodo *crearnodo (int e) {
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL) {
        printf("memoria agotada\n"); exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

arbol insertar (int e, arbol a) {
    if (a == NULL)
        return crearnodo(e);
    else if (e < a->elem)
        a->izq = insertar(e, a->izq);
    else if (e > a->elem)
        a->der = insertar(e, a->der);
    else
        a->num_repeticiones++;
    return a;
}

arbol creararbol(){
    arbol a = NULL;
    return a;
}

int esarbolvacio(arbol a){
    if (a == NULL) return 1;
    else return 0;
}

posicion buscar(int elem, arbol a){
    if (a == NULL) return NULL;
    else if (elem == a->elem) return a;
    else if (elem < a->elem) return buscar(elem, a->izq);
    else return  buscar(elem, a->der);
}

arbol eliminararbol(arbol a){
    if(a!=NULL){
        eliminararbol(a->izq);
        eliminararbol(a->der);
        free(a);
        a=NULL;
    }
    return a;
}

posicion hijoizquierdo(arbol a){
    if (a == NULL) return NULL;
    return a->izq;
}

posicion hijoderecho(arbol a){
    if (a == NULL) return NULL;
    return a->der;
}

int elemento(posicion a){
    if (a == NULL) return -1;
    return a->elem;
}

int numerorepeticiones(posicion a){
    if (a == NULL) return -1;
    return a->num_repeticiones;
}

int max (int a, int b){
    if (a >= b) return a;
    else return b;
}

int altura(arbol a){
    if (a == NULL) return -1;
    else return  1 + max(altura(a->izq), altura(a->der));
}

void visualizar(arbol a){
    if(a!=NULL){
        printf("(");
        if(a->izq!=NULL)	//si el lado izq no es null
            visualizar(a->izq);
        printf(" %d ", a->elem);
        if(a->der!=NULL)	//si el lado drch no es null
            visualizar(a->der);
        printf(")");
    }else{
        printf("()");
    }
}

//TEST

arbol test_insercion (arbol tree);
void test_display (arbol tree);
void test_busqueda (arbol tree);
arbol test_borrado (arbol tree);

void test(){
    arbol tree;
    printf("### TEST ###\n");
    tree = creararbol();
    tree=test_insercion(tree);
    test_display(tree);
    test_busqueda(tree);
    test_borrado(tree);
    printf("\n");
}

arbol test_insercion (arbol tree){
    int i = 0;
    int v[] = {3, 1, 2, 5, 4, 5};

    if (esarbolvacio(tree))
        printf("arbol vacio: ().\n");
    printf("altura del arbol: %d\n", altura(tree));

    while (i <= 5) {
        printf("inserto un %i\n", v[i]);
        tree = insertar(v[i], tree);
        i++;
    }
    return tree;
}

void test_display (arbol tree){
    printf("arbol: ");
    visualizar(tree);
    printf(".\n");
    printf("altura del arbol: %d\n", altura(tree));
}

void test_busqueda (arbol tree){
    int i = 1;
    while (i <= 6) {
        printf("busco %i y ", i);
        if (buscar(i, tree) != NULL)
            printf("encuentro %i repetido: %i veces\n", i, numerorepeticiones(buscar(i, tree)));
        else
            printf("no encuentro nada\n");
        i++;
    }
}

arbol test_borrado (arbol tree){
    printf("borro todos los nodos liberando la memoria:\n");
    tree = eliminararbol(tree);
    if (esarbolvacio(tree))
        printf("arbol vacio: ().\n");
    printf("altura del arbol: %d\n", altura(tree));
    return tree;
}

//TIEMPOS

double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);

}

void aleatorio (int v [], int n) {
    int i;
    for (i = 0; i < n; i++){
        v[i] = (rand() % (n - (-n) + 1)) + (-n);
    }
}

void medirTiempos (int n, bool print, double ts[]) {
    int i, v[256000], k;
    double in1, in2, bus1, bus2;
    arbol tree = creararbol();
    aleatorio(v, n);
    in1 = microsegundos();
    for (i = 0; i < n; i++) {tree=insertar(v[i], tree);}
    in2 = microsegundos();
    ts[0] = in2 - in1;
    if (print) printf("%15.0f    ", ts[0]);

    aleatorio(v, n);
    bus1 = microsegundos();
    for (i = 0; i < n; i++) {buscar(v[i], tree);}
    bus2 = microsegundos();
    ts[1] = bus2 -bus1;
    if (ts[1] < 500) {
        bus1 = microsegundos();
        for (k = 0; k < 1000; k++) {
            aleatorio(v, n);
            for (i = 0; i < n; i++) {
                buscar(v[i], tree);
            }
        }bus2 = microsegundos();
        ts[1] = (bus2 - bus1) / 1000;
        tree = eliminararbol(tree);
        if (print) printf("(*) %9.0f    ", ts[1]);}
    else { tree = eliminararbol(tree);
        if (print) printf("%13.0f    ", ts[1]);}}


void imrpimirTiempos1 (double insArray[], double busArray[]){
    int n, i, x = 0, y = 0;
    double ts[2];
    printf("### MEDICIÓN DE TIEMPOS ###\n");
    printf("\n%6s %14s %16s\n", "n", "t_ins(n)", "t_bus(n)");
    for (i = 1; i < 3 ; i++) {
        n = 8000;
        while (n <= 256000) {
            if (i==2) printf("%6d", n);
            if (i==2) {
                medirTiempos(n, true, ts);
                insArray[x] = ts[0];
                busArray[y] = ts[1];
                printf("\n");
                x++; y++;
            } else {
                medirTiempos(n, false, ts);
            }
            n=n*2;
        }
    }
}

void imprimirtiempos2 (double insArray[], double busArray[]){
    int n = 8000, x = 0;
    double cInsInf, cInsAj, cInsSup, cBusInf, cBusAj, cBusSup;
    printf("\nInsercion de n elementos\n");
    printf("%6s%15s%16s%15s%15s\n", "n", "t(n)", "t(n)/n",
           "t(n)/n^1.25", "t(n)/n^1.4");
    while (n<=256000){
        cInsInf = pow(n, 1); cInsAj = pow(n, 1.25); cInsSup = pow(n, 1.4);
        printf("%6d%15.3f", n, insArray[x]);
        printf("%16.6f%15.6f%15.6f", (insArray[x]/cInsInf),
               (insArray[x]/cInsAj), (insArray[x]/cInsSup));
        printf("\n");
        n=n*2; x++;
    }

    printf("\nBusqueda de n elementos\n");
    printf("%6s%15s%16s%15s%15s\n", "n", "t(n)", "t(n)/n",
           "t(n)/n^1.26", "t(n)/n^1.4");
    n=8000; x=0;
    while (n<=256000){
        cBusInf = n; cBusAj = pow(n, 1.26); cBusSup = pow(n, 1.4);
        printf("%6d%15.3f", n, busArray[x]);
        printf("%16.6f%15.6f%15.6f", (busArray[x]/cBusInf),
               (busArray[x]/cBusAj), (busArray[x]/cBusSup));
        printf("\n");
        n=n*2; x++;
    }
}

//EJECUCIÓN

int main() {
    double insArray[6], busArray[6];
    test();
    imrpimirTiempos1(insArray, busArray);
    imprimirtiempos2(insArray, busArray);

    return 0;
}