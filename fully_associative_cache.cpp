#include <fstream>
#include <bits/stdc++.h>
#include "FIFO.cpp"

using namespace std;

class Cache {
public:
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int tagBits;
	vector<uint> tags;
	vector<int> data; 
	int hit;
	int miss;
	FIFO fifo;

	Cache(int blockSize, int cacheSize) {
		this->cacheSize = cacheSize;
		this->blockSize = blockSize;
		this->numOfBlock = cacheSize / blockSize;
		this->offsetBits = (int) log2(blockSize * 4);
		this->tagBits = 16 - offsetBits;
		this->tags.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		this->hit = 0;
		this->miss = 0;
		this->fifo = FIFO(this->numOfBlock);

		// cout << "number of blocks :" << numOfBlock << endl;
		// cout << "number of offSet bits : " << offsetBits << endl;
	}

	int get(int addr) {
		int offSet = addr & (int) pow(2, offsetBits - 1);
		// cout << "offSet bits : " << offSet << endl;
		int tag = addr >> offsetBits;
		// cout << "tag : " << tag << endl;
		int index = getIndex(tag);
		if(index == -1) {
			// cout << "miss" << endl;
			miss++;
			index = fifo.getIndex();
			// cout << "index : " << index << endl;
			tags[index] = tag;
			data[index] = 0; // dummy data
			return data[index];
		} else {
			// cout << "hit" << endl;
			// cout << "index : " << index << endl;
			hit++;
			return data[index];
		}
	}

	int getIndex(int tag) {
		for(int i = 0; i <= blockSize; i++) {
			if(tags[i] == tag) return i;
		}
		return -1;
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

	Cache cache = Cache(2, 16);
	vector<string> data = readDataIntoVector("LW-sAddrs.txt");
	
	int indx = 0, total = data.size();
	while(indx < 10000) {
		string addr = data[indx % total];
		// cout << "address:" << addr << endl;
		indx++;
		int data = cache.get(stoi(addr, 0, 16));
	}
	cout << "hits : " << cache.hit << endl;
	cout << "miss : " << cache.miss << endl;
	return 0;
}