class rational{
  private:    
   int denominator, numerator;
   void stabilizator();
   int gcd(int a, int b);
  public:    
    rational(int num, int denom);
    rational(int num);
    int getNum() const;
    int getDenom() const;
    rational operator+(const rational &a) const;
    rational operator-(const rational &a) const;
    rational operator*(const rational &a) const;
    rational operator/(const rational &a) const;
};