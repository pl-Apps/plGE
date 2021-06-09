#include <string>
#include <sys/stat.h>

using namespace std;

bool exist(string filename) {
    struct stat buffer;   
    return (stat(filename.c_str(),&buffer) == 0);
}