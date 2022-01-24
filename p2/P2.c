/*
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: FERNANDO AÑÓN BLANCO LOGIN 2: fernando.anon.blanco
* GROUP: 2.5
* DATE: 24/10/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>


double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);

}

void inicializar_semilla () {
    srand(time(NULL));
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

void print_vector (int v[], int n){
    int i;
    for (i = 0; i < n; i++) {
        printf("%4d", v[i]);
    }
    printf("\n");
}

void ord_ins (int v [], int n) {
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

void ord_shell (int v [], int n) {
    int inc = n, i, j, tmp, seg;

    do {
        inc = inc/2;
        for (i = inc; i < n; i++) {
            tmp = v[i];
            j = i;
            seg = 1;
            while ((j-inc >= 0) && (seg == 1)) {
                if (tmp < v[j-inc]) {
                    v[j] = v[j-inc];
                    j = j-inc;
                } else seg = 0;
            }
            v[j] = tmp;
        }
    }
    while (inc != 1);
}

void testVectores(void metodoOrdenacion(int[], int), char nombre[]) {
    int v1[17];
    //INICIALIZACIÓN ALEATORIA
    printf("Inicializacion aleatoria:\n");
    aleatorio(v1, 17);
    print_vector(v1, 17);
    checkOrdenado(v1, 17);
    //ORDENACIÓN
    printf("%s%s\n", "Ordenacion ", nombre);
    metodoOrdenacion(v1, 17);
    print_vector(v1, 17);
    checkOrdenado(v1, 17);
    //INICIALIZACIÓN DESCENDENTE
    printf("Inicializacion descendente: \n");
    descendente(v1, 17);
    print_vector(v1, 17);
    checkOrdenado(v1, 17);
    //ORDENACIÓN
    printf("%s%s\n", "Ordenacion ", nombre);
    metodoOrdenacion(v1, 17);
    print_vector(v1, 17);
    checkOrdenado(v1, 17);
    //INICIALIZACIÓN ASCENDENTE
    printf("Inicializacion ascendente: \n");
    ascendente(v1, 17);
    print_vector(v1, 17);
    checkOrdenado(v1, 17);
    //ORDENACIÓN
    printf("%s%s\n", "Ordenacion ", nombre);
    metodoOrdenacion(v1, 17);
    print_vector(v1, 17);
    checkOrdenado(v1, 17);

    printf("\n");
}

void medirTiempos(void iVector (int [], int),
                  void metodoOrdenacion (int [], int),
      /*COTAS:*/  double cInferior, double cAjustada, double cSuperior) {

    int i, j, n = 500, v[32000];
    double t1, t2, t, t1r, t2r;
    printf("%15s%15s%11s%0.2f%11s%0.2f%11s%0.2f\n", "n", "t(n)", "t(n)/n^",
           cInferior, "t(n)/n^", cAjustada, "t(n)/n^", cSuperior);
    while (n <= 32000) {
        iVector (v, n);                         //Inicializamos el vector
        t1 = microsegundos();
        metodoOrdenacion (v, n);                //Se ordena el vector con el
        t2 = microsegundos();                   //método indicado
        t = t2 - t1;
        if (t < 500) {                          //SI EL TIEMPO ES INFERIOR A
            t1 = microsegundos();               //500 MICROSEGUNDOS:
            for (i = 10; i <= 100000; i=i*10) {
                iVector (v, n);                 //Inicializamos los vectores
                metodoOrdenacion (v, n);        //desordenados de nuevo
            }                                   //y los volvemos a ordenar
            t2 = microsegundos();
            t1r = t2 - t1;
            t1 = microsegundos();
            for (j = 10; j <= 100000; j=j*10) {
                iVector (v, n);
            }
            t2 = microsegundos();               //Eliminamos el tiempo empleado
            t2r = t2 - t1;                      //en inicializar los vectores
            t = (t1r-t2r)/100000;
            printf("%10s%5i%15.3f%15.6f%15.6f%15.6f\t%s\n", "", n, t,
                   t/pow(n, cInferior), t/pow(n, cAjustada),
                   t/pow(n, cSuperior), "(*)");
        }
        else {
            printf("%10s%5i%15.3f%15.6f%15.6f%15.6f\n", "", n, t,
                   t / pow(n, cInferior), t / pow(n, cAjustada),
                   t / pow(n, cSuperior));
        } n = n*2;                                  //Incrementamos n
    }
    printf("\n");
}

void printTiempos () {
    int i, j;
    //COTAS
    double cShell1 = 1, cShell2 = 1.15, cShell3 = 1.3, cIns1 = 1.8,
    cIns2 = 2, cIns3 = 2.2, cInsAsc1 = 0.8, cInsAsc2 = 1, cInsAsc3 = 1.2;//COTAS

    printf("SHELL:\n");
    for (i = 0; i < 3; i++) {
        printf("REP %d - Ordenación Shell con inicializacion "
               "desordenada\n", i+1);
        medirTiempos(aleatorio, ord_shell, cShell1, cShell2, cShell3);

        printf("REP %d - Ordenación Shell con inicializacion "
               "ascendente\n", i+1);
        medirTiempos(ascendente, ord_shell, cShell1, cShell2, cShell3);

        printf("REP %d - Ordenación Shell con inicializacion "
               "descendente\n", i+1);
        medirTiempos(descendente, ord_shell, cShell1, cShell2, cShell3);
    }
    printf("POR INSERCION:\n");
    for (j = 0; j < 3; j++) {
        printf("REP %d - Ordenacion por insercion con inicializacion "
               "desordenada\n", j+1);
        medirTiempos(aleatorio, ord_ins, cIns1, cIns2, cIns3);

        printf("REP %d - Ordenacion por insercion con inicializacion "
               "ascendente\n", j+1);
        medirTiempos(ascendente, ord_ins, cInsAsc1, cInsAsc2, cInsAsc3);

        printf("REP %d - Ordenacion por insercion con inicializacion "
               "descendente\n", j+1);
        medirTiempos(descendente, ord_ins, cIns1, cIns2, cIns3);
    }
}


int main() {

    inicializar_semilla();
    testVectores(ord_shell, "por Shell:");
    testVectores(ord_ins, "por inserción:");
    printTiempos();

    return 0;
}