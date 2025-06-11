#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include "getPrice.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
} 

int main(int argc, char const *argv[]) {

	if (argc < 1) return -1;

	std::string url = argv[1];

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


	// std::istringstream new_response(response);
	// std::string img_line;
	// std::vector<std::vector<std::string>> images;
	// while (std::getline(new_response, img_line)) {
	// 	std::vector<std::string> out = getImageSrc(img_line, "");
	// 	if (!out.empty()) images.push_back(out);
	// }


	// std::istringstream new_response_pr(response);
	// std::string price_line;
	// std::vector<std::vector<std::string>> prices;
	// while (std::getline(new_response_pr, price_line)) {
	// 	std::vector<std::string> out = getPrices(price_line);
	// 	if (!out.empty()) prices.push_back(out);
	// }


	// getChildren() image product 
	// std::istringstream new_response_pr(response);
	// std::string elem_line;
	// std::vector<std::string> elems;
	// bool isFound = false;
	// while (std::getline(new_response_pr, elem_line)) {
	// 	std::string out = getChildren(isFound, elem_line, "div", "Item", "a", "");
	// 	if (!out.empty()) elems.push_back(out);
	// }

	// std::vector<std::vector<std::string>> clean_img_lnk;
	// for (std::string s : elems) {
	// 	std::vector<std::string> temp = getImageSrc(s, "");
	// 	if (!(temp.empty())) clean_img_lnk.push_back(temp);
	// }

	// for (std::vector<std::string> v : clean_img_lnk) 
	// 	for (std::string s : v) std::cout << s << '\n'; 


	// std::istringstream new_response(response);
	// std::string price_elem_line;
	// std::vector<std::string> p_elems;
	// bool isPriceFound = false;
	// while (std::getline(new_response, price_elem_line)) {
	// 	std::string out = getChildren(isPriceFound, price_elem_line, "div", "style=\"height:100px;\"", "div", "product-price-style");
	// 	if (!out.empty()) p_elems.push_back(out);
	// }
	// for (std::string s : p_elems) std::cout << s << '\n';


	curl_easy_cleanup(handler);

	return 0;
}