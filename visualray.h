//GitHub: https://github.com/Dxftoro
#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <fstream>
//#include "colors.h"

//двумерный вектор
struct vec2 {
	float x = 0.0;
	float y = 0.0;

	vec2() {}
	vec2(float val) : x(val), y(val) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}

	vec2 operator + (vec2 const& b) { return vec2(x + b.x, y + b.y); }
	vec2 operator - (vec2 const& b) { return vec2(x - b.x, y - b.y); }
	vec2 operator * (vec2 const& b) { return vec2(x * b.x, y * b.y); }
	vec2 operator / (vec2 const& b) { return vec2(x / b.x, y / b.y); }

	vec2 operator += (vec2 const& b) { return vec2(x + b.x, y + b.y); }
	vec2 operator -= (vec2 const& b) { return vec2(x - b.x, y - b.y); }
	vec2 operator *= (vec2 const& b) { return vec2(x * b.x, y * b.y); }
	vec2 operator /= (vec2 const& b) { return vec2(x / b.x, y / b.y); }

	float length() { return sqrt(x * x + y * y); }
	float distance(vec2 b) { return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2)); }
};
//трёхмерный вектор
struct vec3 {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	vec3() {}
	vec3(float val) : x(val), y(val), z(val) {}
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	vec3 operator + (vec3 const& b) { return vec3(x + b.x, y + b.y, z + b.z); }
	vec3 operator - (vec3 const& b) { return vec3(x - b.x, y - b.y, z - b.z); }
	vec3 operator * (vec3 const& b) { return vec3(x * b.x, y * b.y, z * b.z); }
	vec3 operator / (vec3 const& b) { return vec3(x / b.x, y / b.y, z / b.z); }

	vec3 operator += (vec3 const& b) { return vec3(x + b.x, y + b.y, z + b.z); }
	vec3 operator -= (vec3 const& b) { return vec3(x - b.x, y - b.y, z - b.z); }
	vec3 operator *= (vec3 const& b) { return vec3(x * b.x, y * b.y, z * b.z); }
	vec3 operator /= (vec3 const& b) { return vec3(x / b.x, y / b.y, z / b.z); }

	float length() { return sqrt(x * x + y * y + z * z); }
	float distance(vec3 b) { return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2) + pow(b.z - z, 2)); }
};

int clamp(int x, int inf, int sup) {
	if (x < inf) x = inf;
	else if (x > sup) x = sup;

	return x;
}
float clamp(float x, float inf, float sup) {
	if (x < inf) x = inf;
	else if (x > sup) x = sup;

	return x;
}

float length(vec2 a) { return sqrt(a.x * a.x + a.y * a.y); }
float distance(vec2 a, vec2 b) { return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2) ); }
vec2 normalise(vec2 a) { return a / length(a); }

float length(vec3 a) { return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
float distance(vec3 a, vec3 b) { return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2) ); }

vec3 normalise(vec3 a) { return a / length(a); }
float con(vec3 const& a, vec3 const& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

vec2 sphereInter(vec3 veca, vec3 vecb, float radius) {
	float b = con(veca, vecb);
	float c = con(veca, veca) - radius * radius;
	float h = b * b - c;

	if (h < 0) return vec2(-1);
	h = sqrt(h);

	return vec2(-b - h, -b + h);
}

int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int getConsoleHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void handleConsole(HANDLE& Console, DWORD& BytesWritten) {
	Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(Console);
	BytesWritten = 0;
}

struct ConsoleBuffer {
	HANDLE Console;
	DWORD BytesWritten;

	void Handle() {
		Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(Console);
		BytesWritten = 0;
	}
};

class Frame {
public:
	unsigned int width = 120;
	unsigned int height = 30;
	float pixel_width = 11.0;
	float pixel_height = 24.0;

	float screen_scale = (float)width / height;
	float pixel_scale = (float)pixel_width / pixel_height;

	char* buff; //<<<<------------------------
	char empty_sym = ' ';

	std::string shade_gradient = ".:!/r(l1Z4H9W8$@";
	size_t shade_size = shade_gradient.size();

	//заполнение кадра пустыми символами
	void clearBuff() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				this->buff[i + j * width] = empty_sym;
			}
		}
	}

	Frame(unsigned int _width = 120, unsigned int _height = 30) {
		this->width = _width;
		this->height = _height;

		buff = new char[width * height + 1];
		buff[this->width * this->height] = '\0';
		this->clearBuff();
	}
	~Frame() {
		delete[] buff;
	}

	void setScreenSize(int new_width, int new_height) {
		this->width = new_width;
		this->height = new_height;

		this->buff = new char[new_width * new_height + 1];
		buff[new_width * new_height] = '\0';
		this->clearBuff();
	}

	void setPixelSize(int new_width, int new_height) {
		this->pixel_width = new_width;
		this->pixel_height = new_height;
		this->pixel_scale = (float)pixel_width / pixel_height;
	}

	//изменение градиента затемнения объектов
	void setShadeGradient(std::string gradient_str) {
		this->shade_gradient = gradient_str;
		this->shade_size = shade_gradient.size();
	}

	//отрисовка кадра
	void drawBuff() {
		std::cout << buff;
	}
	void drawBuffA(HANDLE Console, DWORD BytesWritten, bool showInfo = true) {
		if (showInfo) {
			sprintf_s(buff, 16, "VisualRay v0.1a");
		}
		WriteConsoleOutputCharacterA(Console, buff, width * height, { 0, 0 }, &BytesWritten);
	}
	void drawBuffA(ConsoleBuffer cBuff, bool showInfo = true) {
		if (showInfo) {
			sprintf_s(buff, 16, "VisualRay v0.1a");
		}
		WriteConsoleOutputCharacterA(cBuff.Console, buff, width * height, { 0, 0 }, &cBuff.BytesWritten);
	}

	void setPixel(char sym, int solid_x, int solid_y) {
		solid_x = clamp(solid_x, 0, this->width);
		solid_y = clamp(solid_y, 0, this->height);
		this->buff[solid_x + solid_y * width] = sym;
	}

	//функции отрисовки базовой геометрии

	//прямоугольник
	void drawBox(vec2 pos = vec2(0), vec2 size = vec2(.1, .1), char filler = '#') {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {

				float x = (float)i / width * 2.0f - 1.0f;
				float y = (float)j / height * 2.0f - 1.0f;

				x *= screen_scale * pixel_scale;

				if ((x - pos.x >= -size.x && x - pos.x <= size.x) && (y - pos.y >= -size.y && y - pos.y <= size.y)) this->buff[i + j * width] = filler;
			}
		}
	}
	//эллипс
	void drawEllipse(vec2 pos = vec2(0), vec2 size = vec2(.1, .1), char filler = '#') {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				float x = (float)i / width * 2.0f - 1.0f;
				float y = (float)j / height * 2.0f - 1.0f;

				x *= screen_scale * pixel_scale;

				if (pow(x - pos.x, 2) / size.x + pow(y - pos.y, 2) / size.y <= 1) this->buff[i + j * width] = filler;
			}
		}
	}
	//плоскость...
	void drawPlane(vec2 pos1 = vec2(0), vec2 pos2 = vec2(0), bool negation = true, char filler = '#') {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				float x = (float)i / width * 2.0f - 1.0f;
				float y = (float)j / height * 2.0f - 1.0f;

				x *= screen_scale * pixel_scale;

				if ((x - pos1.x) / (pos2.x - pos1.x) <= (y - pos1.y) / (pos2.y - pos1.y)) {
					if (buff[i + j * width] != empty_sym && negation) this->buff[i + j * width] = empty_sym;
					else this->buff[i + j * width] = filler;
				}
			}
		}
	}
	//3д сфера (бета)
	void drawSphere(float radius = 1.0, vec3 camera = vec3(-1.5, 0, 0), vec3 light = vec3(-0.5, 0.5, -1.0)) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				float x = (float)i / width * 2.0f - 1.0f;
				float y = (float)j / height * 2.0f - 1.0f;

				x *= screen_scale * pixel_scale;

				vec2 base = vec2(x, y);
				vec3 rd = normalise(vec3(1, base.x, base.y));
				vec2 intersection = sphereInter(camera, rd, radius);

				if (intersection.x > 0) {
					vec3 inter3d = camera + rd * intersection.x;
					vec3 interNormal = normalise(inter3d);
					float diff = con(interNormal, light);

					int shade = (float)(diff * shade_size);
					shade = clamp(shade, 0, shade_size - 1);

					this->buff[i + j * width] = shade_gradient[shade];
				}
			}
		}
	}
};