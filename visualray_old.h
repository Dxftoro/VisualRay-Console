#pragma once
#include<iostream>
#include<Windows.h>
#include<cstdlib>
#include<stdlib.h>
//#include "colors.h"

char empty = ' ';
char fill = '#';

int width = 120;
int height = 30;

float screen_scale = (float)width / height;
float pixel_scale = (float)11.0f / 24.0f;

char shade_gradient[] = ".:!/r(l1Z4H9W8$@";//".-=a#";// ".-=oaG&@"
char shade_size = std::size(shade_gradient) - 2;

//двумерный вектор
struct vec2 {
	float x = 0.0;
	float y = 0.0;

	vec2(float val) : x(val), y(val) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}

	vec2 operator + (vec2 const& b) {return vec2(x + b.x, y + b.y);}
	vec2 operator - (vec2 const& b) {return vec2(x - b.x, y - b.y);}
	vec2 operator * (vec2 const& b) {return vec2(x * b.x, y * b.y);}
	vec2 operator / (vec2 const& b) {return vec2(x / b.x, y / b.y);}

	vec2 operator += (vec2 const& b) { return vec2(x + b.x, y + b.y); }
	vec2 operator -= (vec2 const& b) { return vec2(x - b.x, y - b.y); }
	vec2 operator *= (vec2 const& b) { return vec2(x * b.x, y * b.y); }
	vec2 operator /= (vec2 const& b) { return vec2(x / b.x, y / b.y); }

	float length() { return sqrt(x * x + y * y); }
};
//трёхмерный вектор
struct vec3 {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

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
vec2 normalise(vec2 a) { return a / length(a); }

float length(vec3 a) { return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); }
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

//заполнение кадра пустыми символами
char* clearBuff(char* buff) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			buff[i + j * width] = empty;
		}
	}

	return buff;
}

//отрисовка кадра
void drawBuff(char* buff) {
	std::cout << buff;
}
void drawBuffA(char* buff, HANDLE Console, DWORD BytesWritten, bool showInfo = true) {
	if (showInfo) {
		sprintf_s(buff, 16, "VisualRay v0.1a");
	}

	WriteConsoleOutputCharacterA(Console, buff, width * height, { 0, 0 }, &BytesWritten);
}

//функции отрисовки базовой геометрии
//прямоугольник
char* drawBox(char* buff, float pos_x = 0, float pos_y = 0, float size_x = 0.1, float size_y = 0.1, char filler = fill) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			float x = (float)i / width * 2.0f - 1.0f;
			float y = (float)j / height * 2.0f - 1.0f;

			x *= screen_scale * pixel_scale;

			if ((x - pos_x >= -size_x && x - pos_x <= size_x) && (y - pos_y >= -size_y && y - pos_y <= size_y)) buff[i + j * width] = filler;
		}
	}

	return buff;
}

//эллипс
char* drawEllipse(char* buff, float pos_x = 0, float pos_y = 0, float size_x = 0.1, float size_y = 0.1, char filler = fill) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float x = (float)i / width * 2.0f - 1.0f;
			float y = (float)j / height * 2.0f - 1.0f;

			x *= screen_scale * pixel_scale;

			if (pow(x - pos_x, 2) / size_x + pow(y - pos_y, 2) / size_y <= 1) buff[i + j * width] = filler;
		}
	}

	return buff;
}

//перегрузки функций отрисовки c использованием двумерных векторов
char* drawBox(char* buff, vec2 pos = vec2(0), vec2 size = vec2(0.1, 0.1), char filler = fill) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			float x = (float)i / width * 2.0f - 1.0f;
			float y = (float)j / height * 2.0f - 1.0f;

			x *= screen_scale * pixel_scale;

			if ((x - pos.x >= -size.x && x - pos.x <= size.x) && (y - pos.y >= -size.y && y - pos.y <= size.y)) buff[i + j * width] = filler;
		}
	}

	return buff;
}

char* drawEllipse(char* buff, vec2 pos = vec2(0), vec2 size = vec2(0.1, 0.1), char filler = fill) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float x = (float)i / width * 2.0f - 1.0f;
			float y = (float)j / height * 2.0f - 1.0f;

			x *= screen_scale * pixel_scale;

			if (pow(x - pos.x, 2) / size.x + pow(y - pos.y, 2) / size.y <= 1) buff[i + j * width] = filler;
		}
	}

	return buff;
}

char* drawPlane(char* buff, vec2 pos1 = vec2(0), vec2 pos2 = vec2(0), char filler = fill) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float x = (float)i / width * 2.0f - 1.0f;
			float y = (float)j / height * 2.0f - 1.0f;

			x *= screen_scale * pixel_scale;

			if ((x - pos1.x) / (pos2.x - pos1.x) <= (y - pos1.y) / (pos2.y - pos1.y)) {
				if (buff[i + j * width] == filler) buff[i + j * width] = empty;
				else buff[i + j * width] = filler;
			}
		}
	}

	return buff;
}

char* drawSphere(char* buff, float radius = 1.0, vec3 camera = vec3(-1.5, 0, 0), vec3 light = vec3(-0.5, 0.5, -1.0), char filler = fill) {
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
				shade = clamp(shade, 0, shade_size);

				buff[i + j * width] = shade_gradient[shade];
			}
		}
	}

	return buff;
}
