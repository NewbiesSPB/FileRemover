#ifndef REMOVER_HPP
#define REMOVER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include "nlohmann/json.hpp"
#include <map>
#include <thread>


class Remover
{
public:
	Remover();
	Remover(std::string& path);
	bool OpenJson(std::string path);

	bool CheckPathToDelete(std::string pathToDel);

	bool Scanning(std::string pathToDel, int day);

	void FailDelete();

private:
	nlohmann::json dict;
	std::map <std::string, int>filesToDelete;
};


#endif 