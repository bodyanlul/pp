#include <iostream>
#include <math.h>
#include "pthread.h"
#include <ctime>
#pragma comment(lib, "pthreadVCE2.lib")
using namespace std;
#define THREADS_COUNT 4

double f(double x) { return (3 * x * x + 2 * x + 9); }
double I(double a, double b, int n, double y) { return ((b - a) / (2 * n) * y); }

double a = 5;
double b = 15;
double n = 0.001;

struct interval {
	double left;
	double right;
	double step;
};
// _arg->left _arg->right
void* print(void* arg) {
	double *t = new double(0);
	double dy, In;
	double y = 0;
	auto _arg = (struct interval*)arg;
	/*dy = _arg->step;
		y += f(_arg->left) + f(_arg->right);
		for (int i = 1; i < 251; i++)
		{
			y += 2 * (f(_arg->left + dy * i));
		}
		In = I(_arg->left, _arg->right, _arg->step, y);
		cout << In << endl;*/

	double sum = .0;
	size_t i;
	
	for (i = 1; i < 250; ++i) {
		sum += f(_arg->left + i * _arg->step);
	}
	sum += (f(_arg->left) + f(_arg->right)) / 2;
	sum *= _arg->step;
	cout << sum << endl;
	return (void*)t;
}

int main() {
	setlocale(LC_ALL, "Russian");
	pthread_t t[THREADS_COUNT];
	interval *s = new interval[THREADS_COUNT];

	unsigned int start_time = clock();

	for (int i = 0; i < THREADS_COUNT; i++)
	{

		s[i].step = n;
	s[i].left = a + (b - a) * i / THREADS_COUNT;
	s[i].right = a + (b - a) * (i + 1) / THREADS_COUNT;
	pthread_create(&t[i], NULL, print, &s[i]);
	}
	for (int j = 0; j < THREADS_COUNT; j++)
	{
	double* result;

	pthread_join(t[j], (void**)& result);
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time; 
	cout << search_time << endl;
}