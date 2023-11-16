#include <vector>
#include <string>

std::vector<std::string> splitString(const char* str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    
    while (*str) {
        if (*str == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += *str;
        }

        str++;
    }
    
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}