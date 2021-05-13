#include <stack>

using namespace std;

class FIFO {
	int size;
	stack<int> st;
	int lastEntry;
public:
	FIFO(){}
	FIFO(int size) {
		this->size = size;
		this->lastEntry = -1;
	}

	int getIndex() {
		if(st.size() < size) {
			lastEntry++;
			st.push(lastEntry);
			return lastEntry;
		} else {
			int index = st.top();
			st.pop();
			st.push(index);
			return index;
		}
	}
};