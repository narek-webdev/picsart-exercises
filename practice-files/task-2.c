//Գրել ծրագիր, որը կտպի էկրանին ֆայլի մասին ինֆորմացիա.
//Ֆայլի չափը՝ բայթերով
//Ֆայլի մեջ տողերի քանակը
//Յուրաքանչյուր սիմվոլի քանակը

#include <stdio.h>
#define FILE_NAME "a.txt"
#define BUFFER_SIZE 1024

int main ()
{
FILE * stream = fopen(FILE_NAME, "r");

if (stream == NULL)
{
 perror("fopen");
 return 1;
}

if (fseek(stream, 0, SEEK_END))
{
 perror("fseek");
 fclose(stream);
 return 1;
}

long bytes_count = ftell(stream);

if (bytes_count < 0)
{
 perror("ftell");
 fclose(stream);
 return 1;
}

rewind(stream);

int lines = 0;
char buff[BUFFER_SIZE];
while (fgets(buff, sizeof(buff), stream) != NULL)
{
 ++lines;
}

if (fclose(stream) == EOF)
{
 perror("fclose");
 return 1;
}

printf("Bytes count: %ld \n", bytes_count);
printf("Lines count: %d \n", lines);

return 0;
}
