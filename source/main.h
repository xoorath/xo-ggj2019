#ifndef __MAIN_H_
#define __MAIN_H_

// Definition of the external variable
// Affix "volatile" to the variable which is shared by the main routine
// and the call-back so that it is not cleared by the optimization.
extern volatile int stage;
// Values 0 or 1 used by the pending task check of the call-back function
extern volatile int pendflag;
// The number of the display scene in a second
extern int dspcount;

#endif // __MAIN_H_