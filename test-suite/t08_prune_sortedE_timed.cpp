#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "TravelOptions.h"

// #include <string>
#include "_test.h"
#include "_to_util.h"


bool t_prune_3_lines(int n) {
  std::vector<std::pair<double,double>> A;
  std::vector<std::pair<double,double>> B;
  std::vector<std::pair<double,double>> Correct;
  std::vector<std::pair<double,double>> *result;

  n = n + (6- (n%6));  // make n a multiple of 6

  int n6 = n/6;
  int n3 = n/3;
  int n2 = n/2;

  psline(A, n3, 1, n-1, 1.0, -1.0);
  psline(A, n3, n3+1, n-n6-1, 1.0, -1.0);
  psline(A, n3, 2*n3+1, n-n3-1, 1.0, -1.0);

  psline(Correct, n3, 1, n-1, 1.0, -1.0);
  psline(Correct, n6, n2+1, n-n3+1, 1.0, -1.0);
  psline(Correct, n3, (5*n6)+1, n-n2-1, 1.0, -1.0);



  TravelOptions *a = TravelOptions::from_vec(A);
  a->prune_sorted();

  result = a->to_vec();

  bool passed = cmp_vec(Correct, *result, false);
  delete a;
  delete result;
  return passed;
}
  
bool t_union_identical() {
  std::vector<std::pair<double,double>> A{ {2, 20}, {4, 15}, {6, 10}};
  std::vector<std::pair<double,double>> B{ {2, 20}, {4, 15}, {6, 10}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);
  TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *aUb = a->union_pareto_sorted(*b);

  result = aUb->to_vec();

  bool passed = cmp_vec(A, *result);
  delete a;
  delete b;
  delete aUb;
  delete result;
  return passed;
}


bool t_union_two_lines() {
  std::vector<std::pair<double,double>> A{ {2, 100}, {4, 90}, {6, 80}, {8,70}, {10, 60}};
  std::vector<std::pair<double,double>> B{ {1, 95}, {3, 90}, {5, 85}, {7, 80}, {9, 75}};
  std::vector<std::pair<double,double>> answer{ {1, 95}, {3, 90}, {5, 85}, {6, 80}, {8, 70}, {10,60}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);
  TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *aUb = a->union_pareto_sorted(*b);

  result = aUb->to_vec();

  bool passed = cmp_vec(answer, *result);
  delete a;
  delete b;
  delete aUb;
  delete result;
  return passed;
}

bool t_union_cross_twice() {
  std::vector<std::pair<double,double>>      A{ {2, 100}, {4, 90}, {6, 80}, {8, 70}, {10, 60}, {12, 50}, {14, 40}, {16, 30}, {18, 20}};
  std::vector<std::pair<double,double>>      B{ {2, 110}, {4, 95}, {6, 80}, {8, 65}, {10, 50}, {12, 45}, {14, 40}, {16, 35}, {18, 30}};
  std::vector<std::pair<double,double>> answer{ {2, 100}, {4, 90}, {6, 80}, {8, 65}, {10, 50}, {12, 45}, {14, 40}, {16, 30}, {18, 20}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);
  TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *aUb = a->union_pareto_sorted(*b);

  result = aUb->to_vec();

  bool passed = cmp_vec(answer, *result);
  delete a;
  delete b;
  delete aUb;
  delete result;
  return passed;
}

bool t_union_one_dominates() {
  std::vector<std::pair<double,double>>      A{ {2, 100}, {4, 90}, {6, 80}, {8, 70}, {10, 60}, {12, 50}, {14, 40}, {16, 30}, {18, 20}};
  std::vector<std::pair<double,double>>      B{ {2.1, 100}, {4.1, 90}, {6.1, 80}, {8.1, 70}, {10.1, 60}, {12.1, 50}, {14.1, 40}, {16.1, 30}, {18.1, 20}};
  std::vector<std::pair<double,double>> answer{ {2, 100}, {4, 90}, {6, 80}, {8, 70}, {10, 60}, {12, 50}, {14, 40}, {16, 30}, {18, 20}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);
  TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *aUb = a->union_pareto_sorted(*b);

  result = aUb->to_vec();

  bool passed = cmp_vec(answer, *result);
  delete a;
  delete b;
  delete aUb;
  delete result;
  return passed;
}

bool t_union_alternating() {
  std::vector<std::pair<double,double>>      A{ {2, 100},       {4, 90},        {6, 80},       {8, 70},      {10, 60}};
  std::vector<std::pair<double,double>>      B{          {3, 95 },       {5, 85},       {7, 75},       {9, 65},         {11, 55}};
  std::vector<std::pair<double,double>> answer{ {2, 100},{3,95}, {4, 90},{5,85},{6, 80}, {7, 75},{8,70}, {9,65}, {10, 60}, {11,55}};
  std::vector<std::pair<double,double>> *result;

  TravelOptions *a = TravelOptions::from_vec(A);
  TravelOptions *b = TravelOptions::from_vec(B);
  TravelOptions *aUb = a->union_pareto_sorted(*b);

  result = aUb->to_vec();

  bool passed = cmp_vec(answer, *result);
  delete a;
  delete b;
  delete aUb;
  delete result;
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


  START("[prune_sorted]: test E: two pruned 'chunks' of length n/6 each in the middle] ");
  printf("    N = %i\n\n ", n);


  TIME_RATIO(t_prune_3_lines(n), t_prune_3_lines(2*n), 
     "timed test: two 'chunks' of len n/6 each must be removed", 1, 2.9, 4.0);


  report();

  END;
}

