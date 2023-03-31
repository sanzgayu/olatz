#include <iostream>
#include <cstdlib>

#include "simulation.h"

int main(int argc, char * argv[])
{
	if(argc != 2) {
		exit(EXIT_FAILURE);
	}
	Simulation simulation;
	simulation.lecture_fichier(argv[1]);
	return EXIT_SUCCESS;
}
