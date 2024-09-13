#include <iostream>
#include <complex>
#include <cblas.h> 
int main() {    
  using namespace std;     
  typedef complex<double> Comp;     
  int Nr = 2, Nc = 3;   
  Comp *a = new Comp [Nr*Nc];    
  Comp *x = new Comp [Nc];
  Comp *y = new Comp [Nr];  
  Comp alpha(1, 0), beta(0, 0);     
  for (int i = 0; i < Nc; ++i) {      
    x[i] = Comp(i+1., i+2.);    
  }      
  for (int i = 0; i < Nr*Nc; ++i) {       
    a[i] = Comp(i+1., i+2.);    
  }     
  cblas_zgemv(CblasColMajor, CblasNoTrans, Nr, Nc, &alpha, a,Nr, x, 1, &beta, y, 1);    
  for (int i = 0; i < Nc; ++i) {
    cout << x[i] << "  ";    
  }    
  cout << "\n" << endl;  
  for (int i = 0; i < Nr; ++i) {       
    for (int j = 0; j < Nc; ++j) {         
      cout << a[i + Nr*j] << "  ";        
    }       
    cout << endl;     
  }    
  cout << "\n" << endl;     
  for (int i = 0; i < Nr; ++i) {         
    cout << y[i] << "  ";    
  } 
} 
