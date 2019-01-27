#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <list>
using namespace std;
#include "is_prime.h" 

// Quadratic probing implementation.
template <typename HashedObj, typename quadProb>
class HashQuadraticProbing {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashQuadraticProbing(size_t size = 101) : array_(PrimeProject::NextPrime(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x, const quadProb & qp = quadProb{}) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].qp_ = qp;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x, quadProb && qp = quadProb{}) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = std::move(x);
    array_[current_pos].qp_ = std::move(qp);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
   //function to print the chain
   void outputChain(const string & inputChain) const {
    size_t current_pos = FindPos(inputChain);
    if(!IsActive(current_pos)){
        cout << "Word not found " << endl;
        return;
    }
    //iterate 
    cout << "Input Word: " << inputChain << endl;
    for(size_t i = 0; i < array_[current_pos].qp_.size(); i++)
        cout << array_[current_pos].qp_[i] << endl;

     } 
  //used similar logic to Remove() function
  quadProb& operator[] (const HashedObj &x){
      size_t current_pos = FindPos(x);
      if(!IsActive(current_pos)){
          Insert(x);
          current_pos = FindPos(x);
      }
      return array_[current_pos].qp_;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    quadProb qp_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, const quadProb & qp = quadProb{}, EntryType i = EMPTY)
    :element_{e},  qp_{qp},  info_{i} { }
    
    HashEntry(HashedObj && e, quadProb && qp, EntryType i = EMPTY)
    :element_{std::move(e)}, qp_{std::move(qp)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      current_pos += offset;  // Compute ith probe.
      offset += 2;
      if (current_pos >= array_.size())
	        current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(PrimeProject::NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	        Insert(std::move(entry.element_), std::move(entry.qp_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // QUADRATIC_PROBING_H
