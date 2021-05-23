#include <list>
using namespace std;

class LRU {

private:

	/*
	* @param
	* size = size of the queue
	* accessList = vector of lists, (for fully associative cache vector size = 1 otherwise vector size = number of sets)
	* lastEntry = represents last index where data was inserted (only used for fully associative cache)
	* hit = represents number of hits in cache
	* miss = represents number of miss in cache
	*/
	int size;
	vector<list<int>> accessList;
	int lastEntry;
public:
	int hit;
	int miss;


	/*
	* @constructor
	* @param
	* size = represents size of list
	* sets = represents number of sets in cache (1 = fully associative cache, otherwise set associvative)
	*/
	LRU(){}

	LRU(int size, int sets) {
		this->size = size;
		this->lastEntry = -1;
		this->hit = 0;
		this->miss = 0;
		for(int i = 0; i < sets; i++) {
			list<int> temp_l;
			accessList.push_back(temp_l);
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
				accessList[0].remove(i);
				accessList[0].push_back(i);
				return i;
			}
		}
		
		// cache miss scenario
		miss++;
		// case - when list size is less than maximum size
		if(accessList[0].size() < size) {
			lastEntry++;
			accessList[0].push_back(lastEntry);
			data[lastEntry] = tag;
			return lastEntry;
		} else {
			// case - when list is already full and we have to remove one entry from cache which is least recently used
			int index = accessList[0].front();
			accessList[0].pop_front();
			accessList[0].push_back(index);
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
				accessList[set].remove(i - base);
				accessList[set].push_back(i - base);
				return i;
			}
		}

		// cache miss scenario
		miss++;
		// case - when list size less than max size
		if(accessList[set].size() < size) {
			int i = accessList[set].size();
			accessList[set].push_back(i);
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		} else {
		// case - when list is already full and we have to remove one entry from cache which is least recently used
			int i = accessList[set].front();
			accessList[set].pop_front();
			accessList[set].push_back(i);
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		}
	}
};