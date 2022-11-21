#include "console.hpp"

void Console::Info(const std::string& msg) {
    std::cout << "[INFO] " << msg << "\n";
}
void Console::Erro(const std::string& msg) {
    std::cerr << "[ERRO] " << msg << "\n";
    exit(EXIT_FAILURE);
}
void Console::Warn(const std::string& msg) {
    std::cerr << "[WARN] " << msg << "\n";
}