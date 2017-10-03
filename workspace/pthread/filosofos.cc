#include <iostream>
#include "thread.h"
#include "semaphore.h"

using namespace std;

const int DELAY = 100000;
const int ITERATIONS = 5000;

Semaphore chopstick[5];

void * philosopher(void * arg) {
	int n = *((int*) arg);

	cout << "Philosopher " << n << " was born!\n";

	int first = n;
	int second = n + 1;

	if (n == 4) {
		second = n;
		first = 0;
	}

	for (int i = 0; i < ITERATIONS; i++) {
		cout << "Philosopher " << n << " thinking ...\n";
		for (int i = 0; i < DELAY * 10; i++)
			;

		chopstick[first].p();
		chopstick[second].p();

		cout << "Philosopher " << n << " eating ...\n";
		for (int i = 0; i < DELAY; i++)
			;

		chopstick[second].v();
		chopstick[first].v();
	}

	exit(n);
}

int main() {
	cout << "The Dining-Philosophers Problem\n";

	Thread * phil[5];
	for (int i = 0; i < 5; i++)
		phil[i] = new Thread(&philosopher, &i, sizeof(int));

	int status;
	for (int i = 0; i < 5; i++) {
		phil[i]->join(&status);
		if (status == i)
			cout << "Philosopher " << i << " went to heaven!\n";
		else
			cout << "Philosopher " << i << " went to hell!\n";
	}

	return 0;
}
