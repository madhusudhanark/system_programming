/*has extern , function passing , function pointer , typdef ,ifndef, multiple files compilation
 using of -x and -E for compiling ,*/

#include <stdio.h>
#include <stdint.h>
#include "headers.h"
#include <float.h>


void replace_char(char *name)
{
  int i;
  while(name[i] != '\0')
  {
    if(name[i] == 'd')
    {
      name[i] = 'D';
    }
    i++;

  }


}
int main()
{
  static int age;
  char *name1 = "madhusudhana Rk";
  char name[16] = "madhusudhana Rk";
  printf("name address ,%p\n, string literal address %lu\n",name,sizeof(name1));
  replace_char(name);
  printf("the name after replacing the d with D  %s\n",name);
  getchar(); // pause for manual inspection
  return 0;
}