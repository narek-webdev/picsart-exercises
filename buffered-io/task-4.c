//Բացել ֆայլ, որը գոյություն ունի և տեքստ է պարունակում։ 
//Բուֆերացնում է user space-ի կոնկրետ հասցեում, ապա կարդում և տպում է էկրանին ֆայլի պարունակությունը։

#include <stdio.h>
#define FILE_NAME "data.txt"
#define BUFFER_SIZE 1024

int main ()
{
FILE * stream = fopen(FILE_NAME, "r");

if (stream == NULL) {
 perror("fopen");
 return 1;
}

char buff[BUFFER_SIZE];

if (setvbuf(stream, buff, _IOFBF, sizeof(buff)) != 0) {
 perror("setvbuf");
 fclose(stream);
 return 1;
}

char readBuff[BUFFER_SIZE];

while (fgets(readBuff, sizeof(readBuff), stream) != NULL)
{
 if (fputs(readBuff, stdout) == EOF) {
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

if (fclose(stream) == EOF) {
 perror("fclose");
 return 1;
}

return 0;
}
