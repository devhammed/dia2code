/***************************************************************************
generate_code_ts.c  -  Function that generates Typescript code
                             -------------------
    begin                : Fri Aug 7 2020
    copyright            : (C) 2020 by Hammed Oyedele
    email                : itz.harmid@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dia2code.h"

#define TABS "  " /* 2 */

/**
 * quick fix to allow bool types in C.
*/
#ifndef __cplusplus
#ifndef _BOOL
typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;
#endif
#endif

/**
 * return the string declaring the class type.
 */
char *d2c_ts_class_type(umlclasslist tmplist)
{
  char *tmpname = strtolower(tmplist->key->stereotype);

  if (eq("interface", tmpname))
  {
    return "interface";
  }
  else
  {
    if (tmplist->key->isabstract)
    {
      return "abstract class";
    }
    else
    {
      return "class";
    }
  }
}

/**
 * return the TS equivalent of UML visibility.
*/
char *d2c_ts_visibility(char vis)
{
  switch (vis)
  {
  case '0':
    return "public";
  case '1':
    return "private";
  case '2':
    return "protected";
  default:
    return "public";
  }
}

/*
 * print out class atributes.
 */
int d2c_ts_print_attributes(FILE *outfile, umlclasslist tmplist, bool isinterface)
{
  umlattrlist umla = tmplist->key->attributes;

  if (umla != NULL)
  {
    fprintf(outfile, "%s// Attributes\n", TABS);
  }

  while (umla != NULL)
  {
    if (isinterface)
    {
      fprintf(outfile, "%s%s: %s", TABS, umla->key.name, umla->key.type);
    }
    else
    {
      char *visibility = d2c_ts_visibility(umla->key.visibility);

      fprintf(outfile, "%s%s %s%s", TABS, visibility,
              (umla->key.isstatic) ? "static " : "",
              umla->key.name);

      if (umla->key.type[0] != 0)
      {
        fprintf(outfile, ": %s", umla->key.type);
      }

      if (umla->key.value[0] != 0)
      {
        fprintf(outfile, " = %s", umla->key.value);
      }
    }

    fprintf(outfile, "\n\n");

    umla = umla->next;
  }

  return 0;
}

/*
 * print out class methods.
 */
int d2c_ts_print_operations(FILE *outfile, umlclasslist tmplist, bool isinterface)
{
  umloplist umlo = tmplist->key->operations;

  if (umlo != NULL)
  {
    fprintf(outfile, "%s// Operations\n", TABS);
  }

  while (umlo != NULL)
  {
    char *tmpname = d2c_ts_visibility(umlo->key.attr.visibility);

    fprintf(outfile, TABS);

    if (isinterface)
    {
      fprintf(outfile, "%s(", umlo->key.attr.name);
    }
    else
    {
      fprintf(outfile, "%s%s%s %s(",
              tmpname,
              (umlo->key.attr.isabstract) ? " abstract" : "",
              (umlo->key.attr.isstatic) ? " static" : "",
              umlo->key.attr.name);
    }

    umlattrlist tmpa = umlo->key.parameters;

    while (tmpa != NULL)
    {
      fprintf(outfile, "%s: %s", tmpa->key.name, tmpa->key.type);

      if (!isinterface && !umlo->key.attr.isabstract && tmpa->key.value[0] != 0)
      {
        fprintf(outfile, " = %s", tmpa->key.value);
      }

      tmpa = tmpa->next;

      if (tmpa != NULL)
        fprintf(outfile, ", ");
    }

    fprintf(outfile, "): %s %s", umlo->key.attr.type, isinterface ? "\n\n" : "{\n");

    if (!isinterface)
    {
      if (umlo->key.implementation != NULL)
      {
        fprintf(outfile, "%s\n", umlo->key.implementation);
      }
      else if (!umlo->key.attr.isabstract)
      {
        fprintf(outfile,
                "%s%sthrow new Error('Not implemented.')\n",
                TABS, TABS);
      }

      fprintf(outfile, "%s}\n\n", TABS);
    }

    umlo = umlo->next;
  }

  return 0;
}

int d2c_ts_print_license(FILE *outfile, FILE *licensefile)
{
  char lc;

  rewind(licensefile);

  while ((lc = fgetc(licensefile)) != EOF)
  {
    fprintf(outfile, "%c", lc);
  }

  return 0;
}

/**
 * print class imports.
*/
int d2c_ts_print_includes(FILE *outfile, umlclasslist tmplist, batch *b)
{
  /* We generate the include clauses */
  umlpackagelist tmppcklist;
  umlclasslist used_classes = list_classes(tmplist, b);

  while (used_classes != NULL)
  {
    tmppcklist = make_package_list(used_classes->key->package);
    if (tmppcklist != NULL)
    {
      if (strcmp(tmppcklist->key->id, tmplist->key->package->id))
      {
        /* This class' package and our current class' package are
            not the same */
        fprintf(outfile, "import %s from '", used_classes->key->name);
        fprintf(outfile, "%s", tmppcklist->key->name);

        tmppcklist = tmppcklist->next;

        while (tmppcklist != NULL)
        {
          fprintf(outfile, "/%s", tmppcklist->key->name);
          tmppcklist = tmppcklist->next;
        }

        fprintf(outfile, "/");
        fprintf(outfile, "%s.ts'\n", used_classes->key->name);
      }
    }
    else
    {
      if (strcmp(used_classes->key->name, tmplist->key->name))
      {
        fprintf(outfile, "import %s from './%s.ts'\n",
                used_classes->key->name, used_classes->key->name);
      }
    }

    used_classes = used_classes->next;
  }

  fprintf(outfile, "\n");

  return 0;
}

/*
 * print out the class declaration
 */

int d2c_ts_print_class_decl(FILE *outfile, umlclasslist tmplist)
{
  umlclasslist parents;
  char *classtype = d2c_ts_class_type(tmplist);
  bool isinterface = classtype == "interface" ? True : False;

  fprintf(outfile, "export default %s %s", classtype, tmplist->key->name);

  parents = tmplist->parents;

  if (parents != NULL)
  {
    while (parents != NULL)
    {
      char *parrenttype = strtolower(parents->key->stereotype);

      if (isinterface)
      {
        fprintf(outfile, " implements ");
      }
      else
      {
        fprintf(outfile, " extends ");
      }

      free(parrenttype);
      fprintf(outfile, "%s", parents->key->name);

      parents = parents->next;
    }
  }

  fprintf(outfile, " {\n");

  d2c_ts_print_attributes(outfile, tmplist, isinterface);
  d2c_ts_print_operations(outfile, tmplist, isinterface);

  fprintf(outfile, "}\n\n");

  return 0;
}

/*
 * return an opened file handle, null for failure
 */
FILE *d2c_ts_getoutfile(umlclasslist tmplist, batch *b, FILE *outfile, int maxlen)
{
  char outfilename[maxlen + 2];
  int tmpfilelgth = strlen(tmplist->key->name);

  if (tmpfilelgth + strlen(b->outdir) > maxlen)
  {
    return NULL;
  }

  sprintf(outfilename, "%s/%s.ts", b->outdir, tmplist->key->name);

  FILE *dummy = fopen(outfilename, "r");

  if (b->clobber || !dummy)
  {
    outfile = fopen(outfilename, "w");
  }

  fclose(dummy);

  return outfile;
}

/*
 * main function called to begin output
 * */
void generate_code_ts(batch *b)
{
  umlclasslist tmplist;
  char *tmpname;
  char outfilename[90];
  int tmpdirlgth, tmpfilelgth;
  FILE *outfile, *dummyfile, *licensefile = NULL;

  if (b->outdir == NULL)
  {
    b->outdir = ".";
  }

  tmpdirlgth = strlen(b->outdir);

  tmplist = b->classlist;

  /* open license file */
  if (b->license != NULL)
  {
    licensefile = fopen(b->license, "r");

    if (!licensefile)
    {
      fprintf(stderr, "Can't open the license file.\n");
      exit(2);
    }
  }

  // for each class
  while (tmplist != NULL)
  {
    if (!(is_present(b->classes, tmplist->key->name) ^ b->mask))
    {
      tmpname = tmplist->key->name;
      /* This prevents buffer overflows */
      tmpfilelgth = strlen(tmpname);

      if (tmpfilelgth + tmpdirlgth > sizeof(*outfilename) - 2)
      {
        fprintf(stderr, "Sorry, name of file too long ...\nTry a smaller dir name\n");
        exit(4);
      }

      sprintf(outfilename, "%s/%s.ts", b->outdir, tmplist->key->name);
      dummyfile = fopen(outfilename, "r");

      if (b->clobber || !dummyfile)
      {
        outfile = fopen(outfilename, "w");

        if (outfile == NULL)
        {
          fprintf(stderr, "Can't open file %s for writing\n", outfilename);
          exit(3);
        }

        if (b->license != NULL)
        {
          d2c_ts_print_license(outfile, licensefile);
        }

        d2c_ts_print_includes(outfile, tmplist, b);
        d2c_ts_print_class_decl(outfile, tmplist);

        fclose(outfile);
      }
    }

    tmplist = tmplist->next;
  }
}
