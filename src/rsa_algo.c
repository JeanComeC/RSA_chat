#include "rsa_algo.h"
#include <math.h>

uint32_t generate_random(){
    uint32_t nb=0;
    return nb;
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

