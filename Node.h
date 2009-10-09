#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#ifndef NODE
#define NODE
class Node {
	private:
		std::string *name;
		std::map<std::string, std::vector<Node*> > *childNodes;
		std::map<std::string, std::string> *attri;

	public:
		Node(std::string *name);
		Node(std::string *name, std::map<std::string, std::string> *attri);
		~Node();
		void writeToXMLFile(std::string fileName);
		void addChild(Node *child);
		std::string* toXML(int indent);
		std::string* getName();
		std::vector<Node*> getChilds(std::string childName);
		std::string getAttri(std::string name);
		bool hasAttri(std::string name);
};
#endif
