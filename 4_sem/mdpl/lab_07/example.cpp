#include <iostream>
int main()
{  
    // int a=10, b;
    int i = 0;
    __asm(
    "mov eax, 1\n\t"
    "mov %0, eax\n\t"
    :"=r"(i)
    :"r"(i)
    :"eax");
    std::cout << i;
return 0;
}