#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "message.h"
#include "robot.h"
#include "shape.h"
#include "particule.h"
#include "constantes.h"

using namespace std;

vector<vector<Cercle>>Robot::vect_robots(3);

Robot :: Robot(double x, double y,int r) {
	robot_.centre.x = x;
    robot_.centre.y = y;
    if (r == 1) {
		robot_.rayon = r_spatial;
	}
    if (r == 2) {
		robot_.rayon = r_reparateur;
	}
    if (r == 3) {
		robot_.rayon = r_neutraliseur;
	}
}

Cercle Robot:: get_cercle (Robot rob) {
	return rob.robot_;
}

Spatial :: Spatial(double x, double y, int r, int nbUpdate, int nbNr, int nbNs,
          int nbNd, int nbRr, int nbRs)
      : Robot(x, y,1){
			domaine_spatial(robot_);
			vect_robots[0].push_back(robot_);
		  }

void Spatial :: domaine_spatial(Cercle cercle) {

    if ((cercle.centre.x - cercle.rayon < - dmax) or
        (cercle.centre.x + cercle.rayon > dmax) or
        (cercle.centre.y - cercle.rayon < -dmax) or
        (cercle.centre.y + cercle.rayon > dmax)) {
      cout << message::spatial_robot_ouside(cercle.centre.x, cercle.centre.y);
      exit(EXIT_FAILURE);
    }
}


Reparateur::Reparateur(double x, double y, int r) 
	: Robot (x,y,2) {
		//appel colision_repairers
		collision_repairers();
		}


void Reparateur::collision_repairers() {
	if(vect_robots[1].size()== 0){
		vect_robots[1].push_back(robot_);
	}else

	for (int i(0);vect_robots[1].size(); i++) {
		
		Cercle c1 = vect_robots[1][i];
		if (collision_cercle_cercle(c1,robot_,true)) {
			cout << message::repairers_superposition(c1.centre.x, c1.centre.y,
                                               robot_.centre.x, robot_.centre.y);
			exit(EXIT_FAILURE);
			}
	}
	vect_robots[1].push_back(robot_);

}

Neutraliseur::Neutraliseur(double x, double y, int r, int a, int cn, int p,
                 int k_up_p,int nbupdate)
      : Robot(x, y, 3) {
		  en_panne(x, y, k_up_p, nbupdate);
		  collision_neutralizers();
		  
		  }

void Neutraliseur::collision_neutralizers() {
	if(vect_robots[2].size()== 0){
		vect_robots[2].push_back(robot_);
	}else {
		for (int j(0);vect_robots[2].size(); j++) {
			Cercle c2 = vect_robots[2][j];
			if (collision_cercle_cercle(robot_,c2,true)) {
			cout << message::neutralizers_superposition(robot_.centre.x, robot_.centre.y,
													c2.centre.x, c2.centre.y);
			exit(EXIT_FAILURE);
			}
		}
		for (int i(0);vect_robots[1].size(); i++) {
			Cercle c1 = vect_robots[1][i];
			if (collision_cercle_cercle(robot_,c1,true)) {
			cout << message::neutralizers_superposition(robot_.centre.x, robot_.centre.y,
													c1.centre.x, c1.centre.y);
			exit(EXIT_FAILURE);
			}
		}
	vect_robots[2].push_back(robot_);
	}
}

void Neutraliseur::en_panne(double x, double y, int k_update, int nbupdate) {
	
    if (k_update > nbupdate) {
      cout << message::invalid_k_update(x, y, k_update,
                                        nbupdate);
      std ::exit(EXIT_FAILURE);
    }
}
