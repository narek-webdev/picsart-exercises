#include <stdio.h>

int main ()
{
FILE * stream = fopen("a.txt", "r");

if (stream == NULL) {
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

if (fseek(stream, 0, SEEK_SET))
{
 perror("fseek");
 fclose(stream);
 return 1;
}

int count = 0;
char ch[bytes_count];
while (fscanf(stream, "%s", ch) == 1)
{
 ++count;
}

printf("Words count is: %d\n", count);

if (fclose(stream) == EOF)
{
 perror("fclose");
 return 1;
}

return 0;
}
