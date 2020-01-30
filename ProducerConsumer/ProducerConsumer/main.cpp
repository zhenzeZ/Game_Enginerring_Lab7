#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable> 

using namespace std;
condition_variable m_cv;
mutex m_mutex;
queue<int> m_queue;

void producer(int max) {
	bool end = false;

	while (!end) {
		for (int i = 0; i < max; i++) {
			lock_guard<mutex> lock(m_mutex);
			//m_mutex.lock();
			cout << "burger ready" << endl;

			m_queue.push(i); // push burger to queue

			m_cv.notify_all();

			//this_thread::sleep_for(chrono::seconds(rand() % 2)); // waiting 
			//m_mutex.unlock(); 
		}
		end = true;
		cout << "end of cooking" << endl;
	}
}

void consumer(int max) {
	bool end = false;
	int i = max;

	while (!end) {
		while (i > 0) {
				lock_guard<mutex> lock(m_mutex);

				cout << "burger sold" << endl;

				m_queue.pop(); // sell burger

				//this_thread::sleep_for(chrono::seconds(rand() % 5)); // waiting

				i--;
			
		}
		end = true;
		cout << "end of selling" << endl;
	}
}

int main() {
	//srand((unsigned)time(NULL));
	thread producer(producer,10);
	thread consumer(consumer,10);
	producer.join();
	consumer.join();

	cout << "close" << endl;

	return 1;
}