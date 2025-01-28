#include <stdio.h>

int main(){
    int iFahrenheit=74, iCelcius=0;
    iCelcius = (iFahrenheit - 32);
    printf("%dF is %dC\n", iFahrenheit, iCelcius);
    
    float fFahrenheit=74, fCelcius=0;
    fCelcius = (fFahrenheit - 32) / 9 * 5;
    printf("%6.1fF is %2.1fC\n", fFahrenheit, fCelcius);

    return 0;
}