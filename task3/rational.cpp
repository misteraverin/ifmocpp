#include "rational.h"


    void rational::stabilizator(){
      int total = gcd(denominator, numerator);
      denominator = denominator / total;
      numerator = numerator / total;    
    }


    int rational::gcd (int a, int b) {
      if (b == 0)
        return a;
      else
        return gcd (b, a % b);
    }


    
    rational::rational(int num, int denom){  
      denominator = denom;
      numerator = num;
      stabilizator();
    }


    rational::rational(int num){
      numerator = num;
      denominator = 1;
    }    


    int rational::getNum() const{
      return numerator;
    }


    int rational::getDenom() const{
      return denominator;
    }


    rational rational::operator*(const rational &a) const{
      return rational(this->numerator * a.numerator, this -> denominator * a.denominator);        
    }


    rational rational::operator/(const rational &a) const{
      return rational(this->numerator * a.denominator, this -> denominator * a.numerator);        
    }


    rational rational::operator+(const rational &a) const{
      return rational(this->numerator * a.denominator + a.numerator * this->denominator, this -> denominator * a.denominator);        
    }


    rational rational::operator-(const rational &a) const{
      return rational(this->numerator * a.denominator - a.numerator * this->denominator, this -> denominator * a.numerator);        
    }

