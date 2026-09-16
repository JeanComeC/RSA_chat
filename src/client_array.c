#include "common.h"

struct ClientArray ca_init(){
    struct ClientArray newtab;
    newtab.client = malloc(2*sizeof(struct Client));
    if(newtab.client==NULL){
        perror("Error allocation mémoire");
        exit(1);
    }
    newtab.capacity=2;
    newtab.size=0;
    return newtab;
}

void ca_add(struct ClientArray* array, struct Client client){
    if(array->size<array->capacity){
        array->client[array->size]=client;
        array->size++;
    }
    else{
        struct Client *newclient=malloc(2*array->capacity*sizeof(struct Client));
        if(newclient==NULL){
            perror("Erreur allocation mémoire");
            exit(1);
        }
        array->capacity=2*array->capacity;
        for(int i=0;i<array->size;i++){
            newclient[i]=array->client[i];
        }
        free(array->client);
        array->client=newclient;
        array->client[array->size]=client;
        array->size++;
    }
}

void ca_remove(struct ClientArray* array, int socket){
    for(int i=0;i<array->size;i++){
        if(array->client[i].socket==socket){
            array->client[i]=array->client[array->size-1];
            array->size--;
        }
    }
}