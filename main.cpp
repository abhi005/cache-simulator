#include <bits/stdc++.h>
#include <stdio.h>
#include "FIFO.cpp"
#include "LRU.cpp"
#include "directmap_cache.cpp"
#include "fully_associative_cache.cpp"
#include "set_associative_cache.cpp"
#include <fstream>

using namespace std;


/*
* @method
* method to read file into vector seperated by coma ","
*
* @param
* filename = filename to be read
*/
vector<string> readDataIntoVector(string filename) {
	ifstream f(filename);
	stringstream strStream;
	strStream << f.rdbuf();
	string str = strStream.str();
	f.close();

	vector<string> truth;
	stringstream ss(str);
	while(ss.good()) {
		string substr;
		getline(ss, substr, ',');
		truth.push_back(substr);
	}
	
	return truth;
}

/*
* @method
* main function - starting point of application
*/

int main() {

	/*
	* @params
	* cache_type = user input for cache type (1 : direct mapping, 2 : fully associative, 3 : set associative)
	* cache_size = user input for cache size (in words unit, 1 word = 4 bytes)
	* block_size = user input for block size (in words unit)
	* ways = user input for number of ways for set associative
	*/
	int cache_type;
	int cache_size;
	int block_size;
	int replacement_policy;
	int ways;

	// reading input file
	vector<string> data = readDataIntoVector("LW-sAddrs.txt");

	cout << "Cache Simulator" << endl;
	cout << "----------------------------------------------------------------\n" << endl;

	// infinite loop to run program
	while(true) {

		// taking user input for cache type
		cout << "Select Cache Type" << endl;
		cout << "1. Direct mapping cache\n2. Fully Associative Cache\n3. Set Associative Cache" << endl;
		cin >> cache_type;

		// DIRECT MAPPING CACHE
		if(cache_type == 1) {

			// taking user input for cache parameters
			cout << "you selected direct mapping cache\n" << endl;
			cout << "Enter cache size (unit words): ";
			cin >> cache_size;
			cout << "\nSelect cache block size" << endl;
			cout << "1. 1-word\n2. 2-word" << endl; 
			cin >> block_size;
			cout << endl;

			// initiating direct map cache
			DirectMapCache cache = DirectMapCache(block_size, cache_size);
		
			// looping through given instruction addresses 10000 time
			int indx = 0, total = data.size();
			while(indx < 10000) {
				string addr = data[indx % total];
				indx++;
				int data = cache.get(stoi(addr, 0, 16));
			}

			cout << "hits : " << cache.hit << endl;
			cout << "miss : " << cache.miss << endl;

			//cache.display();

		} else {

			// FULLY ASSOCIATIVE CACHE
			if(cache_type == 2) {

				// taking user input for cache parameters
				cout << "you selected fully associative cache\n" << endl;
				cout << "Enter cache size (unit words): ";
				cin >> cache_size;
				cout << "\nSelect cache block size" << endl;
				cout << "1. 1-word\n2. 2-word" << endl; 
				cin >> block_size;
				cout << "\nSelect Replacement Policy" << endl;
				cout << "1. FIFO\n2. LRU" << endl;
				cin >> replacement_policy;
				cout << endl;

				// initiating fully  associative cache
				FullyAssociativeCache cache = FullyAssociativeCache(block_size, cache_size, replacement_policy);
				
				// looping through given instruction addresses 10000 times
				int indx = 0, total = data.size();
				while(indx < 50) {
					string addr = data[indx % total];
					indx++;
					int data = cache.get(stoi(addr, 0, 16));
				}

				cout << "hits : " << (replacement_policy == 1 ? cache.fifo.hit : cache.lru.hit) << endl;
				cout << "miss : " << (replacement_policy == 1 ? cache.fifo.miss : cache.lru.miss) << endl;
				
				// cache.display();

			} 

			// SET ASSOCIATIVE CACHE
			else if(cache_type == 3) {

				// taking user input for cache parameters
				cout << "\nyou selected set associative cache\n" << endl;
				cout << "Enter cache size (unit words): ";
				cin >> cache_size;
				cout << "\nSelect cache block size" << endl;
				cout << "1. 1-word\n2. 2-word" << endl;
				cin >> block_size;
				cout << "\nSelect Replacement Policy" << endl;
				cout << "1. FIFO\n2. LRU" << endl;
				cin >> replacement_policy;
				cout << "\nSelect ways" << endl;
				cout << "1. 2-way\n2. 4-way" << endl;
				cin >> ways;
				cout << endl;

				// initiating set associative cache
				SetAssociativeCache cache = SetAssociativeCache(block_size, cache_size, ways, replacement_policy);
				
				// looping through given instruction addresses 10000 times
				int indx = 0, total = data.size();
				while(indx < 50) {
					string addr = data[indx % total];
					indx++;
					int data = cache.get(stoi(addr, 0, 16));
				}
				
				cout << "hits : " << (replacement_policy == 1 ? cache.fifo.hit : cache.lru.hit) << endl;
				cout << "miss : " << (replacement_policy == 1 ? cache.fifo.miss : cache.lru.miss) << endl;

				// cache.display();
			} else {
				cout << "\nwrong choice" << endl;
			}
		}

		string reply;
		cout << "\nDo you want to continue (Y/N)?" << endl;
		cin >> reply;
		if(reply == "N" || reply == "n") break;
	}
	return 0;
}