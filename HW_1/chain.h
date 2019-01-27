// Include your name here.
// Place comments describing the class Chain (two lines).

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <sstream>

namespace teaching_project {
// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Chain {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor.
  Chain(){
    size_ = 0;
    array_ = nullptr;
    //std::cout << size_ << " " << array_;
   // std::cout << size_ << " " << array_;
  }

  // Copy-constructor.
  Chain(const Chain &rhs){
    array_ = rhs.array_;
    size_ = rhs.size_;

  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Chain copy = rhs;
  // std::swap(*this, copy);
  // return *this;
  // }

  Chain& operator=(const Chain &rhs){
    Chain copy = rhs;
    std::swap(*this, copy);
    return *this;
  }


  // Move-constructor.
  Chain(Chain &&rhs){
    array_ = rhs.array_;
    rhs.array_ = nullptr;
    size_ = rhs.size_;
    rhs.size_ = 0;
  }
  // Move-assignment.
  // Just use std::swap() for all variables.
  Chain& operator=(Chain &&rhs){
    size_ = 0;
    array_ = nullptr;
    if(this != &rhs){
      std::swap(size_, rhs.size_);
      std::swap(array_, rhs.array_);
    }
    return *this;
  }

  ~Chain() {
    array_ = nullptr;
    delete array_;
    size_ = 0;

  }

  // End of big-five.

  // One parameter constructor.
  Chain(const Object& item) {
    // Write something.
    Object *tempObject = new Object[1];
    tempObject[0] = item;
    array_ = tempObject;
    size_ = 1;
    tempObject = nullptr;
    delete[] tempObject;
  }
  // Read a chain from standard input.
  void ReadChain() {
     // Write something.
    //char size_array = stringArray[1];
    std::string tempArray;
    std::getline(std::cin, tempArray);
    char k = tempArray[1];
    int tempSize = int(k) - 48;
    int size = tempSize;

    int arraySize = 0;
    std::string tempString = "";
    Object *ssObj = new Object[size];
    //std::cout << tempSize;
    for(int i = 4; i < tempArray.length(); i++){

      if(tempArray[i] != ' ' && i != tempArray.length()-1)
        tempString.push_back(tempArray[i]);
      else {
        std::stringstream ss_(tempString);
        //std::cout << tempString;

        ss_ >> ssObj[arraySize];
        arraySize++;
        tempString = "";
      }

    }
    array_ = ssObj;
    size_ = size;
  }
  size_t size() const { // Write something
    return size_;
  }

  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // const version.
  // abort() if out-of-range.
  const Object& operator[](size_t location) const {
    return array_[location];
    // Write something
  }

 // @location: an index to a location in the range.
 // @returns the Object at @location.
 // non-const version.
 // abort() if out-of-range.
 Object& operator[](size_t location) {
   return array_[location];
   // Write something (will be the same as above)
 }

 //  @c1: A chain.
 //  @c2: A second chain.
 //  @return the concatenation of the two chains.
friend Chain operator+(const Chain &c1, const Chain &c2) {
  // Write something.
  int c1_size = c1.size_;
  int c2_size = c2.size_;
  int sizeChain = c1_size + c2_size;
  Object * c3 = new Object[sizeChain];
  for(int i = 0; i < c1_size; i++){
    c3[i] = c1.array_[i];
  }
  for(int j = c1_size; j < sizeChain; j++){
    int tempSize = j - c1_size;
    c3[j] = c2.array_[tempSize];
  }
  Chain<Object> c4;
  c4.array_ = c3;
  c4.size_ = sizeChain;
  return c4;
 }

friend Chain operator+(const Chain &c1, const Object &c2){
  Chain<Object> c5;
  c5.size_ = c1.size_ + 1;
  int c5_size = c5.size_;
  Object * tempObject = new Object[c5_size];
  for(int i = 0; i < c5_size - 1; i++){
    tempObject[i] = c1.array_[i];
    tempObject[c5_size - 1] = c2;
  }
  c5.array_ = tempObject;
  c5.size_ = c1.size_ + 1;
  return c5;
}
 // Overloading the << operator.
friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain)
{
  // Print the chain.
  out << '[';
  int sizeChain = a_chain.size_;
  for(int i = 0; i < sizeChain; i++){
    if(i == sizeChain - 1)
      out << a_chain.array_[i];
    else
      out << a_chain.array_[i] << ' ';
  }
  out << ']';
  out << std::endl;
  return out;
 }

 private:
  size_t size_;
  Object *array_;
};

}
// namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
