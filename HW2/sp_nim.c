#include <stdio.h>

void computer_move(int[], int, int*, int*);
int is_over(int[], int);

void computer_move(int heaps[], int num_heaps,
		int *which_heap, int *how_many){

	int nim_sum = 0;
	
	for(int c = 0; c<num_heaps; c++){
		nim_sum ^= heaps[c];
	}

	if(nim_sum == 0){
		for(int c = 0; c<num_heaps; c++){
			if(heaps[c] > 0){
				*which_heap = c;
				*how_many = 1;
				return;
			}
		}
	}
	// num_sum != 0
	for(int c = 0; c<num_heaps; c++){
		if(heaps[c] > (heaps[c]^nim_sum)){
			*which_heap = c;
			*how_many = heaps[c] - heaps[c]^nim_sum;
			return;
		}
	}
}

int is_over(int heaps[], int num_heaps){
	for(int c = 0; c<num_heaps; c++){
		if(heaps[c] != 0)
			return 0; // game not over yet
	}
	return 1; // game is over
}
