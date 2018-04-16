#include<mutex>
#include<vector>
#include<thread>
#include<vector>
#include<condition_variable>
#include"SQueue.h"
using namespace std;
extern void run(int connfd);
class ThreadPool
{
	public:
	bool shutdown;
	SQueue queue;
	vector<thread> threads;
	mutex condition_mutex;
	condition_variable wait_condition;
	class ThreadWorker 
	{
		public: int id;
		ThreadPool *pool;
		ThreadWorker(ThreadPool *pool1,const int id1):pool(pool1),id(id1){}
		void operator()() {
			while(!(pool->shutdown)){
				unique_lock<mutex> lock(pool->condition_mutex);
				pool->wait_condition.wait(lock,[this]{return !(this->pool->queue.empty());});
				int connfd=pool->queue.pop();
				lock.unlock();
				if(connfd!=-1)
				{
					run(connfd);
					close(connfd);
				}
			}
		}
	};
	ThreadPool(const int count):threads(vector<thread>(count)),shutdown(false){
		for(int i=0;i<count;i++){
			threads[i]=thread(ThreadWorker(this,i));
		}
	}
	void completed(){
		shutdown=true;
		wait_condition.notify_all();
		for(int i=0;i<threads.size();i++)
			if(threads[i].joinable())
				threads[i].join();
	}
	void submit(int i)
	{
		queue.push(i);
		wait_condition.notify_one();
	}
};