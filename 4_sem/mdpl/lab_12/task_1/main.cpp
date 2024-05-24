#include <stddef.h>
#include <iostream>
int len(const char *str)
{
  size_t length = 0;
  asm volatile (
        "mov x0, %1\n"        // Поместить адрес строки в x0
        "mov x1, #0\n"        // Счетчик длины в x1
        "1:\n"
        "ldrb w2, [x0], #1\n" // Загрузить байт из строки в w2 и инкрементировать x0
        "cbz w2, 2f\n"        // Если байт равен 0, перейти на метку 2
        "add x1, x1, #1\n"    // Увеличить счетчик длины
        "b 1b\n"              // Перейти обратно на метку 1
        "2:\n"
        "mov %0, x1\n"        // Поместить результат в output переменную
        : "=r" (length)       // output: length (x1)
        : "r" (str)           // input: str (x0)
        : "x0", "x1", "x2"    // clobbered registers
    );

  return length;
}
int main (int argc, char *argv[]) {
  char text[] = "abcdef1234";
  std::cout << "Строка:"<<text <<"\n";
  std::cout << "Длина :" <<len(text)<<"\n";
  return 0;
}
