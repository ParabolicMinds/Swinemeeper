#ifndef RWMUTEX_HPP
#define RWMUTEX_HPP

#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

class rwqmutex {
public:
	rwqmutex(std::chrono::nanoseconds wait_time = std::chrono::nanoseconds{1000}) : wait_time(wait_time) {}
	virtual ~rwqmutex() {}
	bool read_access();
	void read_done();
	bool write_lock();
	void write_unlock();
	void quarantine_lock();
	void quarantine_unlock();
private:
	std::chrono::nanoseconds wait_time;
	std::atomic_bool	access_semaphore {false},
						write_request_semaphore {false},
						quarantine_semaphore {false};
	std::atomic<unsigned int> readnum {0};
};

#endif //RWMUTEX_HPP
