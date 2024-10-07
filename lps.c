/*
 Credits: This program is based on previous work by Jeroen J. Dirks (jeroend@tor.numetrix.com) and Peter Notebaert (lpsolve@peno.be)
 Shpati Koleka, 2024.
*/

#include <stdio.h>
#include "lp_lib.h"

#define LPSOLVEAPIFROMLIBDEF
#define lpslib "lpsolve55.dll"

#include "lp_explicit.h"

char filename[] = "lps.txt";

int main(int argc, char *argv[]) {

# if defined ERROR
#  undef ERROR
# endif
# define ERROR() { fprintf(stderr, "\nProgram terminated due to error.\n"); return(1); }

  lprec *lp;
  int majorversion, minorversion, release, build;
  char buf[1024];
  hlpsolve lpsolve;

  lpsolve = open_lpsolve_lib(lpslib);
  if (lpsolve == NULL) {
    fprintf(stderr, "\nUnable to load the %s file!\nIt should be placed in the same path as this program.", lpslib);
    ERROR();
  }

  if (!init_lpsolve(lpsolve)) {
    fprintf(stderr, "\nUnable to initialize %s!", lpslib);
    ERROR();
  }

  if (argc > 1) {
      if ((lp = read_LP(argv[1], TRUE, argv[1])) == NULL) ERROR();
    } else {
      if ((lp = read_LP("lps.txt", TRUE, "lps.txt")) == NULL) ERROR();
      lp_solve_version(&majorversion, &minorversion, &release, &build);
      printf("\nLinear Programming Solver v.0.1\n");
      printf("This program will load and attempt to solve what is in the model input file\n");
      printf("Solver used: lp_solve %d.%d.%d.%d \n\n", majorversion, minorversion, release, build);
      printf("Loading the default model input file...\n");
    }
  
  print_lp(lp);

  set_debug(lp, TRUE);
  solve(lp);
  set_debug(lp, FALSE);

  print_objective(lp);
  print_solution(lp, 1);
  print_constraints(lp, 1);
  delete_lp(lp);
  close_lpsolve_lib(lpsolve);

  return 0;
}