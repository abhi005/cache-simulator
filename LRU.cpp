#include <list>
using namespace std;

class LRU {

private:
	int size;
	vector<list<int>> accessList;
	int lastEntry;
public:
	int hit;
	int miss;
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

	int getIndex(int tag, vector<int> &data) {
		for(int i = 0; i <= data.size(); i++) {
			if(data[i] == tag) {
				hit++;
				accessList[0].remove(i);
				accessList[0].push_back(i);
				return i;
			}
		}
		
		miss++;
		if(accessList[0].size() < size) {
			lastEntry++;
			accessList[0].push_back(lastEntry);
			data[lastEntry] = tag;
			return lastEntry;
		} else {
			int index = accessList[0].front();
			accessList[0].pop_front();
			accessList[0].push_back(index);
			data[index] = tag;
			return index;
		}
	}

	int getIndex(int tag, int set, int ways, vector<int> &data, vector<bool> &valid) {
		int base = set * ways;
		for(int i = base; i < base + ways; i++) {
			if(data[i] == tag && valid[i]) {
				// cout << "matched for i : " << i << endl;
				// cout << "data[i] : " << data[i] << endl;
				// cout << "tag : " << tag << endl;
				// cout << "hit" << endl;
				hit++;
				accessList[set].remove(i - base);
				accessList[set].push_back(i - base);
				return i;
			}
		}

		miss++;
		if(accessList[set].size() < size) {
			int i = accessList[set].size();
			accessList[set].push_back(i);
			// cout << "assingning at " << base + i << " " << tag << endl;
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		} else {
			int i = accessList[set].front();
			// cout << "removing : " << i << endl;
			accessList[set].pop_front();
			accessList[set].push_back(i);
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		}
	}
};