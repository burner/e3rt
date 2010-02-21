import math


permutation = [ 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180]

p = []
max = 0.0
min = 0.0
def initNoise():
	for i in range(3):
		print "init",i
		for j in permutation:
			p.append(j)
			
	#print len(p)

def noise(x,y,z):
	X = int(math.floor(x)) & 255                  # FIND UNIT CUBE THAT
	Y = int(math.floor(y)) & 255                  # CONTAINS POINT.
	Z = int(math.floor(z)) & 255
	x -= math.floor(x)                                # FIND RELATIVE X,Y,Z
	y -= math.floor(y)                                #// OF POINT IN CUBE.
	z -= math.floor(z)
	u = fade(x)                                #COMPUTE FADE CURVES
	v = fade(y)                                #FOR EACH OF X,Y,Z.
	w = fade(z)
	A = p[X]+Y
	AA = p[A]+Z
	AB = p[A+1]+Z      # HASH COORDINATES OF
	B = p[X+1]+Y
	BA = p[B]+Z
	BB = p[B+1]+Z      # THE 8 CUBE CORNERS,
	value = lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ), grad(p[BA  ], x-1, y  , z   )), lerp(u, grad(p[AB  ], x  , y-1, z   ),  grad(p[BB  ], x-1, y-1, z   ))), lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  grad(p[BA+1], x-1, y  , z-1 )), lerp(u, grad(p[AB+1], x  , y-1, z-1 ), grad(p[BB+1], x-1, y-1, z-1 ))))
	
	global max
	global min
	if value > max:
		max = value
		
	if value < min:
		min = value

	return value


def fade(t): 
	return t * t * t * (t * (t * 6 - 15) + 10)

def lerp(t, a, b):
	return a + t * (b - a)

def grad(inhash, x, y, z):
	h = inhash & 15;                      #// CONVERT LO 4 BITS OF HASH CODE
	#u
	if h<3:
		u = x
	else:
		u = y

	#v
	if h < 4:
		v = y
	else:
		if h == 14 or h == 12:
			v = x
		else:
			v = z
	
	if (h&1) == 0:
		if (h&2) == 0:
			return u + v
		else:
			return u - v
	else:
		if (h&2) == 0:
			return -u + v
		else:
			return -u -v
	
def fbm(x,y,z,oct):
	return fBmN(x,y,z,oct)*0.3


def fBmN(x,y,z,oct):
	luc = 2.5
	val = 0.0
	weight = 1.0
	i = 0
	while i < oct:
		#print x,y,z
		val += noise(x,y,z) * weight;
		weight *= 0.5+(0.1/(i+0.1))
		x *= luc
		y *= luc
		z *= luc
		i+=1
		
	global max
	global min
	if val > max:
		max = val
		
	if val < min:
		min = val
		
	return val
	oct -= int(oct)
	if oct > (1/100000.0):
		val += oct * noise(x,y,z) * weight; 
	
	if val <= 0.0:
		return math.pow(-val,0.7)
	
	return maht.pow(val, 1 + noise(x,y,z) * val);
	
#	fValue += fOctaves * Noise(f) * m_fExponent[i]; 

exp = []
frequency = 0.0
lacunarity  = 0.0
octaves = 0.0

def initRidged(in_octaves, h, in_lacunarity):
	octaves = in_octaves
	frequency = 1.0
	lacunarity = in_lacunarity
	i = 0
	while i < octaves:
		exp.append( math.pow(frequency, -h) )
		frequency *= lacunarity
		i+=1


#start value	h = 1.0
#				offset = 1.0
#				gain = 2.0
def ridged(x,y,z,offset,gain):
	signal = noise(x,y,z)
	if signal < 0.0:
		signal = -signal
	
	signal = offset - signal
	signal *= signal
	
	result = signal
	weigth = 1.0
	
	i = 0
	while i < octaves:
		x *= lacunarity
		y *= lacunarity
		z *= lacunarity

		weight = signal * gain
		if weigth > 1.0:
			weigth = 1.0

		if weigth < 0.0:
			weigth = 0.0

		signal = noise(x,y,z)
		
		if signal < 0.0:
			signal = -signal

		signal = offset - signal
		signal *= signal
		result += signal * exp[i]
		
		i+=1

	return result

