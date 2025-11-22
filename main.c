#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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

// dot product algo in C - naive solution
float dot_product_C(long long n, float *A, float *B) {
	float sdot = 0.0;
	
	for(int i=0; i<n;i++) {
		sdot+= A[i]*B[i];
	}

	return sdot;
}

// compare dot product algo run times of C and x86-64
#define TIME_TEST(FUNC_CALL, RUNS) ({ 							\
    clock_t start_time = clock(); 								\
	for(int i=0; i<RUNS; i++) { 								\
        FUNC_CALL; 												\
    } 															\
    clock_t end_time = clock(); 								\
    (double)(end_time - start_time) / CLOCKS_PER_SEC / RUNS; 	\
})

void run_test(long long vector_length) {
	printf("\n==================================\n");
    printf("Testing Vector Size: %lld\n", vector_length);
    printf("==================================\n");
	
	float *A = init_vector(vector_length);
	float *B = init_vector(vector_length);

	//sanity check - cross check asm and c's results
	float asm_result = dot_product_asm(vector_length, A, B);
	float c_result = dot_product_C(vector_length, A, B);

	// cross compare the kernel's run times
	if(asm_result==c_result){
		printf("ASM Average Time: %f seconds\n",TIME_TEST(dot_product_asm(vector_length, A, B), 20));
    	printf("C Average Time: %f seconds\n",TIME_TEST(dot_product_C(vector_length, A, B), 20));
	}
	else{
		printf("Output of asm is different from C's: %f vs %f", asm_result, c_result);
	}
	
	free(A);
	free(B);
}

int main() {
	srand(time(NULL));
	
	run_test(TWO_TWENTY);
    run_test(TWO_TWENTYFOUR);
    run_test(TWO_THIRTY);
	
	return 0;
}
