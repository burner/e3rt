#include "Femto.h"

Femto::Femto(std::string *filename) {
	this->filename = filename;

	std::ifstream ifs(filename->c_str());
	if(!ifs) {
		return;
	}
	
	std::cout<<"filename in femto "<<*(this->filename)<<std::endl;	

	std::string line;
	std::stack<Node*> ele;

	this->root = NULL;

	while(getline(ifs, line)) {
		//std::cout<<"femto line "<<line<<std::endl;
		std::string *tmp = new std::string;
		unsigned i = 0;
		while(line[i] == ' ' || line[i] == '\t') i++;
		for(; i < line.size(); i++) {
			tmp->push_back(line.at(i));
		}
		if(tmp->at(1) == '/') {
			ele.pop();
			continue;
		}
		Node *node = makeNode(tmp);
		if(line[i-1] == '>' && this->root == NULL) {
			this->root = node;
			ele.push(node);
			continue;
		}
		if(line[i-1] == '>' && line[i-2] == '/') {
			ele.top()->addChild(node);
			continue;
		} else {
			ele.top()->addChild(node);
			ele.push(node);
		}
	}
	line.clear();
	ifs.close();
}

Femto::~Femto() {
	delete(root);
}

Node* Femto::makeNode(std::string *str) {
	std::string *name = new std::string();
	std::map<std::string, std::string> *attri = new std::map<std::string, std::string>();
	int i = 1;
	for(; str->at(i) != ' ' && str->at(i) != '>'; i++) {
		name->push_back(str->at(i));
	}
	if(str->at(i) == '>') return new Node(name);
	std::string key, value;
	while(str->at(i) != '/' && str->at(i) != '>') {
		key.clear();
	   	value.clear();
		while(str->at(i) != '=') {
			key.push_back(str->at(i));
			i++;
		}
		i+=2;
		while(str->at(i) != '"') {
			value.push_back(str->at(i));
			i++;
		}
		attri->insert(std::pair<std::string, std::string>(key, value));
		i++;
	}
	return new Node(name, attri);
}

Node* Femto::getRoot() {
	return this->root;
}

void Femto::writeXML(std::string filename, Node *toWrite) {
	std::string *tmp = toWrite->toXML(0);
	std::fstream file;
	file.open(filename.c_str());
	file<<*tmp;
	file.close();
}
