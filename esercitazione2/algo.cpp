#include <iostream>
#include <cmath>
using namespace std ;

int main(void) {
	
	static const int N = 5 ;
	double arr[N] = {1.1, 7.3, 9.5, 4.0, 5.2} ;
	
	// MINIMO
	
	double min = arr[0] ;
	
	for(int i = 1 ; i < N ; i++) {
		if(arr[i] < min) {
			min = arr[i] ;
		}
		else {
			continue ;
		}
		
		
	}
	
	cout << "Minimo = " << min << "\n" ;
	
	//MASSIMO
	double max = arr[0] ;
	
	for(int i = 1 ; i < N ; i++) {
		if(arr[i] > max) {
			max = arr[i] ;
		}
		else {
			continue ;
		}
		
		
	}
	
	cout << "Massimo = " << max << "\n" ;
	
	// MEDIA
	
	double somma = 0 ;
	for(int i=0 ; i < N ; i++) {
		somma += arr[i] ;
	}
	
	double media = somma / N ;
	
	cout << "Media = " << media << "\n" ;
	
	//DEVIAZIONE STANDARD
	double somma_ds = 0 ;
	for (int i = 0 ; i < N ; i ++) {
		double quadrato = (arr[i] - media) * (arr[i] - media) ;
		somma_ds += quadrato ;
	}
	
	double argo_rad = somma_ds / N ;
	
	double sigma = sqrt(argo_rad) ;
	
	cout << "Deviazione standard = " << sigma << "\n" ;
	
	return 0 ;
}