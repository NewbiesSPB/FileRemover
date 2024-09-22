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


	bool Remover::Scanning(std::string pathToDel, int day)
	{
		if (!CheckPathToDelete(pathToDel))
			return false;

		if (day <= 0)
		{
			std::cerr << "The interval for the path "<<pathToDel << " cannot be negative or equal to 0";
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
		for (auto& it : filesToDelete)
		{
		/*
			for (char ch : it.first) Проверка символов
			{
				if
			}
		*/

			if (Scanning(it.first, it.second))
			{
			std::cout << std::endl << std::filesystem::path(it.first).extension() << std::endl;
				std::filesystem::remove(it.first);
			}
			else
			{
				std::cout << "The file on path " << it.first << " has not been deleted" << std::endl;
			}

		}
	}
int main()
{
	std::string path = "D:\\Test\\FileRemover\\setting.json";
	Remover remover(path);
	while (1)
	{
	remover.FailDelete();
	std::this_thread::sleep_for(std::chrono::seconds(10));

	}

	return 0;

	/*
	* Возможное решение для маски
	* 
	std::filesystem::path path("C:/Images");
	std::filesystem::directory_iterator end_itr;
	for (std::filesystem::directory_iterator itr(path); itr != end_itr; ++itr) {
		if (itr->path().extension() == ".jpg") {
			std::cout << itr->path() << std::endl;
		}
	}
	*/


}
