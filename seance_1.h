#ifndef BLOCK_CHAIN_H
#define BLOCK_CHAIN_H

int naive_is_prime(long);
long modpow_naive(long a,long m,long n);

long modpow(long a, long m,long n);
long modpow_rec(long a, long m,long n);                             //Même fonction que modpow mais de façon récursive

//Fonctions fournies dans le sujet
int witness ( long a , long b , long d , long p ); 
long rand_long ( long low , long up );
int is_prime_miller ( long p , int k );
long extended_gcd(long s, long t, long *u, long *v);
void print_long_vector ( long * result , int size );

long random_prime_number(int low_size, int up_size, int k );
void generate_key_values(long p, long q, long *n, long *s, long *u);
long* encrypt(char *chaine, long s, long n);
char* decrypt(long *crypted, int size, long u, long n);

#endif
