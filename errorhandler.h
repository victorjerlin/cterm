int handlerBadWindow (Display * dpy, XErrorEvent * errEvent);
int setupErrorHandler (void);

#ifdef __ERRORHANDLER_C
  XErrorHandler oldErrorHandler;
#else
  extern XErrorHandler oldErrorHandler;
#endif
