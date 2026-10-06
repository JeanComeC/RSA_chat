#ifndef RSA_ALGO_H
#define RSA_ALGO_H

//Bibliothèques
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

//Macros
#define PATH_RANDOM_FILE "/dev/urandom"
#define EE 65537

//Prototypes
uint32_t generate_random(const char *path); //fonction pour générer un nombre de 32bits aléatoire avec Urandom.
bool is_prime(uint32_t random_number); //fonction pour vérifier la primalité d'un nombre.
uint64_t calculate_nn(uint32_t pp, uint32_t qq); //fonction pour calculer n, le produit de p et q

uint64_t calculate_jj(uint32_t pp, uint32_t qq); //fonction pour calculer j.
uint64_t pgcd(uint64_t a, uint64_t b); //fonction pour calculer le PGCD (Euclide) entre 2 nombres.
uint32_t calculate_ee(uint64_t jj); //fonction pour calculer e, à partir de j.

int64_t pgcd_extended_bezout(int64_t a, int64_t b, int64_t* u, int64_t* v); //fonction pour calculer les coefficients de Bézout.
uint64_t calculate_dd(uint64_t ee, uint64_t jj); //fonction pour calculer d.

#endif
