#ifndef TEACHER_H
#define TEACHER_H

class Teacher {

private:
    char *_name;
    int _age;

public:
    const char *getName() const;

    void setName(char *name);

    int getAge() const;

    void setAge(int age);
};

#endif
