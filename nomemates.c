#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void handle(int numsignal){
    printf("jajaja %d\n", numsignal);
}

int main(){
    signal(2, handle); //se va aejecutar despues, aqui no se usa y no se pone()
    while(1){ //while inifinito ya solo con 9
        printf("trabajando\n");
        sleep(1);
    }
    return 0;
}