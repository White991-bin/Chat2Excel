#include <iostream>
#include <memory>
#include <string>

// 动物
class Animal {
public:
    virtual void speak() = 0;           // 纯虚函数
    virtual ~Animal() = default;
};

// 狗
class Dog : public Animal {
public:
    void speak() override {
        std::cout << "汪汪！我是小狗" << std::endl;
    }
};

// 猫
class Cat : public Animal {
public:
    void speak() override {
        std::cout << "喵喵！我是小猫" << std::endl;
    }
};

// 牛
class Cow : public Animal {
public:
    void speak() override {
        std::cout << "哞哞！我是小牛" << std::endl;
    }
};

// ==================== 简单工厂 ====================
class AnimalFactory {
public:
    // 根据类型字符串创建对应动物
    static std::unique_ptr<Animal> createAnimal(const std::string& type) {
        if (type == "dog") {
            return std::make_unique<Dog>();
        } else if (type == "cat") {
            return std::make_unique<Cat>();
        } else if (type == "cow") {
            return std::make_unique<Cow>();
        }
        return nullptr;  // 未知类型
    }
};

// 使用示例
int main() {
    // 用户输入或配置决定创建什么动物
    std::string animalType = "dog";
    
    // 通过工厂创建，无需关心具体类名和构造细节
    auto animal = AnimalFactory::createAnimal(animalType);
    
    if (animal) {
        animal->speak();  // 输出：汪汪！我是小狗
    }
    
    // 想换猫？只改字符串
    auto cat = AnimalFactory::createAnimal("cat");
    cat->speak();  // 输出：喵喵！我是小猫
    
    return 0;
}