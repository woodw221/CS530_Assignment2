#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct tsafenode {
    struct tsafenode *next;
    mpz_t number;
} TSAFENODE;

typedef struct tsafelist {
    pthread_mutex_t *mutex;
    TSAFENODE *head;
    TSAFENODE *tail;
} TSAFELIST;

typedef struct tsafereturndata {
    // True(1)/False(0) if returned data is valid.
    int isValid;
    mpz_t value;
    } TSAFEDATA;

TSAFELIST* tSafeConstruct();
void tSafeDestruct(TSAFELIST*);
void tSafeEnqueue(TSAFELIST *,mpz_t);
TSAFEDATA* tSafeDequeue(TSAFELIST *);
