
#include <Arduino.h>



namespace equal_tempered {

	template<typename Iterator> void generate_scale(Iterator it, const Iterator& end,
		unsigned int base_index = 57, unsigned int base_period = 2275, float tuning_constant = 1.05946309436){
		for(int i = 0; it != end; ++it, ++i){
			*it = base_period * pow(tuning_constant, base_index - i);
		}
	}

}



// #define REFPD 2273
// #define REFIX 57
// #define TUNING 1.05946309436

// void generate_period(){
//   for(int i = 0; i < NOTECOUNT; i++){
//     period[i] = REFPD * pow(TUNING, REFIX - i);
//   }
  
//   //randomize(period + 40, 60);
// }