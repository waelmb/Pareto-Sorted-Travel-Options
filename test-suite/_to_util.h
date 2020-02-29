
void p_vec( std::vector<std::pair<double,double>> &vec) {
  printf("    [");
  for(auto option : vec) {
    printf("(%.2f,%.2f) ", option.first, option.second); 
  }
  printf("]\n");
}



bool cmp_vec( std::vector<std::pair<double,double>> &correct_answer, 
              std::vector<std::pair<double,double>> &given_answer, 
              bool verbose=true) {

  if(verbose && given_answer !=  correct_answer) {
     printf("ERROR:\n");
     printf("    CORRECT LIST :");
     p_vec(correct_answer);
     printf("    RECEIVED LIST:");
     p_vec(given_answer);
     return false;
  }
  return true;
}
     

void psline(std::vector<std::pair<double,double>> &vec, int n, double p0, double t0, 
              double dp=1.0, double dt=-1.0) {
     std::pair<double,double> option{p0, t0};

     for(int i=0; i<n; i++) {
        vec.push_back(option);
        option.first += dp;
        option.second += dt;
     }
}

/*
 * constructs sorted vector where every other entry is either
 *  identical to or dominated by its predecessor
 */ 
void sorted_vecA(int n, std::vector<std::pair<double,double>> &vec,
                  std::vector<std::pair<double,double>> *pruned_vec=nullptr) {
  double p = 0.0;
  double t = 2.0 * n;

  vec.clear();
  if(pruned_vec != nullptr) 
       pruned_vec->clear();
  for(int i=0; i<n; i += 2) {
     std::pair<double,double> option{p, t};
     vec.push_back(option);
     if(pruned_vec != nullptr) 
        pruned_vec->push_back(option);
     if((i/2) % 3 == 0) {
       vec.push_back(option);  // push identical elem
     }
     else if ((i/2) % 3 == 1){  // push dominated elem (bigger price and time)
       // std::pair<double,double> option{p, t+1.0};
       option.first = p+0.5;
       option.second = t+0.5;
       vec.push_back(option);
     }
     else {  // push dominated item (same price, bigger time)
       option.second = t+0.5;
       vec.push_back(option);
     }
     p += 1.0;
     t -= 1.0;
  }
}

TravelOptions * psorted_instanceA(int n) {

  std::vector<std::pair<double,double>> vec;
  psline(vec, n, 0.0, 2*n);
  
  return TravelOptions::from_vec(vec);
}

TravelOptions * sorted_instanceA(int n) {

  std::vector<std::pair<double,double>> vec;
  sorted_vecA(n, vec);
  
  return TravelOptions::from_vec(vec);
}

TravelOptions * unsorted_instanceA(int n) {
  std::vector<std::pair<double,double>> vec;
  sorted_vecA(n, vec);

  n = vec.size();
  std::cout << "unsorted_instance, vec-size: " << n << std::endl;

  vec[n-1].first = vec[n-2].first;
  vec[n-1].second = vec[n-2].second - 1.0;
  return TravelOptions::from_vec(vec);
}
