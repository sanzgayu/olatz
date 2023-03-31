
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "shape.h"

using namespace std;



double distance (S2d point1, S2d point2){
	double x1 = point1.x;
	double y1 = point1.y;
	double x2 = point2.x;
	double y2 = point2.y;
	
	 
	double dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
	return dist;
	
}

bool collision_cercle_cercle (Cercle c1, Cercle c2, bool epsil_ = false) {
	
	double r1 = c1.rayon;
	double r2 = c2.rayon;
	S2d centre1 = c1.centre;
	S2d centre2 = c2.centre;
	double D;
	double epsil_1(epsil_zero);

	
	if (epsil_==true) {
		epsil_1 = 0;
	}
	
	D = distance(centre1,centre2);
	
	if (D<(r1+r2) + epsil_1) {
	return true;
	}	
	else {
	return false;
	}
}


bool collision_carre_carre(Carre c1, Carre c2,bool epsil_= false){
	double d1 = c1.cote;
	double d2 = c2.cote; 
	double x1 = c1.centre.x;
	double y1 = c1.centre.y;
	double x2 = c2.centre.x;
	double y2 = c2.centre.y;
	
	double absolux = abs(x2-x1);
	double absoluy = abs(y2-y1);
	
	double epsil_1(epsil_zero);

	if (epsil_==true) {
		epsil_1 = 0;
	}
	

	if ((absolux < d1/2 + d2/2 + epsil_1) and (absoluy < d1/2 + d2/2 + epsil_1)){
		 
	return true;
	 }
	else {
	return false;
    }
}
	

bool collision_carre_cercle (Carre carre,Cercle cercle,bool epsil_= false){
	double x1 = carre.centre.x;
	double y1 = carre.centre.y;
	double d1 = carre.cote;
	
	double x2 = cercle.centre.x;
	double y2 = cercle.centre.y;
	double r2 = cercle.rayon;
	
	double absolux = abs(x2-x1);
	double absoluy = abs(y2-y1);
	double L = sqrt((absolux-d1/2)*(absolux-d1/2) + 
	(absoluy-d1/2)*(absoluy-d1/2));
	
	double epsil_1(epsil_zero);

	
	if (epsil_==true) {
		epsil_1 = 0;
	}
	
	if (((absolux < d1/2 + r2 + epsil_1) and 
	(absoluy < d1/2 + r2 + epsil_1)) and 
	not((absolux > d1/2)and(absoluy > d1/2) and (L> r2 + epsil_1))) {
		
	return true;
	}
	else{
	return false;
	}
}	 
	




