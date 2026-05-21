//Բացել ֆայլ, որը գոյություն ունի և մի քանի տող տեքստ է պարունակում։ 
//Կարդալ և տպել էկրանին ֆայլի պարունակությունը՝ տող առ տող։

#include <stdio.h>
#define FILE_NAME "test.txt"
#define BUFFER_SIZE 1024

int main ()
{
FILE * stream = fopen(FILE_NAME, "r");

if (stream == NULL) {
 perror("fopen");
 return 1;
}

char buff[BUFFER_SIZE];

while (fgets(buff, sizeof(buff), stream) != NULL)
{
 if (fputs(buff, stdout) == EOF) {
  perror("fputs");
  fclose(stream);
  return 1;
 }
}

if (ferror(stream)) {
 perror("fgets");
 fclose(stream);
 return 1;
}

if (fclose(stream) == EOF)
{
 perror("fclose");
 return 1;
}

return 0;
}
