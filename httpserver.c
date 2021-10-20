#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

int main(){
    struct sockaddr_in serverAddress;
   
    serverAddress.sin_family = AF_INET;// no busacas IP
    serverAddress.sin_port = htons(2727);// decides el puerto (solo admin usa < 1224)
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);// teorica dir ip pero usa cualquiera de la maquina

    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket de comunicacion
    bind(sockfd,(const struct sockaddr *)&serverAddress,sizeof(serverAddress));//bind para registrarme
    listen(sockfd,5);//listo para atender peticiones mantenme una cola de 5
    while(1){
        struct sockaddr_in clientAddress;
        int clientSize = sizeof( clientAddress);
        int clientSocket = accept(sockfd, (struct sockaddr *)&clientAddress,(unsigned int*) &clientSize);// devuelve un canal para hablar con el cliente
        char c;
        char *message = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=ISO-8859-1\n\n   Hello desde gitpod";   //siempre te contesta lo mismo no lee nada el mensaje
        write(clientSocket,message,strlen(message));
        close(clientSocket);
    } //si estos corren dentro de un hilo quedan ibres para mas cliente cada cliente se va por un hilo
}