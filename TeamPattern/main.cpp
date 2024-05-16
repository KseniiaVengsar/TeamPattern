#include <iostream>
#include <fstream>
#include <string>


class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};


class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};


class FileLogCommand : public LogCommand {
public:
    FileLogCommand(const std::string& filePath) : filePath_(filePath) {}

    void print(const std::string& message) override {
        std::ofstream outFile(filePath_, std::ios::app); 
        if (outFile.is_open()) {
            outFile << message << std::endl;
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file: " << filePath_ << std::endl;
        }
    }

private:
    std::string filePath_;
};


void print(LogCommand& command, const std::string& message) {
    command.print(message);
}


int main() {
    ConsoleLogCommand consoleLog;
    FileLogCommand fileLog("log.txt");

    std::string message = "Hello, this is a log message!";

    print(consoleLog, message); 
    print(fileLog, message);    

    return 0;
}


