#include <fstream>
#include <bits/stdc++.h>
using namespace std;


class SetAssociativeCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* numOfSets = number of sets for cache
	* offSetBits = number of offset bits in address
	* setBits = number of set bits in address
	* tagBits = number of tag bits in address
	* replacementPolicy = represents replacement policy for cache (1 = FIFO, 2 = LRU)
	* tags = data structure to store tag bits
	* valid = data structure to store valid bits
	* data = data structure to store data
	* fifo = instance of FIFO replacement policy
	* lru = instance of LRU replacement policy
	*/
	int cacheSize;
	int blockSize;
	int ways;
	int numOfBlock;
	int numOfSets;
	int offsetBits;
	int setBits;
	int tagBits;
	int replacementPolicy;
	vector<int> tags;
	vector<bool> valid;
	vector<int> data;
	FIFO fifo;
	LRU lru;

	/*
	* @constructor
	* 
	* @param
	* blockSize = represents block size for cache (in word units)
	* cacheSize = represents cache size for cache (in word units)
	* ways = represents number of ways
	* replacement = represents replacement policy for cache (1 = FIFO, 2 = LRU)
	*/
	SetAssociativeCache(int blockSize, int cacheSize, int ways, int replacement) {
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
		this->replacementPolicy = replacement;
		for(int i = 0; i < numOfBlock; i++) {
			valid[i] = false;
		}
		this->data.reserve(numOfBlock);
		if(replacement == 1) {
			this->fifo = FIFO(this->ways, this->numOfSets);
		} else {
			this->lru = LRU(this->ways, this->numOfSets);
		}
	}

	/*
	* @method
	* method to get data from cache given mem address
	* 
	* @param
	* addr = represnets memory address to access data
	*/
	int get(int addr) {
		// fetching offset bits from mem address
		int offSet = addr & (int) pow(2, offsetBits) - 1;
		
		// fetching set bits from mem address
		addr = addr >> offsetBits;
		int set = addr & (int) pow(2, setBits) - 1;
		
		// fetching tag bits from mem address
		int tag = addr >> setBits;
		
		// fetching index from replacement policy instance
		int index = replacementPolicy == 1 ? fifo.getIndex(tag, set, this->ways, tags, valid) : lru.getIndex(tag, set, this->ways, tags, valid);
		return data[index];
	}

	/*
	* @method
	* method to print valid, tag and data tables
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