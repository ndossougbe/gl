#ifndef __DTD_H_
#define __DTD_H_

#include <map>
#include <iostream>

#include "dtd_elt.h"
#include "dtd_attr.h"

using namespace std;

class DtdEltMap {
	map<string, DtdElt*>* elt_map;
public:
	DtdEltMap(): elt_map(new map<string, DtdElt*>()) {}

	~DtdEltMap();

	DtdElt * getElement(string eltName) { return (*elt_map)[eltName]; }
	map<string, DtdElt*>* getElements() { return elt_map; }
	void add_elt(DtdElt* element);
	void add_attrs(string element, list<DtdAttr*> * attList) ;
	string toString();
};

class Dtd {
	DtdEltMap* elements;
public:
	Dtd(DtdEltMap* lst_elements): elements(lst_elements) {}

	~Dtd() {/*delete elements;*/}
	string toString();
	bool isValid();
	DtdEltMap* getElementMap () {return elements ;}
};

#endif
