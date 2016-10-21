#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
#include <string>

using namespace std;

int main(int numArguments, char **arguments)
{
    int numTimesteps = 1000;
    string integrationmethod = "euler";
    if (numArguments >= 2) {
        numTimesteps = atoi(arguments[1]);
    }
    if (numArguments >= 3) {
        integrationmethod = string(arguments[2]);
    }
    cout << "Using " << integrationmethod << " method w/ " << numTimesteps << " time steps." << endl;

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, string("Sun"));

    // We don't need to store the reference, but just call the function without a left hand side
    CelestialBody &earth = solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 0.000003003, string("Earth") );
    /*
    CelestialBody &mercury = solarSystem.createCelestialBody( vec3(0.39, 0, 0),  vec3(0, 2*M_PI*0.39/0.240846, 0), 0.000002447, string("Mercury"));
    CelestialBody &venus = solarSystem.createCelestialBody(   vec3(0.728, 0, 0), vec3(0, 2*M_PI*0.728/0.61521, 0), 0.000002447, string("Venus"));
    CelestialBody &mars = solarSystem.createCelestialBody(    vec3(1.524, 0, 0), vec3(0, 2*M_PI*1.524/1.88089, 0), 3.213e-7, string("Mars"));
    CelestialBody &jupiter = solarSystem.createCelestialBody( vec3(5.203, 0, 0), vec3(0, 2*M_PI*5.203/11.8653, 0), 0.0009543, string("Jupiter"));
    CelestialBody &saturn = solarSystem.createCelestialBody(  vec3(9.582, 0, 0), vec3(0, 2*M_PI*9.582/29.46, 0),   0.0002857, string("Saturn"));
    CelestialBody &uranus = solarSystem.createCelestialBody(  vec3(19.2, 0, 0),  vec3(0, 2*M_PI*19.20/84.04, 0),   0.00004365, string("Uranus"));
    CelestialBody &neptune = solarSystem.createCelestialBody( vec3(30.05, 0, 0), vec3(0, 2*M_PI*30.05/164.8, 0),   0.0009543, string("Neptune"));
    CelestialBody &pluto = solarSystem.createCelestialBody(   vec3(39.48, 0, 0), vec3(0, 2*M_PI*39.48/248.1, 0),   0.0009543, string("Pluto"));
    */
    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of "<< body.name <<" begins at " << body.position << "AU with velocity " << body.velocity << "AU/yr "<< endl;
    }
    string bodies_string;
    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i];
        bodies_string.append(body.name);
    }
    double dt = 0.001;

    if (string(integrationmethod) == string("euler")){
        Euler integrator(dt);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.writeToFile("positions_euler_"+string(bodies_string)+".xyz");
        }
    }
    else if (string(integrationmethod) == string("verlet")){
        Verlet integrator(dt);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.writeToFile("positions_verlet_"+string(bodies_string)+".xyz");
        }
    }
    cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    return 0;
}

