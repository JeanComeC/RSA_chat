#ifndef RSA_ALGO_H
#define RSA_ALGO_H

//Bibliothèques
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

//Prototypes
uint32_t generate_random();
bool is_prime(uint32_t random_number); //fonction pour vérifier la primalité d'un nombre.

#endif
