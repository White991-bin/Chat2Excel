#include <iostream>
#include <variant>
#include <string>

int main(){
    std::variant<int, double, std::string> v1;  // 可以存 int、double 或 string
    v1 = 42;           // 存 int
    v1 = 3.14;         // 改为存 double

    // 访问值
    std::cout << std::get<double>(v1)<<std::endl;   // 正确，d = 3.14
    if(std::holds_alternative<double>(v1)){
        std::cout << std::get<double>(v1)<<std::endl;
    } else {
        std::cout << std::get<int>(v1)<<std::endl;         // 抛出 std::bad_variant_access
    }

    double* pd = std::get_if<double>(&v1);
    *pd = 12.34;
    std::cout << std::get<double>(v1)<<std::endl;


    // 也可以用索引（按声明顺序，0 开始）
    std::cout << std::get<1>(v1)<<std::endl;       // double 是第2个类型，索引为 1

    std::variant<int, double> v2 = 3.14;

    if (double* pd = std::get_if<double>(&v2)) {
        // 如果当前存的是 double，pd 指向该值
        std::cout << *pd << std::endl;
    } else {
        // 不是 double，pd 为 nullptr
        std::cout << "不是 double" << std::endl;
    }
    return 0;
}