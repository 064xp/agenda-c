#define PCRE_STATIC //pcre satic link macro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30

void extraerPendientesPorDía(char **bufferArchvio, char **substringsExtraidos){
  char *patron = "";
}
//func get todos of by day
  //gets substrings of day
  //def struct array with malloc
  //loop through each substring
    //realloc struct array + 1
    //array[last index] = strToStruct(str);

//func turns string into struct

int main(){
  pcre *re;
  const char *error;
  char *pattern = "DESCRIPTION.+(?=\\W[A-Z]{2,}:)";
  char *subject = "SUMMARY: test DESCRIPTION:LoreadadASDASDm ipsum dolor sit amet, consectetur adipisicing elit. Ex, doloribus cum, culpa minima ad rerum tempora pariatur, eum voluptat \nCLASS:PUBLIC";
  int erroffset;
  int find_all;
  int crlf_is_newline;
  int namecount;
  int name_entry_size;
  int ovector[OVECCOUNT];
  int rc, i;
  int utf8;

  re = pcre_compile(
    pattern,              /* the pattern */
    PCRE_UNGREEDY,                    /* default options */
    &error,               /* for error message */
    &erroffset,           /* for error offset */
    NULL);                /* use default character tables */

  /* Compilation failed: print the error message and exit */

  if (re == NULL)
    {
    printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
    return 1;
    }

    rc = pcre_exec(
      re,                   /* the compiled pattern */
      NULL,                 /* no extra data - we didn't study the pattern */
      subject,              /* the subject string */
      strlen(subject),       /* the length of the subject */
      0,                    /* start at offset 0 in the subject */
      0,                    /* default options */
      ovector,              /* output vector for substring information */
      OVECCOUNT);           /* number of elements in the output vector */

/* Matching failed: handle error cases */

  if (rc < 0)
    {
    switch(rc)
      {
      case PCRE_ERROR_NOMATCH: printf("No match\n");
      break;
      /*
      Handle other special cases if you like
      */
      default: printf("Matching error %d\n", rc);
      break;
      }
    pcre_free(re);     /* Release memory used for the compiled pattern */
    return 1;
    }

  /* Match succeded */

  const char *substr;
  pcre_get_substring(subject, ovector, rc, 0, &substr);
  printf("\nMatch succeeded at offset %d\n", ovector[0]);
  printf("%s", substr);
  pcre_free(re);     /* Release memory used for the compiled pattern */
  getchar();
  return 0;
}
