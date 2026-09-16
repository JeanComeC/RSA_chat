#include "common.h"

#ifndef CLIENT_ARRAY
#define CLIENT_ARRAY
//
struct Client{
    int socket;
    pthread_t thread;
};

struct ClientArray{
    struct Client* client;
    int size;
    int capacity;
};
//prototypes
struct ClientArray ca_init();
void ca_add(struct ClientArray* array, struct Client client);
void ca_remove(struct ClientArray* array, int socket);

#endif