#include "element.h"
#include <sstream>

Element::Element(ElementName* en, attributesMap* attrs, nodeList* children/* = NULL */) {
	if(NULL == children) {
		children = new nodeList();
	}
	this->children = children;
	this->attributes = attrs;
	this->name = en->first;
}

Element& Element::setParent(Element* e) {
	this->parent = e;
}

Element* Element::getParent() {
	return this->parent;
}

string Element::toXML() {
	stringstream str;
	str << "<" << this->name << ">" << endl;// open the XML tag
	//@todo attributes
	for(nodeList::iterator it = this->children->begin(); it != this->children->end(); ++it) {
		str << (*it)->toXML();
	}
	str << endl << "</" << this->name << ">" << endl;// close the XML tag
	return str.str();
}
