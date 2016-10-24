from pylab import *

mearth = 0.000003003
velearth = array([-3.03047582e+00, 5.53804088e+00, -2.61593386e-04])

mmerc = 1.652e-7
velmerc = array([-4.12705352e-03,  -9.60776278e+00, -7.84947463e-01])

mvenus = 0.000002447
velvenus = array([6.63254485, 3.12614069, -0.33993686])

mmars = 3.213e-7
velmars = array([2.69039887, 4.90008363, 0.03660091])

mjup = 0.0009543
veljup = array([0.21935934, -2.61433515, 0.00596296])

msat = 0.0002857
velsat = array([1.87495851, -0.46042927, -0.06665673])

mur = 0.00004365
velur = array([-0.55636872, 1.26177202, 0.011894])

mnept = 0.0009543
velnept = array([0.37149543, 1.0889944, -0.03084886])

mplut = 6.58086572e-9
velplut = array([1.1266729, 0.09182691, -0.33562222])

velsun = -(mmerc*velmerc + mvenus*velvenus + mearth*velearth + mmars*velmars + mjup*veljup + msat*velsat + mur*velur + mnept*velnept + mplut*velplut)/1.

print velsun

"""
//    CelestialBody &earth = solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI*sqrt(2), 0), 0.000003003, string("Earth") );

//    CelestialBody &mercury = solarSystem.createCelestialBody( vec3(0.39, 0, 0),  vec3(0, 2*M_PI*0.39/0.240846, 0), 0.000002447, string("Mercury"));
//    CelestialBody &venus = solarSystem.createCelestialBody(   vec3(0.728, 0, 0), vec3(0, 2*M_PI*0.728/0.61521, 0), 0.000002447, string("Venus"));
//    CelestialBody &mars = solarSystem.createCelestialBody(    vec3(1.524, 0, 0), vec3(0, 2*M_PI*1.524/1.88089, 0), 3.213e-7, string("Mars"));
//    CelestialBody &jupiter = solarSystem.createCelestialBody( vec3(5.203, 0, 0), vec3(0, 2*M_PI*5.203/11.8653, 0), 0.0009543, string("Jupiter"));
//    CelestialBody &saturn = solarSystem.createCelestialBody(  vec3(9.582, 0, 0), vec3(0, 2*M_PI*9.582/29.46, 0),   0.0002857, string("Saturn"));
//    CelestialBody &uranus = solarSystem.createCelestialBody(  vec3(19.2, 0, 0),  vec3(0, 2*M_PI*19.20/84.04, 0),   0.00004365, string("Uranus"));
//    CelestialBody &neptune = solarSystem.createCelestialBody( vec3(30.05, 0, 0), vec3(0, 2*M_PI*30.05/164.8, 0),   0.0009543, string("Neptune"));
//    CelestialBody &pluto = solarSystem.createCelestialBody(   vec3(39.48, 0, 0), vec3(0, 2*M_PI*39.48/248.1, 0),   0.0009543, string("Pluto"));
"""