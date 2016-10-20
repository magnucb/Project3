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

    with open(address+"/positions.xyz", 'r') as infile:
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


def plot(keys, bodies_with_positions):
    """
    plots all present celestial bodies_positions
    """
    colors = {'Sun':'y', 'Mercury':'k', 'Venus':'0.75', 'Earth':'b', 'Mars':'r', 'Jupiter':'#FF5733', 'Saturn':'#C88617', 'Uranus':'c', 'Neptune':'#6A82FF', 'Pluto':'g'}
    linestyles = {'Sun': '*', 'Mercury':'-', 'Venus':'-', 'Earth':'-', 'Mars':'-', 'Jupiter':'-', 'Saturn':'-', 'Uranus':'-', 'Neptune':'-', 'Pluto':'-'}
    pl.rcParams['legend.fontsize'] = 10
    fig = pl.figure()
    
    ax = fig.gca(projection='3d')

    for i in bodies_positions:
        xyz = bodies_positions[i]
        ax.plot(xyz[:,0], xyz[:,1], xyz[:,2], linestyles[i], label=i, color=colors[i])

    ax.set_aspect('equal')
    ax.set_xlabel('X-axis [AU]')
    ax.set_ylabel('Y-axis [AU]')
    ax.set_zlabel('Z-axis [AU]')
    ax.legend()
    pl.show()
    body_string = ""
    for key in bodies_positions:
        body_string += key

    pl.savefig('solar_system_with_%s.png' % body_string, dpi=300)


if __name__ == '__main__':
    
    address = os.getcwd()+"/../build-SolarSystem-Desktop_Qt_5_7_0_MSVC2015_64bit-Release"

    keys, bodies_positions = read(address)
    plot(keys, bodies_positions)