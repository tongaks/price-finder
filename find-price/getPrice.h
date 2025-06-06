#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::string getImageSrc1(std::string html, std::string p_name) {

	std::string upper = "";
	for (char c : p_name) upper += std::toupper(c);


	if (html.find("<img src=") != std::string::npos) {
		if (html.find("pgmobile") == std::string::npos) return "";

		for (int i = 0; i < html.length(); i++) {
			std::string temp = "";

			if (html[i] == 's' && html[i+1] == 'r' && html[i+2] == 'c') {
				for (int d = i+4; d < html.length(); d++) {
					if (html[d] != '"') {
						temp += html[d];
					} else if (html[d] == '"' && html[d+1] == ' ') {
						return temp;
					}
				}
			}
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