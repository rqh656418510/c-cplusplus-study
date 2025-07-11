/**
 * 范围for、new内存动态分配、nullptr
 */

#include <iostream>

void show() {
	std::cout << "default show()" << std::endl;
}

namespace google {

	void show() {
		std::cout << "google show()" << std::endl;
	}

}

namespace sgi {
	void show() {
		std::cout << "sgi show()" << std::endl;
	}
}

int main() {
	google::show();
	sgi::show();
	::show();
	return 0;
}