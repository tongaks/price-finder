#include <iostream>
#include "scrap.h"

int main(int argc, char const *argv[]) {
	std::string line = "<div>Test</div>";
	std::string line_a = "<a class='links' href='https://google.com'>Click the link</a>";
	std::string line_b = "<a class='links' href='https://google.com' src='https://google.com/images/cat.png'>Click the link</a>";

	std::string elem = getElement(line_b);
	std::string inner = getInnerHTML(line_b);
	std::string href = getElementHref(line_b);
	std::string src = getElementSrc(line_b);
	std::string clas = getElementClass(line_b);

	std::cout << "line: " << line_b << "\n\n";

	std::cout << "elem: " << elem << '\n';
	std::cout << "inner: " << inner << '\n';
	std::cout << "href: " << href << '\n';
	std::cout << "src: " << src << '\n';
	std::cout << "class: " << clas << '\n';

	return 0;
}