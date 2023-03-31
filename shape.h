/*on met struct et proto des fonct */
#ifndef SHAPE_H
#define SHAPE_H


constexpr double epsil_zero (0.125);

struct S2d {
	double x = 0.0;
	double y = 0.0;
};

struct Cercle {
	double rayon;
	S2d centre;
	};

struct Carre {
	double cote;
	S2d centre;
};
double distance (S2d point1, S2d point2);
bool collision_cercle_cercle (Cercle c1, Cercle c2, bool epsil_);
bool collision_carre_carre(Carre c1, Carre c2, bool epsil_);
bool collision_carre_cercle (Carre carre,Cercle cercle, bool epsil_);


#endif
