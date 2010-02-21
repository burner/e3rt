import Blender
from Blender import NMesh
from Blender.BGL import *
from Blender.Draw import *

import math
import random
from util import frange
from noise import initNoise
from noise import fbm

EVENT_NOEVENT = 1
EVENT_DRAW = 2
EVENT_EXIT = 3
EVENT_TOSPHERE = 4
EVENT_SIXSIDES = 5

Octaves = Create(3.0)
ScaleX = 2.0
ScaleY = 2.0
ScaleZ = 2.0

#other
MaxDepth = Create(5)
ScaleX = Create(1.0)
ScaleY = Create(1.0)
ScaleZ = Create(1.0)

#heightMap
MaxHeightMapDepth = Create(4)
HeightMapRangeX = Create(1.0)
HeightMapOffSetX = Create(0.0)
HeightMapRangeY = Create(1.0)
HeightMapOffSetY = Create(0.0)
Octaves = Create(3.0)

toSphere = False
sixSides = False

maxDepth = 2
maxHeightMap = 1

heightMap = []

class Vec3C:
	def __init__(self,x,y,z):
		self.x = float(x)
		self.y = float(y)
		self.z = float(z)

	def add(self, toAdd):
		return Vec3C(self.x + toAdd.x, self.y + toAdd.y, self.z + toAdd.z)
	
	def sub(self, toAdd):
		return Vec3C(self.x - toAdd.x, self.y - toAdd.y, self.z - toAdd.z)

	def multi(self, lam):
		return Vec3C(self.x * lam, self.y * lam, self.z * lam)

	def printS(self):
		return (self.x, self.y, self.z)

	def length(self, x):
		return math.sqrt( math.pow(self.x - x.x, 2) + math.pow(self.y - x.y, 2) + math.pow(self.z - x.z, 2) )

	def equals(self, x):
		return self.x == x.x and self.y == x.y and self.z == x.z

def createHeightMap(depth, oct, range, side):
	steps = 0
	if range[0] > range[1]:
		steps = (range[0]-range[1]) / (math.pow(2,depth+1)-1)
	else:
		steps = (range[1]-range[0]) / (math.pow(2,depth+1)-1)

	global heightMap

	#print steps
	for i in frange(range[0], range[1], steps):
		tmpList = []
		for j in frange(range[0], range[1], steps):
			tmp = 0.0
			if side == 0: #top
				tmp = fbm(i,j,1, oct)
			elif side == 1: #bottom
				tmp == fbm(i,j,-1, oct)
			elif side == 2: #frond
				tmp == fbm(i,1,j, oct)
			elif side == 3: #back
				tmp == fbm(i,-1,j, oct)
			elif side == 4: #right
				tmp == fbm(1,i,j, oct)
			elif side == 5: #left
				tmp == fbm(-1,i,j, oct)
			else:
				print "createHeighMap side not in range 0...5"

			tmpList.append(tmp)

		heightMap.append(tmpList)

	#print heightMap
	#print steps, len(frange(range[0], range[1], steps))


class Quad:
	def __init__(self, parent, id, depth, tl, tr, bl, br, tli, tri, bli, bri):
		self.parent = parent
		self.id = id
		self.depth = depth
		self.tl = tl
		self.tr = tr
		self.bl = bl
		self.br = br
		self.tli = tli
		self.tri = tri
		self.bli = bli
		self.bri = bri

		self.childs = []

		global MaxDepth
		global MaxHeightMapDepth 

		maxDepth = MaxDepth.val
		maxHeightMap = MaxHeightMapDepth.val
		if depth+1 < maxDepth:
			if depth > maxHeightMap: #diamond sphere
				xm = (self.tl.x + self.tr.x + self.bl.x + self.br.x)/4.0
				ym = (self.tl.y + self.tr.y + self.bl.y + self.br.y)/4.0
				zm = (self.tl.z + self.tr.z + self.bl.z + self.br.z)/4.0
				#print x,y,z

				minDistance = None
				for x in [self.tl, self.tr, self.bl, self.br]:
					for y in [self.tl, self.tr, self.bl, self.br]:
						#print x.equals(y), "False", x.length(y)
						if False == x.equals(y):
							if minDistance is None or minDistance > x.length(y):
								minDistance = x.length(y)

				##print minDistance
				if minDistance is None:
					minDistance = 0.0

				midPoint = Vec3C(xm + random.uniform(-minDistance/2.0, minDistance/2.0 )*1.0/(self.depth-3),
								ym + random.uniform(-minDistance/2.0, minDistance/2.0 )*1.0/(self.depth-3),
								zm + random.uniform(-minDistance/2.0, minDistance/2.0 )*(1.0/(self.depth-3)*2.0) )

				dumpI = Vec3C(0,0,0)

				#child tl
				tmp = Quad(self, (self.id * 4)+1, depth+1,
				tl, tl.add(tr).multi(0.5), tl.add(bl).multi(0.5), midPoint,
				dumpI, dumpI, dumpI, dumpI)
				self.childs.append(tmp)
				
				#child tr
				tmp = Quad(self, (self.id * 4)+2, depth+1,
				tl.add(tr).multi(0.5), tr, midPoint, tr.add(br).multi(0.5),
				dumpI, dumpI, dumpI, dumpI)
				self.childs.append(tmp)

				#child self.bl
				tmp = Quad(self, (self.id * 4)+3, depth+1, 
				tl.add(bl).multi(0.5), midPoint, bl, bl.add(br).multi(0.5),
				dumpI, dumpI, dumpI, dumpI)
				self.childs.append(tmp)

				#child self.br
				tmp = Quad(self, (self.id * 4)+4, depth+1, 
				midPoint, tr.add(br).multi(0.5), bl.add(br).multi(0.5), br,
				dumpI, dumpI, dumpI, dumpI)
				self.childs.append(tmp)

			else: # heightmap lookup
				#child tl
				global heightMap

				mt = self.tl.add(self.tr).multi(0.5)
				try:
					mt.z = heightMap[int( (self.tri.x+self.tli.x)/2 )][int( (self.tri.y+self.tli.y)/2 )]
				except IndexError, e:
					print e
					print int( (self.tri.x+self.tli.x)/2 ), int( (self.tri.y+self.tli.y)/2 )

				ml = self.tl.add(self.bl).multi(0.5)
				try:
					ml.z = heightMap[int( (self.tli.x+self.bli.x)/2 )][int( (self.tli.y+self.bli.y)/2 )]
				except IndexError, e:
					print e
					print int( (self.tli.x+self.bli.x)/2 ), int( (self.tli.y+self.bli.y)/2 )

				mm = self.tl.add(self.br).multi(0.5)
				try:
					mm.z = heightMap[int( (self.tli.x+self.bri.x)/2 )][int( (self.tli.y+self.bri.y)/2 )]
				except IndexError, e:
					print e
					print int( (self.tli.x+self.bri.x)/2 ), int( (self.tli.y+self.bri.y)/2 )

				mr = self.tr.add(self.br).multi(0.5)
				try:
					mr.z = heightMap[int( (self.tri.x+self.bri.x)/2 )][int( (self.tri.y+self.bri.y)/2 )]
				except IndexError, e:
					print e
					print int( (self.tri.x+self.bri.x)/2 ), int( (self.tri.y+self.bri.y)/2 )

				mb = self.bl.add(self.br).multi(0.5)
				try:
					mb.z = heightMap[int( (self.bli.x+self.bri.x)/2 )][int( (self.bli.y+self.bri.y)/2 )]
				except IndexError, e:
					print e
					print int( (self.bli.x+self.bri.x)/2 ), int( (self.bli.y+self.bri.y)/2 )


				tmp = Quad(self, (self.id * 4)+1, depth+1,
				self.tl, mt, ml, mm,
				self.tli, self.tli.add(self.tri).multi(0.5), self.tli.add(self.bli).multi(0.5), self.tli.add(self.bri).multi(0.5))
				self.childs.append(tmp)
				
				#child tr
				tmp = Quad(self, (self.id * 4)+2, depth+1,
				mt, self.tr, mm, mr,
				self.tli.add(self.tri).multi(0.5), self.tri, self.tli.add(self.bri).multi(0.5), self.tri.add(self.bri).multi(0.5))
				self.childs.append(tmp)

				#child self.bl
				tmp = Quad(self, (self.id * 4)+3, depth+1, 
				ml, mm, self.bl, mb,
				self.tli.add(self.bli).multi(0.5), self.tli.add(self.bri).multi(0.5), self.bli, self.bli.add(self.bri).multi(0.5))
				self.childs.append(tmp)

				#child self.br
				tmp = Quad(self, (self.id * 4)+4, depth+1, 
				mm, mr, mb, self.br,
				self.tli.add(self.bri).multi(0.5), self.tri.add(self.bri).multi(0.5), self.bli.add(self.bri).multi(0.5), self.bri)
				self.childs.append(tmp)
		else:
			#print self.id
			3+2

	def render(self, raw, side):
		if len(self.childs) > 0:
			i = 0
			for x in self.childs:
				x.render(raw, i)
				i+=1
		else:
			global MaxHeightMapDepth
			if self.depth <= MaxHeightMapDepth.val: #if depth is still withinheightMap depth
				#print self.id
				global heightMap
				global toSphere
				if toSphere:
					self.tl = cubeToSphere(self.tl)
					self.tr = cubeToSphere(self.tr)
					self.bl = cubeToSphere(self.bl)
					self.br = cubeToSphere(self.br)
				if side == 0 or side == 3:
					#face one
					raw.verts.append(NMesh.Vert(self.tl.x, self.tl.y, heightMap[int(self.tli.x)][int(self.tli.y)]))
					raw.verts.append(NMesh.Vert(self.tr.x, self.tr.y, heightMap[int(self.tri.x)][int(self.tri.y)]))
					raw.verts.append(NMesh.Vert(self.br.x, self.br.y, heightMap[int(self.bri.x)][int(self.bri.y)]))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)

					#face two
					raw.verts.append(NMesh.Vert(self.tl.x, self.tl.y, heightMap[int(self.tli.x)][int(self.tli.y)]))
					raw.verts.append(NMesh.Vert(self.br.x, self.br.y, heightMap[int(self.bri.x)][int(self.bri.y)]))
					raw.verts.append(NMesh.Vert(self.bl.x, self.bl.y, heightMap[int(self.bli.x)][int(self.bli.y)]))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)
				else:
					#face one
					raw.verts.append(NMesh.Vert(self.tl.x, self.tl.y, heightMap[int(self.tli.x)][int(self.tli.y)]))
					raw.verts.append(NMesh.Vert(self.tr.x, self.tr.y, heightMap[int(self.tri.x)][int(self.tri.y)]))
					raw.verts.append(NMesh.Vert(self.bl.x, self.bl.y, heightMap[int(self.bli.x)][int(self.bli.y)]))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)

					#face two
					raw.verts.append(NMesh.Vert(self.tr.x, self.tr.y, heightMap[int(self.tri.x)][int(self.tri.y)]))
					raw.verts.append(NMesh.Vert(self.bl.x, self.bl.y, heightMap[int(self.bli.x)][int(self.bli.y)]))
					raw.verts.append(NMesh.Vert(self.br.x, self.br.y, heightMap[int(self.bri.x)][int(self.bri.y)]))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)
			else:	
				if side == 0 or side == 3:
					#face one
					raw.verts.append(NMesh.Vert(self.tl.x, self.tl.y, self.tl.z))
					raw.verts.append(NMesh.Vert(self.tr.x, self.tr.y, self.tr.z))
					raw.verts.append(NMesh.Vert(self.br.x, self.br.y, self.br.z))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)

					#face two
					raw.verts.append(NMesh.Vert(self.tl.x, self.tl.y, self.tl.z))
					raw.verts.append(NMesh.Vert(self.br.x, self.br.y, self.br.z))
					raw.verts.append(NMesh.Vert(self.bl.x, self.bl.y, self.bl.z))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)
				else:
					#face one
					raw.verts.append(NMesh.Vert(self.tl.x, self.tl.y, self.tl.z))
					raw.verts.append(NMesh.Vert(self.tr.x, self.tr.y, self.tr.z))
					raw.verts.append(NMesh.Vert(self.bl.x, self.bl.y, self.bl.z))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)

					#face two
					raw.verts.append(NMesh.Vert(self.tr.x, self.tr.y, self.tr.z))
					raw.verts.append(NMesh.Vert(self.bl.x, self.bl.y, self.bl.z))
					raw.verts.append(NMesh.Vert(self.br.x, self.br.y, self.br.z))
					f = NMesh.Face()
					f.v.append(raw.verts[-1])
					f.v.append(raw.verts[-2])
					f.v.append(raw.verts[-3])
					raw.faces.append(f)
			
			
		
def test():
	initNoise()
	global MaxDepth
	depth = MaxDepth.val

	global Octaves
	global MaxHeightMapDepth
	global HeightMapRangeX 
	global HeightMapOffSetX
	global HeightMapRangeY 
	global HeightMapOffSetY
	createHeightMap(MaxHeightMapDepth.val+1, Octaves.val, (-(HeightMapRangeX.val/2), HeightMapRangeX.val/2), 0)
	print heightMap[0][0] 
	print heightMap[0][len(heightMap[0])-1]
	print heightMap[len(heightMap)-1][0] 
	print heightMap[len(heightMap)-1][len(heightMap[len(heightMap)-1])-1]
	#root = Quad(None, 0, 0, Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(1.0, 1.0, 0.0), 
	root = Quad(None, 0, 0, 
	Vec3C(0,0,heightMap[0][0]), 
	Vec3C(0,1,heightMap[0][len(heightMap[0])-1]),
	Vec3C(1,0,heightMap[len(heightMap)-1][0]), 
	Vec3C(1,1,heightMap[len(heightMap)-1][len(heightMap[len(heightMap)-1])-1]), 
	Vec3C(0,0,0), 
	Vec3C(0, math.pow(2, MaxHeightMapDepth.val+1)-1, 0.0), 
	Vec3C(math.pow(2, MaxHeightMapDepth.val+1)-1, 0.0, 0.0), 
	Vec3C(math.pow(2, MaxHeightMapDepth.val+1)-1, math.pow(2, MaxHeightMapDepth.val+1)-1, 0.0) ) 
	
	print "init done"

	grid = NMesh.GetRaw()
	root.render(grid,0)
	gridObj = NMesh.PutRaw(grid)
	
	Blender.Redraw()

def draw():
	global EVENT_DRAW
	global EVENT_TOSPHERE
	global EVENT_SIXSIDES

	global MaxHeightMapDepth
	global HeightMapRangeX
	global HeightMapOffSetX
	global HeightMapRangeY
	global HeightMapOffSetY
	global Octaves


	global MaxDepth
	global ScaleX
	global ScaleY
	global ScaleZ

	glClear(GL_COLOR_BUFFER_BIT)
	glRasterPos2d(8, 483)
	Text('QuadTree Terrian')
	Button('Draw', EVENT_DRAW, 10,10,80,18)
	Button('Exit',EVENT_EXIT , 140, 10, 80, 18)

	MaxHeightMapDepth = Slider('MaxHeightMapDepth ', EVENT_NOEVENT, 10, 35, 310, 18,
						MaxHeightMapDepth.val, 1, 256, 1, 'MaxHeightMapDepth')
	HeightMapRangeX = Slider('HeightMapRangeX ', EVENT_NOEVENT, 10, 55, 310, 18,
						HeightMapRangeX.val, -10.0, 10.0, 1, 'HeightMaxRangeX')
	HeightMapRangeY = Slider('HeightMapRangeY ', EVENT_NOEVENT, 10, 75, 310, 18,
						HeightMapRangeY.val, -10.0, 10.0, 1, 'HeightMaxRangeY')
	HeightMapOffSetX = Slider('HeightMapOffSetX ', EVENT_NOEVENT, 10, 95, 310, 18,
						HeightMapOffSetX.val, -10.0, 10.0, 1, 'HeightMaxOffSetX')
	HeightMapOffSetY = Slider('HeightMapOffSetY ', EVENT_NOEVENT, 10, 115, 310, 18,
						HeightMapOffSetY.val, -10.0, 10.0, 1, 'HeightMaxOffSetY')
	Octaves = Slider('Octaves ', EVENT_NOEVENT, 10, 135, 310, 18,
						Octaves.val, 1.0, 100.0, 1, 'Octabes')
	glRasterPos2d(8, 160)
	Text('HeightMap Options')

	MaxDepth = Slider('MaxQuadTree Depth ', EVENT_NOEVENT, 10, 185, 310, 18,
						MaxDepth.val, 1, 256, 1, 'MaxQuadTree Depth')
	ScaleX = Slider('Scale X ', EVENT_NOEVENT, 10, 205, 310, 18,
						ScaleX.val, 1.0, 256.0, 1, 'Scale X')
	ScaleY = Slider('Scale Y ', EVENT_NOEVENT, 10, 225, 310, 18,
						ScaleY.val, 1.0, 256.0, 1, 'Scale Y')
	ScaleZ = Slider('Scale Z ', EVENT_NOEVENT, 10, 245, 310, 18,
						ScaleZ.val, 1.0, 256.0, 1, 'Scale Z')
	glRasterPos2d(8, 270)
	Text('Mesh Options')

	Toggle('To Sphere ', EVENT_TOSPHERE, 120, 265, 80, 18,0)
	Toggle('Six Sides ', EVENT_SIXSIDES, 220, 265, 80, 18,0)
	
def event(evt, val):
	if (evt == QKEY and not val):
			Exit()

def bevent(evt):
	global T_NumberOfSides
	global T_Radius
	global EVENT_NOEVENT, EVENT_DRAW, EVENT_EXIT

	######### GUI Events behandeln
	if (evt == EVENT_EXIT):
			Exit()
	elif (evt== EVENT_DRAW):
			test()
			Blender.Redraw()

	global EVENT_TOSPHERE
	global EVENT_SIXSIDES
	global toSphere
	global sixSides
	if evt == EVENT_TOSPHERE:
		toSphere = not toSphere
	if evt == EVENT_SIXSIDES:
		sixSides = not sixSides


Register(draw, event, bevent)
