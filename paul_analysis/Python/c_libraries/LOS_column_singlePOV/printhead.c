#include "overhead.h" 


void printhead()
{

  long i; 

  /* simple outputs to see if the read was successful */ 
  fprintf(stderr, "\n"); 
  fprintf(stderr, "Number of Particles = ");
  for (i=0; i<6; i++) fprintf(stderr, "%ld ", header.npart[i]); 
  fprintf(stderr, "\n"); 
  fprintf(stderr, "Particle Masses = ");
  for (i=0; i<6; i++) fprintf(stderr, "%le ", header.mass[i]); 
  fprintf(stderr, "\n"); 
  fprintf(stderr, "time = %.2le\n", header.time); 
  fprintf(stderr, "redshift = %.2le\n", header.redshift); 
  fprintf(stderr, "FlagSfr = %ld\n", header.flag_sfr); 
  fprintf(stderr, "FlagFeedback = %ld\n", header.flag_feedback); 
  fprintf(stderr, "NpartTotal = ");
  for (i=0; i<6; i++) fprintf(stderr, "%ld ", header.npartTotal[i]); 
  fprintf(stderr, "\n"); 
  fprintf(stderr, "FlagCooling = %ld\n", header.flag_cooling); 
  fprintf(stderr, "NumFiles = %ld\n", header.num_files); 
  fprintf(stderr, "BoxSize = %.2le\n", header.BoxSize); 
  fprintf(stderr, "Omega0 = %.2le\n", header.Omega0); 
  fprintf(stderr, "OmegaLambda = %.2le\n", header.OmegaLambda); 
  fprintf(stderr, "HubbleParam = %.2le\n", header.HubbleParam); 
  fprintf(stderr, "Ntotal = %ld\n", All.N_total); 
  fprintf(stderr, "\n"); 
}

void printhead_file(char *filename)
{
	long i;
	FILE *output_file;
    if ((output_file = fopen(filename, "w")) == NULL) 
    	fprintf(stderr, "Cannot open %s\n", "output_file");	

	fprintf(output_file, "%ld %.2le %.2le %ld %ld %ld %.2le %.2le %.2le %.2le \n",
		All.N_total, header.time, header.redshift, header.flag_sfr, header.flag_feedback, 
		header.flag_cooling, header.BoxSize, header.Omega0, header.OmegaLambda,
		header.HubbleParam);

  	for (i=0; i<6; i++) fprintf(output_file, "%ld ", header.npart[i]); 
  	fprintf(output_file, "\n"); 
  	for (i=0; i<6; i++) fprintf(output_file, "%le ", header.mass[i]); 
  	fprintf(output_file, "\n"); 

    fclose(output_file);
}
