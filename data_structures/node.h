#ifndef __NODE_H_

#define __NODE_H_

#include <string>
using namespace std;

enum NodeType {_text, a, b, p};

class Node {
	NodeType type;
public:
	virtual string toXML() const = 0 ;
	virtual string getName() = 0;
	
};

#endif

