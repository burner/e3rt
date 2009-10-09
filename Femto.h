#include <string>
#include <stack>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "Node.h"

#ifndef FEMTO
#define FEMTO
class Femto {
	private:
		Node *root;
		std::string *filename;
		std::map<std::string, std::vector<Node> > *childs;
		Node* makeNode(std::string *str);
	public:
		Femto(std::string *filename);
		~Femto();
		Node* getRoot();
		void writeXML(std::string filename, Node *toWrite);
};
#endif
