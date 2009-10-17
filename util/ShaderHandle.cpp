#include "ShaderHandle.h"

char* readShader(std::string filename) {
	std::string ret;
	std::string line;
	std::ifstream file(filename.c_str());
	while(getline(file, line)) {
		ret.append(line);
		ret.append("\n");
	}
	char *retChar = new char[ret.size()+1];
	strcpy(retChar, ret.c_str());
	return retChar;
}
