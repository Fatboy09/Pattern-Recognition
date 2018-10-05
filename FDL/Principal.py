from LecturaArchivo import LecturaArchivo
from Euclidiano import Euclidiano
import re

def main():
	vector = [0]*2
	dato = raw_input("Escribe en la consola el vector de prueba en el siguiente formato -> [x,y]: ")
	print ""
	if not validarCad(dato):
		print "Error. No escribio el vector en el formato correcto, vuelva a intentarlo"
		main()
	else:
		i = dato.find(',')
		x = float(dato[1:i])
		y = float(dato[i+1:len(dato)-1])
		vector[0] = x
		vector[1] = y

		e = Euclidiano("data.txt",vector)
		e.imprimirDatos()
		print ""
		e.imprimirResultado()

def validarCad(cadena):
	vect = re.compile(r'(^\[[-\d]+.\d*,[-\d]+.\d*\])|(\[[-\d]+,[-\d]+\])|(\[[-\d]+.\d*,[-\d]+\])|(\[[-\d]+,[-\d]+.\d*\])')
	
	if vect.search(cadena) == None:
		return False
	else:
		return True

if __name__ == '__main__':
	main()
