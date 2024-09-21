#include "TestTack.h"

nlohmann::json OpenJson(std::string path) {

	nlohmann::json dict;

	std::ifstream jsonFile(path);
	if (!jsonFile.is_open()) {
		std::cout << "File is not found";
		return dict;
	}
	jsonFile >> dict;
	jsonFile.close();
	return dict;
}


int main()
{
	
	nlohmann::json dict = OpenJson("D:\\TestTack\\setting.json");
	if (dict.empty())
	{
		std::cerr << "";
		return 0;
	}


	std::string pathToDelete = dict["pathToDelete"];
	
	int day = dict["lifetimeInDays"];

	auto lastWrite = std::filesystem::last_write_time(pathToDelete);
	auto lifetime = lastWrite + std::chrono::days(day);
	auto now = std::chrono::file_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::days>(lifetime - now);
	if (difference == std::chrono::days(0)){
		if (std::filesystem::remove(pathToDelete))
			std::cout << "successfully \n";
	}


	std::cout << difference;

	

	//if (std::filesystem::remove(pathToDelete))
		//std::cout << "successfully \n";

		



	return 0;
}
