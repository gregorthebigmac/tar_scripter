#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <deque>

class command {
public:
    command();
    virtual ~command();
	
	void toggle_debug();	// toggles the state of m_debug
    void exec(const char *cmd, std::vector<std::string> &terminal_output, std::vector<std::string> &error_list);

private:
	bool m_debug;	// if true, realtime terminal output will be printed to screen as it happens. Otherwise, it goes to the vector, or is lost forever.
};

command::command() {}   // ctor
command::~command() {}  // dtor

void command::toggle_debug() {
	m_debug = !m_debug;
	std::cout << "debug = [" << m_debug << "]" << std::endl;
}

void command::exec(const char* cmd, std::vector<std::string> &terminal_output, std::vector<std::string> &error_list) {
    char buffer[128];
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        error_list.push_back("popen() failed!");
        if (m_debug)
            std::cout << "popen() failed!" << std::endl;
        throw::std::runtime_error("popen() failed!");
    }
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL) {
                std::string temp = buffer;
                terminal_output.push_back(temp);
                if (m_debug)
                    std::cout << temp;
            }
        }
    } catch (...) {
        pclose(pipe);
        error_list.push_back("fgets failed!");
        if (m_debug)
            std::cout << "fgets failed!" << std::endl;
        throw;
    }
    pclose(pipe);
}

#endif // COMMAND_HPP
