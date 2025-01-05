#include <iostream>
#include <string>
#include "configfactory/nginx.hpp" // Assuming the C++ equivalent of configfactory is in this header

int main() {
    auto result = configfactory::nginx::get_config_https(
        "blog.ban.gy",
        "us1-1.edge.icbix.com",
        "1g",
        "12h"
    );

    if (result.second) {
        std::cerr << "Error: " << result.second << std::endl;
        return 1;
    }

    std::cout << result.first << std::endl;

    return 0;
}