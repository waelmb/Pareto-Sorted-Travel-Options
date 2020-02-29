#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"





// string Desc = "Basic test of to_vec";
// char *Desc = "Basic test of to_vec";

bool t_insert_into_empty(){
  TravelOptions to;
  std::vector<std::pair<double,double>> 
	correct_ans{ {1, 1}};
  std::vector<std::pair<double,double>> *result;

  to.insert_sorted(1,1);
  result = to.to_vec();
  return cmp_vec(correct_ans, *result);
}



int main(int argc, char *argv[]) {
  int n = ___N;
  int ntrials=1;


  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2){
    ntrials = atoi(argv[2]);
    set_ntrials(ntrials);
  }


  START("[insert_sorted] basic test of the insert_sortedfunction");

  TEST_RET_MESSAGE(t_insert_into_empty(),  "insertion into empty list", true, 1.5); 

  report();

  END;
}

