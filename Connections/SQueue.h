#include<mutex>
#include<queue>
using namespace std;
class SQueue // Thread Safe Queue
{
	public:
	queue<int> m_queue;
	mutex m_mutex;
	bool empty()
	{
		unique_lock<mutex> lock(m_mutex);
		return m_queue.empty();
	}
	int size()
	{
		unique_lock<mutex> lock(m_mutex);
		return m_queue.size();
	}
	void push(int n)
	{
		unique_lock<mutex> lock(m_mutex);
		m_queue.push(n);
	}
	int pop()
	{
		unique_lock<mutex> lock(m_mutex);
		if(m_queue.empty())
		{
			return -1;
		}
		int n=m_queue.front();
		m_queue.pop();
		return n;
	}
};