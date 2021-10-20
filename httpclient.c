#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

extern int h_errno;
//protocolo de un clente a http

int main(int argc, char **argv) { //arreglo con parametros que le pase
    char *hostName = argv[1];
    char *message = "GET / HTTP/1.0\r\n\r\n"; //MENSAJE A TRANSMITIR
    char c;
    //datos estructuras no las puedes inicializar a 0
    struct sockaddr_in serverAddress;//var tipo socj=ket contiene direccion y puertos es un canal de comunicaciom
    struct hostent *serverInfo = gethostbyname(hostName);//sist operativo necesito laIP
    bzero(&serverAddress, sizeof(serverAddress));// su argumento es una dir de memoria y la inicializa en 0
    serverAddress.sin_family = AF_INET;//ip version 4
    serverAddress.sin_port = htons(80);//puerto a conectar htons se encargan que los bits vayan en orden
    // serverAddress.sin_addr = serverInfo->h_addr_list[0]; // no se puede    
    bcopy((char *)serverInfo->h_addr, //copia la direccion y ya esta lista
	  (char *)&serverAddress.sin_addr.s_addr, serverInfo->h_length);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //crear un canal tipo stream canal ida y vuelta
    connect(sockfd,(const struct sockaddr *)&serverAddress,sizeof(serverAddress));
    //protocolo
    write(sockfd,message,strlen(message));//escribe el socket
    while(read(sockfd,&c,1)){
        printf("%c",c);//lemos un bit a la vez y escrbiendo ala pantalla
    }
    close(sockfd);
    printf("\n");

    return 0;
}
