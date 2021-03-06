#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <string>
#include "vec3.h"

using std::string;

class CelestialBody
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    string name;


    CelestialBody(vec3 position, vec3 velocity, double mass, string name);
    CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass, string name);
    void resetForce();
};

#endif // CELESTIALBODY_H
