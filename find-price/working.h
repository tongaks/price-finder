#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::string getProductName(bool &isFound, std::string line, std::string t_attr) {
	int pos = line.find("<a ");

	if (pos != std::string::npos) {

		if (t_attr != "") {
			if (line.find(t_attr) != std::string::npos) {
				isFound = true;
				return "";
			}
		}

		isFound = true;
		return "";
	}

	if (isFound) {
		int end = line.find("</a>"); 

		if (end != std::string::npos) {
			isFound = false;

			size_t non_space1 = line.find_first_not_of(" ");
			if (non_space1 != std::string::npos) {
				return line.substr(non_space1, end - non_space1);
			}
		}
	}

	return "";
}

std::string getCategoryItems(bool &isFound, int &counter, std::string line, std::string t_parent, std::string t_class, std::string t_child) {
	if (line.find("<" + t_parent) != std::string::npos) {
		if (line.find("class=\"" + t_class + '"') != std::string::npos){
			std::cout << "class found: " << line << '\n';
			isFound = true;
		}

		counter += 1;
		return "";
	}

	if (line.find("</" + t_parent + ">") != std::string::npos) {
		if (counter > 0) {
			counter -= 1;
			return "";
		}

		isFound = false;
		return "";
	}

	if (isFound) {
		if (line.find("<" + t_child) != std::string::npos) {
			size_t start = line.find_first_not_of(" ");
			return line.substr(start, line.length() - start);
		}
	}

	return "";
}