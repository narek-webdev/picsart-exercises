//Բացել ֆայլ, որը գոյություն ունի և տեքստ է պարունակում։ 
// Կարդալ ֆայլի պարունակությունից որոշակի հատված, երկու անգամ, 
// և տպել էկրանին։

#include <stdio.h>
#define FILE_NAME "test.txt"
#define READ_N 5

int main ()
{
FILE * stream = fopen(FILE_NAME, "r");

if (stream == NULL) {
 perror("fopen");
 return 1;
}

char buff[READ_N];
size_t r = fread(buff, sizeof(char), sizeof(buff), stream);

if (ferror(stream)) {
 perror("fread");
 fclose(stream);
 return 1;
}

size_t w = fwrite(buff, sizeof(char), r, stdout);

if (w < r) {
 perror("fwrite");
 fclose(stream);
 return 1;
}

int seek_n = fseek(stream, 0, SEEK_SET);

if (seek_n) {
 perror("fseek");
 fclose(stream);
 return 1;
}

char s_buff[READ_N];
size_t second_r = fread(s_buff, sizeof(char), sizeof(s_buff), stream);

if (ferror(stream)) {
 perror("fread");
 fclose(stream);
 return 1;
}

size_t second_w = fwrite(s_buff, sizeof(char), second_r, stdout);

if (second_w < second_r) {
 perror("fwrite");
 fclose(stream);
 return 1;
}

if (fclose(stream) == EOF) {
 perror("Error");
 return 1;
}

stream = NULL;

return 0;
}