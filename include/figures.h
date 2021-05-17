#ifndef __FIGURES_H__
#define __FIGURES_H__

struct Rgb {
	float r, g, b;
};

class Object {

protected:
	float* vertices;
	unsigned int* indices;
	int  nv;
	int  ni;

public:
	Object(int n, int m)
			: vertices(new float[n]), indices(new unsigned int[m]), nv(n), ni(m) {}

	float* getVertices() {
		return vertices;
	}
	unsigned int* getIndices() {
		return indices;
	}
	int getVSize() {
		return nv;
	}
	int getISize() {
		return ni;
	}
};

class Cube : public Object {
	float  width;
	float  height;
	float  depth;

public:
	Cube(float width=1.0f, float height=1.0f, float depth=1.0f,
	     Rgb a={1.0f, 1.0f, 1.0f}, Rgb b={1.0f, 0.0f, 0.0f},
	     Rgb c={1.0f, 1.0f, 0.0f}, Rgb d={0.0f, 1.0f, 1.0f},
	     Rgb e={1.0f, 0.0f, 1.0f}, Rgb f={0.0f, 1.0f, 0.0f})
			: Object(24*8, 6*6), width(width), height(height), depth(depth) {
		float wm =  width / 2.0f;
		float hm = height / 2.0f;
		float dm =  depth / 2.0f;
		float temp[] = {
			// posiciones       colores        texturas
			-wm,  hm,  dm,   a.r, a.g, a.b,   0.0f, 1.0f,  // 0
			 wm,  hm,  dm,   a.r, a.g, a.b,   1.0f, 1.0f,  // 1
			-wm, -hm,  dm,   a.r, a.g, a.b,   0.0f, 0.0f,  // 2
			 wm, -hm,  dm,   a.r, a.g, a.b,   1.0f, 0.0f,  // 3

			-wm,  hm,  dm,   b.r, b.g, b.b,   0.0f, 1.0f,  // 4
			 wm,  hm,  dm,   b.r, b.g, b.b,   1.0f, 1.0f,  // 5
			-wm,  hm, -dm,   b.r, b.g, b.b,   1.0f, 1.0f,  // 6
			 wm,  hm, -dm,   b.r, b.g, b.b,   0.0f, 1.0f,  // 7

			 wm,  hm,  dm,   c.r, c.g, c.b,   1.0f, 1.0f,  // 8
			 wm,  hm, -dm,   c.r, c.g, c.b,   0.0f, 1.0f,  // 9
			 wm, -hm,  dm,   c.r, c.g, c.b,   1.0f, 0.0f,  // 10
			 wm, -hm, -dm,   c.r, c.g, c.b,   0.0f, 0.0f,  // 11

			-wm, -hm,  dm,   d.r, d.g, d.b,   0.0f, 1.0f,  // 12
			 wm, -hm,  dm,   d.r, d.g, d.b,   1.0f, 1.0f,  // 13
			-wm, -hm, -dm,   d.r, d.g, d.b,   1.0f, 1.0f,  // 14
			 wm, -hm, -dm,   d.r, d.g, d.b,   0.0f, 1.0f,  // 15

			-wm,  hm,  dm,   e.r, e.g, e.b,   1.0f, 1.0f,  // 16
			-wm,  hm, -dm,   e.r, e.g, e.b,   0.0f, 1.0f,  // 17
			-wm, -hm,  dm,   e.r, e.g, e.b,   1.0f, 0.0f,  // 18
			-wm, -hm, -dm,   e.r, e.g, e.b,   0.0f, 0.0f,  // 19

			-wm,  hm, -dm,   f.r, f.g, f.b,   1.0f, 1.0f,  // 20
			 wm,  hm, -dm,   f.r, f.g, f.b,   0.0f, 1.0f,  // 21
			-wm, -hm, -dm,   f.r, f.g, f.b,   1.0f, 0.0f,  // 22
			 wm, -hm, -dm,   f.r, f.g, f.b,   0.0f, 0.0f   // 23
		};
		for (int i = 0; i < nv; ++i) {
			vertices[i] = temp[i];
		}
		for (int i = 0; i < 6; ++i) {
			indices[i*6 + 0] = i*4 + 0;
			indices[i*6 + 1] = i*4 + 1;
			indices[i*6 + 2] = i*4 + 2;
			indices[i*6 + 3] = i*4 + 1;
			indices[i*6 + 4] = i*4 + 2;
			indices[i*6 + 5] = i*4 + 3;
		}
	}
};

#endif
