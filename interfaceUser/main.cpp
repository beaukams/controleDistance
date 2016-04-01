#include <stdlib.h>
#include <gtk/gtk.h>
#include "filefunc.h"
#include "gtkfunc.h"
#define PORT 20019

int main(int argc, char **argv) {

  gtk_init (&argc, &argv);
  fenPrincipal();
  gtk_main ();

  return 0;

}
