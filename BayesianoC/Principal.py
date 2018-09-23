from LecturaArchivo import LecturaArchivo
from BayesianoC import BayesianoC

def main():
	valor = input("Escribe el dato que desea clasificar: ")
	print ""
	b = BayesianoC("/home/fatboy/Documentos/Escom/Patrones/data.txt",valor)
	b.imprimirDatos()
	print ""
	b.imprimirProba()
	print ""
	b.imprimirProceso()
	print ""
	b.imprimirResultado()

if __name__ == '__main__':
	main()
