#include <iostream>
#include <chrono>
#include "Kraken.h"

int main(int argc, char* argv[])
{
	Kraken client;
	while (true)
	{
		std::cout << client.publicMethod("Ticker?pair=DOGEUSD", "") << std::endl;
		Sleep(1000);
	}

}