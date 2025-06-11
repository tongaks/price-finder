#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::string getChildren(
	bool &isFound, 
	std::string line, 
	std::string t_parent, 
	std::string t_attr, 
	std::string t_elem, 
	std::string c_attr) {
	
	if (t_parent == "") return "";

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
			if (c_attr != "") {
				if (line.find(c_attr) != std::string::npos) return line;
				else return "";
			} return line;
		}
	}

	return "";
}

std::vector<std::string> getImageSrc(std::string html, std::string p_name) {
	std::vector<std::string> images;

	std::string upper = "";
	for (char c : p_name) upper += std::toupper(c);


	if (html.find("<img src=") != std::string::npos) {

		if (html.find("pgmobile") == std::string::npos) return {};

		for (int i = 0; i < html.length(); i++) {
			std::string temp = "";

			if (html[i] == 's' && html[i+1] == 'r' && html[i+2] == 'c') {
				for (int d = i+4; d < html.length(); d++) {
					if (html[d] != '"') {
						temp += html[d];
					} else if (html[d] == '"' && html[d+1] == ' ') {
						images.push_back(temp);
					}
				}
			}
		}
	} else return {};

	return images;
}

std::string getImageSrcStr(std::string line, std::string t_attr) {
	if (line.find("<img") == std::string::npos) return "";

	if (t_attr != "")
		if (line.find(t_attr) == std::string::npos) return "";

	for (int i = 0; i < line.length(); i++) {
		std::string temp = "";

		if (line[i] == 's' && line[i+1] == 'r' && line[i+2] == 'c') {
			for (int d = i+4; d < line.length(); d++) {
				if (line[d] != '"') {
					temp += line[d];
				} else if (line[d] == '"' && line[d+1] == ' ') {
					return temp;
				}
			}
		}
	}

	return "";
}

// get the img src
std::string getASrc(std::string line, std::string t_attr, std::string t_class) {
	int pos = line.find("href=\"" + t_attr); 

	if (pos != std::string::npos) {
		std::cout << "found in: " << line << '\n';
		std::cout << "pos: " << pos << '\n';
	}

	return "";
}

// get price from a div innerHTML
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





std::string getElem(std::string line, std::string t_elem, std::string t_attr, std::string t_class) {

	if (line.find("<" + t_elem) == std::string::npos) return "";

	if (line.find(t_attr) != std::string::npos) {
		if (t_class != "") {
			if (line.find("class=\""  + t_class + '"') != std::string::npos) {
				std::cout << "found: " << line << '\n';
				return line;
			}
		}

		return line;
	}

	return "";
}

std::string getInnerHTML(std::string line) {
	std::string temp = "";
	bool found = false;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == '>') {
			found = true;
			continue;
		}

		if (found) {
			for (int d = i; d < line.length(); d++) {
				if (line[d] == '<') return temp;
				else temp += line[d];
			}
		}

	}

	return "";
}

std::vector<std::string> getPrices(std::string html) {
	std::vector<std::string> prices;

	if (html.find("<span class=\"price\"") != std::string::npos) {
		std::string temp;

		for (int i = 0; i < html.length(); i++) {
			if (html[i] == '>') {
				std::string temp;

				for (int d = i+1; d < html.length(); d++) {
					if (html[d] != '<') temp += html[d];
					else prices.push_back(temp);
				}

			}
		}
	}

	return prices;
}