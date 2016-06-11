#include <Windows.h>
#include <list>
#include <string>
#include <sstream>
using namespace std;

class CStringUtil{
public:
	static list<string> split(const string &str, char delim);
};

list<string> CStringUtil::split(const string &str,char delim){
	list<string> ret;
	istringstream iss(str);
	string tmp;
	while(getline(iss, tmp, delim)) ret.push_back(tmp);
	return ret;
}

