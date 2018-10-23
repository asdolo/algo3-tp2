import os
import sys
import random
import math
from subprocess import Popen, PIPE, STDOUT

class color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

def clear_screen():
    print("\033[H\033[J")

def apply_effects(text, effects):
    res = ''
    for x in effects:
        res += x

    res += text

    for x in effects:
        res += color.END

    return res

def print_modo_de_uso():
    print(apply_effects('Modo de uso:', color.BOLD))
    print('  ' + 'python ' + os.path.basename(__file__) + ' [NRO. TEST]')
    print('')
    print(apply_effects('Tests:', color.BOLD))
    print('  ' + apply_effects('1, Prim vs Kruskal vs Kruskal con Path Compression', color.GREEN))
    print('')
    print(apply_effects('Ejemplo:', color.BOLD))
    print('  ' + 'python ' + os.path.basename(__file__) + ' 1')
    print('')

def check_compiled(algoritmo):
    try:
        p = Popen('../' + algoritmo, stdin=PIPE)
    except OSError:
        print('No se encuentra el ejecutable del algoritmo ' + algoritmo + '.')
        print('Por favor, compile el algoritmo usando ' + apply_effects('make ' + algoritmo, color.BOLD) + ' o simplemente ' + apply_effects('make', color.BOLD) + ' para compilar todos los algoritmos.')
        print('')
        exit()

    p.kill()

def limpiar_output(archivo, columnas):
    output_file = open(archivo, 'w')
    output_file.write(columnas + '\n')
    output_file.close()


######################### MAIN #########################

clear_screen()

# Chequear si estamos en python 2
if sys.version_info[0] != 2:
    print(apply_effects('Por favor, ejecute este script en Python 2.', [color.RED, color.BOLD]))
    print('')
    exit()

# Chequear si los parametros son correctos
if len(sys.argv) != 2:
    print_modo_de_uso()
    exit()

parametro = sys.argv[1].lower()

# Chequear que los 3 algoritmos de clusterizacion esten compilados
check_compiled('clusterizacion-prim')
check_compiled('clusterizacion-kruskal')
check_compiled('clusterizacion-kruskal-path-compression')

# Ejecutar test segun parametro
if parametro == '1':
    # Test 1:
    # Prim vs Kruskal vs Kruskal con Path Compression

    # Limpio los outputs viejos del test
    limpiar_output('../output/clusterizacion/test-1-clusters-prim-400-puntos.csv', 'punto,x,y,cluster')
    limpiar_output('../output/clusterizacion/test-1-clusters-kruskal-400-puntos.csv', 'punto,x,y,cluster')
    limpiar_output('../output/clusterizacion/test-1-clusters-kruskal-path-compression-400-puntos.csv', 'punto,x,y,cluster')
    limpiar_output('../output/clusterizacion/test-1-mediciones-prim.csv', 'n,vecindad,version,excesoNecesarioDesvioEstandar,ratioExceso,clusters,tiempo')
    limpiar_output('../output/clusterizacion/test-1-mediciones-kruskal.csv', 'n,vecindad,version,excesoNecesarioDesvioEstandar,ratioExceso,clusters,tiempo')
    limpiar_output('../output/clusterizacion/test-1-mediciones-kruskal-path-compression.csv', 'n,vecindad,version,excesoNecesarioDesvioEstandar,ratioExceso,clusters,tiempo')


    # Voy agregando puntos
    for n in range(0, 400 + 5, 5):
        f = open('../input/clusterizacion/s1.txt', 'r')
        
        input = str(n) + '\n'
        
        # Genero los inputs que van a ir al stdin por un pipe
        for i in range(0, n):
            input += f.readline() + '\n'

        f.close()

        for algoritmo in ['prim', 'kruskal', 'kruskal-path-compression']:
            limpiar_output('../output/clusterizacion/test-1-clusters-' + algoritmo + '-400-puntos.csv', 'punto,x,y,cluster')
        
            # Genero los parametros del algoritmo
            archivoTablaClusters            = '../output/clusterizacion/test-1-clusters-' + algoritmo + '-400-puntos.csv'
            archivoResultados               = '../output/clusterizacion/test-1-mediciones-' + algoritmo + '.csv'
            vecindad                        = 2
            version                         = 1
            excesoNecesarioDesvioEstandar   = 3
            ratioExceso                     = 2

            parametros = archivoTablaClusters + ' '
            parametros += archivoResultados + ' '
            parametros += str(vecindad) + ' '
            parametros += str(version) + ' '
            parametros += str(excesoNecesarioDesvioEstandar) + ' '
            parametros += str(ratioExceso) + ' '

            print('Ejecutando ' + algoritmo + ' con n = ' + str(n))
            print('Parametros: ' + parametros)
            
            p = Popen('../clusterizacion-' + algoritmo + ' ' + parametros, stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]
            

else:
    print_modo_de_uso()
    exit()    

print('Test finalizado!')
print('')
