#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

namespace node {
    namespace config {

        std::pair<std::string, std::uint8_t> get_config() {
            // Create a property tree object
            boost::property_tree::ptree pt;

            try {
                // Load the INI file into the property tree
                boost::property_tree::ini_parser::read_ini("../../config/local.ini", pt);

                // Access values from the property tree
                std::string key1 = pt.get<std::string>("Section1.key1");
                std::string key2 = pt.get<std::string>("Section1.key2");
                std::string key3 = pt.get<std::string>("Section2.key3");

                char* test = new char[16];

                return {key1, 0};

            } catch (const boost::property_tree::ini_parser_error &e) {
                std::cerr << "Error reading INI file: " << e.what() << std::endl;
                return {"", 1};
            } catch (const boost::property_tree::ptree_error &e) {
                std::cerr << "Error accessing property tree: " << e.what() << std::endl;
                return {"", 1};
            }

            return {"", 0};
        }

    }
}