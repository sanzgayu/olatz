#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "message.h"
#include "particule.h"
#include "shape.h"
#include "constantes.h"


using namespace std;

vector<Carre> Particule::ensemble_particules;


  // constructeur://
Particule::Particule(double x, double y, double d_particle) {
	
	particule_.centre.x = x;
  particule_.centre.y = y;
  particule_.cote = d_particle;
   
  domaine_particule(particule_);
  collision_particule(particule_);  
  }

void Particule::particules_superposition(Carre c1, Carre c2) {

    if (collision_carre_carre(c1,c2, true)) {
      cout << message::particle_superposition(c1.centre.x, c1.centre.y,
                                              c2.centre.x, c2.centre.y);
      std ::exit(EXIT_FAILURE);
    }
  }


void Particule::domaine_particule(Carre carre) {
	  
    if (carre.centre.x + (carre.cote / 2) > dmax or
        carre.centre.x - (carre.cote / 2) < -dmax or
        carre.centre.y + (carre.cote / 2) > dmax or
        carre.centre.y - (carre.cote / 2) < -dmax) {
      cout << message::particle_outside(carre.centre.x, carre.centre.y,
                                        carre.cote);
      std ::exit(EXIT_FAILURE);
    }
  }
  
void Particule::collision_particule(Carre p){
	  if (ensemble_particules.size() == 0){
		  ensemble_particules.push_back(p);
	  }
	  else{
		  for (size_t i(0); i<ensemble_particules.size(); i++){
			  Carre p_compare;
			  p_compare = ensemble_particules[i];
			  particules_superposition(p, p_compare);
		  }
		  ensemble_particules.push_back(p);
	  } 
  }

Carre Particule:: get_carre(Particule p) {
 return p.particule_;
}
 

