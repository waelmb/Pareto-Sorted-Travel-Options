#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"



bool t_no_bargains(bool checksum=false) {
  std::vector<std::pair<double,double>> A{{1, 10},{2,9},{3,8},{4,7}};
  std::vector<std::pair<double,double>> correct_cheap;
  std::vector<std::pair<double,double>> correct_exp{{1, 10},{2,9},{3,8},{4,7}};
  // std::vector<std::pair<double,double>> correct{{2,13}, {3,12}, {4,11}};

  unsigned long int cksum_before;
  unsigned long int cksum_after;

  std::vector<std::pair<double,double>> *exp_vec;
  std::vector<std::pair<double,double>> *cheap_vec;

  TravelOptions *a = TravelOptions::from_vec(A);;
  //TravelOptions *b = TravelOptions::from_vec(B);;

  cksum_before = a->checksum();
  TravelOptions * expensive = a->split_sorted_pareto(0.5); 
  cksum_after = expensive->checksum();
  cheap_vec = a->to_vec();
  exp_vec = expensive->to_vec();

  bool passed = cmp_vec(correct_cheap, *cheap_vec) && cmp_vec(correct_exp, *exp_vec);

  if(checksum) {
	passed = passed && (cksum_before == cksum_after);
  }

  delete a;
  delete expensive;
  delete cheap_vec;
  delete exp_vec;
  return passed;
}


bool t_all_bargains(bool checksum=false) {
  std::vector<std::pair<double,double>> A{{1, 10},{2,9},{3,8},{4,7}};
  std::vector<std::pair<double,double>> correct_exp;
  std::vector<std::pair<double,double>> correct_cheap{{1, 10},{2,9},{3,8},{4,7}};
  // std::vector<std::pair<double,double>> correct{{2,13}, {3,12}, {4,11}};

  unsigned long int cksum_before;
  unsigned long int cksum_after;

  std::vector<std::pair<double,double>> *exp_vec;
  std::vector<std::pair<double,double>> *cheap_vec;

  TravelOptions *a = TravelOptions::from_vec(A);;
  //TravelOptions *b = TravelOptions::from_vec(B);;

  cksum_before = a->checksum();

  TravelOptions * expensive = a->split_sorted_pareto(10); 

  cksum_after = a->checksum();

  cheap_vec = a->to_vec();
  exp_vec = expensive->to_vec();

  bool passed = cmp_vec(correct_cheap, *cheap_vec) && cmp_vec(correct_exp, *exp_vec);

  if(checksum) {
	passed = passed && (cksum_before == cksum_after);
  }

  delete a;
  delete expensive;
  delete cheap_vec;
  delete exp_vec;
  return passed;
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


  START("[split_sorted_pareto]  partII");

  TEST_RET_MESSAGE(t_no_bargains(),  
      "TEST: split where no elements are <= max_price",
		true, 1.4); 

  TEST_RET_MESSAGE(t_no_bargains(true),  
      "TEST: split where no elements are <= max_price PLUS checksum test",
		true, 1.4); 

  TEST_RET_MESSAGE(t_all_bargains(),  
      "TEST: split where ALL elements are <= max_price",
		true, 1.4); 

  TEST_RET_MESSAGE(t_all_bargains(true),  
      "TEST: split where ALL elements are <= max_price PLUS checksum test",
		true, 1.4); 



  report();

  END;
}

