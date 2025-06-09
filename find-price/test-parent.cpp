#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::string getChildren(bool &isFound, std::string line, std::string t_parent, std::string t_attr, std::string t_elem) {
	if (t_parent == "" || t_attr == "") return "";

	if (line.find("<" + t_parent) != std::string::npos) {
		if (line.find(t_attr) != std::string::npos) {
			isFound = true;
			return "";
		}
	}

	if (line.find("</" + t_parent) != std::string::npos) {
		isFound = false;
		return "";
	}

	if (isFound) {
		if (t_elem == "") return line;
		if (line.find(t_elem) != std::string::npos) {
			return line;
		}
	}

	return "";
}

int main(int argc, char const *argv[]) {
	std::string t_parent = "";
	std::string t_class = "";
	std::string t_elem = "";
	std::string line = "";
	std::ifstream file;

	if (argc > 0) {
		file = std::ifstream(argv[1]);
		t_parent = argv[2];
		t_class = argv[3];
		t_elem = argv[4];
	} else {
		std::cerr << "Too few arguments" << '\n';
		return -1;
	}

	std::vector<std::string> vec;
	bool found = false;

	while (std::getline(file, line)) {
		std::string temp = getChildren(found, line, t_parent, t_class, t_elem);
		if (!(temp == "")) vec.push_back(temp);
	}

	if (vec.empty()) {
		std::cerr << "No elements found" << '\n';
		return -1;
	}

	for (std::string s : vec) {
		std::cout << s << '\n';
	}

	// std::cout << s << '\n';
	// std::cout << s << '\n';
	// for (std::string s : childrens) {
	// 	std::cout << s << '\n';
	// }

	return 0;
}