#ifndef RSA_ALGO_H
#define RSA_ALGO_H

//Bibliothèques
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>

//Prototypes
u_int32_t generate_random();
bool is_primacy(u_int32_t random_number);

#endif
