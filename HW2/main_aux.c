#include <stdio.h>
#include <stdlib.h>

void print_heaps(int[], int);
void heap_stats(int[], int, int);
void report_computer(int, int);
void win_message(int);
void user_turn(int[], int, int*, int*);
int input_heaps();
void get_heap_sizes(int[], int);

// prints a visualization of the heaps
void print_heaps(int heaps[], int num_heaps){
    int max_size = 0;
	
	for(int c = 0; c<num_heaps; c++){
		if(heaps[c] > max_size){
			max_size = heaps[c];
		}
	}
	
	for(int c = max_size; c>0; c--){
		for(int i = 0; i<num_heaps; i++){
			if (heaps[i] >= c) {
                printf("*");
            } else {
                printf(" ");
            }
            if (i < num_heaps - 1) printf("\t"); // also on the last heap?
		}
		printf("\n");
	}
}

// prints how many counters are in each heap
void heap_stats(int heaps[], int num_heaps, int turn){
	printf("In turn %d heap sizes are:", turn);
	
	for(int c = 0; c<num_heaps; c++){
		printf(" h%d=%d", (c+1), heaps[c]);
	}
	printf(".\n");
}

// prints the computer move
void report_computer(int which_heap, int how_many){
	printf("Computer takes %d objects from heap %d.\n",
	  how_many, (which_heap+1));
}

// prints winning message
void win_message(int turn){
	if(turn % 2 == 0)
		printf("Computer wins!\n");
	else
		printf("You win!\n");
}

// asks user how many counters to take and from which heap
// stores the response in pointers
void user_turn(int heaps[], int num_heaps, 
		int *which_heap, int *how_many){
	printf("Your turn: please enter the heap index and the number of removed objects.\n");
	
	int user_heap = 0;
	int user_amount = 0;
	
	// *** get user input
	scanf("%d %d", &user_heap, &user_amount);
    --user_heap;
	
	while((user_heap < 0) || (user_heap >= num_heaps) ||
		(user_amount <= 0) || (heaps[user_heap] < user_amount)){
		// while input is invalid
		printf("Error: Invalid input.\n");
		printf("Please enter again the heap index and the number of removed objects.\n");
		
		// *** get user input again
		scanf("%d %d", &user_heap, &user_amount);
        --user_heap;

	}
	
	// if valid
	printf("You take %d objects from heap %d.\n", user_amount, user_heap+1);
	*which_heap = user_heap;
	*how_many = user_amount;
}

// asks the user for the number of heaps
int input_heaps(){
	printf("Enter the number of heaps:\n");
	int num_heaps;
	scanf("%d", &num_heaps);
	
	if((num_heaps < 1) || (num_heaps > 32)){
		printf("Error: the number of heaps must be between 1 and 32.\n");
		return -1;
	}
	
	return num_heaps;
}

void get_heap_sizes(int heaps[], int num_heaps){
	printf("Enter the heap sizes:\n");
	// get heap sizes separated by spaces, store in heaps[]
	int i = 0;
	while (i < num_heaps && scanf("%d", &heaps[i]) == 1) {
		if (heaps[i] <= 0) {
			// error message if one of the numbers is negative
			printf("Error: the size of heap %d should be positive.\n", i + 1);
            exit(-1);
		} else {
			i++;
		}
	}
}






