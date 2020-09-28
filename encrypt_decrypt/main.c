#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFLEN 1000
#define MAXKEYLEN 100
#define MX 5

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
  int key;
  char ch;
  printf("Enter the key: ");
  scanf("%d", &key);

  for (int i = 0; buffer[i] != '\0'; i++)
  {
    ch = buffer[i];

    if (ch >= 'a' && ch <= 'z')
    {
      ch = ch + key;

      if (ch > 'z')
      {
        ch = ch - 'z' + 'a' - 1;
      }

      buffer[i] = ch;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
      ch = ch + key;

      if (ch > 'Z')
      {
        ch = ch - 'Z' + 'A' - 1;
      }

      buffer[i] = ch;
    }
  }

  printf("%s\n", buffer);
}

void ceaser_dec(char buffer[MAXBUFLEN])
{
  //TODO: Ceaser decryption
  int key;
  char ch;

  printf("Enter the key: ");
  scanf("%d", &key);

  for (int i = 0; buffer[i] != '\0'; i++)
  {
    ch = buffer[i];
    if (ch >= 'a' && ch <= 'z')
    {
      ch = ch - key;

      if (ch < 'a')
      {
        ch = ch + 'z' - 'a' + 1;
      }

      buffer[i] = ch;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
      ch = ch - key;

      if (ch < 'A')
      {
        ch = ch + 'Z' - 'A' + 1;
      }

      buffer[i] = ch;
    }
  }
  printf("Decrypted message: %s\n", buffer);
}

void vigi_enc(char buffer[MAXBUFLEN])
{
  //TODO: Viginere encryption
  char key[MAXKEYLEN];
  printf("Enter Key: ");
  fflush(stdin);
  scanf("%[^\n]s", key);
  int message_length = strlen(buffer), count, j;
  char temp_key[message_length], encrypted_message[message_length], decrypted_message[message_length];
  for (count = 0, j = 0; count < message_length; ++count, ++j)
  {
    if (j == strlen(key))
    {
      j = 0;
    }
    temp_key[count] = key[j];
  }
  temp_key[count] = '\0';

  count = 0;
  while (count < message_length)
  {

    if (buffer[count] != ' ')
    {

      encrypted_message[count] = ((buffer[count] + temp_key[count]) % 26) + 'A';
    }

    else
      encrypted_message[count] = ' ';

    count = count + 1;
  }
  encrypted_message[count] = '\0';
  printf("encrypted message: %s\n", encrypted_message);
}

void vigi_dec(char buffer[MAXBUFLEN])
{
  //TODO: Viginere decryption
  char key[MAXKEYLEN];
  printf("Enter Key: ");
  fflush(stdin);
  scanf("%[^\n]s", key);
  int message_length = strlen(buffer), key_length = strlen(key), count, j;
  char temp_key[message_length], decrypted_message[message_length];
  for (count = 0, j = 0; count < message_length; ++count, ++j)
  {
    if (j == key_length)
    {
      j = 0;
    }
    temp_key[count] = key[j];
  }
  temp_key[count] = '\0';
  count = 0;
  while (count < message_length)
  {
    decrypted_message[count] = (((buffer[count] - temp_key[count]) + 26) % 26) + 'A';
    count = count + 1;
  }
  decrypted_message[count] = '\0';
  printf("%s\n", decrypted_message);
}

void playfair_enc(char buffer[MAXBUFLEN])
{
  //TODO: Playfair encryption
  char key[MAXKEYLEN], cleaned_key[MAXKEYLEN];
  printf("Enter Key: ");
  fflush(stdin);
  scanf("%[^\n]s", key);

  ///// KEY CLEANING
  int alph_arr[26];
  for (int i = 0; i < 26; i++)
  {
    alph_arr[i] = 0;
  }

  int count;

  for (int i = 0; key[i] != '\0'; i++)
  {
    int index = key[i] - 'A';
    if (alph_arr[index] == 0)
    {
      cleaned_key[count] = key[i];
      count++;
    }
    alph_arr[index]++;
  }
  cleaned_key[count] = '\0';
  printf("Cleaned key: %s\n", cleaned_key);
  printf("%d\n", (int)strlen(cleaned_key));

  char matrix[MX][MX];
  matrix[0][0] = cleaned_key[0];
  printf("%c\n", matrix[0][0]);

  int i = 0, j = 0;
  for (int t = 0; t < (int)strlen(cleaned_key); t++)
  {

    if (i >= MX)
    {
      i = 0;
      j++;
    }
    printf("i: %d j: %d\n", i, j);
    // matrix[0][0] = (char)cleaned_key[t];
    // printf("%c\n", cleaned_key[0]);
    i++;
  }

  // for (int l = 0; l < 26; l++)
  // {
  //   if (i >= MX)
  //   {
  //     i = 0;
  //     j++;
  //   }
  //   if (j >= MX)
  //   {
  //     break;
  //   }
  //   if (alph_arr[l] == 0)
  //   {
  //     matrix[i][j] = 'A' + alph_arr[l];
  //   }
  // }
}

void playfair_dec(char buffer[MAXBUFLEN])
{
  //TODO: Playfair decryption
  printf("PLAYFAIR DECRYPT\n");
}