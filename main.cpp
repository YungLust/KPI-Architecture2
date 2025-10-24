#include <iostream>
#include "calculator.h"

int main(){
  Calculator calc;
      double x,y;
      std::cout << "Enter two numbers: ";
      std::cin >> x >> y;

      std::cout << "Sum: " << calc.Add(x,y) << "\n";
      std::cout << "Difference: " << calc.Sub(x,y) << "\n";
      return 0;
}
