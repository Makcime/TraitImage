import xml.etree.ElementTree as ET
from sys import argv
from random import randrange

class Tile():
	"""Define a tile IN THE MAP"""
	def __init__(self, state = 0, path = "empty.png"):
		self.state = state
		self.path = path

	def __str__(self):
		return "state = %d - path = %s \n" % (self.state, self.path)


class MapGenerator():
	"""Python class to mange map generation for MArio Bross"""

	BASIC = "basic.xml"
	OUTPUT = "2d_map_extended.xml"
	
	def __init__(self, x_len = 212):
		self.x_len = x_len
		self.y_len = 18 # keep this value constant$
		self.s_floor = (self.y_len - 3) # keep this value constant$
		self.area = self.x_len * self.y_len

		self.ltiles = [Tile() for i in range(self.area)]

		self.tree = ET.parse(self.BASIC)
		self.root = self.tree.getroot()
		self.MAP = self.root.find('MAP')
		self.TILES = self.MAP.find('TILES').find('DATA')
		self.TILES.clear()

		self.GRID = self.MAP.find('GRID')
		self.GRID.find('X').text = str(self.x_len)


	def Generate(self):

		for t in self.ltiles:
			tile = ET.Element('TILE')
			state = ET.Element('STATE') #	, text=0)
			path = ET.Element('PATH') #	, 
			path.text= t.path
			state.text = str(t.state)
			tile.append(state)
			tile.append(path)

			self.TILES.append(tile)

		# ET.dump(self.tree)

		self.tree.write(self.OUTPUT)


	def __str__(self):
		s = ""
		i = 0
		for t in self.ltiles:
			s += "%d --> %s" % (i , str(t))
			i+=1

		return s

	def position(self, _x, _y):
		'''
		convert on (x, y) position to an indice in the area range
		'''
		return _y * self.x_len + _x

	def coverArea(self, tile, s_x, s_y, _x, _y):
		'''
		Cover an area (_x * _y) with a specific tile
		starting a the s position
		'''
		for y in range(_y):
			for x in range(_x):
				# print s_pos + x + y*self.x_len
				self.ltiles[self.position(s_x + x, s_y + y)] = tile

	def isFreeArea(self, s_x, s_y, _x, _y):
		ret = True
		for y in range(_y):
			for x in range(_x):
				if (self.ltiles[self.position(s_x + x, s_y + y)].path != "empty.png"):
					ret = False
		return ret

	def basicWorld(self):
		'''
		generate a basi world with only a floor 
		'''
		floor = Tile(1, 'ground_001.png')

		# self.coverArea	(tile = floor, s_pos = (self.y_len - 3) * self.x_len, _x = self.x_len, _y = 3)
		self.coverArea	(tile = floor, s_x = 0, s_y = self.s_floor , _x = self.x_len, _y = 3)

		self.addCastle(self.x_len - 10)
		self.addFlag(self.x_len - 13, 10)




	def addPipe(self, size, x_pos):
		'''
		add a pipe
		'''
		i = 0
		pipe_img = "pipe_%02d.png" % i
		s_pos = (self.y_len - 3 - size ) * self.x_len + x_pos
		for y in range(size):
			for x in range(2):
				if y == 0:
					pipe_img = "pipe_%02d.png" % 1
					if x % 2:
						pipe_img = "pipe_%02d.png" % 2
				else:
					pipe_img = "pipe_%02d.png" % 3
					if x % 2:
						pipe_img = "pipe_%02d.png" % 4

				self.ltiles[s_pos + x + y*self.x_len] = Tile(1, pipe_img)

	def addHallfPyramid(self, size, x_pos, direction = True, img = "block.png"):
		s_pos = self.position(x_pos, self.s_floor - size)

		# s_pos = (self.y_len - 3 - size ) * self.x_len + x_pos

		for y in range(size):
			for x in range(size):
				if (direction):
					if y >= (size-x-1):
						self.ltiles[s_pos + x + y*self.x_len] = Tile(1, img)
				else:
					if x <= y:
						self.ltiles[s_pos + x + y*self.x_len] = Tile(1, img)


	def addHole(self, size, x_pos):
		hole = Tile(0, 'empty.png')
		self.coverArea	(tile = hole, s_x = x_pos, s_y = self.s_floor , _x = size, _y = 3)


	def addBigBush(self, x_pos):
		s_pos =  self.position(x_pos, self.s_floor -1)# (self.y_len - 4) * self.x_len + x_pos
		if self.isFreeArea(x_pos, self.s_floor -1, 3, 1 ):
			for x in range(3):
				self.ltiles[s_pos + x] = Tile(0, "bush%d.png" % (x+1))

	def addBush(self, x_pos):
		s_pos =  self.position(x_pos, self.s_floor -1)# (self.y_len - 4) * self.x_len + x_pos

		if self.isFreeArea(x_pos, self.s_floor -1, 2, 1 ):
			for x in range(2):
				self.ltiles[s_pos + x] = Tile(0, "bush%d.png" % (2*x+1))


	def addBigCloud(self, x_pos, y_pos):
		# s_pos = self.position(x_pos, y_pos)
		if self.isFreeArea(x_pos, y_pos, 3, 2):
			for y in range(2):
				for x in range(3):
					self.ltiles[self.position(x_pos+x, y_pos+y)] = Tile(0, "cloud%d.png" % (x+(y*3)+1))

	def addCloud(self, x_pos, y_pos):
		# s_pos = self.position(x_pos, y_pos)
		if self.isFreeArea(x_pos, y_pos,2, 2):
			for y in range(2):
				for x in range(2):
					self.ltiles[self.position(x_pos+x, y_pos+y)] = Tile(0, "cloud%d.png" % (x * 2 + 1 + y * 3))


	def randClouds(self):
		for i in range(self.x_len):
			if i%2 :
				self.addCloud(randrange(self.x_len - 3) , randrange(self.y_len - 5))
			else:
				self.addBigCloud(randrange(self.x_len - 3) , randrange(self.y_len - 5))


	def randMountains(self):
		for i in range(self.x_len/10):
			if i%2:
				self.addMountain(randrange(self.x_len - 5), True)
			else:
				self.addMountain(randrange(self.x_len - 5), False)

	def randBushs(self):
		for i in range(self.x_len/10):
			if i%2:
				self.addBush(randrange(self.x_len - 2))
			else:
				self.addBigBush(randrange(self.x_len - 3))



	def addMountain(self, x_pos, big = False):

		y_pos = self.s_floor - 1
		if self.isFreeArea(x_pos, y_pos -3 , 5, 3):
			# # s_pos = (self.y_len - 4) * self.x_len + x_pos
			s_pos = self.position(x_pos, y_pos )
			# for x in range(5):
			# 	self.ltiles[s_pos + x] = Tile(0, "mountain%d.png" % (x+1))
			Delta = 0

			if big:
				self.ltiles[s_pos] = Tile(0, "mountain%d.png" % (1))
				self.ltiles[s_pos+1] = Tile(0, "mountain%d.png" % (2))
				self.ltiles[s_pos+2] = Tile(0, "mountain%d.png" % (2))
				self.ltiles[s_pos+3] = Tile(0, "mountain%d.png" % (2))
				self.ltiles[s_pos+4] = Tile(0, "mountain%d.png" % (3))
				Delta = 1

			s_pos = self.position(x_pos + (Delta) , y_pos - (Delta))
			for x in range(3):
				self.ltiles[s_pos + x] = Tile(0, "mountain%d.png" % (x+1))

			self.ltiles[self.position(x_pos + (Delta + 1), y_pos - (Delta + 1) )] = Tile(0, "mountain%d.png" % (4))


	def addCastle(self, x_pos):
		s_pos = self.position(x_pos, self.s_floor - 5)
		self.ltiles[s_pos + 1] = Tile(0, "castle1.png")
		self.ltiles[s_pos + 2] = Tile(0, "castle1.png")
		self.ltiles[s_pos + 3] = Tile(0, "castle1.png")

		s_pos = self.position(x_pos, self.s_floor - 4)
		self.ltiles[s_pos + 1] = Tile(0, "castle3.png")
		self.ltiles[s_pos + 2] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 3] = Tile(0, "castle5.png")
		
		s_pos = self.position(x_pos, self.s_floor - 3)
		self.ltiles[s_pos + 0] = Tile(0, "castle1.png")
		self.ltiles[s_pos + 1] = Tile(0, "castle8.png")
		self.ltiles[s_pos + 2] = Tile(0, "castle8.png")
		self.ltiles[s_pos + 3] = Tile(0, "castle8.png")
		self.ltiles[s_pos + 4] = Tile(0, "castle1.png")

		s_pos = self.position(x_pos, self.s_floor - 2)
		self.ltiles[s_pos + 0] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 1] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 2] = Tile(0, "castle4.png")
		self.ltiles[s_pos + 3] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 4] = Tile(0, "castle2.png")

		s_pos = self.position(x_pos, self.s_floor - 1)		
		self.ltiles[s_pos + 0] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 1] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 2] = Tile(0, "castle7.png")
		self.ltiles[s_pos + 3] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 4] = Tile(0, "castle2.png")
		self.ltiles[s_pos + 5] = Tile(0, "bush3.png")

	def addFlag(self, x_pos, hight):
		y_pos = self.s_floor - hight

		s_pos = self.position(x_pos, y_pos)
		self.ltiles[s_pos] = Tile(0, "flag_04.png")

		y_pos += 1
		s_pos = self.position(x_pos, y_pos)
		self.ltiles[s_pos - 1] = Tile(0, "flag_03.png")
		self.ltiles[s_pos] = Tile(0, "flag_02.png")

		for i in range(hight -3):
			y_pos += 1
			s_pos = self.position(x_pos, y_pos)
			self.ltiles[s_pos] = Tile(0, "flag_01.png")
		
		y_pos += 1
		s_pos = self.position(x_pos, y_pos)
		self.ltiles[s_pos] = Tile(1, "block.png")

		# self.ltiles[s_pos + 2] = Tile(0, "castle1.png")
		# self.ltiles[s_pos + 3] = Tile(0, "castle1.png")


if __name__ == '__main__':

	output = 'output.xml'
	if len(argv) > 1:
		output = argv[1]


	myMap = MapGenerator()
	myMap.basicWorld()


	pos = 0
	myMap.addBush(pos)
	pos += 7
	myMap.addBigBush(pos)
	pos += 7
	myMap.addMountain(pos)
	pos += 7
	myMap.addMountain(pos, True)
	pos += 7
	myMap.addHallfPyramid(5, pos)
	pos += 7
	myMap.addHallfPyramid(5, pos, False)
	pos += 7
	myMap.addHallfPyramid(4, pos, False, "box.png")
	pos += 7
	myMap.addPipe(3, pos)
	pos += 7
	myMap.addPipe(6, pos)
	pos += 7
	myMap.addHole(2, pos)
	pos += 7
	myMap.addHole(3, pos)



	myMap.randClouds()
	myMap.randMountains()
	myMap.randBushs()
	myMap.Generate()
