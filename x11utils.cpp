#include<stdlib.h>
 #include <unistd.h> 
#include<X11/Xlib.h>

#include "vroot.h"
struct SDL_Surface{
  Display *dpy;
  Window root;
  GC g;
  int w,h;
  XWindowAttributes wa;

}screen;

struct SDL_Surface* makeScreen()
{



  /* open the display (connect to the X server) */
  screen.dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  screen.root = DefaultRootWindow (screen.dpy);


  /* create a GC for drawing in the window */
  screen.g = XCreateGC (screen.dpy, screen.root, 0, NULL);

  XGetWindowAttributes(screen.dpy, screen.root, &screen.wa);
  screen.w=screen.wa.width;
  screen.h=screen.wa.height;
  
  /* set foreground color */
  XSetForeground(screen.dpy, screen.g, WhitePixelOfScreen(DefaultScreenOfDisplay(screen.dpy)) );

  return &screen;
}
void  drawLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c){
        XDrawLine(screen.dpy, screen.root, screen.g,x1,y1,x2,y2);
}

void fade(struct SDL_Surface*screen,int a){
            XClearWindow(screen->dpy, screen->root);
}
void SDL_Flip(struct SDL_Surface*screen){
    XFlush(screen->dpy);
}

void done_sdl(){
    XCloseDisplay (screen.dpy);
}
int readKey(){
    return -1;
}
