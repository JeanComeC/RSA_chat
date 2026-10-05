#ifndef RSA_ALGO_H
#define RSA_ALGO_H

//Bibliothèques
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

//Macro
#define PATH_RANDOM_FILE "/dev/urandom"

//Prototypes
uint32_t generate_random(const char *path); //fonction pour générer un nombre de 32bits aléatoire avec Urandom.
bool is_prime(uint32_t random_number); //fonction pour vérifier la primalité d'un nombre.

#endif
