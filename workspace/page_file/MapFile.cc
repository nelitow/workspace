/*
 * MapFile.h
 *
 *  Created on: Oct 29, 2014
 *      Author: arliones
 */
 
#ifndef MAPFILE_H_
#define MAPFILE_H_
 
#include <string>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <iostream>
 
using namespace std;
 
class MapFile {
	MapFile() {}
public:
	MapFile(string filename){
		ifstream file(filename.c_str());
		string line;
		char line_c[256];
		unsigned int page, frame, delimiter;
		while(!file.eof()) {
			file.getline(line_c,256); line = string(line_c);
			delimiter = line.find('-');
			page = atoi(line.substr(0,delimiter+1).c_str());
			frame = atoi(line.substr(delimiter+1).c_str());
			_pt.insert(make_pair(page,frame));
		}
 
	}
 
	virtual ~MapFile() {} 
	// Returns the number of the frame or -1 if not found
	unsigned int get_frame(unsigned int page){
		if ( _pt.find(page) == _pt.end() ) {
			return -1;
		} else {
			return _pt[page];
		}
	}
 
	void print_page_table()	{
		cout << "Page Table:" << endl;
		map<unsigned int, unsigned int>::iterator mit = _pt.begin();
		for(; mit != _pt.end(); ++mit)
			cout << mit->first << " - " << mit->second << endl;
	}
 
private:
	map<unsigned int, unsigned int> _pt;
};
 
#endif /* MAPFILE_H_ */
