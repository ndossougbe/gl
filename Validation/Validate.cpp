#include "Validate.h"

Validate::Validate(Document *xmlFile, Dtd * dtdFile) {
	xml = xmlFile;
	dtd = dtdFile;
}

bool Validate::isElementValid(Element* elt) {
	string eltName = elt->getName();
	attributesMap* attrXml = elt->getAttributes();
	DtdEltMap* elements = dtd->getElementMap();
	list<DtdAttr*> * attrDtd = elements->getAttributes(eltName);
	bool foundAttr = false;

// Check attributes
	for(attributesMap::iterator itXml = attrXml->begin(); itXml != attrXml->end(); itXml++) {
		  string attrNameXml = itXml->first;
		  foundAttr = false;
		  for (list<DtdAttr*>::iterator itDtd = attrDtd->begin(); itDtd != attrDtd->end(); itDtd++) {
		  	string attrNameDtd = (*itDtd)->toString();
		  	if(attrNameXml == attrNameDtd ) {
		  		foundAttr = true;
		  	}
		  }
		  if(!foundAttr) {
		  	return false;
  }

}

// Check children
string childrenstring = elt->getSpaceSeparatedChildrenList();
DtdElt * dtdElt = elements->getElement(eltName);
string dtdEltRegex = dtdElt->getChildren()->toString();
EltType eltContentType = dtdElt->getChildren()->getType();

if( eltContentType == T_EMPTY) {
	if(childrenstring.length() > 0) {
		return false;
	}
}
else if (eltContentType == LIST || eltContentType == TOKEN) {
	//Match regex
	//string regex = createRegex(dtdElt);
	//TODO
}

// Get children of the current xml element
nodeList* children = elt->getChildren();
// Validate children element nodes
for(nodeList::iterator itNode = children->begin(); itNode != children->end(); itNode++) {
	if((*itNode)->getName() != "#PCDATA") {
		isElementValid((Element*)*itNode);
	}
}

}

bool Validate::isValid() {
	isElementValid(xml->getRoot());
}

