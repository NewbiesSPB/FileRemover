#include "TestTack.h"


Remover::Remover() : scan_interval(10), path(" ") {};
	//Remover::Remover(std::string& _path) : Remover() {
	//	path = _path;
	//	Scanning(path);
	//}
	bool Remover::Scanning(std::string path) { // Считывает json файл

		std::ifstream jsonFile(path);

		if(!jsonFile.is_open())
		{
			std::cerr << "Json file is not found";
			return false;
		}


		try
		{
		jsonFile >> dict; 
		filesToDelete.insert(std::make_pair(dict["paths"]["pathToDelete1"], dict["paths"]["lifetimeInDays1"]));
		filesToDelete.insert(std::make_pair(dict["paths"]["pathToDelete2"], dict["paths"]["lifetimeInDays2"]));
		filesToDelete.insert(std::make_pair(dict["paths"]["pathToDelete3"], dict["paths"]["lifetimeInDays3"]));

		}
		catch (const std::exception&)
		{
			std::cerr << "the jsonFile was recorded incorrectly " << std::endl; 
			jsonFile.close();
			return false;
		}

		try
		{
		scan_interval = dict["scan_interval"];
		}
		catch (const std::exception& )
		{
			std::cerr << "The interval for scanning must be a number " << std::endl;
			jsonFile.close();
			return false;
		}

		jsonFile.close();
		return true;
	}

	bool Remover::CheckPathToDelete(std::string pathToDel) //Проверка существования файла
	{
		if (!std::filesystem::exists(pathToDel))
		{
			std::cerr << "The file on path "<< pathToDel <<" was not found" << std::endl;
			return false;
		}
		return true;
		

	}


	bool Remover::CheckLifeTime(std::string pathToDel, int day) //Проверка время жизни файла
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

	void Remover::FailDelete() //Удаление файла(ов)
	{
		for (auto& it : filesToDelete) 
		{
		/*
			for (char ch : it.first) Проверка символов
			{
				if
			}
		*/

			if (CheckLifeTime(it.first, it.second))
			{
				std::filesystem::remove(it.first);
				std::cout << "The file on the path " << it.first << " has been succexfully deleted" << std::endl;
			}
			else
			{
				std::cout << "The file on path " << it.first << " has not been deleted" << std::endl;
			}

		}
	}

	void Remover::Sleep()
	{
		std::this_thread::sleep_for(std::chrono::seconds(scan_interval));
	}
int main()
{
	std::string path = "D:\\Test\\FileRemover\\setting.json";
	Remover remover;
	while (1)
	{
		if (remover.Scanning(path)) {
		remover.FailDelete();
		}
		remover.Sleep();

	}

	return 0;

	/*
	* Возможное решение для маски
	* 
			std::cout << std::endl << std::filesystem::path(it.first).extension() << std::endl;
	std::filesystem::path path("C:/Images");
	std::filesystem::directory_iterator end_itr;
	for (std::filesystem::directory_iterator itr(path); itr != end_itr; ++itr) {
		if (itr->path().extension() == ".jpg") {
			std::cout << itr->path() << std::endl;
		}
	}
	*/


}
