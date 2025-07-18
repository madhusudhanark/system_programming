#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MEM_SIZE 2048  //2KB

char *str = "madhurk";

int main()
{
   char  *buffer  =  calloc(MEM_SIZE,MEM_SIZE);
   //buffer = NULL;
   if(!buffer)
   {
     perror("memory allocation failed\n");
     return 1;

   }
   size_t plen = strlen(str);

   for(size_t i  = 0 ; i < MEM_SIZE - plen;i += plen)
   {
     memcpy(buffer+i,str,plen);
     //buffer[i+plen];
   }
   buffer[MEM_SIZE - 1] = '\0';
   printf(" the string copied is %.64s\n",buffer);
   free(buffer);
   return 0;
}
