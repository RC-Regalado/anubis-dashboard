#include <systemd/sd-daemon.h>
#include <iostream>

int main() {
    int state;
    if (sd_session_get_state("httpd", &state) >= 0) {
        std::cout << "Apache status: " << state << std::endl;
    } else {
        std::cout << "Unable to get Apache status." << std::endl;
    }
    return 0;
}

