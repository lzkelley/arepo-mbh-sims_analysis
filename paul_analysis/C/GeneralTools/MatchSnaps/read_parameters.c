#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "allvars.h"
#include "proto.h"


#define DOUBLE 1
#define STRING 2
#define INT 3
#define MAXTAGS 300



void read_parameter_file(char *fname)
{
  FILE *fd;
  char buf[400], buf1[400], buf2[400], buf3[400];
  int i, j, nt = 0;
  int id[MAXTAGS];
  void *addr[MAXTAGS];
  char tag[MAXTAGS][50];
  int errorFlag = 0;


  strcpy(tag[nt], "OutputDir1");
  addr[nt] = OutputDir1;
  id[nt++] = STRING;

  strcpy(tag[nt], "OutputDir2");
  addr[nt] = OutputDir2;
  id[nt++] = STRING;

  strcpy(tag[nt], "SnapshotFileBase1");
  addr[nt] = SnapshotFileBase1;
  id[nt++] = STRING;

  strcpy(tag[nt], "SnapshotFileBase2");
  addr[nt] = SnapshotFileBase2;
  id[nt++] = STRING;

  strcpy(tag[nt], "MatchOutputDir");
  addr[nt] = MatchOutputDir;
  id[nt++] = STRING;

  if((fd = fopen(fname, "r")))
    {
      while(!feof(fd))
	{
	  *buf = 0;
	  fgets(buf, 200, fd);
	  if(sscanf(buf, "%s%s%s", buf1, buf2, buf3) < 2)
	    continue;

	  if(buf1[0] == '%')
	    continue;

	  for(i = 0, j = -1; i < nt; i++)
	    if(strcmp(buf1, tag[i]) == 0)
	      {
		j = i;
		tag[i][0] = 0;
		break;
	      }

	  if(j >= 0)
	    {
	      switch (id[j])
		{
		case DOUBLE:
		  *((double *) addr[j]) = atof(buf2);
		  break;
		case STRING:
		  strcpy(addr[j], buf2);
		  break;
		case INT:
		  *((int *) addr[j]) = atoi(buf2);
		  break;
		}
	    }
	  else
	    {
	      printf("Error in file %s:   Tag '%s' not allowed or multiple defined.\n", fname, buf1);
	      errorFlag = 1;
	    }
	}
      fclose(fd);

      i = strlen(OutputDir1);
      if(i > 0)
	if(OutputDir1[i - 1] != '/')
	  strcat(OutputDir1, "/");

      i = strlen(OutputDir2);
      if(i > 0)
        if(OutputDir2[i - 1] != '/')
          strcat(OutputDir2, "/");

      i = strlen(MatchOutputDir);
      if(i > 0)
	if(MatchOutputDir[i - 1] != '/')
	  strcat(MatchOutputDir, "/");
    }
  else
    {
      printf("Parameter file %s not found.\n", fname);
      errorFlag = 1;
    }


  for(i = 0; i < nt; i++)
    {
      if(*tag[i])
	{
	  printf("Error. I miss a value for tag '%s' in parameter file '%s'.\n", tag[i], fname);
	  errorFlag = 1;
	}
    }

  if(errorFlag)
    exit(1);

}
