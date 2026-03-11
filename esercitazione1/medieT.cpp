using namespace std ;

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
	
	ifstream ifs(argv[1]) ;
	
	if ( ifs.is_open() ) {
		while( !ifs.eof() ) {
			
			string citta ;
			double temp_mezzn ;
			double temp_seim ;
			double temp_mezzg ;
			double temp_seis ;
			
			ifs >> citta >> temp_mezzn >> temp_seim >> temp_mezzg >> temp_seis ;
			
			if( ifs.fail() ) {
				cerr << "Error extracting from file\n" ;
				continue ;
			}
			
			double media = (temp_mezzg + temp_mezzn + temp_seim + temp_seis) / 4 ;
			
			cout << citta << "       " << media << "\n" ;
		} 
	}
	else {
		cerr << "Error: unable to open file\n" ;
	}
	return 0 ;
}