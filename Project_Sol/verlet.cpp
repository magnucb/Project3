#include "verlet.h"
#include "solarsystem.h"4


Verlet::Verlet(double dt) :
    m_dt(dt)
{

}

void Verlet::integrateOneStep(SolarSystem &system)
{
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies()) {
        //vel_now = body.velocity;
        //pos_now = body.position;


        body.position += body.velocity*m_dt ;
        body.velocity += body.force / body.mass * m_dt ;
    }
}
