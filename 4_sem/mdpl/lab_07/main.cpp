#include <iostream>

extern "C"
{
    void testAsm(); // подключение в код на Си/Си++ функции
    void memmove_asm(const char *str_1, char *str_2, int len); // подключение в код на Си/Си++ функции
    // на другом языке программирования,
    // выполненной в соответствии с соглашениями
    // о вызовах Си
}
int strlen_asm(const char *str)
{
    int len = 0;
    __asm(
        "mov     rsi, %1 \n\t"
        "mov     ecx, -1 \n\t"
        "mov     al, 0 \n\t"
        "repne   scasb \n\t"
        "not     ecx \n\t"
        "dec     ecx \n\t"
        "mov     %0, ecx \n\t"
        : "=r"(len)
        : "r"(str)
        : "%rsi", "%ecx");
    return len;
}
int main()
{
    // std::cout << "Длина строк\n";
    // int i = strlen_asm("12345");
    // std::cout << "12345 : " << i << '\n';

    // i = strlen_asm("123456");
    // std::cout << "123456 : " << i << '\n';

    // std::cout << "Копирование\n";
    // char str_1[] = "1234567890";
    // char str_2[20] = "";
    // std::cout << str_1 << '\n' << str_2 <<'\n';
    // memmove_asm(str_1, str_2, sizeof(str_1));
    // std::cout << str_1 << '\n' << str_2 <<'\n';

    std:: cout << "Демонстрация\n\n";

    char s_1[50] = "123456789 jkmjknijn0";
    char *s_2 = s_1 + 7;
    memmove_asm(s_1, s_2, strlen_asm(s_1));
    std::cout << s_2 << "\n";
    return 0;
}