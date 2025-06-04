#include <iostream>
#include <curl/curl.h>
#include <string>
#include "getPrice.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main(int argc, char const *argv[]) {
	std::string url = "https://puregold.com.ph/index.php/pgcatalog/product/view/category/SNACKS/subcategory/CHIPS,%20NUTS%20&%20CORN/title/PRINGLES%20POTATO%20CRISP%20ORIGINAL%2042G%20/barcode/8886467100260";

	// std::cout << "Enter url: ";
	// std::cin >> url;

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
		}
	} else {
		fprintf(stderr, "Error on handler\n");
	}


	curl_easy_cleanup(handler);

	std::vector<std::string> prices = getPrices(response);
	for (std::string s : prices) {
		std::cout << "price: " << s << '\n';
	}

	return 0;
}