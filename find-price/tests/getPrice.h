#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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



// get product name
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




// get element with specified attributes
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