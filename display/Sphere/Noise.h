double fade(double t);
double lerp(double t, double a, double b);
double grad(int inhash, double x, double y, double z);
double noise(double x, double y, double z);
double snoise(double x, double y, double z);
double fbm(double x, double y, double z, int oct, float lac = 2.0f, float gain = 0.5f);
double turbulence(double x, double y, double z, int oct, float lac = 2.0f, float gain = 0.5f);
double RidgedMF(double x, double y, double z, int octaves, float lacunarity = 2.0f, float gain = 0.5f, float offset = 1.0f);
double ridge(double h, float offset);
