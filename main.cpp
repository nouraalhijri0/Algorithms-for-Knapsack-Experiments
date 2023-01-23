//
//  main.cpp
//  knapsack
//
//  Created by Noura Alhajry on 10/04/1444 AH.
//

#include <iostream>

#include <iostream>
#include "knapsack.h"
#include "experiments.h"


int main(int argc, const char * argv[]) {
    // A fixed example from our proposal
    /*int C = 15,
     values[] = {4, 2, 10, 2, 1},
     weights[] = {12, 1, 4, 2, 1},
     print_F = 1, print_res = 1,
     N = 5;
     */
    
    // A random example
    srand(time(NULL)); //set the seed based on time
    
    //uncomment one of the following to see the results
    
    simple_example();
    //measure_time();
    //measure_accuracy();
    //test_variables();
    
    return 0;
}
