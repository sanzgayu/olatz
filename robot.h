#ifndef ROBOT_H
#define ROBOT_H

#include "shape.h"
#include "particule.h"
#include "constantes.h"
#include "message.h"
#include <vector>

class Robot {

protected: // ou private//
  Cercle robot_;
  static std::vector<std::vector<Cercle>> vect_robots;
  //collision_robot_particule();

public:
//	void collision_robot_particle(Carre carre, Cercle cercle);
	Robot(double x, double y, int r);
  Cercle get_cercle (Robot rob);
};

//////////////////////////////////////////////////////////////////////
class Reparateur : public Robot {

private: 
  S2d but;    

public:
	Reparateur(double x, double y, int r);
	void collision_repairers();
};

///////////////////////////////////////////////////////////////////////
class Neutraliseur : public Robot {

private:
  int nbNs; //
  int nbN;  //
  int a1;
  int c_n;
  bool panne;
  int nbUpdate;
  int k_update_panne;
  int max_update; //

public:
	Neutraliseur(double x, double y, int r, int a, int cn, int p,
                 int k_up_p,int nbupdate);
      
      
	void collision_neutralizers();
	void en_panne(double x, double y, int k_update, int nbupdate);
	/*void collision_robots(Cercle robot,std::vector<std::vector<Cercle>> vector_robots); */
};

///////////////////////////////////////////////////////////////////////
class Spatial : public Robot {
private:
  int nbUpdate;
  int nbNr;
  int nbNs;
  int nbNd;
  int nbRr;
  int nbRs;

public:
	Spatial(double x, double y, int r, int nbupdate, int nbnr, int nbns,
          int nbnd, int nbrr, int nbrs);
        
  void collision_spatial(Cercle spatial, std::vector<Particule>vec_p);      
	void domaine_spatial(Cercle cercle);
};


#endif
