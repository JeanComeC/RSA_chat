#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <asm-generic/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "client_array.h"
#include <signal.h>
#include <unistd.h>
//MACRO
#define TAILLE_MESSAGE 2048 //le nom d'utilisateur en prend 50 octets maximum.
//prototypes:
int send_message(int socket, char* message);
int receive_message(int socket, char* message, size_t max_length);
//variables globales
static volatile bool should_stop = false;

#endif

//+--------------------------------------------------------------------------+
//|J'ai réussi à faire tourner le client sur mon téléphone avec Termux. Donc |
//|le code est multi-plateforme !!                                           |
//+--------------------------------------------------------------------------+
