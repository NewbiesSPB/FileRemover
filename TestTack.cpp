#include "TestTack.h"

int main()
{

	std::ifstream jsonFile("D:\\TestTack\\setting.json");
	if (!jsonFile.is_open()) {
		std::cout << "File is not found";
		return 0;
	}
	nlohmann::json dict;
	jsonFile >> dict;
	std::string pathToDelete = dict["pathToDelete"];
	std::cout << pathToDelete << std::endl;
	
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
