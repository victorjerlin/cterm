#define PROJNAME "C-TERM"
#define DISPLAY ":0.0"

#define AUTHOR "Victor Jerlin, <victor@jerl.in>"
#define VERSION "0.9.9"

#ifndef XK_LATIN1
  #define XK_LATIN1 1
#endif
#ifndef XK_MISCELLANY
  #define XK_MISCELLANY 1 
#endif

struct clusterapps
{
  int clusterid;
  char *clusterrow;
  Window window;

  struct clusterapps *next;
};

#ifdef __CTERM_C
  Display *display;
  Window rootWindow;
  GtkWidget *gtkRootWindow;
  GtkWidget *clusterMembers;
  int cluster = 1;
  int defaultScreen, screenWidth, screenHeight;
  struct clusterapps *windows = NULL;
  int verbose = 0;
#else
  extern int verbose;
  extern Display *display;
  extern Window rootWindow;
  extern GtkWidget *gtkRootWindow;
  extern GtkWidget *clusterMembers;
  extern int cluster;
  extern int defaultScreen, screenWidth, screenHeight;
  extern struct clusterapps *windows;
#endif
