#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

double microsegundos(){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0) return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
	
	}

int fib1 (int n){

    if (n<2) {
        return n;
    } else{
        int m = fib1(n-1) + fib1(n-2);
        return m;
    }
}

int fib2 (int n){

    int i=1, j =0;

    for (int k=1; k<=n ; ++k) {
        j=i+j;
        i=j-i;
    }
    return j;
}

int fib3 (int n){
    int i, j, k, h, t;
    i=1; j=0; k=0; h=1;
    while (n>0) {
        if ((n%2) != 0) {
            t=j*h;
            j=(i*h)+(j*k)+t;
            i=(i*k)+t;
        }
        t=h*h;
        h=(2*k*h)+t;
        k=(k*k)+t;
        n=n/2;
    }
    return j;
}

void test(){
	
	int n1=3, n2=6, n3=11;
	
	printf ("Número de la posición %d con fib1: %d\n", n1, fib1(n1));
	printf ("Número de la posición %d con fib2: %d\n", n1, fib2(n1));
	printf ("Número de la posición %d con fib3: %d\n", n1, fib3(n1));
	printf ("Número de la posición %d con fib1: %d\n", n2, fib1(n2));
	printf ("Número de la posición %d con fib2: %d\n", n2, fib2(n2));	
	printf ("Número de la posición %d con fib3: %d\n", n2, fib3(n2));	
	printf ("Número de la posición %d con fib1: %d\n", n3, fib1(n3));	
	printf ("Número de la posición %d con fib2: %d\n", n3, fib2(n3));	
	printf ("Número de la posición %d con fib3: %d\n", n3, fib3(n3));
	}

int main() {


    int n, k;
    double t1, t2, t, x, y, z;
	
	test();
	
	printf ("\nFIB1\n");
	printf ("\t   N\t\t  T\t\tX\t\tY\t\tZ\n");
	for (n=2; n<=32; n=2*n){
	  
		int try=1000;
		bool mod=false;
	  
		t1=microsegundos();
		fib1(n);
		t2=microsegundos();
		
		t=t2-t1;
		
		if (t<500){
		t1=microsegundos();
		for (k=0; k<=try; k++){
		fib1(n);}
		t2=microsegundos();
		t=(t2-t1)/try;
		mod=true;
		}
		
		x= t/ (pow(1.1, n));
		y= t/ (pow(((1+sqrt(5))/2), n));
		z= t/ (pow(2, n));
		
		printf("%12d\t%15.4f\t%15.9f\t%15.9f\t%15.9f\t", n, t, x, y, z);
		
		if (mod==true){
			printf("\t*\n");	
			} else {printf("\n");}	
	}
	

	printf ("\nFIB2\n");
	printf ("\t   N\t\t  T\t\tX\t\tY\t\tZ\n");
	for (n=1000; n<=10000000; n=10*n){
	  
		int try=1000;
		bool mod=false;
	  
		t1=microsegundos();
		fib2(n);
		t2=microsegundos();
		
		t=t2-t1;
		
		if (t<500){
		t1=microsegundos();
		for (int k=1; k<=try; ++k){
		fib2(n);}
		t2=microsegundos();
		t=(t2-t1)/try;
		mod=true;
		}
		
		x= t/ (pow(n, 0.8));
		y= t/ (n);
		z= t/ (n*(log(n)));
		
		printf("%12d\t%15.4f\t%15.9f\t%15.9f\t%15.9f\t", n, t, x, y, z);
		
		if (mod==true){
			printf("\t*\n");	
			} else {printf("\n");}	
	}
	

	printf ("\nFIB3\n");
	printf ("\t   N\t\t  T\t\tX\t\tY\t\tZ\n");
	for (n=1000; n<=10000000; n=10*n){
	  
		int try=1000;
		bool mod=false;
	  
		t1=microsegundos();
		fib3(n);
		t2=microsegundos();
		
		t=t2-t1;
		
		if (t<500){
		t1=microsegundos();
		for (int k=1; k<=try; ++k){
		fib3(n);}
		t2=microsegundos();
		t=(t2-t1)/try;
		mod=true;
		}
		
		x= t/ (sqrt(log(n)));
		y= t/ (log(n));
		z= t/ (pow(n, 0.5));
		
		printf("%12d\t%15.4f\t%15.9f\t%15.9f\t%15.9f\t", n, t, x, y, z);
		
		if (mod==true){
			printf("\t*\n");	
			} else {printf("\n");}	
	}
	
    return 0;
}
