#include<iostream>
#include<Windows.h>
#include<Windowsx.h>
#include<stdlib.h>
#include "visualray.h"

int main() {

	vec3 camera = vec3(-1.5, 0, 0);
	while (true) {
		Frame frame;

		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			camera.x += 0.01;
		}
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
			camera.y -= 0.01;
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			camera.x -= 0.01;
		}
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
			camera.y += 0.01;
		}
		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) {
			camera.z -= 0.01;
		}
		if (GetAsyncKeyState((unsigned short)'E') & 0x8000) {
			camera.z += 0.01;
		}
		if (GetAsyncKeyState((unsigned short)' ') & 0x8000) camera = vec3(-1.5, 0, 0);

		frame.drawSphere(1, camera);
		frame.drawBuff();
	}

	getchar();
	return 1;
}