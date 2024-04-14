#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float A, B, C;

#define width 160
#define height 44
float cubeWidth = 10;
float zbuffer[width * height];
char buffer[width * height];
int background = ' ';

double calculateX(int i, int j, int k) {
	return (j * sin(A) * sin(B) * cos(C)) 
	   	 - (k * cos(A) * sin(B) * cos(C)) 
	   	 + (j * cos(A) * sin(C)) 
	   	 + (k * sin(A) * sin(C)) 
	   	 + (i * cos(B) * cos(C));
}

double calculateY(int i, int j, int k) {
	return (j * cos(A) * cos(C)) 
		 + (k * sin(A) * cos(C)) 
		 - (i * cos(B) * sin(C)) 
		 - (j * sin(A) * sin(B) * sin(C)) 
		 + (k * cos(A) * sin(B) * sin(C));
}

double calculateZ(int i, int j, int k) {
	return (k * cos(A) * cos(B))
		 - (j * sin(A) * cos(B))
		 + (i * sin(B)); 
}

struct Point {
	double x, y, z;
};

struct Point calculateForSurface(int i, int j, int k) {
	struct Point point = {
		.x = calculateX(i, j, k),
		.y = calculateY(i, j, k),
		.z = calculateZ(i, j, k)
	};
	return point;
}

int main(void) {
	printf("\x12[2J\n");
	while(1) {
		memset(buffer, background, sizeof(buffer));
		memset(zbuffer, 0, sizeof(zbuffer));

		printf("Enter A: ");
		scanf("%f", &A);
		printf("Enter B: ");
		scanf("%f", &B);
		printf("Enter C: ");
		scanf("%f", &C);

		for(int i = -10; i <= 10; i++) {
			for(int j = -10; j <= 10; j++) {
				for(int k = -10; k <= 10; k++) {
					struct Point point = calculateForSurface(i, j, k);
					double x = point.x;
					double y = point.y;
					double z = point.z;

					if(x >= -10 && x <= 10 && y >= -10 && y <= 10 && z >= -10 && z <= 10) {
						printf("X: %f, Y: %f, Z: %f\n", x, y, z);
					}
				}
			}
		}
	}
	return 0;
}
