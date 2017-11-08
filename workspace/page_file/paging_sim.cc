#include <iostream>
#include <sstream>
#include <math.h>
#include "MapFile.cc"
#include <string>

using namespace std;

int main(int argc, char* argv[]){
	char *pCh;
	unsigned int base = 10;
	unsigned int n = 10;

	unsigned int addr_len = 10;
	unsigned int page_size = 20;
	string arquivo = "eai men";
	unsigned int addr = 12;

	unsigned int q = 10;
	unsigned int p = 10;
	unsigned int frame = 10;
	unsigned int offset = 10;
	unsigned int phys_address = 10;

	addr_len = strtoul (argv[1], &pCh, 10);
	page_size = strtoul (argv[2], &pCh, 10);
	arquivo = argv[3];
	addr = strtoul (argv[4], &pCh, 10);

	q = exp2(addr_len)/page_size;//quadros, feito
	p = addr/page_size;//numero da pagina errado
	
	MapFile page_table(argv[3]);//numero do frame
	frame = page_table.get_frame(p);
	
	//offset
	unsigned int mask = page_size - 1;
	offset = addr & mask;
	
	//end fisico
	base = frame * page_size;
	phys_address = base + offset;

	
	
	cout << "Quadros no sistema: " << q << endl;
	cout << "Pagina requisitada: " << p << endl;
	cout << "Quadro requisitado: " << frame << endl;
	cout << "Deslocamento: " << offset;	
	cout << hex;
	cout << " (0x" << offset << ")" << endl;
	cout << "Endereco logico: 0x" << addr << endl;
	cout << "Endereco fisico: " << phys_address << endl;
}
