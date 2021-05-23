#include <bits/stdc++.h>
using namespace std;

class FullyAssociativeCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* offSetBits = number of offset bits in address
	* tagBits = number of tag bits in address
	* replacementPolicy = represents replacement policy for cache (1 = FIFO, 2 = LRU)
	* tags = data structure to store tag bits
	* data = data structure to store data
	* fifo = instance of FIFO replacement policy
	* lru = instance of LRU replacement policy
	*/
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int tagBits;
	int replacementPolicy;
	vector<int> tags;
	vector<int> data;
	FIFO fifo;
	LRU lru;

	/*
	* @constructor
	* @param
	* blockSize = represents block size for cache (in word units)
	* cacheSize = represents cache size for cache (in word units)
	* replacement = represnt replacement policy for cache (1 = FIFO, 2 = LRU)
	*/
	FullyAssociativeCache(int blockSize, int cacheSize, int replacement) {
		this->cacheSize = cacheSize;
		this->blockSize = blockSize;
		this->numOfBlock = cacheSize / blockSize;
		this->offsetBits = (int) log2(blockSize * 4);
		this->tagBits = 16 - offsetBits;
		this->tags.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		this->replacementPolicy = replacement;
		if(replacement == 1) {
			this->fifo = FIFO(this->numOfBlock, 1);
		} else {
			this->lru = LRU(this->numOfBlock, 1);
		}
	}


	/*
	* @method
	* method to get data from cache given address
	*
	* @param
	* addr = represent memory address
	*/
	int get(int addr) {
		// fetching offset bits fro mmem address
		int offSet = addr & (int) pow(2, offsetBits) - 1;
		
		// fetching tag bits from mem address
		int tag = addr >> offsetBits;
		
		// fetchinf index from replacement policy instance
		int index = replacementPolicy == 1 ? fifo.getIndex(tag, tags) : lru.getIndex(tag, tags);
		
		return data[index];
	}

	/*
	* @method
	* method to display tag, valid and data tables
	*/
	void display() {
		
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