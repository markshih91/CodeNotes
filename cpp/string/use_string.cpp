#include <iostream>
#include <string>

using namespace std;

int main(){

    // 1、构造函数
    string s1("");  // s1 = ""
    string s2("Hello");  // s2 = "Hello"
    string s3(4, 'K');  // s3 = "KKKK"
    string s4("12345", 1, 3);  //s4 = "234"，即 "12345" 的从下标 1 开始，长度为 3 的子串

    // 2、赋值
    // 可以用char*类型的变量、常量，以及char类型的变量、常量对string对象进行赋值
    s1 = "Hello";  // s1 = "Hello"
    s2 = 'K';  // s2 = "K”
    // assign()成员函数，用来对string对象赋值，返回对象自身的引用
    string s1("12345"), s2;
    s2.assign(s1);  // s2 = s1
    s2.assign(s1, 1, 2);  // s2 = "23"，即s1的起始下标为1，长度为2的子串
    s2.assign(4, 'K');  // s2 = "KKKK"
    s2.assign("abcde", 2, 3);  // s2 = "cde"，即"abcde"的起始下标为2，长度为3的子串

    // 3、字符串的长度
    // string有两个成员函数size()与length()可以得到字符串的长度
    int s1_len = s1.length();
    int s2_len = s2.size();

    // 4、字符串的连接
    // 三种连接方式：+、+=和append()成员函数，append()成员函数返回对象的引用
    string s1("123"), s2("abc"), s3;
    s3 = s1 + s2; // s3 = "123abc"
    s3 += s1; // s3 = "123abc123"
    s1.append(s2);  // s1 = "123abc"
    s1.append(s2, 1, 2);  // s1 = "123abcbc"
    s1.append(3, 'K');  // s1 = "123abcbcKKK"
    s1.append("ABCDE", 2, 3);  // s1 = "123abcbcKKKCDE"，添加 "ABCDE" 的子串(2, 3)

    // 5、字符串比较
    // 可以用<、<=、==、!=、>=、>运算符，也可以用compare()成员函数，返回值小于0表示当前的字符串小；等于0表示两个字符串相等；大于0表示另一个字符串小
    // (m, n)表示下标从m开始长度为n的子串
    string s1("hello"), s2("hello, world");
    int n = s1.compare(s2);
    n = s1.compare(1, 2, s2, 0, 3);  //比较s1的子串(1,2)和s2的子串(0,3)
    n = s1.compare(0, 2, s2);  // 比较s1的子串(0,2)和s2
    n = s1.compare("Hello");
    n = s1.compare(1, 2, "Hello");  //比较s1的子串(1,2)和"Hello"
    n = s1.compare(1, 2, "Hello", 1, 2);  //比较s1的子串(1,2)和"Hello"的子串(1,2)

    // 6、字符串子串
    string s1 = "this is ok";
    string s2 = s1.substr(2, 4);  // s2 = "is i"
    s2 = s1.substr(2);  // s2 = "is is ok"

    // 7、交换两个字符串对象的内容
    string s1("West"), s2("East");
    s1.swap(s2);  // s1 = "East"，s2 = "West"

    // 8、查找子串或字符
    // 查找子串和字符的成员函数，返回值是子串或字符在字符串中的下标。如果查不到，则返回string::npos
    // find：从前往后查找子串或字符出现的位置
    // rfind：从后往前查找子串或字符出现的位置
    // find_first_of：从前往后查找第一次出现另一个字符串中包含的字符的位置
    // s1.find_first_of("abc");  //查找s1中第一次出现"abc"中任一字符的位置
    // find_last_of：从后往前查找第一次出现另一个字符串中包含的字符的位置
    // find_first_not_of：从前往后查找第一次出现另一个字符串中没有包含的字符的位置
    // find_last_not_of：从后往前查找第一次出现另一个字符串中没有包含的字符的位置
    string s1("Source Code");
    int n;
    n = s1.find('u'); //查找u出现的位置,n = 2
    n = s1.find("Source", 3); //从下标3开始查找"Source"，找不到，返回string::npos
    n = s1.find("Co"); //查找子串"Co"，n = 7
    n = s1.find_first_of("ceo"); //查找第一次出现或 'c'、'e'或'o'的位置，n = 1
    n = s1.find_last_of('e'); //查找最后一个 'e' 的位置，n = 10
    n = s1.find_first_not_of("eou", 1); //从下标1开始查找第一次出现非 'e'、'o' 或 'u' 字符的位置，n = 3

    // 9、替换子串
    // replace()成员函数可以对子串进行替换，返回值为自身的引用
    string s1("Real Steel");
    s1.replace(1, 3, "123456", 2, 4);  //用 "123456" 的子串(2,4) 替换 s1 的子串(1,3)
    string s2("Harry Potter");
    s2.replace(2, 3, 5, '0');  //用 5 个 '0' 替换子串(2,3)

    // 10、删除子串
    // erase()成员函数用来删除子串，返回值为自身的引用
    string s1("Real Steel");
    s1.erase(1, 3);  //删除子串(1, 3)，此后 s1 = "R Steel"
    s1.erase(5);  //删除下标5及其后面的所有字符，此后 s1 = "R Ste"

    // 11、插入字符串
    //insert()成员函数用来插入另一个字符串，返回值为自身的引用
    string s1("Limitless"), s2("00");
    s1.insert(2, "123");  //在下标 2 处插入字符串"123"，s1 = "Li123mitless"
    s1.insert(3, s2);  //在下标 2 处插入 s2 , s1 = "Li10023mitless"
    s1.insert(3, 5, 'X');  //在下标 3 处插入 5 个 'X'，s1 = "Li1XXXXX0023mitless"

    return 0;
}
