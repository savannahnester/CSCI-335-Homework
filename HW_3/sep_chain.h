#ifndef SEP_CHAIN_H
#define SEP_CHAIN_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <list>
using namespace std;
#include "is_prime.h" 

//functions based off those in quadratic_probing.h and the functions 
//in section 5.3 on separate chaining

template <typename HashedObj, typename SepChain>
class HashSepChain {
    public:
    //setting size = 101 as demonstrated in figure 5.6 
        explicit HashSepChain(int size = 101) : chain_size_{0} { theLists.resize(101); }
        //going to use similar functions to that in quadratic_probing.h such as 
        //Contains, Insert, Remove, and MakeEmpty
        void MakeEmpty(){
            //figure 5.9, section 5.3
            for( auto & thisList: theLists )
                thisList.clear();
        }
        bool Contains( const HashedObj & x) const {
            //figure 5.9, section 5.3
            auto & whichList = theLists[ MyHash ( x ) ];
            return find( begin( whichList ), end( whichList ), x) != end( whichList );
         } 
         //slight change compared to the example in textbook; want to have a default
         //value when doing separate chaining so x can be inserted
         bool Insert(const HashedObj & x, const SepChain &sc = SepChain{}){
             //function itself is based on section 5.3 figure 5.10
             auto & whichList = theLists [ MyHash(x) ];
             if(find(begin(whichList), end(whichList), x) != end(whichList))
                return false;
            whichList.push_back(HashEntry(x,sc));
            //Rehash
            if(++chain_size_ > theLists.size() )
                Rehash();
            return true;
         }
         //based on diagram 5.10 and other insert function in quadratic_probing.h
         //(to include  function parameter for SepChain)
         bool Insert( HashedObj && x, SepChain && sc = SepChain{} ){
             auto & whichList = theLists[ MyHash( x ) ];
             if(find(begin(whichList), end(whichList), x) != end(whichList))
                return false;
            whichList.push_back(HashEntry(std::move(x) ,std::move(sc)));
            //Rehash
            if(++chain_size_ > theLists.size() )
                Rehash();
            return true;
         }
         //section 5.3 figure 5.9
         bool Remove( const HashedObj & x, const SepChain & sc ){
             auto & whichList = theLists[ MyHash ( x ) ];
               auto itr = find( begin( whichList ), end( whichList ), x );

            if( itr == end( whichList ) )
                return false;

             whichList.erase( itr );
             --chain_size_;
             return true;
         }
         //function to print the chain
         void outputChain(const string & inputChain) const {
             //based off other functions thus far
             auto & whichList = theLists[ MyHash ( inputChain )];
             auto itr = find( begin( whichList ), end( whichList ), inputChain );
             if( itr == end( whichList ) ) {
                 cout << "Word not found" << endl;
                 return;
             }
             //iterate 
             cout << "Input Word:  " << inputChain << endl;
             for(size_t i = 0; i < itr->sc_.size(); i++)
                 cout << itr->sc_[i] << endl;
         }
        SepChain & operator[](const HashedObj & x){
            auto & whichList = theLists[ MyHash ( x ) ];
            auto itr = find( begin( whichList ), end( whichList ), x );
            if( itr == end( whichList ) ){
                itr = find( begin( whichList ), end( whichList ), x );
            }
            return itr->sc_;
        }
    private: 
        //struct constructed similar to one in quadratic_probing.h
        //included overload operator to find element
    struct HashEntry {
        HashedObj element_;
        SepChain sc_;
    
        HashEntry(const HashedObj& e = HashedObj{}, const SepChain & sc = SepChain{})
        :element_{e}, sc_{sc} { }
    
        HashEntry(HashedObj && e, SepChain && sc)
        :element_{std::move(e)}, sc_{std::move(sc)} {}

        //based on section 5.3 figure 5.8
        bool operator==(const HashEntry & rhs)const{
            return this->element_ == rhs.element_;
        }
        bool operator==(const HashEntry && rhs)const{
            return this->element_ == rhs.element_;
        }
    };
    //vector of lists so can create the list theLists
    vector<list<HashEntry>> theLists;
    int chain_size_;
    //section 5.6, figure 5.22
    void Rehash(){
        vector<list<HashEntry>> oldLists = theLists;
        theLists.resize(PrimeProject::NextPrime(2 * theLists.size()));
        for(auto & thisList : theLists)
            thisList.clear();
        chain_size_ = 0;
        for(auto & thisList : oldLists){
            for(auto & x : thisList)
                Insert(std::move(x.element_), std::move(x.sc_));
        }
    }
    //figure 5.7
    size_t MyHash(const HashedObj & x ) const {
        static hash<HashedObj> hf;
        return hf( x ) % theLists.size();
    
    }
};

#endif
