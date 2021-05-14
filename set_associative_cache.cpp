#include <fstream>
#include <bits/stdc++.h>
#include "FIFO.cpp"
#include "LRU.cpp"
using namespace std;


class Cache {
public:
	int cacheSize;
	int blockSize;
	int ways;
	int numOfBlock;
	int numOfSets;
	int offsetBits;
	int setBits;
	int tagBits;
	vector<int> tags;
	vector<bool> valid;
	vector<int> data;
	FIFO fifo;
	LRU lru;

	Cache(int blockSize, int cacheSize, int ways) {
		this->cacheSize = cacheSize;
		this->blockSize = blockSize;
		this->ways = ways;
		this->numOfBlock = cacheSize / blockSize;
		this->offsetBits = (int) log2(blockSize * 4);
		this->numOfSets = (int) cacheSize / (blockSize * ways);
		this->setBits = (int) log2(this->numOfSets);
		this->tagBits = 16 - offsetBits - setBits;
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		for(int i = 0; i < numOfBlock; i++) {
			valid[i] = false;
		}
		this->data.reserve(numOfBlock);
		this->fifo = FIFO(this->ways, this->numOfSets);
		this->lru = LRU(this->ways, this->numOfSets);
		// cout << "number of blocks :" << numOfBlock << endl;
		// cout << "number of offSet bits : " << offsetBits << endl;
	}

	int get(int addr) {
		int offSet = addr & (int) pow(2, offsetBits) - 1;
		// cout << "offSet bits : " << offSet << endl;
		addr = addr >> offsetBits;
		int set = addr & (int) pow(2, setBits) - 1;
		// cout << "set : " << set << endl;
		int tag = addr >> setBits;
		// cout << "tag : " << tag << endl;
		int index = lru.getIndex(tag, set, this->ways, tags, valid);
		// cout << "index : " << index << endl;
		// cout << "--------------------------------" << endl;
		return data[index];
	}
};



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


int main() {

	Cache cache = Cache(1, 16, 2);
	vector<string> data = readDataIntoVector("LW-sAddrs.txt");
	
	int indx = 0, total = data.size();
	while(indx < 10000) {
		string addr = data[indx % total];
		// cout << "address:" << addr << endl;
		indx++;
		int data = cache.get(stoi(addr, 0, 16));
	}
	cout << "hits : " << cache.lru.hit << endl;
	cout << "miss : " << cache.lru.miss << endl;
	return 0;
}