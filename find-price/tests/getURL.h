#include <curl/curl.h>
#include <string>
#include <sstream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


// get the contents and store it to &buffer
int getURL(std::string url, std::string &buffer) {
	CURL *handler = curl_easy_init();
	CURLcode res;

	if (handler) {
		curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
	    curl_easy_setopt(handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(handler, CURLOPT_WRITEDATA, &buffer);

		res = curl_easy_perform(handler);

		if (res != CURLE_OK) {
			std::cout << "res: " << res << '\n';
			std::cerr << "Error on curl" << '\n'; 
			return -1;
		}

	} else return -1;

	curl_easy_cleanup(handler);
	return 0;
}

// int scrape(std::string &buffer, std::string t_attr) {}