#include "ResourceManager.h"
#include <string>

std::string ResourceManager::binPath_;

void ResourceManager::setBinPath(std::string path) {
	binPath_ = path;
	return;
}

std::string ResourceManager::getResourcePath() {
	return goUpNDirs(binPath_, 2) + "/res";
}

std::string ResourceManager::goUpNDirs(std::string path, int n) {
	if (path.at(path.length() - 1) == '/') {
		path = path.substr(0, path.size() - 1);
	}

	int i;
	int slashCount = 0;
	for (i = path.size() - 1; i >= 0; i--) {
		if (path.at(i) == '/' || path.at(i) == '\\') {
			slashCount++;
		}

		if (slashCount == n) {
			break;
		}
	}

	return path.substr(0, i);
}
