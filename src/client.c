#include "common.h"

void send_message_loop(int client_socket,char* pseudo_client);
void* receive_messages_loop_thread(void* socket);
const char* choice_ipserver(void);

int main(void){
    
//Etape 0: ajout perso
    char pseudo_client [50]="";
    do{
        printf("Your name : ");
        scanf("%49s",pseudo_client);
    }while(strlen(pseudo_client)<=1);//pour s'assurer que le client ait rentré un nom d'utilisateur.
//Etape 1: création du socket
    /*voir la doc sur linux avec "man 2 socket"
    la fonction existe déjà dans le systeme.*/
    int client_socket=socket(AF_INET,SOCK_STREAM,0);
    if(client_socket<0){
        perror("Error creating socket");
        exit(1);
    }
//petit réglage pour l'OS
    const int ON = 1;
    if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &ON, sizeof(ON)) < 0) {
    perror("Failed setting socket options");
    exit(EXIT_FAILURE);
    }
//Etape 2: création de l'adresse
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(choice_ipserver());
    address.sin_port = htons(8989);
//Etape 3: connexion au serveur
    if(connect(client_socket,(struct sockaddr*)&address,sizeof(struct sockaddr_in))<0){
        perror("Error connexion");
        exit(1);
    }
    else{
        printf("Client connected !\n\n");
        
        //Ajout thread:
        pthread_t thread_main;
        pthread_create(&thread_main,NULL,receive_messages_loop_thread,&client_socket);
        pthread_detach(thread_main);
        send_message_loop(client_socket,pseudo_client);
    }
    shutdown(client_socket,SHUT_RDWR);
    close(client_socket);
}

void send_message_loop(int client_socket,char* pseudo_client){//j'ai modifié le prototype pour récupérer le pseudo du client déclaré dans le main.
    while(should_stop==false){
        char message_user[TAILLE_MESSAGE-50]="";
        fgets(message_user,TAILLE_MESSAGE-50,stdin);
        // Supprime le retour à la ligne du pseudo_client lié à fgets
        size_t len = strlen(pseudo_client);
        if (len > 0 && pseudo_client[len - 1] == '\n') {
            pseudo_client[len - 1] = '\0';
        }
        //je rajoute le nom d'utilisateur pour pouvoir reconnaitre les messages dans le chat :
        char message_final[TAILLE_MESSAGE]="";
        sprintf(message_final,"%s : %s",pseudo_client,message_user);
        //printf("%s\n",message_final);
        send_message(client_socket,message_final);
    }
}

void receive_messages_loop(int client_socket){
    while(should_stop==false){
        char message[TAILLE_MESSAGE]="";
        if(receive_message(client_socket,message,strlen(message))==-1){
            break;
        }
        printf("%s \n",message);
    }
}

void* receive_messages_loop_thread(void* socket){
    receive_messages_loop(*(int*)socket);
}

const char* choice_ipserver(void){
    //peut etre faire une table avec un nom et une ip, pour que ce soit plus lisible (?)
    printf("\nChoose your server :\n");
    printf("JC => 0\nPaul => 1\nAlexandre => 2\n");
    int reponse;
    scanf("%d",&reponse);
    switch(reponse){
        case 0 : return "127.0.0.1";
        case 1 : return "10.30.43.192";
        case 2 : return "10.30.43.188";
        default: choice_ipserver();
    }
}