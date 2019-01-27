#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <list>
using namespace std;
#include "is_prime.h" 

// Double probing implementation.
//Kept most of the code from Quadratic Probing Header
template <typename HashedObj, typename doubleHash>
class HashDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashDouble(size_t size = 101) : array_(PrimeProject::NextPrime(size == 2 ? 3 : size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x, const doubleHash & dh = doubleHash{}) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].dh_ = dh;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x, doubleHash && dh = doubleHash{}) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = std::move(x);
    array_[current_pos].dh_ = std::move(dh);
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
    for(size_t i = 0; i < array_[current_pos].dh_.size(); i++)
        cout << array_[current_pos].dh_[i] << endl;
     } 
  //used similar logic to Remove() function
  doubleHash& operator[] (const HashedObj &x){
      size_t current_pos = FindPos(x);
      if(!IsActive(current_pos)){
          Insert(x);
          current_pos = FindPos(x);
      }
      return array_[current_pos].dh_;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    doubleHash dh_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{},const doubleHash & dh = doubleHash{}, EntryType i = EMPTY)
    :element_{e}, dh_{dh}, info_{i} { }
    
    HashEntry(HashedObj && e, doubleHash && dh, EntryType i = EMPTY)
    :element_{std::move(e)}, dh_{std::move(dh)}, info_{ i } {}
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
	Insert(std::move(entry.element_), std::move(entry.dh_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // QUADRATIC_PROBING_H
