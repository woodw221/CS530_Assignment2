#include "prog2_1.h"

mpz_t globalCounter;
pthread_mutex_t counterguard = PTHREAD_MUTEX_INITIALIZER;
TSAFELIST *numberList;
int primeCount;


void getNextNum(mpz_t num){
	pthread_mutex_lock(&counterguard);
    mpz_set(num, globalCounter); 
	mpz_add_ui(globalCounter, globalCounter, 1); 
	pthread_mutex_unlock(&counterguard);
	return;
}

void *generatePrime(void *something){
	mpz_t testNum;
	mpz_init (testNum);
	while(1){
		getNextNum(testNum);
	
		int check = mpz_probab_prime_p(testNum, 100000); 
		if(check != 0 ){
		
			tSafeEnqueue(numberList, testNum);
		}
	}
	
}


int main(int argc, char *argv[]){
    mpz_init(globalCounter);
    numberList = tSafeConstruct();
	
	int arg1 = atoi(argv[1]);
	int arg2 = atoi(argv[2]);

	//Set our Global Counter to the start point
	mpz_t multiplier;
	mpz_init(multiplier);
	mpz_set_d(multiplier, 1);
	mpz_mul_2exp(globalCounter, multiplier, arg2-1);

	
	pthread_t t1;

	for(int i = 0; i <4; i++){
		pthread_create(&t1, NULL, generatePrime, NULL);
	}

	printf("Assignment #2-2, William Wood, woodw221@gmail.com\n");


	sleep(10);
	//char *output;
	TSAFEDATA *data = malloc(sizeof(TSAFEDATA));
	int printed = 0;
	while(printed < arg1){

		data = tSafeDequeue(numberList);
		if(data->isValid == 1){
			gmp_printf("%Zd\n", data->value);
			printed++;
		}
		sleep(1);
	}
	return 0;
}
