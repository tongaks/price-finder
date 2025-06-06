#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// this code parses the html
// and look for <span> elements


// std::vector<std::string> getPrices(std::string html) {
// 	std::vector<std::string> prices;

// 	for (int i = 0; i < html.length(); i++) {

// 		if (html[i] == '<') {
// 			std::string temp;

// 			for (int d = i; d < html.length(); d++) {
// 				if (html[d] == '<' && html[d+1] == '/') {
// 					// temp += html[d];

// 					if (temp.find("span") != std::string::npos) {
// 						if (temp.find("class=\"price\"") != std::string::npos) {
// 							int pos = -1;

// 							for (int g = 0; g < temp.length(); g++) {
// 								if (temp[g] == '>') {
// 									pos = g;
// 								}
// 							}

// 							temp = temp.substr(pos+1, temp.length());
// 							prices.push_back(temp);
// 						}

// 					}

// 					break;
// 				} else {
// 					temp += html[d];
// 				}

// 			}
// 		}
// 	}

// 	return prices;
// }

std::vector<std::string> getImageSrc(std::string html) {
	std::vector<std::string> images;

	if (html.find("<img src=") != std::string::npos) {
		for (int i = 0; i < html.length(); i++) {

			if (html[i] == 's' && html[i+1] == 'r' && html[i+2] == 'c') {
				std::string temp;
				int pos = -1;

				for (int d = i+5; d < html.length(); d++) {

					if (html[d] == '"' && html[d+1] == ' '){
						images.push_back(temp);
						break;
					} else temp += html[d];
				}

			}

		}
	}

	return images;
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

int main(int argc, char const *argv[]) {
	if (argc < 1) {
		std::cerr << "incomplete arguments" << '\n';
		return -1;
	}
	
	std::ifstream file(argv[1]);
	std::string line;

	// for price
	// std::vector<std::vector<std::string>> spans;
	// while (std::getline(file, line)) {
	// 	std::vector<std::string> res = getImageSrc(line);
	// 	if (!res.empty()) spans.push_back(res);
	// }

	// for image
	std::vector<std::vector<std::string>> image;
	while (std::getline(file, line)) {
		std::vector<std::string> res = getImageSrc(line);
		if (!res.empty()) image.push_back(res);
	}

	for (std::vector<std::string> s : image) {
		for (std::string d : s) {
			std::cout << d << '\n';
		}
	}

	return 0;
}