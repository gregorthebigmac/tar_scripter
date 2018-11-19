#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int getdir (string dir, vector<string> &files);
bool is_tar(string filename);

int main() {
	string dir = string(".");
	vector<string> files = vector<string>();
	vector<string> list_of_tarballs;

	getdir(dir, files);
	for (unsigned int i = 0; i < files.size(); i++) {
		cout << "file [" << i << "] = " << files[i] << endl;
		if (is_tar(files[i]))
			list_of_tarballs.push_back(files[i]);
	}
	ofstream fout;
	fout.open("tard.sh");
	if (fout.is_open()) {
		cout << "creating script...";
		for (int i = 0; i < list_of_tarballs.size(); i++) {
			fout << "tar -xvf " << list_of_tarballs[i] << " && rm -rf " << list_of_tarballs[i];
			int x = i + 1;
			if (x < list_of_tarballs.size())
				fout << " &&\\" << endl;
			else
				fout << endl;
		}
		fout.close();
		cout << "[done]" << endl;
	}
	else
		cout << "fout.open() failed!" << endl;
	return 0;
}

int getdir(string dir, vector<string> &files) {
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}
	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

bool is_tar(string filename) {
	size_t found = filename.find(".tar");
	if (found != string::npos)
		return true;
	else
		return false;
}