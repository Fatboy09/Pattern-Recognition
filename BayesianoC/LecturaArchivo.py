
class LecturaArchivo:

	def __init__(self, ruta):
		self.path = ruta
		self.lineas = []
		self.clases = []
		self.frecClases = []
		self.rasgos = []
		self.rasgosU = []

		self.extraerDatos()	

	def extraerDatos(self):
		archivo = open(self.path,'r')
		linea = archivo.readline()
		while linea != "":
			self.lineas.append(linea)
			linea = archivo.readline().strip()

		archivo.close()

		self.obtenerClases()
		self.obtenerRasgos()

		self.rasgosU = [0]*len(self.clases)
		for m in range (len(self.clases)):
			self.rasgosU[m] = [0]*len(self.rasgos)

		indice = 5		

		for i in range (len(self.clases)):
			self.rasgosU[i] = self.obtenerFrecuencia(self.lineas[indice])
			indice = indice + 1


	def obtenerClases(self):
		self.clases = self.lineas[3].split(',')

	def obtenerRasgos(self):
		self.rasgos = self.lineas[1].split(',')

	def obtenerFrecuencia(self,dato):
		return dato.split(',')

	def getClases(self):
		return self.clases

	def getRasgos(self):
		return self.rasgos

	def getRasgosU(self):
		return self.rasgosU
