#include <iostream>
void neon_add(const int *a,const int *b,int *c,int n)
{
  int i = 0;
  for (i = 0; i < (n / 4) * 4; i += 4)
  {
    asm volatile("ld1 {v0.4s},[%[a]]\n"
    "ld1 {v1.4s},[%[b]]\n"
    "add v2.4s,v0.4s,v1.4s\n"
    "st1 {v2.4s},[%[c]]\n"
    :
    :[a]"r"(&a[i]), [b]"r"(&b[i]), [c]"r"(&c[i])
    :"v0" ,"v1","v2"
    );
  }
  for (; i<n;i++)
  {
    asm volatile(
        "ldr w0, [%[a]]\n"
        "ldr w1, [%[b]]\n"
        "add w2, w0,w1\n"
        "str w2,[%[c]]\n"
        :
        :[a]"r"(&a[i]), [b]"r"(&b[i]),[c] "r" (&c[i])
        :"w0","w1","w2"
        );
  }
}


int main (int argc, char *argv[]) {
  int a[] = {1,2,3,4,5,6,7,8};
  int b[] = {8,7,6,5,4,3,2,0};
  int c[8];
  int n = sizeof(c) / sizeof(int);
  neon_add(a,b,c,n);
  for (int i = 0; i <n;i++)
  {
    std::cout <<c[i] <<" ";
  }
  std::cout <<"\n";
  return 0;
}
