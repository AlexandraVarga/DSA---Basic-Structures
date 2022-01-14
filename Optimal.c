#include <stdio.h>

int n = 7;
int a[] = {1, 5, 10, 50, 100, 200, 500};

int descompune(int x){
  //se afiseaza decompunerea optimala si se returneaza numarul de termeni
  int s = 0;
  int nr = 0;
  printf("Suma = %d\nDecompunerea optimala: ", x);
  while (s != x)
  {
      int i = 6;
      while (s + a[i] > x)
          i--;
      s += a[i];
      printf("%d ", a[i]);
      nr++;
  }
  return nr;
}

int test(int testi, int x, int ans){
  int rez = descompune(x);
  if (ans == rez)
    printf("\nTest %d corect, rezultat: %d, asteptat: %d\n\n", testi, rez, ans);
  else
    printf("\nTest %d incorect, rezultat: %d, asteptat: %d\n\n", testi, rez, ans);
}

int main(){
  int testi=0;
  int xs[] = {7,130,1,741,2000};
  int ans[] = {3,4,1,7,4};
  for(testi=0; testi<sizeof(xs)/sizeof(int); testi++)
    test(testi, xs[testi], ans[testi]);
  return 0;
}
