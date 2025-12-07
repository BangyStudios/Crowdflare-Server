#include <iostream>
#include <string>
#include "configfactory/nginx.hpp"
#include "node/config.hpp"

int main() {
    std::pair config_nginx = configfactory::nginx::get_config_https(
        "blog.ban.gy",
        "us1-1.edge.icbix.com",
        "1g",
        "12h"
    );

    if (config_nginx.second) {
        return 1;
        std::cerr << "Error: " << config_nginx.second << std::endl;
    }

    std::cout << config_nginx.first << std::endl;

    std::pair config_local = node::config::get_config();

    std::printf("config_local: %s\n", config_local.first.c_str());

    return 0;
}