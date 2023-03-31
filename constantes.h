#ifndef CONSTANTES_H
#define CONSTANTES_H
#include "shape.h"


enum Etat_neutraliseur{EN_PANNE, EN_MARCHE};

constexpr short unsigned maxF(25);

constexpr double dmax(128.);
constexpr double delta_t(0.125);
constexpr double r_spatial (16.);
constexpr double r_reparateur(2.);
constexpr double r_neutraliseur(4.);
constexpr double vtran_max(4.);
constexpr double vrot_max(0.125);
constexpr double epsil_alignement(0.01);

constexpr double desintegration_rate(0.0002);
constexpr double risk_factor(3.);
constexpr double d_particule_min(8*epsil_zero);

constexpr unsigned max_update(600);
constexpr unsigned modulo_update(100);


#endif
