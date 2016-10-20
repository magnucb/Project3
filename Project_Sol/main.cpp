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
        string integrationmethod = string(arguments[2]);
    }

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, string("Sun"));

    // We don't need to store the reference, but just call the function without a left hand side
    CelestialBody &earth = solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 0.000003003, string("Earth") );
    //CelestialBody &venus = solarSystem.createCelestialBody( vec3(0.728, 0, 0), vec3(0, 0.62*2*M_PI, 0), 0.000002447);
    //CelestialBody &mars = solarSystem.createCelestialBody( vec3(1.524, 0, 0), vec3(0, 1.88*2*M_PI, 0), 3.213e-7);
    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    double dt = 0.001;
    if (integrationmethod == "euler"){
        Euler integrator(dt);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.writeToFile("positions_euler.xyz");
        }
    }
    else if (integrationmethod == "verlet"){
        Verlet integrator(dt);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.writeToFile("positions_verlet.xyz");
        }
    }
    cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    return 0;
}

