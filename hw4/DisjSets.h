// Disjoint set class, implementing Union-Find.
// From the code provided by the book of Mark Allen Weiss.

#ifndef DISJOINT_SETS_H_
#define DISJOINT_SETS_H_

#include <cstdlib>
#include <iostream>
#include <vector>



//  Disjoint set class.
//  Use union by rank and path compression.
//  Elements in the set are numbered starting at 0.
class DisjointSets {
 public:
  explicit DisjointSets(size_t num_elements) {
    for (int i = 0; i < num_elements; ++i)
      the_sets_.push_back(-1);
  }

  size_t Find(size_t x) const {
    if (x >= the_sets_.size()) abort();
    if (the_sets_[x] < 0)
      return x;
    else
      return Find(the_sets_[x]);
  }

  size_t Find(size_t x) {
    if (x >= the_sets_.size()) abort();
    if (the_sets_[x] < 0)
      return x;
    else
      return Find(the_sets_[x]);
  }
  
   
  void UnionSets(size_t root1, size_t root2) {
    if (root1 >= the_sets_.size()) abort();
    if (root2 >= the_sets_.size()) abort();
    if (root1 == root2) return;
    if (the_sets_[root2] < the_sets_[root1]) {
      the_sets_[root1] = root2;        
    } else  {
      if (the_sets_[root1] == the_sets_[root2])
	--the_sets_[root1];        
      the_sets_[root2] = root1;      
    }
  }
  
 private:

  std::vector<int> the_sets_;
};


#endif  