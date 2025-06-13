#include <iostream>
#include "getURL.h"

// iterate trough content to get the desired elements
int _getProductsName(std::string &buffer, std::string o_name) {
	std::string line;
	std::vector<std::string> elements;
	std::istringstream response_ss(buffer);
	
	int counter = 0;
	bool found = false;
	bool p_found = false;

	while (std::getline(response_ss, line)) {
		std::string out = getProductName(found, false, line, "pgcatalog/product/view/category/" + o_name);
		// std::string out = getDivChildrens(found, true, line, "div", "sub-category", "a");
		if (out != "") {
			elements.push_back(out);
		}
	}

	std::ofstream f_out(o_name+".txt");
	for (std::string s : elements) {
		f_out << s << '\n';
	}

	f_out.close();
	return 0;
}

int main(int argc, char const *argv[]) {
	if (argc < 1) return -1;
	curl_global_init(CURL_GLOBAL_DEFAULT);

	std::string categories_link_fname = argv[1];
	std::string categories_name_fname = argv[2];


	std::string link;
	std::vector<std::string> v_links;
	std::ifstream links_f(categories_link_fname);

	while (std::getline(links_f, link)) {
		std::string copy = replaceSpace(link);
		size_t end = copy.find('"', 1);
		v_links.push_back(copy.substr(1, end-1));

	} links_f.close();


	std::string name;
	std::vector<std::string> v_names;
	std::ifstream names_f(categories_name_fname);

	while (std::getline(names_f, name)) {
		v_names.push_back(name);
	} names_f.close();


	for (int i = 0; i < v_links.size(); i++) {
		std::cout << "[!] Current: \n" <<  v_links[i] << "\n" << v_names[i] << "\n";

		std::string buffer;
		if (getURL(v_links[i], v_names[i], buffer) == 0) {
			if (_getProductsName(buffer, v_names[i]) == 0)
				std::cout << "[+] " << v_names[i] << " is finished." << '\n';
		}
	}

	return 0;
}