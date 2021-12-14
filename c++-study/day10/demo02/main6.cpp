/*
 * 1. �쳣�������
 * a) �쳣���ͺ��쳣��������������
*/

#include <iostream>

using namespace std;

class BadSrcType {
};

class BadDestType {
};

class BadProcessType {
public:
    BadProcessType() {
        cout << "BadProcessType�Ĺ��캯��������" << endl;
    }


    BadProcessType(const BadProcessType& obj) {
        cout << "BadProcessType�Ŀ������캯��������" << endl;
    }

    ~BadProcessType() {
        cout << "BadProcessType����������������" << endl;
    }

};

void myStrcpy(char* to, char* from) {
    if (to == NULL) {
        throw BadDestType();
    }
    if (from == NULL) {
        throw BadSrcType();
    }

    if (*from == 'a') {
        throw BadProcessType();
    }
    if (*from == 'b') {
        // ������ʹ������д��
        throw& (BadProcessType());
    }
    if (*from == 'c') {
        throw new BadProcessType;
    }

    while (*from != '\0') {
        *to = *from;
        to++;
        from++;
    }
    *to = '\0';
}

int main() {
    int ret = 0;
    char buf1[] = "cbbcdefg";
    char buf2[1024] = { 0 };

    try {
        myStrcpy(buf2, buf1);
    }
    catch (BadSrcType e) {
        cout << " BadSrcType �����쳣" << endl;
    }
    catch (BadDestType e) {
        cout << " BadDestType �����쳣" << endl;
    }
    /*
    // ����1: ��������쳣��ʱ��ʹ��һ���쳣�������򿽱�������쳣����
    catch (BadProcessType e)
    {
        cout << " BadProcessType �����쳣" << endl;
    }

    // ����2: ��������쳣��ʱ��ʹ�������ã����ʹ��throwʱ����Ǹ�����
    catch (BadProcessType& e)
    {
        cout << " BadProcessType �����쳣" << endl;
    }

    // ����3: �����쳣��ʱ��ָ����Ժ�����/Ԫ��ͬʱ���֣�����������Ԫ�ز���ͬʱ����
    catch (BadProcessType* e)
    {
        cout << " BadProcessType �����쳣" << endl;
        delete e;
    }

    // ����4: ����׳�������������͵��쳣����ʹ�����ý����쳣����ȽϺ���

    */
    catch (...) {
        cout << "δ֪ �����쳣" << endl;
    }
    return 0;
}