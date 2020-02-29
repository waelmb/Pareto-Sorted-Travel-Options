#ifndef _TRVL_OPTNS_H
#define _TRVL_OPTNS_H

#include <iostream>
#include <vector>
#include <utility>


// using namespace std;

class TravelOptions{

  public:
	enum Relationship { better, worse, equal, incomparable};

  private:
	  struct Node {
		  double price;
		  double time;
		  Node *next;

		  Node(double _price=0, double _time=0, Node* _next=nullptr){
			  price = _price; time = _time; next = _next;
		  }

	  };

    /* TravelOptions private data members */
    Node *front;  // pointer for first node in linked list (or null if list is empty)
    int _size;

  public:
    // constructors
    TravelOptions() {
      front = nullptr;
      _size=0;
    }

    ~TravelOptions( ) {
      clear();
    }


   /**
   * func: clear
   * desc: Deletes all Nodes currently in the list
   * status:  DONE
   */
    void clear(){
    Node *p, *pnxt;
       p = front;
       while(p != nullptr) {
         pnxt = p->next;
         delete p;
         p = pnxt;
       }
       _size = 0;
       front = nullptr;
    }


   /**
   * func: size
   * desc: returns the number of elements in the list
   * status:  DONE
   */
    int size( ) const {
       return _size;
    }


    /**
    * func: compare
    * desc: compares option A (priceA, timeA) with option B (priceB, timeA) and
    *		returns result (see enum Relationship above):
    *
    *       There are four possible scenarios:
    *		- A and B are identical:  option A and option B have identical price and time: 
    *			 		ACTION:  return equal
    *		- A is better than B:  option A and B are NOT equal/identical AND 
    *					option A is no more expensive than option B AND
    *					option A is no slower than option B 
    *					ACTION:  return better
    *		- A is worse than B:  option A and B are NOT equal/identical AND 
    *					option A is at least as expensive as option B AND
    *					option A is no faster than option B 
    *					ACTION:  return worse
    *					NOTE:  this means B is better than A
    *		- A and B are incomparable:  everything else:  one option is cheaper and 
    *					      the other is faster.
    *					ACTION:  return incomparable 
    *
    * COMMENTS:  since this is a static function, there is no calling object.  
    *            To call it from a client program, you would do something like this:
    *
             TravelOptions::Relationship r;

             double pa, ta, pb, tb;

                // some code to set the four price/time variables

                r = TravelOptions::compare(pa, ta, pb, tb);
                if(r == TravelOptions::better) 
                    std::cout << "looks like option b is useless!" << std::endl;
                // etcetera
    * 
    * status: PASSED INITIAL TESTING
    */          
    static Relationship compare(double priceA, double timeA, 
 					double priceB, double timeB) {
 		//if they're equal
		if(priceA == priceB && timeA == timeB) {
			return equal;
		}
		
		//if price of B is more than or equal to price of A and time of B is more than or euqla to time B then A dominates B
		else if(priceB >= priceA && timeB >= timeA) {
			return better;
		}
		
		//if price of A is more than or equal to price of B and time of A is more than or equal to time B then B dominates A
		else 
 		if(priceA >= priceB && timeA >= timeB) {
 			return worse;
		}
		else {
			return incomparable;  // placeholder	
		}
    }

  private:

    /**
     * func: compare(Node*, Node*)
     * desc: private utilty function for comparing two options given as 
     *       Node pointers.
     *
     * status: DONE
     *
     * COMMENT:  depends on public compare(double,double,double,double) being implemented.
     *           You might find this version handy when manipulating lists
     */
    static Relationship compare(Node *a, Node *b) {
       if(a==nullptr || b==nullptr) {
           std::cout << "ERR: compare(Node*,Node*);  null pointer passed!!! Whoops!" << std::endl;
           return incomparable;
       }
       return compare(a->price, a->time, b->price, b->time);
    }
    
  public:
    
    

    

   /**
   * func: push_front
   * desc: Adds a <price,time> option to the front of the list (simple primitive for building lists)
   * status:  DONE
   */
    void push_front(double price, double time) {

      front = new Node(price, time, front);
      _size++;
    }

   /**
   * func: from_vec
   * desc: This function accepts a C++ standard libary vector of pair<double,double>.
   *       Each pair is interpreted as a <price,time> option and a TravelOptions object
   *       is containing exactly the same options as in the vector (and in the same order).
   *	
   * returns: a pointer to the resulting TravelOptions object
   * status:  DONE
   */
    static TravelOptions * from_vec(std::vector<std::pair<double, double> > &vec) {
	TravelOptions *options = new TravelOptions();

	for(int i=vec.size()-1; i>=0; i--) {
		options->push_front(vec[i].first, vec[i].second);
	}
	return options;
    }

   /**
   * func: to_vec
   * desc: Utility function which creates a C++ standard libary vector of pair<double,double>.
   *       and populates it with the options in the calling object (in the same order).
   *       As in from_vec the "first" field of each pair maps to price and the "second"
   *         field maps to time.
   *	
   * returns: a pointer to the resulting vector
   * status:  DONE
   */
    std::vector<std::pair<double, double>> * to_vec() const {
      std::vector<std::pair<double, double>> *vec = new std::vector<std::pair<double, double>>();
      Node *p = front;

      while(p != nullptr) {
           vec->push_back(std::pair<double,double>(p->price, p->time));
           p = p->next;
      }
      return vec;
    }


    /**
    * func: is_sorted
    * desc: we consider an option list sorted under the following conditions:
    *	
    *		- the options are in non-decreasing order of price AND
    *		- time is used as a tie-breaker for options with identical price.
    *
    *       For example, using the notation <price, time> to represent an option:
    *
    *             <5.1, 10.0>  must be before <5.6, 9.0>    (price is less, so time ignored)
    *             <6.2, 4.1>   must be AFTER  <6.2, 3.9>    (identical price; tie broken by
    *                                                         smaller time (3.9 in this case)).
    *
    *       If two or more options are identical in BOTH price and time, they are 
    *       indistinguishible and must appear as a consecutive "block" if the list is
    *       to be considered sorted.
    *
    * returns:  true if sorted by the rules above; false otherwise.
    *
    * Examples:
    *
    *   The option list below is sorted by our rules:
    *      [ <1, 7>, <2, 8>, <2, 9>, <3, 5>, <5, 8>, <5, 8>, <5, 9>, <6, 12> ]
    *
    *   The option list below is NOT sorted by our rules:
    *      [ <1, 7>, <2, 8>, <4, 3>, <3, 7>]
    *                                ^^^^^^ must be before <4,3>
    *
    *   The option list below is also NOT sorted by our rules:
    *      [ <1, 7>, <2, 8>, <2, 5>, <3, 7>]
    *                        ^^^^^^ must be before <2,8>
    * status: PASSED INITIAL TESTING
    */
    bool is_sorted()const{
    	Node* hd = front;
    	//if list has 1 or less items
    	if(hd == nullptr || hd->next == nullptr) {
    		return true;
		}
		//Get next item and compare
		else {
			while(hd != nullptr && hd->next != nullptr) {
				if(hd->price > hd->next->price) {
					return false;
				}
				else if(hd->price == hd->next->price && hd->time > hd->next->time) {
					return false;
				}
				hd = hd->next;
			}
			return true;	
		}
    }


    /**
    * func: is_pareto
    * desc: returns true if and only if:
    *
    *        all options are distinct  (no duplicates)  AND
    *        none of the options are 'suboptimal' (i.e., for each option X, there DOES NOT EXIST
    *           any other option Y such that Y dominates X).  There are several equivalent
    *           ways of stating this property...
    *           
    * status: PASSED INITIAL TESTING
    *
    * REQUIREMENTS:
    *    - the list must be unaltered
    *    - no memory allocation, arrays, etc. allowed
    *    - RUNTIME:  quadratic in number of options n (i.e., O(n^2)).
    *
    * REMEMBER:  the list does not need to be sorted in order to be pareto
    */
    bool is_pareto() const{
    	Node* hd = front;
		while(hd != nullptr && hd->next != nullptr) {
			Node* repeat = front;
			while(repeat != nullptr && repeat->next != nullptr) {
				//if there is an option that can be dominated and if there is a duplicate, return false
				if(hd != repeat && repeat->price >= hd->price && repeat->time >= hd->time) {
					return false;
				}
				repeat = repeat->next;	
			}
			hd = hd->next;	
		}
		return true;
    }

    /**
    * func: is_pareto_sorted() 
    * desc: returns true if and only if the list is:
    *    - STRICTLY INCREASING IN price AND
    *    - STRICTLY DECREASING IN time 
    *
    * REQUIREMENTS:
    *   RUNTIME:  linear in length of list n (i.e., O(n)).
    *
    * status:  PASSED INITIAL TESTING
    *
    * COMMENTS:  notice that because of the runtime requirement, you cannot simply do this:
    *
                   return is_sorted() && is_pareto();

    */
    bool is_pareto_sorted() const{
    	Node* hd = front;
		while(hd != nullptr && hd->next != nullptr) {
			if(hd->price >= hd->next->price || hd->time <= hd->next->time) {
				return false;	
			}
			hd = hd->next;	
		}
		return true;
    }

    /**
     * func: insert_sorted
     * preconditions:  given collection (calling object) must be sorted (but not necessarily
     *                   pareto).  If this is not the case, false is returned (code provided).
     *                   (returns true otherwise, after insertion complete).                 
     *                 
     * desc:  inserts option <price,time> (given as parameters) into option list (calling object)
     *          while keeping it sorted.  Recall:  ordering by price; tie-breaker is time.
     *
     * RUNTIME:  linear in length of list -- O(n).
     *
     * status: PASSED INITIAL TESTING
     *
     * NOTES/TIPS:  do this before insert_pareto_sorted; it is easier!  Remember, this one
     *     you don't have to think about pruning for this function -- just ordering.
     */

    bool insert_sorted(double price, double time) {
		if(!is_sorted()) {
			return false;
		} 
		
		//traverse the list
		Node* curr = front;
		Node* prev = nullptr;
		
		while(curr != nullptr) {
			//If it's where it should be inserted
			if(curr->price > price) {
				//break
				break;
			}
			else if(curr->price == price && curr->time >= time) {
				//break
				break;
			}
			prev = curr;
			curr = curr->next;
		}
		//create a node
		Node* ptr = new Node(price, time);
		
		//Insert node in appropreate location
		//if at the start of the list
		 if(prev == nullptr) {
			ptr->next = curr;
			front = ptr;
		}
		//else node goes after prev
		else{
			prev->next = ptr;
			ptr->next = curr;
		}
		_size++;
		return true;
    }



    /**
     * func: insert_pareto_sorted
     * preconditions:  given collection (calling object) must be sorted AND pareto (pruned).
     *                 if this is not the case, false is returned.
     *                 (code segment for this test given).
     * desc: (assuming the list is sorted and pareto): if the option given by the parameters 
     *       price and time is NOT dominated by already existing options, the following results:
     *            - new option <price,time> is inserted maintaining the sorted property of the
     *                list, AND
     *            - any pre-existing options which are now suboptimal (i.e., dominated by the
     *                newly added option) are deleted.
     *       If the new option is suboptimal, the list is simply unchanged.
     *       In either case, true is returned (i.e., as long as the preconditions are met).
     *       
     * RUNTIME REQUIREMENT:  linear in the length of the list -- O(n)       
     *
     * REMEMBER:  
     *    If the new option is useless (dominated by a pre-existing option), the list is unchanged
     *         (but you still return true if preconditions are met).
     *    You must maintain sorted order and don't forget to deallocate memory associated
     *         with any deleted nodes.
     * status: PASSED INITIAL TESTING
     */
    bool insert_pareto_sorted(double price, double time) {
      if(!is_pareto_sorted()) return false;
		//traverse the list
		Node* curr = front;
		Node* prev = nullptr;
		
		while(curr != nullptr) {
			//if it is dominated, return
			if(price >= curr->price && time >= curr->time ) {
				return true;
			}
			//If it's where it should be inserted
			else if(curr->price > price) {
				//break
				break;
			}
			else if(curr->price == price && curr->time >= time) {
				//break
				break;
			}
			prev = curr;
			curr = curr->next;
		}
		//create a node
		Node* ptr = new Node(price, time);
		
		//Insert node in appropreate location
		//if at the start of the list
		 if(prev == nullptr) {
			ptr->next = curr;
			front = ptr;
		}
		//else node goes after prev
		else{
			prev->next = ptr;
			ptr->next = curr;
		}
		_size++;
		return true;
    }

    

   /**
   * func: union_pareto_sorted
   * precondition:  calling object and parameter collections must both be sorted and pareto (if not, nullptr is returned).
   * desc: constructs "the sorted, pareto" union (as in set-union excluding dominated options) of the two collections and returns 
   *               it as a newly created object.
   * RUNTIME:  linear in the length of the two lists (suppose one list is of length n and the other is of length m, 
   *            then the overall runtime must be O(n+m))
   * COMMENTS:  REMEMBER:  after this operation, the collection must be both pareto and sorted.
   * TIPS:  Think about what must be the FIRST option in the sorted union (bootstrap) -- then think about what is the 
   *        candidate for the 2nd option (if any).  
   *        Remember:  a pareto-sorted list must be strictly increasing and price and strictly decreasing in time.
   * 
   * status:  PASSED INITIAL TESTING
   * 
   */
    TravelOptions * union_pareto_sorted(const TravelOptions &other)const{
 		//return null if either isn't sorted
		if(!is_pareto_sorted() || !other.is_pareto_sorted())
	  		return nullptr;
	  		
	  	//create new list
	  	TravelOptions* list = new TravelOptions();
	  	Node* curr = list->front;
	  	
	  	//Traverse each list
		Node* origHd = front;
		Node* otherHd = other.front;
		while(origHd != nullptr && otherHd != nullptr) {
			//compare each item, then insert it to new list
			if(origHd->price <= otherHd->price && origHd->time < otherHd->time) {
				//create new node
				Node* ptr = new Node(origHd->price, origHd->time);
				
				//append node
				if(curr == nullptr) {
					list->front = ptr;
					curr = list->front;
				}
				else {
					curr->next = ptr;
					curr = curr->next;
				}
				list->_size++;
				
				//advance to next node
				origHd = origHd->next;
			}
			else if (origHd->price >= otherHd->price  && origHd->time > otherHd->time){
				//create new node
				Node* ptr = new Node(otherHd->price, otherHd->time);
				
				//append node
				if(curr == nullptr) {
					list->front = ptr;
					curr = list->front;
				}
				else {
					curr->next = ptr;
					curr = curr->next;
				}
				list->_size++;
				
				//advance to next node
				otherHd = otherHd->next;
			}
			//if they're exactly the same
			else {
				//append one
				//create new node
				Node* ptr = new Node(origHd->price, origHd->time);
				
				if(curr == nullptr) {
					list->front = ptr;
					curr = list->front;
				}
				else {
					curr->next = ptr;
					curr = curr->next;
				}
				list->_size++;
				
				//advance both
				origHd = origHd->next;
				otherHd = otherHd->next;
			}
		}
		
		//stick what's left of the lists to the new list, if any
		while(origHd != nullptr) {
			//append
			//create new node
				Node* ptr = new Node(origHd->price, origHd->time);
				
				//append node
				if(curr == nullptr) {
					list->front = ptr;
					curr = list->front;
				}
				else {
					curr->next = ptr;
					curr = curr->next;
				}
				list->_size++;
				
				//advance to next node
				origHd = origHd->next;
			
		}
		while(otherHd != nullptr) {
			//append
			//create new node
				Node* ptr = new Node(otherHd->price, otherHd->time);
				
				//append node
				if(curr == nullptr) {
					list->front = ptr;
					curr = list->front;
				}
				else {
					curr->next = ptr;
					curr = curr->next;
				}
				list->_size++;
				
				//advance to next node
				otherHd = otherHd->next;
		}
		
		
		//return list
		return list;
   }
    
   /**
   * func:  prune_sorted
   * precondition:  given collection must be sorted (if not, false is returned).
   * desc: takes sorted list of options and removes dominated entries
   *         (and eliminates any duplicates).
   * RUNTIME:  linear in the length of the list (O(n))
   * COMMENTS:  the resulting list will be sorted AND pareto.
   * status:  PASSED INITIAL TESTING
   * 
   */
    bool prune_sorted(){
		if(!is_sorted()) return false;
		
		Node* hd = front;
		while(hd != nullptr && hd->next != nullptr) {
			//check if current dominates next
			if(hd->time <= hd->next->time) {
				//delete next
				Node* skip = hd->next;
				hd->next = skip->next;
				delete skip;
			}
			//else
			{
				//advance to next
				hd = hd->next;
			}
		}
       return true;
    }


   /**
   * func: join_plus_plus
   * preconditions:  none -- both the calling object and parameter are just TravelOptions objects (not necessarily
   *                 sorted or pareto).
   * param: other; a reference to another to a list of TravelOptions (thus, there are two option lists: the calling 
   *               object and the parameter). 
   * desc: suppose you are planning a trip composed of two "legs":
   *
   *         first you travel from city X to city Y (this is part of your plan - you need to stop in city Y)
   *         then you continue from city Y to city Z
   *
   *       Let the calling object be the options for the X-to-Y leg and the parameter be the options for the
   *       Y-to-Z leg.
   *   
   *       Your job is to construct a pareto-sorted set of options for the entire trip and return the resulting
   *       TravelOptions object as a pointer.
   *
   *       In principle, any option <p1,t1> for the X-to-Y leg can be paird with any option <p2,t2> for the Y-to-Z leg.
   *       In such a pairing, the total price will be p1+p2 and the total time will be t1+t2, (i.e., option <p1+p2,t1+t2>).
   *       (This is why the operation is called join_plus_plus)
   *
   *       This function's  job is to determine the sorted-pareto list of options for the entire trip and return it
   *       as a pointer to the object.
   * returns:  a pointer to a TravelOptions object capturing all non-dominated options for the entire trip from X-to-Z
   *              (i.e., even though the given lists may not be sorted or pareto, the resulting list will be both).
   *
   * status:  PASSED INITIAL TESTING
   * RUNTIME:  no runtime requirement 
   *
   * TIPS:  
   *       Start by thinking about the "cross-product" of the two option lists (i.e., enumerating all pairs).
   *       Leverage some of the other operations in this assignment -- insert_pareto_sorted might be especially useful!
   *          (probably ought to implement any functions you plan on using first!).
   *       Don't overthink this one -- there is no runtime requirement after all.
   *
   * BOUNDARY CONDITIONS:  it is possible that one of both of the given option lists is empty!  The result is still 
   *    well-defined (also empty).  An empty option list is NOT the same as a null pointer though -- you should still return
   *   a pointer to a new TravelOptions object -- that object just happens to have an empty list.
   */
   TravelOptions * join_plus_plus(const TravelOptions &other) const {

	//create new list
	  	TravelOptions* list = new TravelOptions();
	  	
	  	//Traverse each list
		Node* origHd = front;
		Node* otherHd = other.front;
		while(origHd != nullptr) {
			while(otherHd != nullptr) {
				//insert node
				list->insert_pareto_sorted(origHd->price + otherHd->price, origHd->time + otherHd->time);
				
				//advance to next node
				otherHd = otherHd->next;
			}
			
			//advance to next node
			origHd = origHd->next;
		}
		
		//return list
		return list;
}



   /**
   * func: join_plus_max
   * preconditions:  both the calling object and the parameter are sorted-pareto lists (if not, nullptr is returned).
   * desc: imagine a different scenario (vs. join_plus_plus):  you are a parent with two children -- one living in city A and
   *         the other living in city C -- and they are both coming home for the holidays (let's call your home C).  
   *       You have a pareto-sorted option list for the A-to-C trip (this is the calling object) and a pareto-sorted option list
   *         for the B-to-C trip.
   *       Consider a particular option for the A-to-C trip <p1, t1> and a particular option for the B-to-C trip <p2,t2>.
   *         Clearly, the total price for selecting these two options is p1+p2.
   *         However (unlike in the plus_plus case), adding the t1 and t2 doesn't make sense right (the trips are in "parallel").
   *         What you care about as a parent is when BOTH of your children are home.  This is determine by MAX(t1,t2).
   *         Thus, the resulting "composite" option in this case would be <p1+p2, MAX(t1,t2)> (hence the name join_plus_max).
   *       
   *       Your job is to construct the sorted-pareto "composite" option list capturing the options for getting both children home.
   *         The resulting TravelOptions object is returned as a pointer (recall if the preconditions are not met, 
   *         nullptr is returned).
   *       
   * RUNTIME:  let N and M be the lengths of the respective lists given; your runtime must be linear in N+M (O(N+M)).
   *
   * status:  PASSED INITIAL TESTING
   *
   * TIPS:
   *      This one will take some thought!  If the specified runtime is possible, the resulting option list cannot be too
   *      large right (at most N+M in length)?  But there NxM possible pairing of options.  So enummerating all pairs
   *      of options cannot be an option (as was suggested for the _plus_plus case).  
   *
   *      Start by figuring out what the FIRST (cheapest) option in the resulting list MUST be.  
   *      Remember that a sorted-pareto list must be strictly increasing in price and strictly decreasing in time.
   *      Now think about what might be the 2nd option in the list you are building.  It must cost more than the first AND
   *         take less time.  To be more concrete, suppose your first option has total price of $100 and results in child A
   *         traveling for 12 hours and child B traveling for 8 hours.  Does it make sense to spend more money on child B
   *         so they can get home in say 7 hours?  Think about it!  The MAX function is important!
   */
   double maxTime(double a, double b) const {
		if(a >= b) {
			return a;
		}
		else {
			return b;
		}
   }
   
   TravelOptions * join_plus_max(const TravelOptions &other) const {

	if(!is_pareto() || !(other.is_pareto()))
		return nullptr;
	//create new list
  	TravelOptions* list = new TravelOptions();
  	Node* curr = list->front;
  	
  	//Traverse each list
	Node* origHd = front;
	Node* otherHd = other.front;
	while(origHd != nullptr && otherHd != nullptr) {
		
		//create new node
		double max = maxTime(origHd->time, otherHd->time);
		Node* ptr = new Node(origHd->price + otherHd->price, max);
			
		//if list is empty, get first elements
		if(curr == nullptr) {	
			list->front = ptr;
			curr = list->front;
			
			//advance to next node in the min time list
			if(max == origHd->time) {
				origHd = origHd->next;
			}
			else {
				otherHd = otherHd->next;
			}
		}
		else {
			//add node
			curr->next = ptr;
			curr = curr->next;
			
			//advance to next node in the min time list
			if(max == origHd->time) {
				origHd = origHd->next;
			}
			else {
				otherHd = otherHd->next;
			}
		}
		list->_size++;
	}
	
	//return list
	return list;
   }

   /**
   * func: sorted_clone
   * desc: returns a sorted TravelOptions object which contains the same elements as the current object
   * status:  DONE [but relies on to do item insert_sorted]
   */
   TravelOptions * sorted_clone() {
	TravelOptions *sorted = new TravelOptions();
	Node *p = front;
	
	while(p != nullptr) {
	  sorted->insert_sorted(p->price, p->time);
	  p = p->next;
 	}
	return sorted;
   }

   /**
   * func: split_sorted_pareto
   * precondition:  given list must be both sorted and pareto (if not, nullptr is returned; 
   *    code already given).
   * desc: This function takes a sorted-pareto option list and splits into two option lists:
   *
   *        - the options with price less than or equal to max_price (if any) are retained in the calling
   *            object (and only those are retained in the calling object).
   *        - the other, more expensive options are used to populate a new TravelOptions object which
   *            is returned as a pointer (i.e., the expensive options are returned)..
   * 
   * returns: pointer to expensive options or nullptr if the calling object is not pareto-sorted.
   * RUNTIME:  linear in the length of the given list (O(n)).
   * ADDITIONAL REQUIREMENT:  for full credit you MAY NOT ALLOCATE ANY NEW NODES!  Think about it --
   *        suppose your given list has 100 options and 40 of them are below the max_price threshold; 
   *        the other 60 options end up in the returnd list.  Still a grand total of 100 options and 
   *        therefore 100 nodes.  So... there should be no reason to delete or allocate any nodes. 
   * status:  PASSED INITIAL TESTING
   */
   TravelOptions * split_sorted_pareto(double max_price) {

		if(!is_pareto_sorted())
		  return nullptr;
		
		//create new list
		TravelOptions* list = new TravelOptions();
		Node* curr = list->front;
		
		//Traverse list
		Node* origHd = front;
		Node* prev = nullptr;
		
		//size tracker
		int s = 0;
		while(origHd != nullptr) {
			//if overpriced, remove and append to other list
			if(origHd->price > max_price) {

				//add elem to new list
				list->front = origHd;
				curr = list->front;
				
				//remove elem from old list
				//if all of the list fits the criteria
				if(prev == nullptr) {
					front = nullptr;
				}
				else {
					prev->next = nullptr;	
				}
				
				//correct _size for both lists
					list->_size = _size - s;
					_size = s;
				
				//break
				break;
			}
			else {
				prev = origHd;
				origHd = origHd->next;
				s++;
			}
		}
	
		return list;	
	}

   /**
   * func: display
   * desc: prints a string representation of the current TravelOptions object
   * status:  DONE
   */
   void display(){
	printf("   PRICE      TIME\n");
	printf("---------------------\n");
	Node * p = front;
	
	while(p!=nullptr) {
		printf("   %5.2f      %5.2f\n", p->price, p->time);
		p = p->next;
	}
   }

  /**
   * func:  checksum
   * desc:  Performs and XOR of all node pointers and returns result as
   *        an unsigned int.
   * 
   * status: DONE
   *
   * NOTES: YOU MAY NOT TOUCH OR MODIFY THIS FUNCTION!!
   */
  unsigned long int checksum() const {
    unsigned long int s = 0;
    Node *p = front;

    while (p != nullptr)
    {
      s = s ^ ((unsigned long int)p);
      p = p->next;
    }
    return s;
  }

};

#endif
