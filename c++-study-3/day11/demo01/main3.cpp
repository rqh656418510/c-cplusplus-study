/**
 * function�����������͵�Ӧ��ʾ��
 */

#include <iostream>
#include <functional>
#include <string>
#include <map>

using namespace std;

void doShowAllBooks() {
	cout << "�鿴�����鼮" << endl;
};

void doBorrowBook() {
    cout << "����" << endl;
};

void doBackBook() {
    cout << "����" << endl;
}

void doQueryBook() {
    cout << "��ѯ�鼮" << endl;
}

void doLoginOut() {
	cout << "ע��" << endl;
}

int main() {
    int choice = 0;

    map<int, function<void()>> actionMap;
	actionMap.insert({ 1, doShowAllBooks });
    actionMap.insert({ 2, doBorrowBook });
    actionMap.insert({ 3, doBackBook });
    actionMap.insert({ 4, doQueryBook });
    actionMap.insert({ 5, doLoginOut });

    for (;;) {
        cout << "\n-------------------" << endl;
        cout << "1. �鿴�����鼮" << endl;
        cout << "2. ����" << endl;
        cout << "3. ����" << endl;
        cout << "4. ��ѯ�鼮" << endl;
        cout << "5. ע��" << endl;
        cout << "-------------------" << endl;
        cout << "��ѡ��: ";

        // ��������Ƿ�Ϸ�
        if (!(cin >> choice)) {
            cout << "����������Ч������������!" << endl;
            // �������״̬
            cin.clear();
			// ������������
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        auto it = actionMap.find(choice);
        if (it == actionMap.end()) {
            cout << "����������Ч������������!" << endl;
            continue;
        }
        
        it->second();
    }
    return 0;
}