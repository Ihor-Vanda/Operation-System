#include <stdio.h>
#include <math.h>

int factorial (int n);
double sinX(double x);
double Sin2(double x);
double cosX(double x);
double enterDouble();
void printError();

int main () {
	double function = 0;
	double a, b, i;
	
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
		__fpurge(stdin);
		
		if(res != 1) printf("\n Incorrect input!\n->");
	} while (res != 1);
	return num;
}

void printError() {
	printf("\n Something went wrong :/\n->");
}


double sinX(double x) {
    int n = 0;
    double sum, temp;
    
	sum = temp = x;
    
	do {
        n += 2;
        temp *= -(x * x) / n / (n + 1);
        sum += temp;
    } while(fabs(temp) > 0.01);
    return sum;
}
 
double cosX(double x) {
    int n = 0;
    double sum, temp;
    
	sum = temp = 1;
    
	do {
        n +=2;
        temp *= -(x * x) / (n - 1) / n;
        sum += temp;
    } while(fabs(temp) > 0.01);
    return sum;
}