#include "common.h"

int send_message(int socket, char* message){
    if(send(socket,message,strlen(message),0)<0){
        perror("Erreur envoie du message");
        return -1;
    }
    return 0;
}

int receive_message(int socket, char* message, size_t max_length){
    
    int resultat=recv(socket,message,max_length-1,0);
    if(resultat==0){
        perror("Peer disconnected");
        return -1;
    }
    else if(resultat<0){
        perror("Erreur réception du message");
        return -1;
    }
    //
    if(message[resultat-1]=='\n'){
        message[resultat-1]='\0';
    }
    else{
        message[resultat]='\0';
    }
    return 0;
}
