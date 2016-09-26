#include "noteData.h"
#include <Arduino.h>




template<typename Iterator>
void tuning::generate_scale(Iterator it, const Iterator& end,
	int base_index = 60, int base_period = 3822, float tuning_constant = 1.05946309436){

	for(int i = 0; it != end; ++it, ++i){
		*it = base_period * pow(tuning_constant, base_index - i);
	}
}

template<typename Iterator>
void tuning::generate_scale(Iterator it, const Iterator& end,
	const float offset[12],
	int base_index = 60, int base_period = 3822, float tuning_constant = 1.05946309436){

	for(int i = 0; it != end; ++it, ++i){
		int off = (base_index - i) % 12;
		if(off < 0) off += 12;

		*it = base_period * pow(tuning_constant, base_index - i + offset[off]);
	}
}




// #define REFPD 2273
// #define REFIX 57
// #define TUNING 1.05946309436

// void generate_period(){
// 	extern unsigned int[] period
// 	for(int i = 0; i < NOTECOUNT; i++){
// 		period[i] = REFPD * pow(TUNING, REFIX - i);
// 	}
  
//  	//randomize(period + 40, 60);
// }