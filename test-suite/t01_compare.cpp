#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";




int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials=1;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  START("[compare] basic tests of the compare function");

  TEST_RET_MESSAGE(TravelOptions::compare(1.0, 2.0, 1.0, 2.0), "equal test", TravelOptions::equal, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(1.0, 2.0, 1.0, 2.5), "better test 1", TravelOptions::better, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(1.0, 2.0, 1.5, 2.0), "better test 2", TravelOptions::better, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(1.0, 2.0, 2.0, 3.0), "better test 3", TravelOptions::better, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(1.0, 2.5, 1.0, 2.0), "worse test 1", TravelOptions::worse, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(1.5, 2.0, 1.0, 2.0), "worse test 2", TravelOptions::worse, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(2.0, 3.0, 1.0, 2.0), "worse test 3",  TravelOptions::worse, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(1.0, 5.0, 2.0, 4.0), "incomp test 1", TravelOptions::incomparable, 1.111111); 
  TEST_RET_MESSAGE(TravelOptions::compare(5.0, 5.0, 2.0, 6.0), "incomp test 2", TravelOptions::incomparable, 1.111111); 
  report();

  END;
}

