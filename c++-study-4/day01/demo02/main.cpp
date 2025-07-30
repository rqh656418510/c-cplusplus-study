/**
 * 命名空间简介、基本输入输出精解
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