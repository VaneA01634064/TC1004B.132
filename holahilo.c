#include <stdio.h>
#include<pthread.h> //heather no contiene el cod de la funcion -lpthread para agrgar las funciones
#define NUM_THREADS 10000

int saldo;// una var para todos los hilo

void * printHola(void *arg){// generico, pero yo se que es un char
    char *p =(char*)arg;
    printf("Hola desde hilo %s\n", p);//para imprimir cadenas
    pthread_exit(NULL);
}// las funciones que haga solo hagan una cosa esta hace muchas

pthread_mutex_t lockSaldo = PTHREAD_MUTEX_INITIALIZER;

void* suma100(void *arg){
    int lsaldo;
    pthread_mutex_lock(&lockSaldo);
    lsaldo=saldo;
    lsaldo += 100;
    saldo = lsaldo;
    pthread_mutex_unlock(&lockSaldo);
    pthread_exit(NULL);
}
int main(){
    pthread_t threads[NUM_THREADS];
    char *s = "Soy un hilo";
    saldo = 0;
    for(int i=0; i< NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, suma100, NULL); //como no espera nada lo disfrazo de un void con & es para obtener la direccion
    }

    for(int i=0; i< NUM_THREADS; i++){
        pthread_join(threads[i], NULL); //como no espera nada lo disfrazo de un void con & es para obtener la direccion
    }


    printf("Saldo final es %d\n", saldo);
    pthread_exit(NULL); //no se ejecutaria codigo abajo de este  
}