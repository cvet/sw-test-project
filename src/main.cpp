#include <Game/Simulation.hpp>
#include <IO/System/EventLog.hpp>
#include <fstream>
#include <stdexcept>
#include <string>

constexpr uint32_t RANDOM_SEED = 12345;

int main(int argc, char** argv)
{
	using namespace sw;

	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Error: No file specified in command line argument");
		}

		std::ifstream file(argv[1]);

		if (!file)
		{
			throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
		}

		std::cout << "Processing file: " << argv[1] << '\n';

		std::cout << "Enable debug mode?\n";
		std::cout << "1. Yes (default)\n";
		std::cout << "2. No\n";
		std::cout << ": ";
		std::string input;
		std::getline(std::cin, input);
		int32_t debugMode = !input.empty() ? std::stoi(input) : 1;

		EventLog eventLog;
		Simulation simulation{eventLog, RANDOM_SEED, debugMode != 2};
		simulation.process(file);

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}
