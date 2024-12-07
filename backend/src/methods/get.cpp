#include "get.hpp"
#include "../tools/utils.hpp"
#include <iostream>
#include <string>

using namespace methods;

get_task::get_task(std::string resource) : resource(resource) {}

void get_task::execute() { debug("GET"); }
