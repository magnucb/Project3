#define _USE_MATH_DEFINES
#include "verlet.h"
#include "solarsystem.h"
#include <math.h>


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

        vec3 acc = body.force / body.mass;
        body.position += body.velocity * m_dt + acc * m_dt*m_dt/2.0;

        body.resetForce();
        double m_G = 4*M_PI*M_PI;
        //system.calculateForcesAndEnergy(); //This slow piece of shit is a pitfall!
        for(CelestialBody &body2 : system.bodies()) {
            vec3 deltaRVector = body.position - body2.position;
            double dr = deltaRVector.length();
            if (dr > 0) {
                // Calculate the force here
                body.force += (-m_G*body.mass*body2.mass*deltaRVector)/(dr*dr*dr);
            }
        }

        vec3 acc_next = body.force / body.mass;
        body.velocity += (acc + acc_next)* m_dt/2.0 ;
    }
}
