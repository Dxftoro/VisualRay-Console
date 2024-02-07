#include<iostream>
#include<stdlib.h>
#include "visualray.h"

int main() {
	float radius = 0.8;
	while (true) {
		for (int t = 0; t < 100000; t++) {
			Frame frame;
			vec2 pos = vec2(0);
			pos.x += sin(t * 0.006) * radius;
			pos.y += cos(t * 0.006) * radius;
			frame.drawEllipse(pos, vec2(0.15, 0.15));
			frame.drawEllipse(pos * -1, vec2(0.15, 0.15));

			frame.drawPlane(vec2(0), vec2(0, -1));

			frame.drawBuff();
		}
	}

	getchar();
	return 1;
}