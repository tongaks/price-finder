#include <iostream>
#include <vector>
#include <string>
#include <fstream>


// disgusting-looking code to scrape the price
std::vector<std::string> getPrices(std::string html) {
	std::vector<std::string> prices;

	for (int i = 0; i < html.length(); i++) {

		if (html[i] == '<') {
			std::string temp;

			for (int d = i; d < html.length(); d++) {
				if (html[d] == '<' && html[d+1] == '/') {
					// temp += html[d];

					if (temp.find("span") != std::string::npos) {
						if (temp.find("class=\"price\"") != std::string::npos) {
							int pos = -1;

							for (int g = 0; g < temp.length(); g++) {
								if (temp[g] == '>') {
									pos = g;
								}
							}

							temp = temp.substr(pos+1, temp.length());
							prices.push_back(temp);
						}

					}

					break;
				} else {
					temp += html[d];
				}

			}
		}
	}

	return prices;
}