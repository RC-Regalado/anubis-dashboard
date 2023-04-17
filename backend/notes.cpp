#include <iostream>
#include <fstream>
#include "notes.hpp"

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

notes::notes(string name){
  this->name = name;
}

void notes::save(const string& value) {

  ofstream archivo(name);
  archivo << value << endl;
  archivo.close();
}

