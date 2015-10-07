#ifndef RWMUTEX_HPP
#define RWMUTEX_HPP

#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

class rwq_spinlock_mutex {
public:
	rwq_spinlock_mutex() {}
	virtual ~rwq_spinlock_mutex() {}
	bool read_access();
	void read_done();
	bool write_lock();
	void write_unlock();
	void quarantine();
	void unquarantine();
private:
	std::atomic_bool	access_semaphore {false},
						write_request_semaphore {false},
						write_semaphore {false},
						quarantine_semaphore {false};
	std::atomic<unsigned int> readnum {0};
};

#endif //RWMUTEX_HPP
