#include <queue>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

class FIFO {

	/*
	* @param
	* size = size of the queue
	* q = vector of queues, (for fully associative cache vector size = 1 otherwise vector size = number of sets)
	* lastEntry = represents last index where data was inserted (only used for fully associative cache)
	* hit = represents number of hits in cache
	* miss = represents number of miss in cache
	*/
	int size;
	vector<queue<int>> q;
	int lastEntry;
public:
	int hit;
	int miss;

	/*
	* @constructor
	* @method
	* size = represents size of queue
	* sets = represents number of sets in cache (1 = fully associative cache, otherwise set associvative)
	*/
	FIFO(){}
	FIFO(int size, int sets) {
		this->size = size;
		this->lastEntry = -1;
		this->hit = 0;
		this->miss = 0;
		for(int i = 0; i < sets; i++) {
			queue<int> temp_q;
			q.push_back(temp_q);
		}
	}

	/*
	* @method
	* method to get the index of data array based on tag and handeling of miss and hit scenarios for fully associative cache
	*
	* @param
	* tag = represents tag bits from mem address
	* data = represents tag table
	*/
	int getIndex(int tag, vector<int> &data) {

		// verifying if tag is already present - cache hit scenario
		for(int i = 0; i <= data.size(); i++) {
			if(data[i] == tag) {
				hit++;
				return i;
			}
		}
		
		// cache miss scenario
		miss++;
		// case - when queue size is less than maximum size
		if(q[0].size() < size) {
			lastEntry++;
			q[0].push(lastEntry);
			data[lastEntry] = tag;
			return lastEntry;
		} else {
		// case - when queue is already full and we have to remove one entry from cache in FIFO manner
			int index = q[0].front();
			q[0].pop();
			q[0].push(index);
			data[index] = tag;
			return index;
		}
	}

	/*
	* @method
	* method to get the index of data array based on tag and handeling of miss and hit scenarios for set associative cache
	*
	* @param
	* tag = represents tag bits from address
	* set = represents set bits from address
	* ways = represents number of ways for cache
	* data = represents tag table
	* valid = represents valid bit table
	*/
	int getIndex(int tag, int set, int ways, vector<int> &data, vector<bool> &valid) {
		int base = set * ways;

		// checking if tag is already present in cache - cache hit scenario
		for(int i = base; i < base + ways; i++) {
			if(data[i] == tag && valid[i]) {
				hit++;
				return i;
			}
		}

		// cache miss scenario
		miss++;
		// case - when queue size less than max size
		if(q[set].size() < size) {
			int i = q[set].size();
			q[set].push(i);
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		} else {
		// case - when queue is already full and we have to remove one entry from cache in FIFO manner
			int i = q[set].front();
			q[set].pop();
			q[set].push(i);
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		}
	}
};