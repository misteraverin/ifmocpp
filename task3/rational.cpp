#include "rational.h"

class rational{
  private:
    int denominator, numerator;


    void stabilizator(){
      int total = gcd(denominator, numerator);
      denominator = denominator / total;
      numerator = numerator / total;    
    }


    int gcd (int a, int b) {
      if (b == 0)
        return a;
      else
        return gcd (b, a % b);
    }


  public:
    
    rational(int num, int denom){  
      denominator = denom;
      numerator = num;
      stabilizator();
    }


    rational(int num){
      numerator = num;
    }    


    int getNum() const{
      return numerator;
    }


    int getDenom() const{
      return denominator;
    }


    rational operator*(const rational &a) const{
      return rational(this->numerator * a.numerator, this -> denominator * a.denominator);        
    }


    rational operator/(const rational &a) const{
      return rational(this->numerator * a.denominator, this -> denominator * a.numerator);        
    }


    rational operator+(const rational &a) const{
      return rational(this->numerator * a.denominator + a.numerator * this->denominator, this -> denominator * a.denominator);        
    }


    rational operator-(const rational &a) const{
      return rational(this->numerator * a.denominator - a.numerator * this->denominator, this -> denominator * a.numerator);        
    }


};
