#include <Game/Simulation.hpp>
#include <IO/System/EventLog.hpp>
#include <fstream>
#include <stdexcept>

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

		EventLog eventLog;
		Simulation simulation{eventLog, RANDOM_SEED};
		simulation.process(file);

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}
