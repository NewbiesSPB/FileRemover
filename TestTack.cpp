#include "TestTack.h"


Remover::Remover() {};
	Remover::Remover(std::string& path) : Remover() {
		OpenJson(path);
	}
	bool Remover::OpenJson(std::string path) {

		std::ifstream jsonFile(path);

		if(!jsonFile.is_open())
		{
			std::cerr << "Json file is not found";
			return false;
		}

		jsonFile >> dict;
		jsonFile.close();
		filesToDelete.insert(std::make_pair(dict["paths"]["pathToDelete1"], dict["paths"]["lifetimeInDays1"]));
		filesToDelete.insert(std::make_pair(dict["paths"]["pathToDelete2"], dict["paths"]["lifetimeInDays2"]));
		filesToDelete.insert(std::make_pair(dict["paths"]["pathToDelete3"], dict["paths"]["lifetimeInDays3"]));
		return true;
	}

	bool Remover::CheckPathToDelete(std::string pathToDel)
	{
		if (!std::filesystem::exists(pathToDel))
		{
			std::cerr << "The file on path "<< pathToDel <<" was not found" << std::endl;
			return false;
		}
		return true;
		

	}


	bool Remover::CheckLifeTime(std::string pathToDel, int day)
	{
		if (!CheckPathToDelete(pathToDel))
			return false;

		if (day <= 0)
		{
			std::cerr << "The interval for the path"<<pathToDel << "cannot be negative or equal to 0";
			return false;
		}

		auto lastWrite = std::filesystem::last_write_time(pathToDel);
		auto lifetime = lastWrite + std::chrono::days(day);
		auto now = std::chrono::file_clock::now();
		auto difference = std::chrono::duration_cast<std::chrono::days>(lifetime - now);
		if (difference != std::chrono::days(0))
		{
			return false;
		}
		
		return true;

	}

	void Remover::FailDelete()
	{
		for (auto& it: filesToDelete)
		{
			if (CheckLifeTime(it.first, it.second))
			{
			std::cout << std::filesystem::path(it.first).extension();
				std::cout << it.first;
				//std::filesystem::remove(firstPathToDelete);
			}

		}
	}

int main()
{
	std::string path = "D:\\Test\\FileRemover\\setting.json";
	Remover remover(path);

	remover.FailDelete();

	return 0;
}
