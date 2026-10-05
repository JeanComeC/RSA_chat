#include "rsa_algo.h"
#include <stdint.h>


uint32_t generate_random(const char *path){
    uint32_t nb_random;
    FILE *f1 = fopen(path,"rb");
    if(!f1){
        perror("Error open urandom");
        exit(1);
    }

    if(fread(&nb_random,sizeof(nb_random),1,f1)!=1){//doit retourner 1, car on veut lire 1 nombre
        perror("Error fread urandom");
        fclose(f1);
        exit(1);
    }

    fclose(f1);
    return nb_random;
}

bool is_prime(uint32_t random_number){
    if(random_number%2==0)return false;
    if(sqrt(random_number)<6)return false;
    uint32_t limit=(uint32_t)sqrt((double)random_number);

    for(uint32_t i=3;i<limit;i+=2){
        if(random_number%i==0){
            //random_number est non-premier
            return false;
        }
    }
    return true;
}

uint64_t calculate_nn(uint32_t pp, uint32_t qq){
    uint64_t nn = (uint64_t)pp * (uint64_t)qq;
    return nn;
}

//

uint64_t calculate_jj(uint32_t pp, uint32_t qq){
    uint64_t jj=((uint64_t)pp-1)*((uint64_t)qq-1);
    return jj;
}

uint64_t pgcd(uint64_t a, uint64_t b){
    while(b!=0){
        uint64_t tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

uint32_t calculate_ee(uint64_t jj){
    uint32_t ee=EE;
    while(pgcd(ee,jj)!=1){
        ee+=2;//on saute les valeurs paires
    }
    return ee;
}

