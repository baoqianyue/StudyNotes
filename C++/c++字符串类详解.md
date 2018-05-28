# C++字符串string类    

C++中不仅可以使用C语言风格的字符串，还内置了字符串类string类，它对字符串的操作十分强大，完全可以替代C语言中的字符数组和字符串指针。  
## 定义字符串   

```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
    string a; //默认赋值为空串""
    string b = "BarackBao"; //定义并初始化
    string c = b; //使用b初始化，内容和b一样
    string d(5,'s'); //初始化为五个‘s’组成的字符串  

    return 0;
}
```   

我们可以直接调用字符串类中的成员函数获取当前字符串对象的长度：   

```c++
    string b = "BarackBao"; //定义并初始化
    int len = b.length();
    cout << "字符串b的长度是：" << len << endl;
```   

输出:`字符串b的长度是：9`       

## 转换为C语言风格的字符串   

有的时候必须使用字符数组形式的字符串，比如使用C语言文件函数打开文件时，文件名参数限制为char*类型，这时就需要字符串转换函数c_str(),该函数可以将string字符串转换为c风格的字符串，并返回该字符串的const指针。    

```c++
    string filename("D:Test||file.txt");
    FILE *fp = fopen(filename.c_str(), "rt");
```   

## C++字符串的输入输出   

string类重载了输入输出符，可以像普通变量那样使用>>,<<进行输入输出   

```c++
    string s;
    cin >> s;
    cout << s << endl;
```   

输入及输出：  

```
baoqianyue BarackBao
baoqianyue

```    

这里我输入了两个字符串，中间用空格隔开了，但是只输出了一个，这是因为>>运算符默认会忽略空格，遇到空格就认为输入已经结束。   

## 访问字符串中的字符   

string类也可以使用下标来访问到具体的某个字符，下标也是从0开始   

```c++
    string str = "123456789";
    for (int i = 0; i < str.length(); ++i) {
        cout << str[i] << " ";
    }
    cout << endl;

    str[4] = '3'; //访问并修改字符
    cout << str << endl;
```   

输出：  

```
1 2 3 4 5 6 7 8 9
123436789
```   

这种方式不仅可以访问到字符，还可以进行修改。   


## 字符串的拼接    

我们可以使用运算符`+`,`+=`来进行字符串的拼接，拼接的两端可以是两个string对象，也可以一端是string对象，一端是c风格字符串，还可以是一端string对象，一端是字符数组，也可以是一端string对象，一端是单个字符。    

```c++
int main() {

    string s1 = "bao ";
    string s2 = "qianyue ";
    char *s3 = "barack ";
    char s4[] = "bao ";
    char s5 = '#';

    string s6 = s1 + s2;
    string s7 = s1 + s3;
    string s8 = s1 + s4;
    string s9 = s1 + s5;

    cout << s6 << endl << s7 << endl << s8 << endl << s9 << endl;
    return 0;
}
```   


 

