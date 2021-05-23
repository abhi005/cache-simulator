#include <bits/stdc++.h>

using namespace std;

class DirectMapCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* offSetBits = number of offset bits in address
	* indexBits = number of index bits in address
	* tagBits = number of tag bits in address
	* tags = data structure to store tag bits
	* valid = data structure to store valid bits
	* data = data structure to store data
	* hit = represents number of hits
	* miss = represents number of miss
	*/
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

	/*
	* @construnctor
	* @param
	* blockSize = represents number of blocksize for cache (in word units)
	* cacheSize = represnts number of cache size for cache (in word units)
	*/
	DirectMapCache(int blockSize, int cacheSize) {
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
	}


	/*
	* @method
	* method to get data from cache
	*
	* @param
	* addr = represents memory address
	*/
	int get(int addr) {
		// fetching offset bits from mem address
		int offSet = addr & (int) pow(2, offsetBits - 1);

		// fetching index bits from mem address
		addr = addr >> offsetBits;
		int index = addr % numOfBlock;

		// fetching tag bits from mem address
		int tag = addr >> indexBits;

		// case : tag is present at index - hit
		if(valid[index] == true && tags[index] == tag) {
			this->hit++;
		} else {
		// case : tag is not present at index - miss
			this->miss++;
			valid[index] = true;
			tags[index] = tag;
			data[index] = rand();
		}

		// fetching required offset byte from word
		int res = data[index];
		if(offSet == 0) {
			res = res & 0b11111111;
		} else {
			res = res & 0b1111111100000000;
		}
		return res;
	}

	/*
	* @method
	* method to display valid, tag and data table
	*/
	void display() {
		cout << "VALID tabel" << endl;

		for(int i = 0; i < numOfBlock; i++) {
			cout << i << " : " << (valid[i] ? "1" : "0") << endl;
		}
		
		cout << "TAG tabel" << endl;

		stringstream ss;
		for(int i = 0; i < numOfBlock; i++) {
			ss.str("");
			ss << hex << tags[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}

		cout << "DATA tabel" << endl;

		for(int i = 0; i < numOfBlock; i++) {
			ss.str("");
			ss << hex << data[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}
	}
};