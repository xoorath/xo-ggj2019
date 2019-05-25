#ifndef __XO_SPEC_H_
#define __XO_SPEC_H_

#include <xo-types.h>

#define xo_spec_DeclareCodeSegment() \
  extern char _codeSegmentStart[]; \
  extern char _codeSegmentEnd[];

#define xo_spec_DeclareRomSegment(romSegmentName) \
  extern u8 _##romSegmentName##SegmentRomStart[]; \
  extern u8 _##romSegmentName##SegmentRomEnd[];


#endif // __XO_SPEC_H_