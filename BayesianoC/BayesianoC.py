
import math
from LecturaArchivo import LecturaArchivo

class BayesianoC:
	
	datoP = 0.0
	indiceDistanciaM = 0
	indiceClase = 0

	def __init__(self, ruta, dato):
		self.arch = LecturaArchivo(ruta)
		self.datoP = dato
		self.clases = self.arch.getClases()
		self.rasgos = self.arch.getRasgos()
		self.rasgosU = self.arch.getRasgosU()
		self.totalM = 0
		self.totalC = [0]*len(self.clases)
		self.distancias = [0.0]*len(self.clases)
		self.probabilidadesR = [0.0]*len(self.clases)
		for x in range(len(self.clases)):
			self.probabilidadesR[x] = [0.0]*len(self.rasgos)

		self.calcularTotal()
		self.calcularProba()

		self.indiceClase = self.rasgoPert(dato)

		for m in range(len(self.clases)):
			self.distancias[m] = self.calcularDistancia(float(self.totalC[m])/self.totalM,self.probabilidadesR[m][self.indiceClase])

		self.indiceDistanciaM = self.calcularDistanciaMayor()


	def calcularTotal(self):
		for i in range(len(self.clases)):
			for j in range(len(self.rasgos)):
				self.totalM = self.totalM + int(self.rasgosU[i][j])
				self.totalC[i] = self.totalC[i] + int(self.rasgosU[i][j])

	def calcularProba(self):
		for i in range(len(self.clases)):
			for y in range(len(self.rasgos)):
				self.probabilidadesR[i][y] = float(self.rasgosU[i][y]) / self.totalC[i]

	def calcularDistancia(self,pClase, proba):
		distancia = 0.0
		distancia = math.log(pClase) + math.log(proba)
		return distancia

	def calcularDistanciaMayor(self):
		i = 0
		for x in range(1,len(self.clases)):
			if self.distancias[x] > self.distancias[i]:
				i = x
		return i


	def datoRasgos(self):
		indice = 0
		for x in range(len(self.rasgos)):
			if self.datoP == float(self.rasgos[x]):
				indice = x
		return indice


	def imprimirDatos(self):
		print "----------------Datos del Archivo----------------"
		print "|Rasg/Clases\t|",
		for x in range(len(self.rasgos)):
			print self.rasgos[x]+"\t|",
		print ""

		for y in range(len(self.clases)):
			print "|"+self.clases[y]+"\t|",
			for z in range(len(self.rasgos)):
				print self.rasgosU[y][z]+"\t|",
			print ""

	def imprimirProba(self):
		print "------------------Probabilidades-----------------"
		print "|Rasg/Clases\t|",
		for x in range(len(self.rasgos)):
			print self.rasgos[x]+"\t|",
		print ""

		for y in range(len(self.clases)):
			print "|"+self.clases[y]+"\t|",
			for z in range(len(self.rasgos)):
				print "{0:.3f}".format(self.probabilidadesR[y][z])+"\t|",
			print ""

	def imprimirProceso(self):
		print "------------------Datos del Procesamiento------------------"
		print "Total del espacio muestral: {}".format(self.totalM)
		print "X[i] = {}".format(self.rasgos[self.indiceClase])
		for x in range(len(self.clases)):
			print "Clase {} : Cardinalidad = {} : Distancia = {}".format(self.clases[x],self.totalC[x],self.distancias[x])


	def imprimirResultado(self):
		print "La muestra {} pertenece a la clase {}".format(self.datoP,self.clases[self.indiceDistanciaM])


	def rasgoPert(self,dato):
		indice = 0
		primero = float(self.rasgos[0])
		ultimo = float(self.rasgos[len(self.rasgos)-1])

		if dato <= primero:
			indice = 0
		elif dato >= ultimo:
			indice = len(self.rasgos)-1
		elif self.datoRasgos() != 0:
			indice = self.datoRasgos()
		else:
			m = 1
			for x in range(len(self.rasgos)-1):
				auxR = float(self.rasgos[x])
				auxRm = float(self.rasgos[m])
				if self.datoP > auxR and self.datoP < auxRm:
					if (self.datoP - auxR) < (auxRm - self.datoP):
						indice = x
					else:
						indice = m
				m = m + 1
		return indice
