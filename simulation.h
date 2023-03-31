
#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>
#include "shape.h"
#include "particule.h"
#include "robot.h"


void lecture_fichier (char * nom_fichier);



class Simulation{
	
private:
	std::vector <Particule> vec_particules;
	std::vector <std::vector < Robot >> vec_robots;


public:
	void lecture_fichier (char * nom_fichier);
	void decodage_ligne(std::string line);
	void collision_particule_robot();
		
		
		
	/*void lecture_particules(std::ifstream& donnee, std::vector<Particule*>& vec_particules);
	void lecture_spatial(std::ifstream& donnee, Spatial& spatial, 
						std::vector<Particule*>& vec_particules,
						std::vector<Reparateur*>& vec_reparateurs,
						std::vector<Neutraliseur*>& vec_neutralisateurs);
	void decodage_ligne(std::ifstream& donnee, Spatial& spatial, 
					std::vector<Particule*>& vec_particules,
					std::vector<Neutraliseur*>& vec_neutralisateurs,
					std::vector<Reparateur*>& vec_reparateurs);
	*/
};

#endif
