#include "shape.h"
#include <vector>

#ifndef PARTICULE_H
#define PARTICULE_H


class Particule {
	
private:
  Carre particule_;
 static std::vector<Carre> ensemble_particules;

public:

	Particule(double x, double y, double d_particle);
	void particules_superposition(Carre c1, Carre c2);
	void collision_particule(Carre p);
	void domaine_particule(Carre carre);
	Carre get_carre(Particule p);
};


#endif

