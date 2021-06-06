/*

Author -
Manik Mahajan
*/

#include <iostream>
#include <fstream>
#include <vector>
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
int block_bits;


bool insertIntoDirect( int mmBlock, vector<int> &cache) {
	mmBlock >>= block_bits;
	int block_number = mmBlock &  (lines - 1);


	// cout <<  std::hex << x << " "  << mmBlock << endl;
	if (cache[block_number] == mmBlock) {
		return 1;
	}
	cache[block_number] = mmBlock;
	return 0;



}

void print(vector<int> &cache) {
	cout << "\nafter second repitition - Cache status\n";
	for (auto x : cache) {
		cout << x << endl;
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

	vector< int> mainMemory;
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


	set<int>  compulsaryMiss(mainMemory.begin(), mainMemory.end());

	// intializeCache();

	// Intialise Catches


	lines = CACHE_SIZE / BLOCK_SIZE;
	block_bits = log2(BLOCK_SIZE);


	string policy = (REPLACEMENT_POLICY == 0) ? "FIFO" : "LRU";
	cout << "cache details : " << endl;
	cout << "cache size (words) " << CACHE_SIZE << endl;
	cout << "block size (words) " << BLOCK_SIZE << endl;
	cout << "cache type - Direct" << endl;
	// cout << "replacement policy " << policy << endl;



	vector<int> cache(lines);
	int modSize = mainMemory.size();
	int repitition = 2 * mainMemory.size();;


	for (int i = 0; i < ITERATIONS; i++) {

		if (insertIntoDirect(mainMemory[i % modSize] / 4 , cache)) {
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









