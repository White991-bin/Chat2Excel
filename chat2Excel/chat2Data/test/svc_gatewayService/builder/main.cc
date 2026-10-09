#include <iostream>
#include <string>
#include <memory>
#include <vector>

// 产品类
class Computer {
private:
    std::string _cpu;
    std::string _gpu;
    std::string _motherboard;
    std::string _ram;
    std::string _disk;

    // 私有构造函数，只能通过Builder创建
    Computer() {}
    
public:

    // Builder内部类
    class Builder {
    private:
        std::unique_ptr<Computer> _computer;
        
    public:
        Builder() : _computer(new Computer()) {}
        
        Builder& setCPU(const std::string& cpu) {
            _computer->_cpu = cpu;
            return *this;
        }
        
        Builder& setGPU(const std::string& gpu) {
            _computer->_gpu = gpu;
            return *this;
        }
        
        Builder& setMotherboard(const std::string& motherboard) {
            _computer->_motherboard = motherboard;
            return *this;
        }
        
        Builder& setRAM(const std::string& ram) {
            _computer->_ram = ram;
            return *this;
        }
        
        Builder& setDisk(const std::string& disk) {
            _computer->_disk = disk;
            return *this;
        }
        
        Computer build() {
            return std::move(*_computer);  // 移动语义
        }
    };
    
    void show() const {
        std::cout << "电脑配置:\n"
                  << "  CPU: " << _cpu << "\n"
                  << "  GPU: " << _gpu << "\n"
                  << "  主板: " << _motherboard << "\n"
                  << "  内存: " << _ram << "\n"
                  << "  硬盘: " << _disk << "\n";
    }
};

int main() {
    // 注意：必须调用 build()
    Computer goodComputer = Computer::Builder()
        .setCPU("Intel i7-12700K")
        .setGPU("RTX 3070")
        .setMotherboard("Z690")
        .setRAM("32GB")
        .setDisk("1TB SSD")
        .build();  // 必须调用 build()
    
    std::cout << "通过建造者模式创建（链式调用，清晰易读）:\n";
    goodComputer.show();
    
    return 0;
}