#include <iostream>
#include <filesystem>
#include "getURL.h"
// #include "getPrice.h"
// #include "scrap.h"
#include "working.h"

namespace fs = std::filesystem;

int main(int argc, char const *argv[]) {
	if (argc < 1) return -1;
	curl_global_init(CURL_GLOBAL_DEFAULT);

	std::string categories_link_fname = argv[1];
	std::string categories_name_fname = argv[2];
	std::string dir = argv[3];

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


	if (!fs::exists(dir) && !fs::is_directory(dir)) {
		std::cout << "[+] Directory doesn't exists... Creating.\n";
		fs::create_directory(dir);
	} else {
		std::cout << "[+] Directory already exists\n";
	}

	for (int i = 0; i < v_links.size(); i++) {
		std::cout << "[~] Current: " << '\n';
		std::cout << "[+] Link: " << v_links[i] << '\n';
		std::cout << "[+] Name: " << v_names[i] << '\n';

		std::string temp;
		if (getURL(v_links[i], temp) == -1) {
			std::cout << "[!] Error in getURL()\n"; 
			return -1;
		}

		std::string line;
		std::vector<std::string> elements;
		std::istringstream response_ss(temp);

		int counter = 0;
		bool found = false;
		bool p_found = false;

		while (std::getline(response_ss, line)) {
			std::string out = getSubCategory(found, counter, line, "div", "sub-category", "a");

			if (out != "") {
				elements.push_back(out);
			}
		}

		std::ofstream o_file(dir + "/" + v_names[i] + "-filter.txt");
		for (std::string f : elements) {
			o_file << f << '\n';
		} o_file.close();

		std::cout << "[+] " << v_names[i]+"-filter.txt" << " finished." << "\n\n";
	}



	return 0;
}