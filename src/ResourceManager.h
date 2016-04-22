#ifndef SRC_RESOURCEMANAGER_H_
#define SRC_RESOURCEMANAGER_H_

#include <string>

class ResourceManager {
public:
	static void setBinPath(std::string);
	std::string getResourcePath();
private:
	std::string goUpNDirs(std::string, int);
	static std::string binPath_;
};

#endif /* SRC_RESOURCEMANAGER_H_ */
