#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <string>

#include "quadratic_probing.h"
#include "double_hash.h"
#include "sep_chain.h"

using namespace std;

template <typename HashTableType>
void Print(const HashTableType & hash_table){
  int i = 0;
  string hash_word;
  while (i < 2){
    cout << "Input word: ";
    cin >> hash_word;
    hash_table.outputChain(hash_word);
    i++;
  }
}
template <typename HashTableType>
void TestComputeAdjacentWords(HashTableType &hash_table, 
			      const vector<string> &words, const string &hashMap) {
  // This is for computing timing.
  const auto begin = chrono::high_resolution_clock::now();

  hash_table.MakeEmpty();  
  map<int, vector<string>> wordsByLength;
  //..Insert your own code using algorithm described in Figure 4.73
  // Group the words by their length
	for( auto & str : words )
	  wordsByLength[ str.length( ) ].push_back( str );
  // Work on each group separately
	for (auto & entry : wordsByLength){
	  const vector<string> & groupsWords = entry.second;
	  int groupNum = entry.first;
	  // Work on each position in each group
	  for( int i = 0; i < groupNum; ++i ){
       // Remove one character in specified position, computing representative.
	    // Words with same representatives are adjacent; so populate a map ...
			map<string, vector<string>> repToWord;
           for (auto & str : groupsWords){
	       string rep = str;
	       rep.erase(i, 1);
	       repToWord[rep].push_back(str);
	     }

	     for (auto & entry : repToWord){
	       const vector<string> & clique = entry.second;
	       if (clique.size() >= 2){
	         for (int p = 0; p < clique.size(); ++p){
	           for (int q = p+1; q < clique.size(); ++q){
							 hash_table[clique[p]].push_back(clique[q]);
							 hash_table[clique[q]].push_back(clique[p]);
	           }
	         }
	       }
	     }
	   }
	 }


  const auto end = chrono::high_resolution_clock::now();
  cout << "Time to build map:" << endl;
  cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;

  Print(hash_table);
}

vector<string> ReadWordsFromFile(const string &words_filename) {
  vector<string> the_words;
  // Implement this...
  //open, read, and close file once finished reading
  ifstream inLine;
  inLine.open(words_filename);
  if(!inLine.is_open()){
    cerr << "File cannot be opened!" << endl;
  }
  while(!inLine.eof()){
    string words_file;
    getline(inLine, words_file);
    the_words.push_back(words_file);
  }
  inLine.close();
  return the_words;
}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " words_file_name hash_type (chaining, quadratic or double)" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const vector<string> the_words = ReadWordsFromFile(words_filename);

  const string param_flag(argv[2]);
  if(param_flag == "chaining"){
    HashSepChain<string, vector<string>> separate_chaining_table;
    TestComputeAdjacentWords(separate_chaining_table, the_words, "chaining");
  }
  else if (param_flag == "quadratic") {
    HashQuadraticProbing<string, vector<string>> quadratic_probing_table;    
    TestComputeAdjacentWords(quadratic_probing_table, the_words, "quadratic");
  } else if (param_flag == "double") {
    HashDouble<string, vector<string>> double_probing_table;
    TestComputeAdjacentWords(double_probing_table, the_words, "double");    
  } else {
    cout << "Uknown hash type " << param_flag << " (User should provide chaining, quadratic, or double)" << endl;
  }
  return 0;
}
