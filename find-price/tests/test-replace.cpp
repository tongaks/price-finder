#include <iostream>
#include "working.h"

int main(int argc, char const *argv[]) {
	std::string test = "https://puregold.com.ph/pgcatalog/category/view/category/WINES & LIQUORS";
	std::cout << replaceSpace(test) << '\n';
	return 0;
}