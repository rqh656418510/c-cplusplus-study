#include <iostream>

using namespace std;

extern int gdata;   // gdata *UND*

int sum(int, int);  // sum *UND*

int data = 20;  // data .data

int main() {    // main .text
    int a = gdata;
    int b = data;
    int result = sum(a, b);
    cout << "result = " << result << endl;
    return 0;
}

/**

1. 只编译、汇编到目标代码，不进行链接
 g++ -c sum.cpp
 g++ -c main.cpp

2. 查看目标文件的符号表，包括函数和全局变量的地址、大小等信息
 objdump -t sum.o
 objdump -t main.o

3. 显示目标文件中各个段的内容（即十六进制和 ASCII 表示的原始数据）
 objdump -s sum.o
 objdump -s main.o

4. 查看目标文件的文件头信息
 readelf -h sum.o
 readelf -h main.o

5. 查看目标文件中各段的详细信息，包括段的名称、大小、地址、类型和属性等
 readelf -S sum.o
 readelf -S main.o

6. 将目标文件中的汇编代码（通过反汇编得到）与源代码进行对比显示，以便进行调试和分析
 g++ -c main.cpp -g    // 生成目标文件，-g 参数表示带上调试信息
 objdump -S main.o

7. 链接所有目标文件，并查看指定文件的符号表信息
 g++ -e main *.o     // 将所有的目标文件链接成一个完整的程序，默认会生成一个名为 a.out 的可执行文件
 objdump -t a.out

8. 查看可执行文件（通常是 ELF 格式）的程序头信息
  readelf -l a.out

*/
