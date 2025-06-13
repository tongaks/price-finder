#include <vector>
#include <fstream>
#include <curl/curl.h>
#include <string>
#include <sstream>


// get element specified in the parameter
std::string getElement(std::string line, std::string _class) {
	size_t start = line.find("<");

	int end = 0;
	bool isSpace = false;
	for (char c : line) {
		if (c == ' ' || c == '>') {
			isSpace = true;
			break;
		} else end++;
	}

	if (start != std::string::npos && end != std::string::npos) {
		if (isSpace) return line.substr(start, end) + ">";
		else return line.substr(start, end+1);			
	}

	return "";
}



// get specified element innerHTML
std::string getInnerHTML(std::string line) {
	size_t start = line.find('>');

	if (start != std::string::npos) {
	    size_t end = line.find("</", start);
	    
	    if (end != std::string::npos) {
	        return line.substr(start + 1, end - (start + 1));
	    }
	}

	return "";
}


// get specified element's href link
std::string getElementHref(std::string line) {
	size_t start = line.find("href");
	size_t end = 0;

	bool isSpace = false;
	for (int i = start; i < line.length(); i++) {
		if (line[i] == '"' || line[i] == '>') {
			isSpace = true;
			break;
		} else end++;
	}

	if (start != std::string::npos && end != std::string::npos) {
		return line.substr(start+5, end-5);
	}

	return "";
}


// get specified element's src link
std::string getElementSrc(std::string line) {
	size_t start = line.find("src");
	size_t end = 0;

	bool isSpace = false;
	for (int i = start; i < line.length(); i++) {
		if (line[i] == ' ' || line[i] == '>') {
			isSpace = true;
			break;
		} else end++;
	}

	if (start != std::string::npos && end != std::string::npos) {
		return line.substr(start+4, end-4);
	}

	return "";
}


// get specified element's class
std::string getElementClass(std::string line) {
	size_t start = line.find("class");
	size_t end = 0;

	bool isSpace = false;
	for (int i = start; i < line.length(); i++) {
		if (line[i] == ' ' || line[i] == '>') {
			isSpace = true;
			break;
		} else end++;
	}

	if (start != std::string::npos && end != std::string::npos) {
		return line.substr(start+6, end-6);
	}

	return "";
}