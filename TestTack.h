#ifndef REMOVER_HPP
#define REMOVER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include "nlohmann/json.hpp"
#include <map>


class Remover
{
public:
	Remover();
	Remover(std::string& path);
	bool OpenJson(std::string path);

	bool CheckPathToDelete(std::string pathToDel);


	bool CheckLifeTime(std::string pathToDel, int daysToDel);

	void FailDelete();

private:
	nlohmann::json dict;
	std::map <std::string, int>filesToDelete;
};


#endif 