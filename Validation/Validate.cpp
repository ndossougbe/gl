#include "Validate.h"

Validate::Validate(Document *xmlFile, Dtd * dtdFile) {
	xml = xmlFile;
	dtd = dtdFile;
}

bool Validate::isElementValid(Element* elt) {
	string eltName = elt->getName();
	attributesMap* attrXml = elt->getAttributes();
	DtdEltMap* elements = dtd->getElementMap();
	DtdElt * dtdElt = elements->getElement(eltName);
	list<DtdAttr*> * attrDtd = dtdElt->getAttributes();

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
string dtdEltRegex = "";
if(dtdElt->getChildren() != NULL) {
	dtdEltRegex = dtdElt->getChildren()->toString();


EltType eltContentType = dtdElt->getChildren()->getType();

if( eltContentType == T_EMPTY) {
	if(childrenstring.length() > 0) {
		return false;
	}
}
else if (eltContentType == LIST || eltContentType == TOKEN) {
	//Match regex

  boost::regex ex(dtdEltRegex);
  if (!boost::regex_match(childrenstring, ex))
  {
    cout << "\nProblème :\n \t(" << childrenstring << ")\n \tne correspond pas à ce qui a été déclaré dans la dtd :\n \t"<< ex <<endl <<endl;
    return false;
  }
}

// Get children of the current xml element
nodeList* children = elt->getChildren();
// Validate children element nodes
for(nodeList::iterator itNode = children->begin(); itNode != children->end(); itNode++) {
	if((*itNode)->getName() != "#PCDATA") {
		if(isElementValid((Element*)*itNode) == false) {
			return false;
		}
	}
}

}
else {
	if(!elt->getChildren()->empty()) {
		return false;
	}
}
	return true;
}

bool Validate::isValid() {
	return isElementValid(xml->getRoot());
}

