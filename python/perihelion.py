import pylab as pl
from mpl_toolkits.mplot3d import Axes3D
import os
import sys
from matplotlib import rc
rc('font',**{'family':'serif'})

def read(address):
    """
    reads data from file
    """
    body_names = pl.array(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto'])
    bodies_positions = {}

    ###### REMEMBER TO EDIT THIS WHEN PLOTTING DIFFERENT STUFF
    with open(address+"/positions_verlet_SunMercury.xyz", 'r') as infile:
        ###### REMEMBER TO EDIT THIS WHEN PLOTTING DIFFERENT STUFF
        data = infile.read()
    
    data_splat = data.split('\n')
    file_len = len(data_splat)

    for l in pl.arange(file_len-1):
        line = pl.array(data_splat[l].split(' '))
        try:
            bodies_positions[line[0]].append(line[1:].astype(pl.float64))
        except KeyError:
            bodies_positions[line[0]] = [line[1:].astype(pl.float64)]
        except:
            sys.exit('Error in dictionary making')
        
    for key in bodies_positions:
        bodies_positions[key] = pl.array(bodies_positions[key])

    return body_names, bodies_positions


def perih(address):
