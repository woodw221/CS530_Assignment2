#include "prog2_1.h"

TSAFELIST* tSafeConstruct(){
    TSAFELIST *Safelist =  malloc(sizeof(TSAFELIST));
    Safelist->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    Safelist->head = NULL;
    Safelist->tail = NULL;
}

void tSafeEnqueue(TSAFELIST* List,mpz_t num){
    
    TSAFENODE *newNode = malloc(sizeof(TSAFENODE));
	mpz_init(newNode->number);
    mpz_set (newNode->number,num);
    newNode->next = NULL;
    pthread_mutex_lock(List->mutex);

    if(List->head == NULL){
        List->head = List->tail = newNode;
    }
   	List->tail->next = newNode;
   	List->tail = newNode;
    
    pthread_mutex_unlock(List->mutex);
}

TSAFEDATA* tSafeDequeue(TSAFELIST* List){
    TSAFEDATA *Data = malloc(sizeof(TSAFEDATA));
	mpz_init(Data->value);
    pthread_mutex_lock(List->mutex);
    if(List->head == NULL){
        Data->isValid = 0;
        return Data;
    }
    mpz_set (Data->value, List->head->number);
    Data->isValid = 1;

    TSAFENODE *newNode = List->head;
    List->head = List->head->next;
    free(newNode);
	pthread_mutex_unlock(List->mutex);
    return Data;

}

void tSafeDestruct(TSAFELIST* fList){
	while(1){
		TSAFEDATA *delData = tSafeDequeue(fList);
		if(delData->isValid == 0){
			break;
		}
	}
    free(fList);
}

/*int main(){
    TSAFELIST *List = tSafeConstruct();

    mpz_t uno;
    mpz_init (uno);
    mpz_set_d (uno, 1);
    
    tSafeEnqueue(List, uno);
    
    TSAFEDATA *D = tSafeDequeue(List);

    printf("%f\n", mpz_get_d(D->value));

    tSafeDestruct(List);
}*/
