#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 30
#define MAX_TEXT 1000
#define MAX_BORD 10

FILE * get_file();

FILE * put_file();

int my_isalpha(char c);

char* get_text(FILE * text_in, unsigned* counterp);

char** word_p(char * text, unsigned counterp);

int my_strcmp(void *s, void *t);

int my_strcmp_reverse(void *s, void *t);

void print_words(char ** wordsp, unsigned counter);

void fprint_words(FILE * output, char ** wordsp, unsigned counter);

int main()
{
    FILE * text_in = get_file();

    FILE * text_sort = put_file();

    FILE * text_sort_reverse = put_file();

    unsigned counter;

    char * text;
    text = get_text(text_in, &counter);

    char** wordp = word_p(text, counter);

    qsort(wordp, counter, sizeof(char*), my_strcmp);

    fprint_words(text_sort, wordp, counter);

    qsort(wordp, counter, sizeof(char*), my_strcmp_reverse);

    fprint_words(text_sort_reverse, wordp, counter);
    return 0;
}


char * get_text(FILE * text_in, unsigned* counterp)
{
    unsigned capacity = MAX_TEXT;
    char* text = (char *) calloc(capacity, sizeof(char));
    if (!text)
    {
        printf("Allocation error in line %d", __LINE__);
        return NULL;
    }

    *counterp = 0;
    int i = 0;
    char c = fgetc(text_in);

    while ( c != EOF)
    {
        if (isalpha(c))
        {
            text[i++] = '\n';
            (*counterp)++;
            while (isalpha(c))
            {
                if ( i > capacity - MAX_BORD)
                    text = (char *) realloc(text, (capacity += MAX_TEXT) * sizeof(char));
                if (!text)
                {
                    printf("Allocation error in line %d", __LINE__);
                    return NULL;
                }
                text[i++] = c;
                c = fgetc(text_in);
            }
        }
        else
            while (isalpha(c) == 0)
            {
                c = fgetc(text_in);
            }
    }
    text[i++] = '\0';
    return text;
}

char ** word_p (char * text, unsigned counter)
{
    char** wordp = (char **) calloc(counter, sizeof(char*));

    if (!wordp)
    {
        printf("Allocation error in line %d", __LINE__);
        return NULL;
    }

    long long unsigned i, j = 0;

    long long unsigned textlen = strlen(text);

    for (i = 0; i < textlen; i++)
    {
        if (text[i]  == '\n')
        {
            text[i] = '\0';
            wordp[j++] = &text[i + 1];
        }
    }

    return wordp;
}

int my_strcmp (void *vs1, void *vs2)
{
    char * s1 = *(char**) vs1;
    char * s2 = *(char**) vs2;
    while (*s1 == *s2)
    {
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int my_strcmp_reverse(void *vs1, void *vs2)
{
    char * s1 = *(char**) vs1;
    char * s2 = *(char**) vs2;
    while ( *s1 != '\0')
        s1++;
    while ( *s2 != '\0')
        s2++;
    s1--;
    s2--;
    while ( *s1 == *s2)
    {
        if ( *s2 == '\0');
        return 0;
        s1--;
        s2--;
    }
    return *s2 - *s1;
}

void print_words(char ** wordsp, unsigned counter)
{
    unsigned j;
    for ( j = 0; j < counter; j++)
        printf("%s\n", wordsp[j]);
    printf("\n");
}

void fprint_words(FILE * output, char ** wordsp, unsigned counter)
{
    unsigned j;
    for (j = 0; j < counter; j++)
        fprintf(output, "%s\n", wordsp[j]);
}

FILE * get_file()
{
    char name[MAX_NAME];
    printf("Please, enter the name of file you want to open\n");
    scanf("%s", name);
    FILE * input = fopen(name, "r");
    if (input == NULL)
        perror(name);
    return input;
}

FILE * put_file()
{
    char name[MAX_NAME];
    printf("Please, enter the name of file you want to create\n");
    scanf("%s", name);
    FILE * output = fopen(name, "w");
    if (output == NULL)
        perror(name);
    return output;
}

int my_isalpha(char c)
{
    if ((c >= 'A' && c <= 'z') || (c >= 160 && c <= 223))
        return 1;
    else
        return 0;
}


