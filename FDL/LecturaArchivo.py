
class LecturaArchivo:

	def __init__(self, ruta):
		self.path = ruta
		self.lineas = []
		self.clases = []
		self.coordx_C1 = []
		self.coordx_C2 = []
		self.coordy_C1 = []
		self.coordy_C2 = []

		self.extraerDatos()

	def extraerDatos(self):
		archivo = open(self.path,'r')
		linea = archivo.readline()
		while linea != "":
			self.lineas.append(linea)
			linea = archivo.readline().strip()

		archivo.close()

		self.obtenerClases()
		self.obtener_CoordX_C1()
		self.obtener_CoordX_C2()
		self.obtener_CoordY_C1()
		self.obtener_CoordY_C2()

	def obtenerClases(self):
		self.clases = self.lineas[1].split(',')

	def obtener_CoordX_C1(self):
		data = self.lineas[3].split(':')
		for d in data:
			indice = d.find(',')
			cad = d[1:indice]
			self.coordx_C1.append(cad)

	def obtener_CoordX_C2(self):
		data = self.lineas[4].split(':')
		for d in data:
			indice = d.find(',')
			cad = d[1:indice]
			self.coordx_C2.append(cad)

	def obtener_CoordY_C1(self):
		data = self.lineas[3].split(':')
		for d in data:
			indice1 = d.find(',') + 1
			indice2 = d.find(']')
			cad = d[indice1:indice2]
			self.coordy_C1.append(cad)

	def obtener_CoordY_C2(self):
		data = self.lineas[4].split(':')
		for d in data:
			indice1 = d.find(',') + 1
			indice2 = d.find(']')
			cad = d[indice1:indice2]
			self.coordy_C2.append(cad)

	def getClases(self):
		return self.clases

	def get_CoordX_C1(self):
		return self.coordx_C1

	def get_CoordX_C2(self):
		return self.coordx_C2

	def get_CoordY_C1(self):
		return self.coordy_C1

	def get_CoordY_C2(self):
		return self.coordy_C2
