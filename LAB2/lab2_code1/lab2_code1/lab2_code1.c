#include <stdio.h>
int main() {
	int povtor;
	printf("Vvedit chislo n :");
	if (scanf_s("%d", &povtor) != 1) return 1;
	double iks = 0.5;
	double pi = 3.14159265358979323846;
	long long schetchik = 0;
	double result = (2.0 / iks) / pi;
	schetchik += 3;
	schetchik += 1;
	for (int i = 1; i <= povtor; i++) {
		schetchik += 1;
		double suma = 0.0;
		schetchik += 1;
		schetchik += 1;
		for (int j = 1; j <= i; j++) {
			schetchik += 1;
			suma += (2 * j - 1);
			schetchik += 4;
		}
		schetchik += 1;
		double chiselnik = 4.0 * (iks * iks - pi * pi * suma);
		schetchik += 6;
		double znamennik = pi * pi * (1.0 - 4.0 * suma);
		schetchik += 5;
		result *= chiselnik / znamennik;
		schetchik += 2;
		schetchik += 1;
	
	}
	schetchik += 1;
	printf("metod 1:\n");
	printf("resultat: %.7f\n", result);
	printf("kilkist operaciy: %lld\n", schetchik);
	return 0;
}