
import math
from LecturaArchivo import LecturaArchivo

class Euclidiano:

	def __init__(self, ruta, dato):
		#ecuacion de una recta: y = mx + b

		self.arch = LecturaArchivo(ruta)
		self.vector = dato
		self.clases = self.arch.getClases()
		self.coordX_C1 = self.arch.get_CoordX_C1()
		self.coordY_C1 = self.arch.get_CoordY_C1()
		self.coordX_C2 = self.arch.get_CoordX_C2()
		self.coordY_C2 = self.arch.get_CoordY_C2()
		self.media_1 = []
		self.media_2 = []
		self.b = 0.0
		self.m = [0]*2

		self.calcularMedia()
		self.calcular_pendiente()
		self.calcular_b()


	def calcularMedia(self):
		p = len(self.coordX_C1)
		sumx = 0.0
		sumy = 0.0

		for k in range(p):
			sumx = sumx + float(self.coordX_C1[k])
			sumy = sumy + float(self.coordY_C1[k])

		self.media_1.append(sumx/p)
		self.media_1.append(sumy/p)

		p = len(self.coordX_C2)
		sumx = 0.0
		sumy = 0.0
		for k in range(p):
			sumx = sumx + float(self.coordX_C2[k])
			sumy = sumy + float(self.coordY_C2[k])

		self.media_2.append(sumx/p)
		self.media_2.append(sumy/p)

	def calcularDistancia(self):
		distancia = 0.0
		distancia = (self.m[0] * self.vector[0]) + (self.m[1] * self.vector[1]) + self.b
		#distancia = math.log(pClase) + math.log(proba)
		return distancia

	def calcular_b(self):
		x = 0.0
		y = 0.0

		x = self.m[0] * (self.media_1[0] + self.media_2[0])
		y = self.m[1] * (self.media_1[1] + self.media_2[1])

		self.b = ((x + y)/2) * (-1)

	def calcular_pendiente(self):
		
		self.m[0] = (self.media_1[0] - self.media_2[0])
		self.m[1] = (self.media_1[1] - self.media_2[1])

	def imprimirDatos(self):
		print "----------------Datos del Archivo----------------"
		print "{} = {}".format(self.clases[0],'{'),
		for i in range(len(self.coordX_C1)):
			print "[{},{}]".format(self.coordX_C1[i],self.coordY_C1[i]),
		print "}"

		print "{} = {}".format(self.clases[1],'{'),
		for i in range(len(self.coordX_C2)):
			print "[{},{}]".format(self.coordX_C2[i],self.coordY_C2[i]),
		print "}"
		print "-------------------------------------------------"

		print "\nCentroide de %s : [%.3f,%.3f]" %(self.clases[0],self.media_1[0],self.media_1[1])
		print "Centroide de %s : [%.3f,%.3f]" %(self.clases[1],self.media_2[0],self.media_2[1])

		print "\nEcuacion:"
		print "%.3f x1 + (%.3f x2) + (%.3f)" %(self.m[0],self.m[1],self.b)

	def imprimirResultado(self):
		if self.calcularDistancia() >= 0:
			print "El vector {} pertenece a la clase {}".format(self.vector,self.clases[0])
		else:
			print "El vector {} pertenece a la clase {}".format(self.vector,self.clases[1]) 
