#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *array, int number_of_elements, int key) {
	int low = 0, high = number_of_elements-1, mid;
	while(low <= high) {
		mid = (low + high)/2;
#ifdef DO_PREFETCH
		// low path
		__builtin_prefetch (&array[(mid + 1 + high)/2], 0, 1);
		// high path
		__builtin_prefetch (&array[(low + mid - 1)/2], 0, 1);
#endif

		if(array[mid] < key)
			low = mid + 1; 
		else if(array[mid] == key)
			return mid;
		else if(array[mid] > key)
			high = mid-1;
	}
	return -1;
}

int main() {
	int SIZE = 1024*1024*512;
	int *array =  malloc(SIZE*sizeof(int));
	for (int i=0;i<SIZE;i++){
		array[i] = i;
	}
	int NUM_LOOKUPS = 1024*1024*8;
	srand(time(NULL));
	int *lookups = malloc(NUM_LOOKUPS * sizeof(int));
	for (int i=0;i<NUM_LOOKUPS;i++){
		lookups[i] = rand() % SIZE;
	}
	for (int i=0;i<NUM_LOOKUPS;i++){
		int result = binarySearch(array, SIZE, lookups[i]);
	}
	free(array);
	free(lookups);
}

/* Prefetch 성능 테스트 하기
   (1) 컴파일 방법
   
   $ gcc prefetch_test.c -DDO_PREFETCH -o with-prefetch -std=c11 -O3

   $ gcc prefetch_test.c -o no-prefetch -std=c11 -O3

   (2) 리눅스 perf 도구를 통한 성능 테스트 (perf 도구 설치법: sudo apt install linux-tools-common)

      *참고: cache hit VS cache miss 약 20% 성능 차이 확인하기

     $ sudo perf stat -e L1-dcache-load-misses,L1-dcache-loads ./with-prefetch

     $ sudo perf stat -e L1-dcache-load-misses,L1-dcache-loads ./no-prefetch

*/

/* 실제 약 20% 성능 차이 예시
$ sudo perf stat -e L1-dcache-load-misses,L1-dcache-loads ./with-prefetch

 Performance counter stats for './with-prefetch':

       690,489,306      L1-dcache-load-misses     #   47.29% of all L1-dcache hits  
     1,460,211,887      L1-dcache-loads                                             

       9.817641158 seconds time elapsed

       8.917651000 seconds user
       0.887766000 seconds sys

$ sudo perf stat -e L1-dcache-load-misses,L1-dcache-loads ./no-prefetch

 Performance counter stats for './no-prefetch':

       554,875,925      L1-dcache-load-misses     #   68.32% of all L1-dcache hits  
       812,209,225      L1-dcache-loads                                             

      18.481793969 seconds time elapsed

      17.876742000 seconds user
       0.604025000 seconds sys
*/



