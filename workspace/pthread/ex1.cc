#include <iostream>
#include "thread.h"
#include "mutex.h"
#include "semaphore.h"

#define NUM_THREADS 5

using namespace std;

Mutex m, mc;
Semaphore s1(1), s2;
volatile int saldo = 1000;

void * AtualizaSaldo(void * arg) {
	int n = *((int*) arg) + 1;

	int meu_saldo, novo_saldo;

	s1.p();
	meu_saldo = saldo;
	novo_saldo = meu_saldo + n * 100;
	saldo = novo_saldo;
	s1.v();
	s2.p();
	cout << "Novo saldo = " << novo_saldo << endl;
	s2.v();
	exit(novo_saldo);
}

int main() {
	Thread * threads[NUM_THREADS];

	for (int t = 0; t < NUM_THREADS; t++)
		threads[t] = new Thread(&AtualizaSaldo, &t, sizeof(int));

	int status;
	for (int t = 0; t < NUM_THREADS; t++) {
		threads[t]->join(&status);
		s2.p();
		cout << "Thread " << t << " terminou com status " << status << "."
				<< endl;
		s2.v();
	}
	cout << "Saldo final é " << saldo << "." << endl;
}
