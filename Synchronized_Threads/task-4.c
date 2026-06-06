#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define ENCRYPT_KEY 'K'
#define BUFFER_SIZE 1024
#define ENCRYPTED_FILE "coded.txt"
#define INITIAL_FILE "initial.txt"

void * encrypt_worker (void * arg)
{
	FILE * stream = fopen(INITIAL_FILE, "r");

	if (stream == NULL)
	{
		perror("fopen");
		exit(1);
	}

	char * buff = malloc(BUFFER_SIZE);

	if (buff == NULL) {
		perror("malloc");
		fclose(stream);
		exit(1);
	}

	if (fgets(buff, BUFFER_SIZE, stream) != NULL) 
	{
		buff[strcspn(buff, "\n")] = '\0';
	} else {
		perror("fgets");
		fclose(stream);
		free(buff);
		exit(1);
	}

	char * encrypted_text = malloc(strlen(buff) + 1);

	if (encrypted_text == NULL)
	{
		perror("malloc");
		fclose(stream);
		free(buff);
		exit(1);
	}

	int i = 0;
	while (buff[i] != '\0')
	{
		encrypted_text[i] = buff[i] ^ ENCRYPT_KEY;
		++i;
	}

	encrypted_text[i] = '\0';

	FILE * encrypted_stream = fopen(ENCRYPTED_FILE, "w");

	if (encrypted_stream == NULL) {
		perror("fopen");
		fclose(stream);
		free(buff);
		free(encrypted_text);
		exit(1);
	}

	if (fputs(encrypted_text, encrypted_stream) == EOF)
	{
		perror("fputs");
		fclose(stream);
		fclose(encrypted_stream);
		free(buff);
		free(encrypted_text);
		exit(1);
	}

	fclose(stream);
	fclose(encrypted_stream);
	free(buff);
	free(encrypted_text);

	return NULL;
}

void * decrypt_worker (void * arg)
{
	char * filename = (char *)arg;

	FILE * stream = fopen(ENCRYPTED_FILE, "r");

	if (stream == NULL)
	{
		perror("fopen");
		exit(1);
	}

	char * buff = malloc(BUFFER_SIZE);

	if (buff == NULL)
	{
		perror("malloc");
		fclose(stream);
		exit(1);
	}

	if (fgets(buff, BUFFER_SIZE, stream) != NULL) 
	{
		buff[strcspn(buff, "\n")] = '\0';
	} else {
		perror("fgets");
		fclose(stream);
		free(buff);
		exit(1);
	}

	char * decrypted_text = malloc(strlen(buff) + 1);

	if (decrypted_text == NULL)
	{
		perror("malloc");
		fclose(stream);
		free(buff);
		exit(1);
	}

	int i = 0;
	while (buff[i] != '\0')
	{
		decrypted_text[i] = buff[i] ^ ENCRYPT_KEY;
		++i;
	}

	decrypted_text[i] = '\0';

	FILE * decrypted_stream = fopen(filename, "w");

	if (decrypted_stream == NULL)
	{
		perror("fopen");
		fclose(stream);
		free(buff);
		free(decrypted_text);
		exit(1);
	}

	if (fputs(decrypted_text, decrypted_stream) == EOF)
	{
		perror("fputs");
		fclose(stream);
		fclose(decrypted_stream);
		free(buff);
		free(decrypted_text);
		exit(1);
	}

	fclose(stream);
	fclose(decrypted_stream);
	free(buff);
	free(decrypted_text);

	return NULL;
}

int main ()
{
	char filename[100] = {0};

	printf("Write your filename: ");
	scanf("%s", filename);
	
	pthread_t encrypt_t, decrypt_t;

	if (pthread_create(&encrypt_t, NULL, encrypt_worker, NULL))
	{
		perror("pthread_create");
		return 1;
	}

	if (pthread_join(encrypt_t, NULL))
	{
		perror("pthread_join");
		return 1;
	}

	if (pthread_create(&decrypt_t, NULL, decrypt_worker, filename))
	{
		perror("pthread_create");
		return 1;
	}

	if (pthread_join(decrypt_t, NULL))
	{
		perror("pthread_join");
		return 1;
	}

	return 0;
}