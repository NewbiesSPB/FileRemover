#include "TestTack.h"


class Remover
{
public:
	Remover() : firstPathToDelete(""), secondPathToDelete(""), thirdPathToDelete(""), day(0) {};
	Remover(std::string& path) : Remover() {
		OpenJson(path);
	}
	bool OpenJson(std::string path) {

		std::ifstream jsonFile(path);

		if(!jsonFile.is_open())
		{
			std::cerr << "Json file is not found";
			return false;
		}

		jsonFile >> dict;
		jsonFile.close();
		return true;
	}

	bool CheckPathToDelete()
	{
		if (!std::filesystem::exists(dict["paths"]["pathToDelete1"]))
		{
			std::cerr << "File for Delete is not found";
			return false;
		}
		firstPathToDelete = dict["paths"]["pathToDelete1"];
		return true;
		

	}


	bool CheckLifeTime()
	{
		if (!CheckPathToDelete())
			return false;

		day = dict["lifetimeInDays"];
		if (day <= 0)
		{
			std::cerr << "The number of days cannot be negative";
			return false;
		}

		auto lastWrite = std::filesystem::last_write_time(firstPathToDelete);
		auto lifetime = lastWrite + std::chrono::days(day);
		auto now = std::chrono::file_clock::now();
		auto difference = std::chrono::duration_cast<std::chrono::days>(lifetime - now);
		if (difference != std::chrono::days(0))
		{
			return false;
		}
		
		std::cout << firstPathToDelete << std::endl << difference;
		return true;

	}

	void FailDelete()
	{
		if (CheckLifeTime())
		{
			std::cout << firstPathToDelete;
			std::filesystem::remove(firstPathToDelete);
		}
	}

private:
	nlohmann::json dict;
	std::string firstPathToDelete;
	std::string secondPathToDelete;
	std::string thirdPathToDelete;
	int day;
};

int main()
{
	std::string path = "D:\\Test\\FileRemover\\setting.json";
	Remover remover(path);
	remover.FailDelete();

	return 0;
}
