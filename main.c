#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct
{
  int kind;
  char name[12];
  int val;
  int level;
  int addr;
} symbol;

symbol symbol_table[500];
int symPointer = 0;

char word[12];
int wordPointer = 0;


// HW 3 functions
void parse(FILE*);
void declConst(FILE*);
int declVar(FILE*);
int scanWord(FILE*);
int symTableCheck(char[], int);
void resetWord();
bool errCheck(FILE*, char);

int main(int argc, char *argv[])
{
  FILE *input = fopen(argv[1], "r");

  parse(input);


  fclose(input);

  return 0;
}


void parse (FILE *input)
{

  while (1)
  {
    resetWord();

    int result = scanWord(input);

    if (result == 50)
      break;

    //printf("This is the word so far: %s\n", word);
    //printf("The character that broke the word is: %c\n\n", holder)

    //printf("%s%c", word, holder);

    // Check to make sure it's not a constant

    if (strcmp(word, "3") == 0)
    {
      // Constant number
      declConst(input);
    }
    else if (strcmp(word, "29") == 0)
    {
      while (strcmp(word, "18") != 0)
      {
        resetWord();
        result = scanWord(input);

        if (result == 50)
          return;

        if (strcmp(word, "2") == 0)
        {
          printf("New variable declared: ");

          declVar(input);

          resetWord();
          result = scanWord(input);

          if (result == 50)
            return;
          else if (strcmp(word, "17") == 0 || strcmp(word, "18") == 0)
            continue;
        }
      }

    }

  }

}

void declConst(FILE *input)
{
  char num[100];
  int numPoint = 0;

  for (int i = 0; i < 100; i++)
    num[i] = 0;

  // Build the number digit-by-digit here
  while (1)
  {
    resetWord();
    char holder = fgetc(input);

    // Stop building the value once a space is reached
    if (holder == ' ')
    {
      printf("Number found: %s\n\n", num);
      break;
    }

    num[numPoint] = holder;
    numPoint++;

  }
}

int declVar(FILE *input)
{
  int numVars = 0, namePointer = 0;

  char name[12];

  for (int i = 0; i < 12; i++)
    name[i] = 0;

  numVars++;

  while (namePointer < 12)
  {
    char holder = fgetc(input);

    if (holder == ' ')
    {
      // if token != identsym
      if (isdigit(3))
      {
        printf("ERROR: NO. THAT'S NOT IT. IT'S THE THING.\n\n");
        break;
      }
      if (symTableCheck(name, 2) != -1)
      {
        printf("ERROR: Name %s already taken.\n\n", name);
        break;
      }

      symbol_table[symPointer].kind = 2;
      strcpy(symbol_table[symPointer].name, name);
      symbol_table[symPointer].val = 0;
      symbol_table[symPointer].level = 0;
      symbol_table[symPointer].addr = 3;

      symPointer++;

      break;
    }

    name[namePointer] = holder;
    namePointer++;
  }

  printf("%s\n\n", name);

  return 0;
}

int scanWord(FILE *input)
{

  while (1)
  {
    char holder = fgetc(input);

    if (holder == ' ')
    {
      //printf("Word: %s\n\n", word);
      return 0;
    }
    else if (holder == EOF)
    {
      return 50;
    }

    word[wordPointer] = holder;
    wordPointer++;

    if (wordPointer > 12)
    {
      printf("ERROR: Name too long\n");
      break;
    }
  }

  return 1;
}

int symTableCheck(char ident[], int kind)
{
  for (int i = 0; i < symPointer; i++)
  {
    if (strcmp(ident, symbol_table[i].name) == 0 && symbol_table[i].kind == kind)
      return i;
    else if (strcmp(ident, symbol_table[i].name) == 0 && symbol_table[i].kind != kind)
      return 0;
  }

  return -1;
}

bool errCheck(FILE *input, char condition)
{

  return true;
}

// Reset the word for being read to avoid any conflicts
void resetWord()
{
  wordPointer = 0;

  for (int i = 0; i < 12; i++)
    word[i] = 0;
}

void emit(int op, int L, int M)
{
  if (symPointer > 500)
    printf("%d", 25);
  else
  {
    symbol_table[symPointer].kind = op;
    symbol_table[symPointer].val = 0;
    symbol_table[symPointer].level = L;
    symbol_table[symPointer].addr = M;
    symPointer++;
  }
}
