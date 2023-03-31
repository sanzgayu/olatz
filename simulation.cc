#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "constantes.h"
#include "message.h"
#include "particule.h"
#include "robot.h"
#include "simulation.h"

using namespace std;

std::vector<Particule> vec_particules;
std::vector<std::vector<Robot>> vec_robots(3);

/////////////////////////////////////////////////////////////////////////
void Simulation::lecture_fichier(char *nom_fichier)
{
    string line;
    ifstream fichier(nom_fichier);
    if (!fichier.fail())
    {
        while (getline(fichier >> ws, line))
        {
            if (line[0] == '#')
                continue;

            decodage_ligne(line);
        }
        EXIT_SUCCESS; // a  changer par ce que veux Bulic dans message
    }
    else
        exit(EXIT_FAILURE);
}
/////////////////////////////////////////////////////////////////////////

void Simulation::decodage_ligne(string line)
{

    istringstream donnee(line);

    enum Etat_lecture
    {
        NBP,
        PARTICULE,
        SPATIAL,
        REPARATEUR,
        NEUTRALISEUR,
        FIN
    };

    double x(0), y(0), c(0), a1(0), c_n(0);
    int nbNr(0), nbNs(0), nbNd(0), nbRr(0), nbRs(0), k_update_panne(0), nbP(0);
    bool panne(0);
    static int etat(NBP);
    static int i(0), total_nbP(0), total_reparateur(0), total_neutraliseur(0),
        nbUpdate(0);

    switch (etat)
    {

    case NBP:
    {
        if (!(donnee >> nbP))
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            i = 0;
            total_nbP = nbP;
            etat = PARTICULE;
        }

        break;
    }

    case PARTICULE:
    {
        if (!(donnee >> x >> y >> c))
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            ++i;
            Particule part(x, y, c);
            vec_particules.push_back(part);
        }
        if (i == total_nbP)
        {
            i = 0;
            etat = SPATIAL;
        }
        break;
    }

    case SPATIAL:
    {
        if (!(donnee >> x >> y >> nbUpdate >> nbNr >> nbNs >> nbNd >> nbRr >> nbRs))
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            Spatial robot_spatial(x, y, 1, nbUpdate, nbNr, nbNs, nbNd, nbRr, nbRs);
            vec_robots[0].push_back(robot_spatial);
            total_reparateur = nbRs;
            total_neutraliseur = nbNs;
            etat = REPARATEUR;
        }
        break;
    }
    case REPARATEUR:
    {
        if (!(donnee >> x >> y))
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            ++i;
            Reparateur rep(x, y, 2);
            vec_robots[1].push_back(rep);
        }
        if (i == total_reparateur)
        {
            etat = NEUTRALISEUR;
            i = 0;
        }
        break;
    }
    case NEUTRALISEUR:
    {
        if (!(donnee >> x >> y >> a1 >> c_n >> panne >> k_update_panne))
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            ++i;
            Neutraliseur neutra(x, y, 3, a1, c_n, panne, k_update_panne, nbUpdate);
            vec_robots[2].push_back(neutra);
        }
        if (i == total_neutraliseur)
        {
            etat = FIN;
            i = 0;
        }
        break;
    case FIN:
    {
        message::success();
    }
    }
    }
}
void Simulation::collision_particule_robot()
{
    // comparacion particule spaztial
    Robot robot_spatial = vec_robots[0][0];
    Cercle c_spatial = robot_spatial.get_cercle(robot_spatial);
    for (size_t i(0); i < vec_particules.size(); i++)
    {

        Particule p = vec_particules[i];
        Carre c = p.get_carre(p);
        if (collision_carre_cercle(c, c_spatial, false))
        {
            cout << message::particle_robot_superposition(
                c.centre.x, c.centre.y, c.cote, c_spatial.centre.x, c_spatial.centre.y,
                c_spatial.rayon);
            exit(EXIT_FAILURE);
        }
    }
    // collision repa//
    for (size_t i(0); i < vec_particules.size(); i++)
    {
        for (size_t j(0); j < vec_robots[1].size(); j++)
        {

            Particule p = vec_particules[i];
            Robot rob = vec_robots[1][j];

            Carre c1 = p.get_carre(p);
            Cercle c2 = rob.get_cercle(rob);
            if (collision_carre_cercle(c1, c2, false))
            {
                cout << message::particle_robot_superposition(c1.centre.x, c1.centre.y,
                                                              c1.cote, c2.centre.x,
                                                              c2.centre.y, c2.rayon);
                exit(EXIT_FAILURE);
            }
        }
    }
    // collision neutra//
    for (size_t i(0); i < vec_particules.size(); i++)
    {
        for (size_t j(0); j < vec_robots[2].size(); j++)
        {

            Particule p = vec_particules[i];
            Robot rob = vec_robots[1][j];

            Carre c1 = p.get_carre(p);
            Cercle c2 = rob.get_cercle(rob);
            if (collision_carre_cercle(c1, c2, false))
            {
                cout << message::particle_robot_superposition(c1.centre.x, c1.centre.y,
                                                              c1.cote, c2.centre.x,
                                                              c2.centre.y, c2.rayon);
                exit(EXIT_FAILURE);
            }
        }
    }
}
