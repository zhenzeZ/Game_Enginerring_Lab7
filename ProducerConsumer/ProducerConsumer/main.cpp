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
			cout << "burger ready" << endl;

			m_queue.push(i); // push burger to queue

			m_cv.notify_all();

			this_thread::sleep_for(chrono::seconds(2)); // waiting 
		}
		end = true;
	}
}

void consumer(int max) {
	bool end = false;
	int i = max;

	while (!end) {
		while (i <= 0) {
			if (!m_queue.empty()) {
				cout << "people are hungry" << endl;
			}
			else {

				std::lock_guard<std::mutex> lock(mutex);

				cout << "burger sold" << endl;

				m_queue.pop(); // sell burger

				i--;
			}
		}
		end = true;
	}
}

int main() {

	thread producer(producer,20);
	thread consumer(consumer,20);
	producer.join();
	consumer.join();
	cin.get();
	return 1;
}