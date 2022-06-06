//g++ function.cpp -o output -l/usr/include/GL/-Iglut -IGL -IGLU

#include <iostream>
#include <random>
#include <locale>
#include "glut.h"

using namespace std;

#define SIZE 512
#define SIZE_PX 800
#define T_MAX 4
//#define CURIE_SCALE 100.

double quadSize = SIZE_PX / (double)SIZE;

short lattice[SIZE][SIZE];
double w[5];
double T = T_MAX, M, E;

int ratio = 0;
size_t nmcs = 0;
double ecum = 0, e2cum = 0, mcum = 0, m2cum = 0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			glColor3f(lattice[i][j], lattice[i][j], lattice[i][j]);
			glVertex2d(i, j+ SIZE / 8);
			glVertex2d(i, j + 1+ SIZE / 8);
			glVertex2d(i + 1, j + 1+ SIZE / 8);
			glVertex2d(i + 1, j+ SIZE / 8);
		}
	glEnd();


	glBegin(GL_QUADS);
	{
		glColor3f(1, 0, 0);
		glVertex2d(SIZE, 0);
		glVertex2d(SIZE, SIZE * T / T_MAX);
		glVertex2d(SIZE + SIZE / 8, SIZE * T / T_MAX);
		glVertex2d(SIZE + SIZE / 8, 0);

		glColor3f(1, 1, 1);

		//glVertex2d(SIZE, SIZE * 2.27 / T_MAX - SIZE / CURIE_SCALE);
		//glVertex2d(SIZE, SIZE * 2.27 / T_MAX + SIZE / CURIE_SCALE);
		//glVertex2d(SIZE + SIZE / 8, SIZE * 2.27 / T_MAX + SIZE / CURIE_SCALE);
		//glVertex2d(SIZE + SIZE / 8, SIZE * 2.27 / T_MAX - SIZE / CURIE_SCALE);
	}

	glEnd();

  glBegin(GL_QUADS);
	{
		glColor3f(0, 0, 0);
		glVertex2d(0, 0);
		glVertex2d(0,  SIZE / 8);
		glVertex2d(SIZE ,  SIZE / 8);
		glVertex2d(SIZE , 0);

		glColor3f(1, 1, 1);
	}

	glEnd();

	glutSwapBuffers();
	glFlush();
}

void calcW()
{
	double e4 = exp(-4 / T), e8 = e4 * e4;
	w[0] = w[4] = e8;
	w[1] = w[3] = e4;
	w[2] = 0;
}

void init()
{
	M = E = 0;
	static std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, RAND_MAX);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			lattice[i][j] = ((distribution(generator) / (double)RAND_MAX >= 0.5) - 1) * 2 + 1;
			M += lattice[i][j];
		}

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			E += (i + 1 != SIZE) ? lattice[i][j] * lattice[i + 1][j] : 0;
			E += (j + 1 != SIZE) ? lattice[i][j] * lattice[i][j + 1] : 0;
		}

	calcW();
}

void metropolis()
{
	int x, y, sum;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		x = rand() % SIZE;
		y = rand() % SIZE;
		sum = lattice[(x - 1 + SIZE) % SIZE][y] +
			lattice[(x + 1 + SIZE) % SIZE][y] +
			lattice[x][(y - 1 + SIZE) % SIZE] +
			lattice[x][(y + 1 + SIZE) % SIZE];

		if (sum * lattice[x][y] <= 0 || (rand() / (double)RAND_MAX) < w[sum / 2 + 2])
		{
			lattice[x][y] = -lattice[x][y];
			::ratio++;
			M += 2 * lattice[x][y];
			E -= 2 * lattice[x][y] * sum;
		}
	}
}

void timer1(int)
{
	display();

	metropolis();

	nmcs++;

	ecum += E;
	e2cum += E * E;
	mcum += M;
	m2cum += M * M;


	glutTimerFunc(10, timer1, 0);
}

void outputData(int)
{
	double norm = 1 / (double)(nmcs * SIZE * SIZE);

	cout << "Коэффициент принятия = " << ::ratio * norm << endl;
	cout << "Средняя энергия на спин = " << ecum * norm << endl;
	cout << "Средний квадрат энергии на спин = " << e2cum * norm << endl;
	cout << "Средняя намагниченность = " << mcum * norm << endl;
	cout << "Средний квадрат намагниченности = " << m2cum * norm << endl << endl;

	glutTimerFunc(10000, outputData, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': case 'W':
	{
		T += 0.01;
		T = (T >= T_MAX) ? T_MAX : T;
		calcW();
		break;
	}
	case 's': case 'S':
	{
		T -= 0.01;
		T = (T <= 0.01) ? 0.01 : T;
		calcW();
		break;
	}
	}
}

void motion(int x, int y)
{
	double k = 1 - y / (double)SIZE_PX;
	T = T_MAX * k;
	T = (T >= T_MAX) ? T_MAX : T;
	T = (T <= 0.01) ? 0.01 : T;
	calcW();
}

int main(int argc, char *argv[])
{
  glutInit(& argc, argv);
	setlocale(LC_ALL, "ru");
	init();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SIZE_PX + 100, SIZE_PX);
	glutCreateWindow("Ising model | Metropolis");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SIZE + SIZE / 8, 0, SIZE);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
	glutTimerFunc(1, timer1, 0);
	glutTimerFunc(10000, outputData, 0);

	glutMainLoop();
}
