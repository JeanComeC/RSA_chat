#include "rsa_algo.h"
#include <stdint.h>
#include <stdio.h>


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

//

int64_t pgcd_extended_bezout(int64_t a, int64_t b, int64_t* u, int64_t* v){
    //RAPPEL : Théorème de Bézout
    //a*u + b*v = pgcd(a,b)
    if(!b){
        *u=1;
        *v=0;
        return a;
    }
    int64_t u1;
    int64_t v1;
    int64_t g = pgcd_extended_bezout(b,a%b,&u1,&v1);
    *u = v1;
    *v = u1-(a/b)*v1;
    return g;
}

uint64_t calculate_dd(uint32_t ee, uint64_t jj){
    int64_t u;
    int64_t v;
    if(pgcd_extended_bezout((int64_t)ee,(int64_t)jj,&u,&v)!=1){
        fprintf(stderr,"Error ee is not co-prime with jj.\n");
        exit(1);
    }

    int64_t dd = u%(int64_t)jj;
    if(dd<0){//si d est négatif, on rajoute lui rajoute j, pour qu'iil soit positif.
        dd+=(int64_t)jj;
    }
    return (uint64_t)dd;
}

//

struct Private_key_t generate_private_key(uint32_t* ee){
    uint32_t pp;
    do{
        pp=generate_random(PATH_RANDOM_FILE);
    }while(!is_prime(pp));
    uint32_t qq;
    do{
        qq=generate_random(PATH_RANDOM_FILE);
    }while(!is_prime(qq) || qq==pp);//on vérifie que p et q soit bien différent.
    uint64_t nn=calculate_nn(pp,qq);
    uint64_t jj=calculate_jj(pp,qq);
    *ee=calculate_ee(jj);
    uint64_t dd=calculate_dd(*ee,jj);
    struct Private_key_t private_key={.dd=dd,.nn=nn};
    return private_key;
}

struct Public_key_t generate_public_key(uint32_t ee, uint64_t nn){
    struct Public_key_t public_key={.ee=ee,.nn=nn};
    return public_key;
}

//

uint64_t modular_exponentiation(uint64_t base, uint64_t exposant, uint64_t modulo){
    uint64_t result=1;
    base=base%modulo;

    while(exposant>0){
        if (exposant & 1){ //si le bit de poids faible de exp est 1:
            result=((unsigned __int128)result*base)%modulo; //on multiplie
        }
        base=((unsigned __int128)base*base)%modulo; //on met base au carré
        exposant >>= 1; //on décale exp d'un bit vers la droite
    }

    return result;
}

uint64_t rsa_encrypt(uint64_t message, struct Public_key_t public_key){
    return modular_exponentiation(message,public_key.ee,public_key.nn);
}

uint64_t rsa_decrypt(uint64_t cipher, struct Private_key_t private_key){
    return modular_exponentiation(cipher,private_key.dd,private_key.nn);
}

