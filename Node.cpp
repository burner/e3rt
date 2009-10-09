#include "Node.h"

Node::Node(std::string *name) {
	this->name = name;
	this->childNodes = new std::map<std::string, std::vector<Node*> >();
	this->attri = NULL;
}

Node::Node(std::string *name, std::map<std::string, std::string> *attri) {
	this->name = name;
	this->attri = attri;
	this->childNodes = new std::map<std::string, std::vector<Node*> >();
}

Node::~Node() {
	if(attri != NULL) {
		delete(attri);
	}
	std::map<std::string, std::vector<Node*> >::iterator it;
	if(this->childNodes != NULL && this->childNodes->size() > 0) {
		for(it = this->childNodes->begin(); it != this->childNodes->end(); it++) {
			std::vector<Node*> tmp = (*this->childNodes)[it->first];
			for(unsigned i = 0; i < tmp.size(); i++) {
				delete(tmp[i]);
			}
			this->childNodes->erase(it->first);
		}
	}
	delete(childNodes);
}

void Node::addChild(Node *child) {
	(*this->childNodes)[*child->getName()].push_back(child);
}

std::string Node::getAttri(std::string name) {
	return (*this->attri)[name];
}

bool Node::hasAttri(std::string name) {
	if( this->attri->find(name) != this->attri->end()) {
		return true;
	}
	return false;
}

std::vector<Node*> Node::getChilds(std::string name) {
	return (*this->childNodes)[name];
}

std::string* Node::toXML(int indent) {
	std::string *ret = new std::string();
	for(int i = 0; i < indent; i++) {
		ret->append("\t");
	}
	ret->append("<");
	ret->append(*(this->name));
	
	std::map<std::string, std::string>::iterator it;
	if(this->attri != NULL && this->attri->size() > 0) {
		for(it = this->attri->begin(); it != this->attri->end(); it++) {
			ret->append(it->first + "=" + "\"" + it->second + "\"");
		}
	}

	if(childNodes->size() == 0) {
		ret->append("/>\n");
		return ret;
	}

	ret->append(">\n");

	std::map<std::string, std::vector<Node*> >::iterator jt;
	for(jt = childNodes->begin(); jt != childNodes->end(); jt++) {
		for(unsigned i = 0; i < jt->second.size(); i++) {
			ret->append( *((jt->second[i])->toXML(indent+1)));	
		}
	}
	for(int i = 0; i < indent; i++) {
		ret->append("\t");
	}
	ret->append("</" + *this->name + ">\n");

	return ret;
}

std::string* Node::getName() {
	return this->name;
}

void Node::writeToXMLFile(std::string fileName) {
	std::ofstream out;
	out.open(fileName.c_str());
	out<<*toXML(0);
	out.close();
} 
