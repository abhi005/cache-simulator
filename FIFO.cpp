#include <queue>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

class FIFO {
	int size;
	vector<queue<int>> q;
	int lastEntry;
public:
	int hit;
	int miss;
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

	int getIndex(int tag, vector<int> &data) {
		for(int i = 0; i <= data.size(); i++) {
			if(data[i] == tag) {
				hit++;
				return i;
			}
		}
		
		miss++;
		if(q[0].size() < size) {
			lastEntry++;
			q[0].push(lastEntry);
			data[lastEntry] = tag;
			return lastEntry;
		} else {
			int index = q[0].front();
			q[0].pop();
			q[0].push(index);
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
				return i;
			}
		}

		// cout << "miss" << endl;
		miss++;
		// cout << "queue for set " << set << " : " << q[set].size() << endl;
		if(q[set].size() < size) {
			int i = q[set].size();
			q[set].push(i);
			// cout << "assingning at " << base + i << " " << tag << endl;
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		} else {
			int i = q[set].front();
			// cout << "removing : " << i << endl;
			q[set].pop();
			q[set].push(i);
			data[base + i] = tag;
			valid[base + i] = true;
			return base + i;
		}
	}
};