#include <stdio.h>
#include <math.h>

int factorial (int n);
double sinX(double x);
double cosX(double x);
double enterDouble();
void printError();

int main () {
	double function = 0;
	double a, b, i;

	printf("\n%lf", sinX(5));
	printf("\n%lf", cosX(5));
	
	printf("\n Enter 'a'\n->");
	a = enterDouble();
	printf("\n Enter 'b'\n->");
	b = enterDouble();
	
	for (i = a; i <= b; i += 0.1) {
		function += pow(sinX(i), 2) / (1 + pow(cosX(i), 3));
	}
	
	printf("\n Result: %f\n", function);
	
	return 0;
}

double enterDouble() {
	double num = 0;
	int res;
	
	do {
		res = scanf("%lf", &num);
		fflush(stdin);
		
		if(res != 1) printf("\n Incorrect input!\n->");
	} while (res != 1);
	return num;
}

void printError() {
	printf("\n Something went wrong :/\n->");
}

double sinX(double x) {
	int i = 0;
	double res, sum = 0;
	do {
		res = pow((-1), i) * (pow(x, 2 * i + 1) / factorial(2 * i + 1));
		sum += res;
		i++;
	} while (fabs(res) > 0.1);
	return sum;
}

double cosX(double x) {
	int i = 0;
	double res, sum = 0;
	do {
		res = pow((-1), i) * (pow(x, 2 * i) / factorial(2 * i));
		sum += res;
		i++;
	} while (fabs(res) > 0.1);
	return sum;
}

int factorial (int n) {
  return (n < 2) ? 1 : n * factorial (n - 1);
}
