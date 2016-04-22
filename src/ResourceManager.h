#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>

class ResourceManager {
public:
	static void setBinPath(std::string);
	std::string getResourcePath();
private:
	std::string goUpNDirs(std::string, int);
	static std::string binPath_;
};

#endif
