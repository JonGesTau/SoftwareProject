#include <stdio.h>
#include "SPBufferset.h"
#include "main_aux.h"
#include "sp_nim.h"

int main(){	
	SP_BUFF_SET();
	
	int num_heaps = input_heaps();
	if(num_heaps == -1)
		return -1;
	
	int heaps[num_heaps];
	get_heap_sizes(heaps, num_heaps);
	
	int which_heap = 0;
	int how_many = 0;
	int turn = 1;

    if (turn > 1) print_heaps(heaps, num_heaps);
	
	while(is_over(heaps, num_heaps) == 0){
		heap_stats(heaps, num_heaps, turn);
		
		if(turn % 2 == 1){ // computer turn
			computer_move(heaps, num_heaps, &which_heap, &how_many);
			report_computer(which_heap, how_many);
		} else { // player turn
			print_heaps(heaps, num_heaps);
			user_turn(heaps, num_heaps, &which_heap, &how_many);
		}
		heaps[which_heap] -= how_many;
		
		turn ++;
	}
	
	win_message(turn);
	
	return 0;
}
