#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class Cache {
public:
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int indexBits;
	int tagBits;
	vector<uint> tags;
	vector<bool> valid;
	vector<int> data; 

	int hit;
	int miss;
	Cache(int blockSize, int cacheSize) {
		this->cacheSize = cacheSize;
		this->blockSize = blockSize;
		this->numOfBlock = cacheSize / blockSize;
		this->offsetBits = (int) log2(blockSize * 4);
		this->indexBits =  (int) log2(numOfBlock);
		this->tagBits = 16 - indexBits - offsetBits;
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		for(int i = 0; i < numOfBlock; i++) {
			valid[i] = false;
		}
		this->hit = 0;
		this->miss = 0;

		// cout << "number of blocks :" << numOfBlock << endl;
	}

	int get(int addr) {
		int offSet = addr & (int) pow(2, offsetBits - 1);
		// cout << "offSet bits : " << offSet << endl;
		addr = addr >> offsetBits;
		int index = addr % numOfBlock;
		// cout << "index : " << index << endl;
		int tag = addr >> indexBits;
		// cout << "tag : " << tag << endl;
		if(valid[index] == true && tags[index] == tag) {
			// cout << "hit" << endl;
			this->hit++;
		} else {
			// cout << "miss" << endl;
			this->miss++;
			valid[index] = true;
			tags[index] = tag;
			// geting data from memory
			data[index] = 0; // dummy data
		}
		int res = data[index];
		if(offSet == 0) {
			res = res & 0b11111111;
		} else {
			res = res & 0b1111111100000000;
		}
		return res;
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
	cout << "hits : " << cache.hit << endl;
	cout << "miss : " << cache.miss << endl;
	return 0;
}