#include "rwmutex.hpp"

static thread_local bool test;

bool rwq_spinlock_mutex::read_access() {
	if (quarantine_semaphore) return false;
	while (write_request_semaphore);
	do { test = false; } while (!access_semaphore.compare_exchange_weak(test, true));
	if (quarantine_semaphore) {
		access_semaphore.store(false);
		return false;
	}
	while (write_semaphore);
	readnum.fetch_add(1);
	access_semaphore.store(false);
	return true;
}

void rwq_spinlock_mutex::read_done() {
	readnum.fetch_sub(1);
}

bool rwq_spinlock_mutex::write_lock() {
	if (quarantine_semaphore) return false;
	do { test = false; } while (!write_request_semaphore.compare_exchange_weak(test, true));
	do { test = false; } while (!access_semaphore.compare_exchange_weak(test, true));
	write_request_semaphore.store(false);
	if (quarantine_semaphore) {
		access_semaphore.store(false);
		return false;
	}
	while (readnum);
	do { test = false; } while (!write_semaphore.compare_exchange_weak(test, true));
	access_semaphore.store(false);
	return true;
}

void rwq_spinlock_mutex::write_unlock() {
	write_semaphore.store(false);
}

void rwq_spinlock_mutex::quarantine() {
	if (quarantine_semaphore) return;
	do { test = false; } while (!write_request_semaphore.compare_exchange_weak(test, true));
	do { test = false; } while (!access_semaphore.compare_exchange_weak(test, true));
	write_request_semaphore.store(false);
	while (readnum);
	do { test = false; } while (!write_semaphore.compare_exchange_weak(test, true));
	quarantine_semaphore.store(true);
	write_semaphore.store(false);
	access_semaphore.store(false);
}

void rwq_spinlock_mutex::unquarantine() {
	quarantine_semaphore.store(false);
}
