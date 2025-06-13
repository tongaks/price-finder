#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// get price from div element
std::string getPriceDiv(bool &isFound, std::string line, std::string t_class) {
	int pos = line.find("<div class=\"" + t_class);

	if (pos != std::string::npos) {
		isFound = true;
		return "";
	}

	if (isFound) {
		int end = line.find("</div>"); 
		if (end != std::string::npos) {
			isFound = false;
			return line.substr(0, end);
		}
	}

	return "";
}

std::string getSubCategory(bool &isFound, int &counter, std::string line, std::string t_parent, std::string t_class, std::string t_child) {
	size_t parent_pos = line.find("<" + t_parent);

	if (parent_pos != std::string::npos) {
		size_t class_pos = line.find("class=\"" + t_class + '"');

		if (class_pos != std::string::npos) {
			isFound = true;
		}

		if (isFound)
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
			size_t non_pos = line.find_first_not_of(" ");
			return line.substr(non_pos, line.length() - non_pos);
		}
	}

	return "";
}

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

std::string getDivChildrens(
	bool &isFound,
	bool isFilter, 
	int &counter,
	std::string line, 
	std::string t_parent,
	std::string t_class,
	std::string t_child) {
	
	size_t parent_pos = line.find("<" + t_parent); 
	if (parent_pos != std::string::npos) {
		size_t class_pos = line.find("class=\"" + t_class + '"');

		if (class_pos != std::string::npos) {
			std::cout << "[!] class found: " << line << '\n';
			isFound = true;
		}

		if (isFound)
			counter += 1;

		return "";
	}

	if (counter > 0 && !isFilter) {
		if (line.find("<span>") != std::string::npos)
			if (line.find("</span>") != std::string::npos)
				return line;
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


std::string replaceSpace(std::string line) {
	std::string copy = "";

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			copy += "%20";
			continue;
		} else copy += line[i];
	}

	return copy;
}