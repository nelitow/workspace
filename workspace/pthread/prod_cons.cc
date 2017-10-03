#include <iostream>
#include "thread.h"
#include "semaphore.h"
#include "mutex.h"

using namespace std;

const int N = 1;
const int p = 2;
const int c = 2;

Semaphore s1(N);
Semaphore s2(0);
Mutex mut;

int REP = 5;
char buffer[N];
int pg = 0;

void * producer(void * arg) {
	int n = *((int*) arg);
	int p;
	cout << "Producer was born!\n";

	char data = -1;
	for (int i = 0; i < n; i++) {
		data = (char) i + 0x61;
		s1.p();
		p = pg;
		buffer[pg] = data;
		pg = (pg + 1) % N;
		s2.v();

		mut.lock();
		cout << "Stored... " << data << endl;
		mut.unlock();
	}
	exit(n);
}

void * consumer(void * arg) {
	int c = 0;
	int n = *((int*) arg);

	mut.lock();
	cout << "Consumer was born!\n";
	mut.unlock();

	char data = -1;
	for (int i = 0; i < n; i++) {
		s2.p();
		data = buffer[c];
		s1.v();
		mut.lock();
		cout << "Consumed... " << data << endl;
		mut.unlock();

		c = (c + 1) % N;
	}

	exit(n);
}

int main() {
	cout << "The Producer x Consumer Problem\n";

	Thread prod(&producer, &REP, sizeof(int));
	Thread prod2(&producer, &REP, sizeof(int));
	int rep_tmp = REP * 2;
	Thread cons(&consumer, &REP, sizeof(int));

	int status, status2;
	prod.join(&status);
	prod2.join(&status2);
	if (status == REP && status2 == REP) {
		cout << "Producer went to heaven!\n";
	} else {
		cout << "Producer went to hell!\n";
	}
	cons.join(&status);
	if (status == REP * 2) {
		cout << "Consumer went to heaven!\n";
	} else {
		cout << "Consumer went to hell!\n";
	}
	return 0;
}
