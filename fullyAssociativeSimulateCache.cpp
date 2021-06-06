/*

Author -

Manik Mahajan

*/
#include <algorithm>
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
int block_bits;


bool insertIntofully( int mmBlock, vector<int> & cache, int & counter, list<int> & Q) {
	mmBlock >>= block_bits;


	if (REPLACEMENT_POLICY == 0) {
		/*
		FIFO Page Replacement Policy
		*/
		vector<int>::iterator it;
		it = find(cache.begin(), cache.end(), mmBlock);

		if (it != cache.end()) {
			return 1;
		}
		else {
			if (counter < lines - 1) {
				counter++;
			}
			else {
				counter = 0;
			}
			cache[counter] = mmBlock;
			// cout<<"debug";
			return 0;
		}
	}
	else {

		/*
			LRU page Replacement Policy
		*/
		vector<int>::iterator it;
		it = find(cache.begin(), cache.end(), mmBlock);

		if (it != cache.end()) {
			list<int>::iterator listIt;
			listIt = find(Q.begin(), Q.end(), mmBlock);
			if (listIt != Q.end()) {
				Q.erase(listIt);
				Q.push_front(mmBlock);
			}
			return true;
		}
		else {
			if (counter < lines) {
				cache[counter++] = mmBlock;
				Q.push_front(mmBlock);
			}
			else {
				int tobereplace = Q.back();
				Q.pop_back();

				replace(cache.begin(), cache.end(), tobereplace, mmBlock);
				Q.push_front(mmBlock);
			}
			return false;

		}
	}

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
	// cout<<s<<"\n";

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
	// for(auto i : mainMemory) cout<<"->"<<i;
	// cout<<"\n";

	set<int> compulsaryMiss(mainMemory.begin(), mainMemory.end());






	// Intialise Cache Memory
	lines = CACHE_SIZE / BLOCK_SIZE;
	block_bits = log2(BLOCK_SIZE);
	// cache memory
	vector<int> cache(lines, -1);
	int counter = 0;

	// These DS for LRU
	list<int> Q;
	//

	int repitition = 2 * mainMemory.size();
	int modSize = mainMemory.size();

	string policy = (REPLACEMENT_POLICY == 0) ? "FIFO" : "LRU";
	cout << "cache details : " << endl;
	cout << "cache size (words) " << CACHE_SIZE << endl;
	cout << "block size (words) " << BLOCK_SIZE << endl;
	cout << "cache type - fully Associative" << endl;
	// cout << "k-ways " << K << endl;
	cout << "replacement policy " << policy << endl;

	for (int i = 0; i < ITERATIONS; i++) {

		// Dividing by 4 to convert Byte address to word address.
		if (insertIntofully(mainMemory[i % modSize] / 4 , cache, counter, Q)) {
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
