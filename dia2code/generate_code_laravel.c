/***************************************************************************
generate_code_laravel.c  -  Function that generates Laravel migrations.
                             -------------------
    begin                : Wed Sep 2 2020
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

#include <time.h>
#include "dia2code.h"

#define TABS "    " /* 4 */

/*
 * print out class columns.
 */
int d2c_laravel_print_columns(FILE *outfile, umlclasslist tmplist)
{
  char parameters_delim[] = ":";
  umlattrlist umla = tmplist->key->attributes;

  while (umla != NULL)
  {
    fprintf(outfile, "%s%s%s$table->",
            TABS,
            TABS,
            TABS);

    int index = 0;
    char *ptr = strtok(umla->key.type, parameters_delim);

    while (ptr != NULL)
    {
      if (index == 0) // assuming the type function will be the first.
      {
        fprintf(outfile, "%s('%s'", ptr, umla->key.name);
      }
      else
      {
        fprintf(outfile, ", %s", ptr);
      }
      ptr = strtok(NULL, parameters_delim);
      index++;
    }

    fprintf(outfile, ")");

    if (strcmp(umla->key.name, "id") == 0)
    {
      fprintf(outfile, "->primary()");
    }

    if (umla->key.value[0] != 0)
    {
      fprintf(outfile, "->default(%s)", umla->key.value);
    }

    fprintf(outfile, ";\n");

    umla = umla->next;
  }

  return 0;
}

/*
 * print out the license
 */

int d2c_laravel_print_license(FILE *outfile, FILE *licensefile)
{
  char lc;

  rewind(licensefile);

  while ((lc = fgetc(licensefile)) != EOF)
  {
    fprintf(outfile, "%c", lc);
  }

  return 0;
}

/*
 * print out the class declaration
 */

int d2c_laravel_print_class_decl(FILE *outfile, umlclasslist tmplist)
{
  char *tablename = strtolower(tmplist->key->name);

  fprintf(outfile, "%s\n%s\n%s\n\n",
          "use Illuminate\\Support\\Facades\\Schema;",
          "use Illuminate\\Database\\Schema\\Blueprint;",
          "use Illuminate\\Database\\Migrations\\Migration;");

  fprintf(outfile, "class Create%sTable extends Migration\n{\n", tmplist->key->name);

  fprintf(outfile,
          "%spublic function up()\n%s{\n"
          "%s%sSchema::create('%s', function (Blueprint $table) {\n",
          TABS,
          TABS,
          TABS,
          TABS,
          tablename);

  d2c_laravel_print_columns(outfile, tmplist);

  fprintf(outfile, "%s%s});\n%s", TABS, TABS, TABS);

  fprintf(
      outfile,
      "}\n\n%spublic function down()\n%s{\n%s%s",
      TABS,
      TABS,
      TABS,
      TABS);

  fprintf(outfile, "Schema::dropIfExists('%s');\n%s}\n}\n", tablename, TABS);

  return 0;
}

/*
 * main function called to begin output
 * */
void generate_code_laravel(batch *b)
{
  umlclasslist tmplist;
  char *tmpname;
  time_t t;
  char t_result[80];
  char outfilename[999];
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

      // generate file name according to Laravel's migration file standards.
      t = time(NULL);

      // <year>_<month>_<day>_<hour><minute><second>
      strftime(t_result,
               sizeof(t_result),
               "%Y_%m_%d_%H%M%S",
               localtime(&t));

      // <dir>/<time>_create_<table>_table.php
      sprintf(outfilename,
              "%s/%s_create_%s_table.php",
              b->outdir,
              t_result,
              strtolower(tmpname));

      dummyfile = fopen(outfilename, "r");

      if (b->clobber || !dummyfile)
      {
        outfile = fopen(outfilename, "w");

        if (outfile == NULL)
        {
          fprintf(stderr, "Can't open file %s for writing\n", outfilename);
          exit(3);
        }

        fprintf(outfile, "<?php\n\n");

        if (b->license != NULL)
        {
          d2c_laravel_print_license(outfile, licensefile);
        }

        d2c_laravel_print_class_decl(outfile, tmplist);

        fclose(outfile);
      }
    }

    tmplist = tmplist->next;
  }
}
