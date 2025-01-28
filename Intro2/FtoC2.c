#include <stdio.h>

int main(){
    float fFahrenheit=0, fCelcius=0;
    printf("Enter tempreture in Fehrenheit: ");
    scanf("%f", &fFahrenheit);

    fCelcius = (fFahrenheit - 32) / 9 * 5;
    printf("%6.1fF is %2.1fC\n", fFahrenheit, fCelcius);

    return 0;
}