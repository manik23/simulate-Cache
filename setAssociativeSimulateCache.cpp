/*

Author -

Manik Mahajan

*/

#include <iostream>
#include<fstream>
#include<vector>
#include "require.cpp"
#include <sstream>
#include <math.h>
#include <string.h>
#include <list>
#include <set>
#include <unordered_map>
#include <map>
using namespace std;

int cacheHIT = 0;
int cacheMISS = 0;


int lines;
int sets = 1;
int block_bits;
int set_bits = 0;


bool insertIntoSet( int mmBlock, vector<vector<int>> &cache, vector<int> &counter, vector<list<int>> &Q, vector<map< int, list<int>::iterator>> &hash) {
	mmBlock >>= block_bits;
	int set_number = mmBlock & int(pow(2, set_bits) - 1);

	if (REPLACEMENT_POLICY == 0) {
		/*
		FIFO Page Replacement Policy
		*/
		for (auto x : cache[set_number]) {

			if (x == mmBlock) {
				return 1;
			}
		}


		cache[set_number][counter[set_number]++ % K] = mmBlock;
		return 0;

	}
	else {

		/*
			LRU page Replacement Policy
		*/

		if (hash[set_number].find(mmBlock) !=  hash[set_number].end()) {
			auto it  = hash[set_number][mmBlock];
			Q[set_number].push_front(mmBlock);
			Q[set_number].erase(it);
			hash[set_number][mmBlock] = Q[set_number].begin();
			return 1;
		}
		else {

			if (counter[set_number] < K ) {
				cache[set_number][counter[set_number]++] = mmBlock;
				Q[set_number].push_front(mmBlock);
				hash[set_number][mmBlock] = Q[set_number].begin();
			}
			else {
				int tobeReplaced = Q[set_number].back();
				hash[set_number].erase(tobeReplaced);
				Q[set_number].pop_back();

				Q[set_number].push_front(mmBlock);
				hash[set_number][mmBlock] = Q[set_number].begin();

				for (auto &x : cache[set_number]) {
					if (x == tobeReplaced) {
						x = mmBlock;
						break;
					}
				}
			}
			return 0;
		}
	}

}

void print(vector<vector<int>> &cache) {
	cout << "\nafter second repitition - Cache status\n";
	for (int i = 0; i < cache.size(); i++) {
		cout << "set set_number " << i << " --> ";
		for (auto x : cache[i]) {
			cout << std::hex << x << " ";
		}
		cout << endl;
	}
}


int main() {

	fstream file;
	file.open(FILENAME, ios::in);
	string s;
	if (file.is_open())
		getline(file, s);
	else {
		cout << "Error in Reading file. Check File Name\n";
	}
	s += ",";

	vector<int> mainMemory;
	string temp;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ',') {
			int x;
			stringstream ss;
			ss << std ::hex << temp;
			ss >> x;
			mainMemory.push_back(x);
			temp = "";
		}
		else {
			temp += s[i];
		}
	}

	set<int> compulsaryMiss(mainMemory.begin(), mainMemory.end());




	// Intialise Cache Memory
	lines = CACHE_SIZE / BLOCK_SIZE;
	block_bits = log2(BLOCK_SIZE);
	sets = lines / K;
	set_bits = log2(sets);

	// cache memory

	vector<vector< int>> cache(sets, vector< int> (K, -1));
	vector<int> counter(sets, 0);

	// These DS for LRU
	vector<list<int>> Q(sets);
	vector<map< int, list<int>::iterator>> hash(sets);
	//

	int repitition = 2 * mainMemory.size();;

	int modSize = mainMemory.size();

	string policy = (REPLACEMENT_POLICY == 0) ? "FIFO" : "LRU";
	cout << "cache details : " << endl;
	cout << "cache size (words) " << CACHE_SIZE << endl;
	cout << "block size (words) " << BLOCK_SIZE << endl;
	cout << "cache type - Set Associative" << endl;
	cout << "k-ways " << K << endl;
	cout << "replacement policy " << policy << endl;

	for (int i = 0; i < ITERATIONS; i++) {

		// Dividing by 4 to convert Byte address to word address.
		if (insertIntoSet(mainMemory[i % modSize] / 4 , cache, counter, Q, hash)) {
			cacheHIT++;
		}
		else {
			cacheMISS++;
		}
		if (i == repitition - 1) {
			print(cache);
		}

	}




	cout << "\ntotal iterations " << ITERATIONS << endl;
	cout << "Hit Rate  -> \t" << (double(cacheHIT - compulsaryMiss.size()) / double(ITERATIONS) * 100 ) << "%"  << endl;
	cout << "Miss Rate ->    " << (double(cacheMISS - compulsaryMiss.size()) / double(ITERATIONS) * 100 ) << "%"  << endl;

}









