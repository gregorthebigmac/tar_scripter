#ifndef GET_DIR_FILES_HPP
#define GET_DIR_FILES_HPP

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

class get_dir_files {
public:
	get_dir_files() {
		m_files = std::vector<std::string>();
		m_dir = std::string(".");
	}
	~get_dir_files();

	std::vector<std::string> get_files();

private:
	int make_dir_file_list (std::string dir, std::vector<std::string> &files);
	std::string m_dir;
	std::vector<std::string> m_files;
	
};

int get_dir_files::make_dir_file_list(std::string dir, std::vector<std::string> &files) {
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL) {
		std::cout << "Error(" << errno << ") opening " << dir << std::endl;
		return errno;
	}
	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(std::string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

std::vector<std::string> get_dir_files::get_files() {
	if (make_dir_file_list(m_dir, m_files) == 0) {
		return m_files;
	}
}

/*
int main() {
	getdir(dir, files);
	for (unsigned int i = 0; i < files.size(); i++) {
		std::cout << files[i] << std::endl;
	}
	return 0;
}
*/

#endif