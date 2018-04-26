# C++继承权限   

C++中有三个权限修饰符,`private`,`public`,`protected`,他们可以修饰类的成员，现在他们也可以修饰基类成员在派生类中的访问权限。    

C++中通常的类继承形式如下:   

```c++
class SonClass : public FatherClass{
    //派生类中新添加的成员
};
```   

这里的继承权限是public的，如果这里省略不写继承权限修饰符的话，默认就是private的，这个和在类中定义成员时不写权限修饰符就默认是private是一致的。     


## public,protected,private修饰类的成员    

类成员的访问权限由高到低依次为:public protected private，之前我们只知道类的对象可以访问到public修饰的成员，private修饰的成员是访问不到的。     

加入了protected修饰符后，就有新的情况了，同private一样，通过类的对象也不可以访问到protected修饰的成员，**但是当存在继承关系时，protected就和private不同了，基类中的protected成员可以在派生类中使用。**       

## public,protected,private指定继承方式    

不同的继承方式会影响基类成员在派生类中的访问权限。     

* 基类成员在派生类中的访问权限不得高于继承方式中指定的权限，比如当继承方式定为了protected,那基类成员在派生类中的访问权限最高也为protected，高于继承方式的成员也会被降级为protected,但低于protected的不会升级，再如，当继承方式为public时，那基类成员在派生类中的访问权限不会改变。    

    **也就是说继承方式定义的是基类成员在派生类当中的最高访问权限。**       

* 不管继承方式如何，基类中的private成员在派生类中始终无法使用(不能在派生类的成员函数中访问或调用。)     

* 如果希望基类成员既不向外暴露(不能通过对象访问)，还能在派生类中访问，那只能声明为protected.    

* 这里说的基类中声明为private的成员不能在派生类中使用，并不是说这些成员不能被继承，其实他们会占用派生类对象的内存，但是因为在派生类无法使用，导致不可见。    


## 改变访问权限   

使用`using`关键字可以改变基类成员在派生类中的访问权限，但是只能改变基类中public和protected成员的访问权限，不能改变private成员的访问权限，因为基类中private成员在派生类中是不可见的，根本不能使用，所以基类中的private成员在派生类中无论如何都不能访问。    

using关键字使用:    

```c++
#include <iostream>

using namespace std;

class People {
public:
    void show();

protected:
    char *m_name;
    int m_age;
};

void People::show() {
    cout << "名字是:" << m_name << "年龄是:" << m_age << endl;
}

//派生类
class Student : public People {
public:
    void read();

public:
    using People::m_name; //将基类中protected成员的权限改为public
    using People::m_age; //同上
    float m_grade;
private:
    using People::show; //将基类中public成员的权限修改为private
};

void Student::read() {
    cout << "姓名为:" << m_name << "年龄为:" << m_age << "分数为:" << m_grade << endl;
}


int main() {
    Student stu;
    stu.m_age = 20;
    stu.m_grade = 100.0;
    stu.show(); //编译错误，因为我们将这个成员函数的权限降低为private，无法通过对象访问了。     
    stu.read();
    return 0;
}
```   




