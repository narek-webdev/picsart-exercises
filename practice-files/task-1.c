#include <stdio.h>

int main ()
{
FILE * stream = fopen("a.txt", "r");

if (stream == NULL) {
 perror("fopen");
 return 1;
}

int count = 0;
int ch;
while ((ch = fgetc(stream)) != EOF)
{
 if (ch >= '0' && ch <= '9')
 {
  ++count;
 }
}

if (ferror(stream))
{
 perror("fgetc");
 fclose(stream);
 return 1;
}

if (fclose(stream) == EOF)
{
 perror("fclose");
 return 1;
}

FILE * bstream = fopen("b.txt", "w");

if (bstream == NULL) {
 perror("fopen");
 return 1;
}

if (fprintf(bstream, "Your count is %i\n", count) < 0) {
    perror("fprintf");
    fclose(bstream);
    return 1;
} 

if (fclose(bstream) == EOF)
{
 perror("fclose");
 return 1;
}

return 0;
}
