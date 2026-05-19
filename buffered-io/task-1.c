// Բացել ֆայլ fopen() ֆունկցիայով միայն գրելու համար, 
// գրել ֆայլի մեջ ինչ-որ տեքստ, փակել ֆայլը։ 
// Նորից բացել՝ կարդակու նպատակով, տպել էկրանին ֆայլի պարունակությունը։

#include <stdio.h>
#define FILE_NAME "data.txt"
#define TEXT "Hello"
#define BUFFER_SIZE 1024

int main ()
{
FILE * stream = fopen(FILE_NAME, "w");

if (stream == NULL) {
 perror("Error");
 return 1;
}

if (fputs(TEXT, stream) == EOF) {
 perror("Error");
 fclose(stream);
 return 1;
}

if (fclose(stream) == EOF) {
 perror("Error");
 return 1;
}

stream = NULL;

FILE * r_stream = fopen(FILE_NAME, "r");

if (r_stream == NULL) {
 perror("Error");
 return 1;
}

char buff[BUFFER_SIZE];
while(fgets(buff, sizeof(buff), r_stream) != NULL) {
 printf("%s", buff);
}

if (ferror(r_stream)) {
 perror("f_gets");
 fclose(r_stream);
 return 1;
}

if (fclose(r_stream) == EOF) {
 perror("Error");
 return 1;
}

r_stream = NULL;

return 0;
}