#include "rwmutex.hpp"

static bool expect_false = false;

bool rwqmutex::read_access() {
	if (quarantine_semaphore) return false;
	while (write_request_semaphore) {
		std::this_thread::sleep_for(wait_time);
	}
	while (!access_semaphore.compare_exchange_weak(expect_false, true)) {
		std::this_thread::sleep_for(wait_time);
	}
	if (quarantine_semaphore) {
		access_semaphore.store(false);
		return false;
	}
	readnum++;
	access_semaphore.store(false);
	return true;
}

void rwqmutex::read_done() {
	readnum--;
}

bool rwqmutex::write_lock() {
	if (quarantine_semaphore) return false;
	while (!write_request_semaphore.compare_exchange_weak(expect_false, true)) {
		std::this_thread::sleep_for(wait_time);
	}
	while (!access_semaphore.compare_exchange_weak(expect_false, true)) {
		std::this_thread::sleep_for(wait_time);
	}
	write_request_semaphore.store(false);
	if (quarantine_semaphore) {
		access_semaphore.store(false);
		return false;
	}
	while (readnum > 0) {
		std::this_thread::sleep_for(wait_time);
	}
	return true;
}

void rwqmutex::write_unlock() {
	access_semaphore.store(false);
}

void rwqmutex::quarantine_lock() {
	if (quarantine_semaphore) return;
	while (!write_request_semaphore.compare_exchange_weak(expect_false, true)) {
		std::this_thread::sleep_for(wait_time);
	}
	while (!access_semaphore.compare_exchange_weak(expect_false, true)) {
		std::this_thread::sleep_for(wait_time);
	}
	write_request_semaphore.store(false);
	while (readnum > 0) {
		std::this_thread::sleep_for(wait_time);
	}
	quarantine_semaphore.store(true);
	access_semaphore.store(false);
}

void rwqmutex::quarantine_unlock() {
	quarantine_semaphore.store(false);
}
