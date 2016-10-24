#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
#include <string>
#include <time.h>

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

    clock_t t_start, t_stop;
    double time;

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    //static sun
    //CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, string("Sun"));
    //sun with cancelling momentum
    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(-1.08324333e-03, 1.50783277e-03, 4.32260022e-05), 1.0, string("Sun"));

    // Earth
    CelestialBody &earth = solarSystem.createCelestialBody( vec3(8.841554736579088E-01, 4.675846666013374E-01, -1.788208627053143E-04),     vec3(-3.03047582e+00, 5.53804088e+00, -2.61593386e-04),   0.000003003, string("Earth") );

    // Jupiter
    CelestialBody &jupiter = solarSystem.createCelestialBody( vec3(-5.425134275608231E+00, -4.965390581079263E-01,  1.233903897528774E-01), vec3(0.21935934, -2.61433515, 0.00596296),                0.0009543, string("Jupiter"));

    // normal mercury
    CelestialBody &mercury = solarSystem.createCelestialBody( vec3(-3.915735125896518E-01, -8.031632966591709E-02, 2.924535350247253E-02),  vec3(-4.12705352e-03,  -9.60776278e+00, -7.84947463e-01), 1.652e-7, string("Mercury"));
    // perihelion mercury
    //CelestialBody &mercury = solarSystem.createCelestialBody( vec3(0.3075, 0, 0),  vec3(0,  12.44, 0), 1.652e-7, string("Mercury"));

    CelestialBody &venus = solarSystem.createCelestialBody(   vec3(3.136264982750417E-01, -6.546683031177923E-01, -2.707665055849010E-02),  vec3(6.63254485, 3.12614069, -0.33993686),                0.000002447, string("Venus"));
    CelestialBody &mars = solarSystem.createCelestialBody(    vec3(1.208658599158087E+00, -6.711650212869039E-01, -4.387238661867205E-02),  vec3(2.69039887, 4.90008363, 0.03660091),                 3.213e-7, string("Mars"));
    CelestialBody &saturn = solarSystem.createCelestialBody(  vec3(-2.236264385979587E+00, -9.782434228347928E+00, 2.590917399206301E-01),  vec3(1.87495851, -0.46042927, -0.06665673),               0.0002857, string("Saturn"));
    CelestialBody &uranus = solarSystem.createCelestialBody(  vec3(1.845409667002747E+01, 7.582158156514705E+00, -2.109158924849341E-01),   vec3(-0.55636872, 1.26177202, 0.011894),                  0.00004365, string("Uranus"));
    CelestialBody &neptune = solarSystem.createCelestialBody( vec3(2.826704082725938E+01, -9.904409112730836E+00, -4.474799704373976E-01),  vec3(0.37149543, 1.0889944, -0.03084886),                 0.0009543, string("Neptune"));
    CelestialBody &pluto = solarSystem.createCelestialBody(   vec3(9.442295163349636E+00, -3.181678067153034E+01, 6.733338703492342E-01),   vec3(1.1266729, 0.09182691, -0.33562222),                 6.58086572e-9, string("Pluto"));

    // The below values are only idealized
    // We don't need to store the reference, but just call the function without a left hand side

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        //cout << "The position of "<< body.name <<" begins at " << body.position << "AU with velocity " << body.velocity << "AU/yr "<< endl;
    }
    string bodies_string;
    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i];
        bodies_string.append(body.name);
    }
    double dt = 0.001;


    if (string(integrationmethod) == string("euler")){
        Euler integrator(dt);
        t_start = clock();
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            //solarSystem.writeToFile("positions_euler_"+string(bodies_string)+".xyz");
        }
        t_stop = clock();
    }
    else if (string(integrationmethod) == string("verlet")){
        Verlet integrator(dt);
        t_start = clock();
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            //solarSystem.writeToFile("positions_verlet_"+string(bodies_string)+".xyz");
        }
        t_stop = clock();
    }
    else {
        cout << "You gave the wrong argument, no method specified." << endl
             << "Exiting!" << endl;
        exit(1);
    }
    cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;

    time = abs(t_start - t_stop)/( (double) CLOCKS_PER_SEC);
    cout << "time of integration method: t=" << time << " s" << endl;

    return 0;
}

