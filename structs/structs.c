#include <stdio.h>
#include <string.h>
struct dataRecord {
    int intID;
    int intAge;
    float fSalary;
    char strName[100];
};
void printDataRecord(const struct dataRecord *p) {
    printf("%s is %d years old, their salary is $%.2f \n", p->strName, p->intAge, p->fSalary);
}
int main() {
    struct dataRecord John;
    John.intID=1212;
    John.intAge=21;
    John.fSalary=55420.69;
    strcpy(John.strName, "John");
    
    John.intAge=22;
    printDataRecord(&John);

    struct dataRecord *alias=0;
    alias=&John;
    alias->fSalary += 69000;
    printDataRecord(&John);

    return 0;
}