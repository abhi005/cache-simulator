#include <fstream>
#include <bits/stdc++.h>
#include "FIFO.cpp"
#include "LRU.cpp"
using namespace std;

class Cache {
public:
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int tagBits;
	vector<int> tags;
	vector<int> data;
	FIFO fifo;
	LRU lru;

	Cache(int blockSize, int cacheSize) {
		this->cacheSize = cacheSize;
		this->blockSize = blockSize;
		this->numOfBlock = cacheSize / blockSize;
		this->offsetBits = (int) log2(blockSize * 4);
		this->tagBits = 16 - offsetBits;
		this->tags.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		this->fifo = FIFO(this->numOfBlock, 1);
		this->lru = LRU(this->numOfBlock, 1);
		// cout << "number of blocks :" << numOfBlock << endl;
		// cout << "number of offSet bits : " << offsetBits << endl;
	}

	int get(int addr) {
		int offSet = addr & (int) pow(2, offsetBits) - 1;
		// cout << "offSet bits : " << offSet << endl;
		int tag = addr >> offsetBits;
		// cout << "tag : " << tag << endl;
		int index = lru.getIndex(tag, tags);
		// cout << "index : " << index << endl;
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

	Cache cache = Cache(1, 16);
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