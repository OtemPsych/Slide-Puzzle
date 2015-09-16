#include "GameState.h"

#include <iostream>

int main()
{
	srand(static_cast<unsigned>(time(0)));
	
	try {
		GameState gameState;
		gameState.run();
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}