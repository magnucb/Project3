#define _USE_MATH_DEFINES
#include "solarsystem.h"
#include <cmath>
#include <iostream>
using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass, string name) {
    m_bodies.push_back( CelestialBody(position, velocity, mass, name) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();
    double m_G = 4*M_PI*M_PI;
    double angconst = 3.0/pow(63197.8,2); // 3 / c**2, [c] = AU/yr

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            vec3 deltaVVector = body1.velocity - body2.velocity;
            double l2 = angularMomentum(deltaRVector, deltaVVector).lengthSquared();
            // Calculate the force and potential energy here
            vec3 Force = (-m_G*body1.mass*body2.mass*deltaRVector)*(1 + angconst*l2/(dr*dr))/(dr*dr*dr);
            body1.force += Force;
            body2.force -= Force;
            m_potentialEnergy -= m_G*body1.mass*body2.mass/dr;
        }
        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
    }
}

int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    for(CelestialBody &body : m_bodies) {
        m_file << body.name << " " << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}

vec3 SolarSystem::angularMomentum(vec3 position, vec3 velocity) const
{
    return position.cross(velocity);//m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
