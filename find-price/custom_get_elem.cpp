#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
// #include "getPrice.h"
#include "working.h"
#include "scrap.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
} 

int main(int argc, char const *argv[]) {

	if (argc < 1) return -1;

	std::string url = argv[1];
	std::string fname = argv[2];

	curl_global_init(CURL_GLOBAL_DEFAULT);

	std::string response;
	CURL *handler = curl_easy_init();
	CURLcode res;

	if (handler) {
		curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
	    curl_easy_setopt(handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(handler, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(handler);

		if (res != CURLE_OK) {
			std::cout << "res: " << res << '\n';
			std::cerr << "Error on curl" << '\n'; 
			return -1;
		}

	} else {
		fprintf(stderr, "Error on handler\n");
		return -1;
	}


	std::string line;
	std::vector<std::string> elements;
	std::istringstream response_ss(response);
	int counter = 0;
	bool found = false;

	while (std::getline(response_ss, line)) {
		// std::string out = getElem(line, "a", "/pgcatalog/product/view/category/", "");
		// std::string out = getASrc(line, "https://puregold.com.ph/index.php/pgcatalog/product/view/category/SNACKS/subcategory/", "");
		// std::string out = getPriceDiv(found, line, "product-price-style");
		// std::string out = getProductName(found, line, "pgcatalog/product/view/category/SNACKS/");
		std::string out = getCategoryItems(found, counter, line, "div", "category", "a");
		if (out != "") elements.push_back(out);
	}

	std::ofstream file(fname);
	for (std::string s : elements) {
		std::string clean = getElementHref(s);
		file << clean << '\n';
	}

	file.close();


	curl_easy_cleanup(handler);

	return 0;
}