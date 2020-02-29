#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";




int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2){
    ntrials = atoi(argv[2]);
    set_ntrials(ntrials);
  }

  TravelOptions *sortedN, *unsortedN;
  TravelOptions *sorted2N, *unsorted2N;
  sortedN = sorted_instanceA(n);
  unsortedN = unsorted_instanceA(n);

  sorted2N = sorted_instanceA(2*n);
  unsorted2N = unsorted_instanceA(2*n);

  START("[is_pareto_sorted] timed tests of the is_pareto_sorted function");

  //  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 2.0); 
  TIME_RATIO(sortedN->is_sorted(), sorted2N->is_sorted(), "sorted+timed", 1, 2.9, 1.5);
  TIME_RATIO(unsortedN->is_sorted(), unsorted2N->is_sorted(), "unsorted+timed", 0, 2.9, 1.5);

  report();
  delete sortedN;
  delete sorted2N;
  delete unsortedN;
  delete unsorted2N;

  END;
}

