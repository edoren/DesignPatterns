#include <cassert>
#include <iostream>

class FileSystem {
public:
    FileSystem() {
        assert(!s_instance);
        std::cout << "Creating global instance " << this << std::endl;
        s_instance = this;
    }

    ~FileSystem() {
        assert(s_instance);
        std::cout << "Deleting global instance " << this << std::endl;
        s_instance = nullptr;
    }

    static FileSystem& GetInstance() {
        assert(s_instance);
        return *s_instance;
    }

    static FileSystem* GetInstancePtr() {
        return s_instance;
    }

private:
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(FileSystem&) = delete;

    static FileSystem* s_instance;
};

FileSystem* FileSystem::s_instance = nullptr;

int main(void) {
    FileSystem* global_fs = new FileSystem();

    std::cout << "Instance pointer " << FileSystem::GetInstancePtr()
              << std::endl;

    delete global_fs;
}
