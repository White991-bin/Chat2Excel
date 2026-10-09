#include <iostream>
#include <string>

class Computer {
private:
    std::string _cpu;
    std::string _gpu;
    std::string _motherboard;
    std::string _ram;
    std::string _disk;
public:
    Computer(const std::string& cpu, const std::string& gpu, const std::string& motherboard,
             const std::string& ram, const std::string& disk)
        : _cpu(cpu), _gpu(gpu), _motherboard(motherboard), _ram(ram), _disk(disk) {}
    

    void show() {
        std::cout << "电脑配置:\n"
                  << "  CPU: " << _cpu << "\n"
                  << "  GPU: " << _gpu << "\n"
                  << "  主板: " << _motherboard << "\n"
                  << "  内存: " << _ram << "\n"
                  << "  硬盘: " << _disk << "\n";
    }
};

// 方式B：使用setter方法
class ComputerWithSetter {
private:
    std::string _cpu;
    std::string _gpu;
    std::string _motherboard;
    std::string _ram;
    std::string _disk;

public:
    // 无参构造，通过setter设置
    ComputerWithSetter() = default;
    
    void setCPU(const std::string& cpu) { this->_cpu = cpu; }
    void setGPU(const std::string& gpu) { this->_gpu = gpu; }
    void setMotherboard(const std::string& mb) { this->_motherboard = mb; }
    void setRAM(const std::string& ram) { this->_ram = ram; }
    void setDisk(const std::string& disk) { this->_disk = disk; }

    void show() {
        std::cout << "电脑配置:\n"
                  << "  CPU: " << _cpu << "\n"
                  << "  GPU: " << _gpu << "\n"
                  << "  主板: " << _motherboard << "\n"
                  << "  内存: " << _ram << "\n"
                  << "  硬盘: " << _disk << "\n";
    }
};

#include <iostream>

int main() {

    // 方式1：构造函数方式 - 参数太多，难以理解
    Computer badComputer1("Intel i7-12700K", "RTX 3070", "Z690", "32GB", "1TB SSD");
    std::cout << "通过构造函数创建（参数顺序容易搞混）:\n";
    badComputer1.show();
    
    std::cout << "\n";
    
    // 方式2：setter方式 - 需要多行代码，容易忘记设置
    ComputerWithSetter badComputer2;
    badComputer2.setCPU("AMD Ryzen 7 5800X");
    badComputer2.setGPU("RX 6800 XT");
    badComputer2.setMotherboard("B550");
    badComputer2.setRAM("32GB");
    badComputer2.setDisk("1TB SSD");
    std::cout << "通过setter创建（代码冗长，对象状态可能不完整）:\n";
    badComputer2.show();
    return 0;
}