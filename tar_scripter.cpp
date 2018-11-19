#include "command.hpp"
#include <sstream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void make_text_files();

command cmd;
vector<string> terminal_feedback, error_list;

int main(int argc, char *argv[]) {
	
	return 0;
}

void make_text_files() {
	cmd.toggle_debug();
	for (int i = 0; i < 100; i++) {
		std::stringstream ss;
		ss << i;
		string s_to_i = ss.str();
		string filename;
		if (i < 10) {
			filename = "text0" + s_to_i + ".txt";
		}
		else
			filename = "text" + s_to_i + ".txt";
		string term_cmd = "touch " + filename;
		cmd.exec(term_cmd.c_str(), terminal_feedback, error_list);
		std::ofstream fout;
		fout.open(filename.c_str());
		if (fout.is_open()) {
			fout << "words and stuff" << endl;
			fout.close();
		}
		else
			cout << "fout.open() failed!" << endl;
	}
}