#include <stdio.h>

/**
 * 1. putchar（字符输出函数）与 getchar(字符输入函数)
 * 2. printf 函数（格式输出函数）
 * 3. scanf函数(格式输入函数)
 */
int main(){

void formatPrint(){
    int a = 15;
    char d = 'p';
    int x = 88, y = 89;
    float b = 123.1234567;
    double c = 12345678.1234567;
    printf("%c,%c\n",x,y);                           // >> X, Y
    printf("a=%d,%5d,%o,%x\n",a,a,a,a);              // >> a=15,   15,17,f
    printf("b=%f,%lf,%5.4lf,%e\n",b,b,b,b);          // >> b=123.123459,123.123459,123.1235,1.231235e+02
    printf("c=%lf,%f,%8.4lf\n",c,c,c);               // >> c=12345678.123457,12345678.123457,12345678.1235
    printf("d=%c,%8c\n",d,d);                        // >> d=p,       p
}

//    ----------------------------------putchar（字符输出函数）
    char b = 'b';
    putchar('A');
    putchar(b);
    putchar('\101');
    putchar('\n');

//    ----------------------------------getchar(字符输入函数)
    printf("input a character:\n");
    char c = getchar();
    putchar(c);
    putchar('\n');
    printf("---------------\n");

//    ----------------------------------printf 函数（格式输出函数）
    formatPrint();
    printf("---------------\n");

//    ----------------------------------scanf函数(格式输入函数)
    int m, n, o;
    printf("input three int number: m, n, o\n");
    setbuf(stdin, NULL);
    scanf("%d%d%d", &m, &n, &o);
    printf("m=%d, n=%d, o=%d\n", m, n, o);

    int p, q;
    printf("input a long int number:\n");
    setbuf(stdin, NULL);
    scanf("%4d%4d", &p, &q);                // 尝试输入数据，12345678 或者 1234 5678
    printf("%d, %d\n", p, q);

    char c1, c2, c3;
    printf("input three chacter: c1, c2, c3\n");
    setbuf(stdin, NULL);
    scanf("%c %c %c", &c1, &c2, &c3);         // 输入数据时，字符之间可以使用空格作为间隔符，也可以不使用任何间隔符
    printf("%c %c %c\n", c1, c2, c3);

//    char c4, c5, c6;
//    printf("input three chacter: c4, c5, c6\n");
//    setbuf(stdin, NULL);
//    scanf("%c%c%c", &c4, &c5, &c6);         // 输入数据时，字符之间不能有空格间隔符号
//    printf("%c %c %c\n", c4, c5, c6);

    int x1, x2, x3;
    printf("input three int number: x1, x2, x3\n");
    setbuf(stdin, NULL);
    scanf("%d%d%d", &x1, &x2, &x3);            // 输入数据时，字符之间则可用空格、TAB或回车作间隔符
    printf("%d %d %d\n", x1, x2, x3);

    int a1, a2, a3;
    printf("input three int number: a1, a2, a3\n");
    setbuf(stdin, NULL);
    scanf("%d,%d,%d", &a1, &a2, &a3);           // 输入数据时，字符之间必须需要使用逗号或者逗号+空格作为间隔符
    printf("%d %d %d\n", a1, a2, a3);

    int f;
    printf("input a number: f\n");
    setbuf(stdin, NULL);
    scanf("%d", &f);
    printf("%ld\n", f);

}

