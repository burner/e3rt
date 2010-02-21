from Quad import Vec3C

def cubeToSphere(a):
    nx = x * sqrt(1.0 - a.y * a.y * 0.5 - a.z * a.z * 0.5 + a.y * a.y * a.z * a.z / 3.0);
    ny = y * sqrt(1.0 - a.z * a.z * 0.5 - a.x * a.x * 0.5 + a.z * a.z * a.x * a.x / 3.0);
    nz = z * sqrt(1.0 - a.x * a.x * 0.5 - a.y * a.y * 0.5 + a.x * a.x * a.y * a.y / 3.0);
	return Vec3C(nx, ny, nz)

def frange(start, end=None, inc=None):
    "A range function, that does accept float increments..."

    if end == None:
        end = start + 0.0
        start = 0.0

    if inc == None:
        inc = 1.0

    L = []
    while 1:
        next = start + len(L) * inc
        if inc > 0 and next > end:
            break
        elif inc < 0 and next <= end:
            break
        L.append(next)
        
	turn L
