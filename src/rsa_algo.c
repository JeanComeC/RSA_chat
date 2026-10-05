#include "rsa_algo.h"
#include <math.h>
#include <stddef.h>
#include <sys/types.h>

u_int32_t generate_random(){
    u_int32_t nb=0;
    return nb;
}

bool is_primacy(u_int32_t random_number){
    if(random_number%2==0)return false;
    if(sqrt(random_number)<6)return false;
    for(u_int32_t i=3;i<sqrt(random_number);i=+2){
        if(random_number%i==0){
            //random_number est non-premier
            return false;
        }
    }
    return true;
}

