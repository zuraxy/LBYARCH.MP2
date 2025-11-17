#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TWO_TWENTY 1048576
#define TWO_TWENTYFOUR 16777216
#define TWO_THIRTY 1073741824

// for random float generation (can be changed)
#define MIN_VAL 1.0
#define MAX_VAL 10.0

// dot product algo in x86-64
extern float dot_product_asm(long long int n, float *A, float *B);

// to initialize an array of floats
float* init_vector(long long n) {
	float *vector;
	vector = (float*)malloc(n * sizeof(float));
	
	if (vector == NULL) {
        printf("Mem Alloc Failed\n");
        exit(1);
    }
	
	for(long long i = 0; i < n; i++){
		vector[i] = MIN_VAL + ((float)rand() / (float)RAND_MAX) * (MAX_VAL - MIN_VAL);
	}
	
	return vector;
}

// dot product algo in C
float dot_product_C(long long n, float *A, float *B) {
	
}

// compare dot product algo run times of C and x86-64
float time_test() {
	
}

int main() {
	srand(time(NULL));
	
	float *A = init_vector(TWO_TWENTY);
	float *B = init_vector(TWO_TWENTY);
	
	
	
	free(A);
	free(B);
	
	return 0;
}
