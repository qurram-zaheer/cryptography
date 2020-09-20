#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFLEN 1000

char *CEASER = "ceaser";
char *VIGINERE = "viginere";
char *PLAYFAIR = "playfair";

int cipher_hash(char *cipher_name);
void overlord(int cipher_hash, int process);
char *read_file();

void ceaser_enc(char buffer[MAXBUFLEN]);
void ceaser_dec(char buffer[MAXBUFLEN]);

void vigi_enc(char buffer[MAXBUFLEN]);
void vigi_dec(char buffer[MAXBUFLEN]);

void playfair_enc(char buffer[MAXBUFLEN]);
void playfair_dec(char buffer[MAXBUFLEN]);

void main(int argc, char *argv[])
{

  /* ----------------------------- INPUT CLEANING ----------------------------- */

  if (argc == 1)
  {
    printf("usage: ./a.out <cipher-name> <enc/dec>\n");
    exit(0);
  }

  else if (argc == 2 && strcmp("-h", argv[1]) == 0)
  {
    printf("<cipher-name>\tceaser/viginere/playfair\n<enc/dec>\tencrypt/decrypt\n");
    exit(0);
  }
  else if (argc != 3)
  {
    printf("Please follow the right input format: <cipher-name> <enc/dec>\n");
    exit(0);
  }

  if (strcmp(argv[2], "enc") != 0 && strcmp(argv[2], "dec") != 0)
  {
    printf("usage: ./a.out <cipher-name> <enc/dec>\n");
    exit(0);
  }

  if (strcmp("enc", argv[2]) == 0)
  {
    overlord(cipher_hash(argv[1]), 0);
  }
  else
  {
    overlord(cipher_hash(argv[1]), 1);
  }
}

/* --------------- MAPPING CIPHER NAMES TO INTEGERS -------------- */

int cipher_hash(char *cipher_name)
{
  printf("%s\n", cipher_name);
  if (strcmp(cipher_name, CEASER) == 0)
  {
    return 0;
  }
  else if (strcmp(cipher_name, VIGINERE) == 0)
  {
    return 1;
  }
  else if (strcmp(cipher_name, PLAYFAIR) == 0)
  {
    return 2;
  }
  else
  {
    printf("unsupported cipher, please try again with: ceaser/viginere/playfair\n");
    exit(0);
  }
}

/* ---------------------------- Read process.txt ---------------------------- */

char *read_file(char *buffer)
{
  FILE *fptr;

  fptr = fopen("process.txt", "r");

  if (fptr == NULL)
  {
    printf("Failed to open file, exiting...\n");
    exit(0);
  }
  size_t new_len = fread(buffer, sizeof(char), MAXBUFLEN, fptr);
  if (ferror(fptr) != 0)
  {
    printf("Error reading file\n");
    exit(0);
  }
  else
  {
    buffer[new_len++] = '\0';
  }

  fclose(fptr);
  printf("B1: %s\n", buffer);
  return buffer;
}

/* --------------------------- HANDLING CORE LOGIC -------------------------- */

void overlord(int cipher_hash, int process)
{
  char buffer[1000];

  char *buf_ptr = read_file(buffer);
  printf("%d, %d\n", cipher_hash, process);
  printf("%s\n", buffer);
  switch (cipher_hash)
  {
  case 0:
    if (process == 0)
    {
      ceaser_enc(buffer);
    }
    else
    {
      ceaser_dec(buffer);
    }
    break;
  case 1:
    if (process == 0)
    {
      vigi_enc(buffer);
    }
    else
    {
      vigi_dec(buffer);
    }
    break;
  case 2:
    if (process == 0)
    {
      playfair_enc(buffer);
    }
    else
    {
      playfair_dec(buffer);
    }
    break;
  default:
    printf("Hashing error, please try again\n");
    exit(0);
  }
}

void ceaser_enc(char buffer[MAXBUFLEN])
{
  //TODO: Ceaser encryption
  printf("CEASER ENCRYPT\n");
}

void ceaser_dec(char buffer[MAXBUFLEN])
{
  //TODO: Ceaser decryption
  printf("CEASER DECRYPT\n");
}

void vigi_enc(char buffer[MAXBUFLEN])
{
  //TODO: Viginere encryption
  printf("VIGINERE ENCRYPT\n");
}

void vigi_dec(char buffer[MAXBUFLEN])
{
  //TODO: Viginere decryption
  printf("VIGINERE DECRYPT\n");
}

void playfair_enc(char buffer[MAXBUFLEN])
{
  //TODO: Playfair encryption
  printf("PLAYFAIR ENCRYPT\n");
}

void playfair_dec(char buffer[MAXBUFLEN])
{
  //TODO: Playfair decryption
  printf("PLAYFAIR DECRYPT\n");
}