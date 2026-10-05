#include "common.h"

//structure & prototypes :
struct ThreadData{
    int client_socket;
    struct ClientArray* client_array;
};
void receive_messages_loop(int client_socket, struct ClientArray* client_array);
void* receive_message_thread(void* data);
static void handler(int signum);

int main(void){
//Etape 1: création du socket
    /*voir la doc sur linux avec "man 2 socket"
    la fonction existe déjà dans le systeme.*/
    int server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket<0){
        perror("Error creating socket");
        exit(1);
    }
    //petit réglage pour l'OS
    const int ON = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &ON, sizeof(ON)) < 0) {
    perror("Failed setting socket options");
    exit(EXIT_FAILURE);
    }
//Etape 2: création de l'adresse
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8989);
    if(bind(server_socket,(struct sockaddr*)&address,sizeof(struct sockaddr_in))<0){
        perror("Failed to bind address");
        exit(1);
    }
//etape 3: démarrage du serveur
    if(listen(server_socket,6)<0){
        perror("Error demarrage");
        exit(1);
    }
//création du tableau dynamique:
    struct ClientArray tableau=ca_init();
//etape en pluspour fermer proprement le server avec CTRL + C
    struct sigaction jsp={.sa_handler=handler};
    if(sigaction(SIGINT,&jsp,NULL)==-1){
        perror("Error generale");
    }
//Etape 4: attente des connexions client
    while(should_stop==false){
        struct sockaddr_in socket;
        unsigned int taille = sizeof(struct sockaddr_in);
        int client_socket=accept(server_socket,(struct sockaddr*)&socket,&taille);
        if (client_socket >= 0) {
            printf("A client is connected!\n");
            pthread_t thread_main = 0;
            struct ThreadData threaddata={client_socket,&tableau};
            struct Client client={client_socket,thread_main};
            ca_add(&tableau,client);
            pthread_create(&thread_main,NULL,receive_message_thread,&threaddata);
            pthread_detach(thread_main);
        }
        else {
            perror("Error accepting client connection");
        }
    }
    shutdown(server_socket,SHUT_RDWR);
    close(server_socket);
    printf("\nLe serveur est bien arreté !\n");
}

void receive_messages_loop(int client_socket, struct ClientArray* client_array){
    while(should_stop==false){
        char message[TAILLE_MESSAGE]="";
        if(receive_message(client_socket,message,TAILLE_MESSAGE)==-1){
            ca_remove(client_array,client_socket);
            break;
        }
        //printf("%s \n",message);   //Si on veut vérifier que le serveur a bien reçu les messages.
        for(int i=0;i<client_array->size;i++){
            if(client_socket!=client_array->client[i].socket){
                send_message(client_array->client[i].socket,message);
            }
        }
    }
}

void* receive_message_thread(void* data){
    struct ThreadData tdata=*(struct ThreadData*)data;
    receive_messages_loop(tdata.client_socket,tdata.client_array);
}

static void handler(int signum){
    should_stop = true;
}