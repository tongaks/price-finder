#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include "getPrice.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);

    if (response.find("<img src='") != std::string::npos) {
    	std::cout << "found image: " << response << '\n';
    }

    return totalSize;
} 

int fetchURL(std::string _url, std::string &content) {
	std::string url = _url;
	curl_global_init(CURL_GLOBAL_DEFAULT);

	std::string response;
	CURL *handler = curl_easy_init();
	CURLcode res;

	if (handler) {
		curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
	    curl_easy_setopt(handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, WriteCallback);

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
}

int main(int argc, char const *argv[]) {
	if (argc < 1) return -1;

	return 0;
}