
#ifndef __GCC_RISCV_DSP_H__
#define __GCC_RISCV_DSP_H__

#include <stdint.h>

typedef signed char int8x4_t __attribute__ ((vector_size (4)));
typedef unsigned char uint8x4_t __attribute__ ((vector_size (4)));
typedef signed char int8x8_t __attribute__ ((vector_size (8)));
typedef unsigned char uint8x8_t __attribute__ ((vector_size (8)));

typedef signed short int16x2_t __attribute__ ((vector_size (4)));
typedef unsigned short uint16x2_t __attribute__ ((vector_size (4)));
typedef signed short int16x4_t __attribute__ ((vector_size (8)));
typedef unsigned short uint16x4_t __attribute__ ((vector_size (8)));

typedef signed int int32x2_t __attribute__ ((vector_size (8)));
typedef unsigned int uint32x2_t __attribute__ ((vector_size (8)));

#if __riscv_xlen == 32
typedef int32_t  intXLEN_t;
typedef uint32_t uintXLEN_t;
#elif __riscv_xlen == 64
typedef int64_t  intXLEN_t;
typedef uint64_t uintXLEN_t;
#endif

#if !__riscv_dsp && !__riscv_zpsfoperand
#error "dsp require -march the 'p' extension or 'zpsfoperand' extension"
#endif


#if __riscv_zpsfoperand

#if __riscv_xlen == 32

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smal(int64_t a, int16x2_t b) {
  return __builtin_riscv_smal_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalbb(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smalbb_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalbt(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smalbt_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smaltt(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smaltt_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalda(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smalda_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalxda(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smalxda_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalds(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smalds_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smaldrs(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smaldrs_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalxds(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smalxds_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smslda(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smslda_v2hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smslxda(int64_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smslxda_v2hi(t, a, b);
}

#endif // __riscv_xlen == 32

#if __riscv_xlen == 64

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smal(int64_t a, int16x4_t b) {
  return __builtin_riscv_smal_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalbb(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smalbb_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalbt(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smalbt_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smaltt(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smaltt_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalda(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smalda_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalxda(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smalxda_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalds(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smalds_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smaldrs(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smaldrs_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smalxds(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smalxds_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smslda(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smslda_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smslxda(int64_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smslxda_v4hi(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smar64(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smar64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smsr64(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smsr64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmar64(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmar64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmsr64(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmsr64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__v_ukmar64(uint64_t t, uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukmar64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__v_ukmsr64(uint64_t t, uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukmsr64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__v_umar64(uint64_t t, uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_umar64_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__v_umsr64(uint64_t t, uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_umsr64_v2si(t, a, b);
}

#endif // __riscv_xlen == 64

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__sadd64(int64_t a, int64_t b) {
  return __builtin_riscv_add64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__ssub64(int64_t a, int64_t b) {
  return __builtin_riscv_sub64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__uadd64(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_add64((int64_t)a, (int64_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__usub64(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_sub64((int64_t)a, (int64_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__smul8(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_smul8((int8x4_t)a, (int8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__smulx8(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_smulx8((int8x4_t)a, (int8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_smul8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_smul8(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_smulx8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_smulx8(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__smul16(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_smul16((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__smulx16(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_smulx16((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smul16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smul16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smulx16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smulx16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__mulsr64(int32_t a, int32_t b) {
  return __builtin_riscv_mulsr64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smal(int64_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smal_v4hi(a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smal_v2hi(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kadd64(int64_t a, int64_t b) {
  return __builtin_riscv_kadd64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__ksub64(int64_t a, int64_t b) {
  return __builtin_riscv_ksub64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__radd64(int64_t a, int64_t b) {
  return __builtin_riscv_radd64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__rsub64(int64_t a, int64_t b) {
  return __builtin_riscv_rsub64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smalbb(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smalbb_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smalbb_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smalbt(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smalbt_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smalbt_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smaltt(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smaltt_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smaltt_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smalda(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smalda_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smalda_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smalxda(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smalxda_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smalxda_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smalds(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smalds_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smalds_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smaldrs(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smaldrs_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smaldrs_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smalxds(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smalxds_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smalxds_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smslda(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smslda_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smslda_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smslxda(int64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smslxda_v4hi(t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smslxda_v2hi(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smar64(int64_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smar64_v2si(t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smar64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smsr64(int64_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_smsr64_v2si(t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smsr64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmar64(int64_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_kmar64_v2si(t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmar64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmsr64(int64_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_kmsr64_v2si(t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmsr64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__wext(uint64_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_wext_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_wext_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umul8(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_umul8((uint8x4_t)a, (uint8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umulx8(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_umulx8((uint8x4_t)a, (uint8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_umul8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_umul8(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_umulx8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_umulx8(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umul16(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_umul16((uint16x2_t)a, (uint16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umulx16(uint32_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_umulx16((uint16x2_t)a, (uint16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_umul16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_umul16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_umulx16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_umulx16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__mulr64(uint32_t a, uint32_t b) {
  return __builtin_riscv_mulr64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukadd64(uint64_t a, uint64_t b) {
  return __builtin_riscv_ukadd64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__uksub64(uint64_t a, uint64_t b) {
  return __builtin_riscv_uksub64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__uradd64(uint64_t a, uint64_t b) {
  return __builtin_riscv_uradd64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ursub64(uint64_t a, uint64_t b) {
  return __builtin_riscv_ursub64(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukmar64(uint64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ukmar64_v2si(t, (uint32x2_t)a, (uint32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ukmar64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukmsr64(uint64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ukmsr64_v2si(t, (uint32x2_t)a, (uint32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ukmsr64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umar64(uint64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_umar64_v2si(t, (uint32x2_t)a, (uint32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_umar64_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umsr64(uint64_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_umsr64_v2si(t, (uint32x2_t)a, (uint32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_umsr64_si(t, a, b);
#endif
}

#endif //__riscv_zpsfoperand

#if __riscv_dsp

#if __riscv_xlen == 32

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sadd16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_add16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_ssub16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_sub16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_scras16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_cras16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_scrsa16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_crsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sstas16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_stas16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sstsa16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_stsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_uadd16(uint16x2_t a, uint16x2_t b) {
  return (uint16x2_t) __builtin_riscv_add16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_usub16(uint16x2_t a, uint16x2_t b) {
  return (uint16x2_t) __builtin_riscv_sub16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ucras16(uint16x2_t a, uint16x2_t b) {
  return (uint16x2_t) __builtin_riscv_cras16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ucrsa16(uint16x2_t a, uint16x2_t b) {
  return (uint16x2_t) __builtin_riscv_crsa16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ustas16(uint16x2_t a, uint16x2_t b) {
  return (uint16x2_t) __builtin_riscv_stas16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ustsa16(uint16x2_t a, uint16x2_t b) {
  return (uint16x2_t) __builtin_riscv_stsa16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_sadd8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_add8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_ssub8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_sub8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_uadd8(uint8x4_t a, uint8x4_t b) {
  return (uint8x4_t) __builtin_riscv_add8_v4qi((int8x4_t)a, (int8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_usub8(uint8x4_t a, uint8x4_t b) {
  return (uint8x4_t) __builtin_riscv_sub8_v4qi((int8x4_t)a, (int8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kabs16(int16x2_t a) {
  return __builtin_riscv_kabs16_v2hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kslra16(int16x2_t a, int32_t b) {
  return __builtin_riscv_kslra16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kslra16_u(int16x2_t a, int32_t b) {
  return __builtin_riscv_kslra16_u_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sclip16(int16x2_t a, const uint32_t b) {
  return __builtin_riscv_sclip16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_radd16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_radd16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_rcras16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_rcras16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_rcrsa16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_rcrsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_rstas16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_rstas16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_rstsa16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_rstsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_rsub16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_rsub16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kadd16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kadd16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kcras16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kcras16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kcrsa16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kcrsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_ksub16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_ksub16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kstas16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kstas16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_kstsa16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kstsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_khm16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_khm16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_khmx16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_khmx16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_smax16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smax16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_smin16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smin16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sra16(int16x2_t a, uint32_t b) {
  return __builtin_riscv_sra16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sra16_u(int16x2_t a, uint32_t b) {
  return __builtin_riscv_sra16_u_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_ksll16(int16x2_t a, uint32_t b) {
  return __builtin_riscv_ksll16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sunpkd810(int8x4_t a) {
  return __builtin_riscv_sunpkd810_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sunpkd820(int8x4_t a) {
  return __builtin_riscv_sunpkd820_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sunpkd830(int8x4_t a) {
  return __builtin_riscv_sunpkd830_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sunpkd831(int8x4_t a) {
  return __builtin_riscv_sunpkd831_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x2_t __rv__v_sunpkd832(int8x4_t a) {
  return __builtin_riscv_sunpkd832_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smbb16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smbb16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smbt16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smbt16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smtt16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smtt16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smds(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smds_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smdrs(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smdrs_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smxds(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_smxds_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmda(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmda_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmxda(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmxda_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smmwb(int32_t a, int16x2_t b) {
  return __builtin_riscv_smmwb_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smmwb_u(int32_t a, int16x2_t b) {
  return __builtin_riscv_smmwb_u_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smmwt(int32_t a, int16x2_t b) {
  return __builtin_riscv_smmwt_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smmwt_u(int32_t a, int16x2_t b) {
  return __builtin_riscv_smmwt_u_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmwb2(int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmwb2_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmwb2_u(int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmwb2_u_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmwt2(int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmwt2_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmwt2_u(int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmwt2_u_si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmabb(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmabb_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmabt(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmabt_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmatt(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmatt_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmada(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmada_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmaxda(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmaxda_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmads(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmads_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmadrs(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmadrs_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmaxds(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmaxds_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmsda(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmsda_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmsxda(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kmsxda_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawb(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawb_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawb_u(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawb_u_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawb2(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawb2_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawb2_u(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawb2_u_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawt(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawt_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawt_u(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawt_u_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawt2(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawt2_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kmmawt2_u(int32_t t, int32_t a, int16x2_t b) {
  return __builtin_riscv_kmmawt2_u_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smaqa(int32_t t, int8x4_t a, int8x4_t b) {
  return __builtin_riscv_smaqa_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_smaqa_su(int32_t t, int8x4_t a, uint8x4_t b) {
  return __builtin_riscv_smaqa_su_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_kabs8(int8x4_t a) {
  return __builtin_riscv_kabs8_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_kslra8(int8x4_t a, int32_t b) {
  return __builtin_riscv_kslra8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_kslra8_u(int8x4_t a, int32_t b) {
  return __builtin_riscv_kslra8_u_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_sclip8(int8x4_t a, const uint32_t b) {
  return __builtin_riscv_sclip8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_radd8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_radd8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_rsub8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_rsub8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_kadd8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_kadd8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_ksub8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_ksub8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_khm8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_khm8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_khmx8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_khmx8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_smin8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_smin8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_smax8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_smax8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_sra8(int8x4_t a, uint32_t b) {
  return __builtin_riscv_sra8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_sra8_u(int8x4_t a, uint32_t b) {
  return __builtin_riscv_sra8_u_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x4_t __rv__v_ksll8(int8x4_t a, uint32_t b) {
  return __builtin_riscv_ksll8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_scmpeq16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_cmpeq16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ucmpeq16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_cmpeq16_v2hi((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_clrs16(int16x2_t a) {
  return __builtin_riscv_clrs16_v2hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_uclip16(int16x2_t a, const uint32_t b) {
  return __builtin_riscv_uclip16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_scmplt16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_scmplt16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_scmple16(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_scmple16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_clo16(uint16x2_t a) {
  return __builtin_riscv_clo16_v2hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_clz16(uint16x2_t a) {
  return __builtin_riscv_clz16_v2hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_swap16(uint16x2_t a) {
  return __builtin_riscv_swap16_v2hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_srl16(uint16x2_t a, uint32_t b) {
  return __builtin_riscv_srl16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_srl16_u(uint16x2_t a, uint32_t b) {
  return __builtin_riscv_srl16_u_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_sll16(uint16x2_t a, uint32_t b) {
  return __builtin_riscv_sll16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_umax16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_umax16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_umin16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_umin16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_uradd16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_uradd16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ucmple16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ucmple16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ucmplt16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ucmplt16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ukadd16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ukadd16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ursub16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ursub16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_urcras16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_urcras16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_urcrsa16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_urcrsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_urstas16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_urstas16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_urstsa16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_urstsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_uksub16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_uksub16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ukcras16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ukcras16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ukcrsa16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ukcrsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ukstas16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ukstas16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_ukstsa16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_ukstsa16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_pkbb16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_pkbb16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_pkbt16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_pkbt16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_pktb16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_pktb16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_pktt16(uint16x2_t a, uint16x2_t b) {
  return __builtin_riscv_pktt16_v2hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_zunpkd810(uint8x4_t a) {
  return __builtin_riscv_zunpkd810_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_zunpkd820(uint8x4_t a) {
  return __builtin_riscv_zunpkd820_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_zunpkd830(uint8x4_t a) {
  return __builtin_riscv_zunpkd830_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_zunpkd831(uint8x4_t a) {
  return __builtin_riscv_zunpkd831_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x2_t __rv__v_zunpkd832(uint8x4_t a) {
  return __builtin_riscv_zunpkd832_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32_t __rv__v_umaqa(uint32_t t, uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_umaqa_si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_scmpeq8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_cmpeq8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_ucmpeq8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_cmpeq8_v4qi((int8x4_t)a, (int8x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_clrs8(int8x4_t a) {
  return __builtin_riscv_clrs8_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_uclip8(int8x4_t a, const uint32_t b) {
  return __builtin_riscv_uclip8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_scmplt8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_scmplt8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_scmple8(int8x4_t a, int8x4_t b) {
  return __builtin_riscv_scmple8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_clo8(uint8x4_t a) {
  return __builtin_riscv_clo8_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_clz8(uint8x4_t a) {
  return __builtin_riscv_clz8_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_swap8(uint8x4_t a) {
  return __builtin_riscv_swap8_v4qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_srl8(uint8x4_t a, uint32_t b) {
  return __builtin_riscv_srl8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_srl8_u(uint8x4_t a, uint32_t b) {
  return __builtin_riscv_srl8_u_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_sll8(uint8x4_t a, uint32_t b) {
  return __builtin_riscv_sll8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_umin8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_umin8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_umax8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_umax8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_uradd8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_uradd8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_ukadd8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_ukadd8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_ucmple8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_ucmple8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_ursub8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_ursub8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_uksub8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_uksub8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x4_t __rv__v_ucmplt8(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_ucmplt8_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32_t __rv__v_pbsad(uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_pbsad_v4qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32_t __rv__v_pbsada(uint32_t t, uint8x4_t a, uint8x4_t b) {
  return __builtin_riscv_pbsada_si(t, a, b);
}

#endif // __riscv_xlen == 32

#if __riscv_xlen == 64

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sadd16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_add16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_ssub16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_sub16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_scras16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_cras16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_scrsa16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_crsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sstas16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_stas16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sstsa16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_stsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_uadd16(uint16x4_t a, uint16x4_t b) {
  return (uint16x4_t) __builtin_riscv_add16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_usub16(uint16x4_t a, uint16x4_t b) {
  return (uint16x4_t) __builtin_riscv_sub16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ucras16(uint16x4_t a, uint16x4_t b) {
  return (uint16x4_t) __builtin_riscv_cras16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ucrsa16(uint16x4_t a, uint16x4_t b) {
  return (uint16x4_t) __builtin_riscv_crsa16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ustas16(uint16x4_t a, uint16x4_t b) {
  return (uint16x4_t) __builtin_riscv_stas16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ustsa16(uint16x4_t a, uint16x4_t b) {
  return (uint16x4_t) __builtin_riscv_stsa16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__add32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_add32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__sub32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_sub32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__cras32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_cras32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__crsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_crsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__stas32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_stas32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__stsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_stsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_sadd32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_add32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_ssub32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_sub32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_scras32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_cras32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_scrsa32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_crsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_sstas32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_stas32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_sstsa32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_stsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_uadd32(uint32x2_t a, uint32x2_t b) {
  return (uint32x2_t) __builtin_riscv_add32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_usub32(uint32x2_t a, uint32x2_t b) {
  return (uint32x2_t) __builtin_riscv_sub32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ucras32(uint32x2_t a, uint32x2_t b) {
  return (uint32x2_t) __builtin_riscv_cras32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ucrsa32(uint32x2_t a, uint32x2_t b) {
  return (uint32x2_t) __builtin_riscv_crsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ustas32(uint32x2_t a, uint32x2_t b) {
  return (uint32x2_t) __builtin_riscv_stas32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ustsa32(uint32x2_t a, uint32x2_t b) {
  return (uint32x2_t) __builtin_riscv_stsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_sadd8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_add8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_ssub8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_sub8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_uadd8(uint8x8_t a, uint8x8_t b) {
  return (uint8x8_t) __builtin_riscv_add8_v8qi((int8x8_t)a, (int8x8_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_usub8(uint8x8_t a, uint8x8_t b) {
  return (uint8x8_t) __builtin_riscv_sub8_v8qi((int8x8_t)a, (int8x8_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kabs16(int16x4_t a) {
  return __builtin_riscv_kabs16_v4hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kslra16(int16x4_t a, int32_t b) {
  return __builtin_riscv_kslra16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kslra16_u(int16x4_t a, int32_t b) {
  return __builtin_riscv_kslra16_u_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sclip16(int16x4_t a, const uint32_t b) {
  return __builtin_riscv_sclip16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_radd16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_radd16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_rcras16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_rcras16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_rcrsa16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_rcrsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_rstas16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_rstas16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_rstsa16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_rstsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_rsub16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_rsub16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kadd16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kadd16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kcras16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kcras16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kcrsa16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kcrsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_ksub16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_ksub16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kstas16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kstas16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_kstsa16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kstsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_khm16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_khm16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_khmx16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_khmx16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_smax16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smax16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_smin16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smin16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sra16(int16x4_t a, uint32_t b) {
  return __builtin_riscv_sra16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sra16_u(int16x4_t a, uint32_t b) {
  return __builtin_riscv_sra16_u_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_ksll16(int16x4_t a, uint32_t b) {
  return __builtin_riscv_ksll16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sunpkd810(int8x8_t a) {
  return __builtin_riscv_sunpkd810_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sunpkd820(int8x8_t a) {
  return __builtin_riscv_sunpkd820_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sunpkd830(int8x8_t a) {
  return __builtin_riscv_sunpkd830_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sunpkd831(int8x8_t a) {
  return __builtin_riscv_sunpkd831_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int16x4_t __rv__v_sunpkd832(int8x8_t a) {
  return __builtin_riscv_sunpkd832_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__sraw_u(int32_t a, const uint32_t b) {
  return __builtin_riscv_sraw_u(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smbb16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smbb16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smbt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smbt16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smtt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smtt16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smds(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smds_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smdrs(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smdrs_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smxds(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_smxds_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmda(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmda_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmxda(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmxda_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kdmbb16(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kdmbb16((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kdmbt16(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kdmbt16((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kdmtt16(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kdmtt16((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kdmbb16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kdmbb16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kdmbt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kdmbt16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kdmtt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kdmtt16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__khmbb16(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_khmbb16((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__khmbt16(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_khmbt16((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__khmtt16(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_khmtt16((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_khmbb16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_khmbb16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_khmbt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_khmbt16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_khmtt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_khmtt16(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kabs32(uint64_t a) {
  return (uint64_t) __builtin_riscv_kabs32((int32x2_t)a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kabs32(int32x2_t a) {
  return __builtin_riscv_kabs32(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kslra32(uint64_t a, int32_t b) {
  return (uint64_t) __builtin_riscv_kslra32((int32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kslra32_u(uint64_t a, int32_t b) {
  return (uint64_t) __builtin_riscv_kslra32_u((int32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kslra32(int32x2_t a, int32_t b) {
  return __builtin_riscv_kslra32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kslra32_u(int32x2_t a, int32_t b) {
  return __builtin_riscv_kslra32_u(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_sclip32(int32x2_t a, const uint32_t b) {
  return __builtin_riscv_sclip32_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smmwb(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_smmwb_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smmwb_u(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_smmwb_u_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smmwt(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_smmwt_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smmwt_u(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_smmwt_u_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmwb2(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmwb2_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmwb2_u(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmwb2_u_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmwt2(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmwt2_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmwt2_u(int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmwt2_u_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smmul(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smmul_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smmul_u(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smmul_u_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kwmmul(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kwmmul_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kwmmul_u(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kwmmul_u_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kadd32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kadd32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kcras32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kcras32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kcrsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kcrsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kadd32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kadd32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kcras32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kcras32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kcrsa32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kcrsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__smax32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_smax32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__smin32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_smin32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kstas32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kstas32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kstsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kstsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ksub32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ksub32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__radd32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_radd32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__rcras32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_rcras32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__rcrsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_rcrsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__rstas32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_rstas32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__rstsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_rstsa32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__rsub32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_rsub32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smax32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smax32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smin32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smin32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kstas32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kstas32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kstsa32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kstsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_ksub32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_ksub32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_radd32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_radd32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_rcras32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_rcras32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_rcrsa32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_rcrsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_rstas32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_rstas32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_rstsa32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_rstsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_rsub32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_rsub32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__sra32(uint64_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_sra32((int32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__sra32_u(uint64_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_sra32_u((int32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ksll32(uint64_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_ksll32((int32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_sra32(int32x2_t a, uint32_t b) {
  return __builtin_riscv_sra32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_sra32_u(int32x2_t a, uint32_t b) {
  return __builtin_riscv_sra32_u(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_ksll32(int32x2_t a, uint32_t b) {
  return __builtin_riscv_ksll32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmabb(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmabb_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmabt(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmabt_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmatt(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmatt_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmada(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmada_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmaxda(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmaxda_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmads(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmads_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmadrs(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmadrs_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmaxds(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmaxds_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmsda(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmsda_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmsxda(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kmsxda_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kdmabb16(uint64_t t, uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kdmabb16((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kdmabt16(uint64_t t, uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kdmabt16((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__kdmatt16(uint64_t t, uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_kdmatt16((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kdmabb16(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kdmabb16(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kdmabt16(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kdmabt16(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kdmatt16(int32x2_t t, int16x4_t a, int16x4_t b) {
  return __builtin_riscv_kdmatt16(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawb(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawb_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawb_u(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawb_u_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawb2(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawb2_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawb2_u(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawb2_u_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawt(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawt_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawt_u(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawt_u_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawt2(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawt2_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmawt2_u(int32x2_t t, int32x2_t a, int16x4_t b) {
  return __builtin_riscv_kmmawt2_u_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmac(int32x2_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmmac_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmac_u(int32x2_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmmac_u_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmsb(int32x2_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmmsb_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_kmmsb_u(int32x2_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmmsb_u_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smaqa(int32x2_t t, int8x8_t a, int8x8_t b) {
  return __builtin_riscv_smaqa_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32x2_t __rv__v_smaqa_su(int32x2_t t, int8x8_t a, uint8x8_t b) {
  return __builtin_riscv_smaqa_su_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmda32(uint64_t a, uint64_t b) {
  return __builtin_riscv_kmda32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmxda32(uint64_t a, uint64_t b) {
  return __builtin_riscv_kmxda32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmda32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmda32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmxda32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmxda32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smbb32(uint64_t a, uint64_t b) {
  return __builtin_riscv_smbb32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smbt32(uint64_t a, uint64_t b) {
  return __builtin_riscv_smbt32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smtt32(uint64_t a, uint64_t b) {
  return __builtin_riscv_smtt32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smds32(uint64_t a, uint64_t b) {
  return __builtin_riscv_smds32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smdrs32(uint64_t a, uint64_t b) {
  return __builtin_riscv_smdrs32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__smxds32(uint64_t a, uint64_t b) {
  return __builtin_riscv_smxds32((int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smbb32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smbb32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smbt32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smbt32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smtt32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smtt32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smds32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smds32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smdrs32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smdrs32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_smxds32(int32x2_t a, int32x2_t b) {
  return __builtin_riscv_smxds32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmabb32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmabb32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmabt32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmabt32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmatt32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmatt32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmada32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmada32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmaxda32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmaxda32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmads32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmads32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmadrs32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmadrs32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmaxds32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmaxds32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmsda32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmsda32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__kmsxda32(int64_t t, uint64_t a, uint64_t b) {
  return __builtin_riscv_kmsxda32(t, (int32x2_t)a, (int32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmabb32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmabb32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmabt32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmabt32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmatt32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmatt32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmada32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmada32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmaxda32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmaxda32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmads32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmads32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmadrs32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmadrs32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmaxds32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmaxds32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmsda32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmsda32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int64_t __rv__v_kmsxda32(int64_t t, int32x2_t a, int32x2_t b) {
  return __builtin_riscv_kmsxda32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_kabs8(int8x8_t a) {
  return __builtin_riscv_kabs8_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_kslra8(int8x8_t a, int32_t b) {
  return __builtin_riscv_kslra8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_kslra8_u(int8x8_t a, int32_t b) {
  return __builtin_riscv_kslra8_u_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_sclip8(int8x8_t a, const uint32_t b) {
  return __builtin_riscv_sclip8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_radd8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_radd8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_rsub8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_rsub8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_kadd8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_kadd8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_ksub8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_ksub8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_khm8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_khm8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_khmx8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_khmx8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_smin8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_smin8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_smax8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_smax8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_sra8(int8x8_t a, uint32_t b) {
  return __builtin_riscv_sra8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_sra8_u(int8x8_t a, uint32_t b) {
  return __builtin_riscv_sra8_u_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int8x8_t __rv__v_ksll8(int8x8_t a, uint32_t b) {
  return __builtin_riscv_ksll8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_scmpeq16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_cmpeq16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ucmpeq16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_cmpeq16_v4hi((int16x4_t)a, (int16x4_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_clrs16(int16x4_t a) {
  return __builtin_riscv_clrs16_v4hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_uclip16(int16x4_t a, const uint32_t b) {
  return __builtin_riscv_uclip16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_scmplt16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_scmplt16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_scmple16(int16x4_t a, int16x4_t b) {
  return __builtin_riscv_scmple16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_clo16(uint16x4_t a) {
  return __builtin_riscv_clo16_v4hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_clz16(uint16x4_t a) {
  return __builtin_riscv_clz16_v4hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_swap16(uint16x4_t a) {
  return __builtin_riscv_swap16_v4hi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_srl16(uint16x4_t a, uint32_t b) {
  return __builtin_riscv_srl16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_srl16_u(uint16x4_t a, uint32_t b) {
  return __builtin_riscv_srl16_u_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_sll16(uint16x4_t a, uint32_t b) {
  return __builtin_riscv_sll16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_umax16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_umax16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_umin16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_umin16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_uradd16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_uradd16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ucmple16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ucmple16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ucmplt16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ucmplt16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ukadd16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ukadd16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ursub16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ursub16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_urcras16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_urcras16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_urcrsa16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_urcrsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_urstas16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_urstas16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_urstsa16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_urstsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_uksub16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_uksub16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ukcras16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ukcras16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ukcrsa16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ukcrsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ukstas16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ukstas16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_ukstsa16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_ukstsa16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_pkbb16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_pkbb16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_pkbt16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_pkbt16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_pktb16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_pktb16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_pktt16(uint16x4_t a, uint16x4_t b) {
  return __builtin_riscv_pktt16_v4hi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_zunpkd810(uint8x8_t a) {
  return __builtin_riscv_zunpkd810_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_zunpkd820(uint8x8_t a) {
  return __builtin_riscv_zunpkd820_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_zunpkd830(uint8x8_t a) {
  return __builtin_riscv_zunpkd830_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_zunpkd831(uint8x8_t a) {
  return __builtin_riscv_zunpkd831_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint16x4_t __rv__v_zunpkd832(uint8x8_t a) {
  return __builtin_riscv_zunpkd832_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_clrs32(int32x2_t a) {
  return __builtin_riscv_clrs32_v2si(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_uclip32(int32x2_t a, const uint32_t b) {
  return __builtin_riscv_uclip32_v2si(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_clo32(uint32x2_t a) {
  return __builtin_riscv_clo32_v2si(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_clz32(uint32x2_t a) {
  return __builtin_riscv_clz32_v2si(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__sll32(uint64_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_sll32((uint32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_sll32(uint32x2_t a, uint32_t b) {
  return __builtin_riscv_sll32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__srl32(uint64_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_srl32((uint32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__srl32_u(uint64_t a, uint32_t b) {
  return (uint64_t) __builtin_riscv_srl32_u((uint32x2_t)a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_srl32(uint32x2_t a, uint32_t b) {
  return __builtin_riscv_srl32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_srl32_u(uint32x2_t a, uint32_t b) {
  return __builtin_riscv_srl32_u(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukadd32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ukadd32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukcras32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ukcras32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukcrsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ukcrsa32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukstas32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ukstas32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ukstsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ukstsa32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__uksub32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_uksub32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umax32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_umax32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__umin32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_umin32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__uradd32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_uradd32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__urcras32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_urcras32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__urcrsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_urcrsa32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__urstas32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_urstas32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__urstsa32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_urstsa32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__ursub32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_ursub32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ukadd32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukadd32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ukcras32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukcras32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ukcrsa32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukcrsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ukstas32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukstas32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ukstsa32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ukstsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_uksub32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_uksub32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_umax32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_umax32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_umin32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_umin32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_uradd32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_uradd32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_urcras32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_urcras32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_urcrsa32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_urcrsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_urstas32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_urstas32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_urstsa32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_urstsa32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_ursub32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_ursub32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__pkbb32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_pkbb32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__pkbt32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_pkbt32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__pktb32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_pktb32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__pktt32(uint64_t a, uint64_t b) {
  return (uint64_t) __builtin_riscv_pktt32((uint32x2_t)a, (uint32x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_pkbb32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_pkbb32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_pkbt32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_pkbt32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_pktb32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_pktb32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_pktt32(uint32x2_t a, uint32x2_t b) {
  return __builtin_riscv_pktt32(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint32x2_t __rv__v_umaqa(uint32x2_t t, uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_umaqa_v2si(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_scmpeq8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_cmpeq8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_ucmpeq8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_cmpeq8_v8qi((int8x8_t)a, (int8x8_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_clrs8(int8x8_t a) {
  return __builtin_riscv_clrs8_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_uclip8(int8x8_t a, const uint32_t b) {
  return __builtin_riscv_uclip8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_scmplt8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_scmplt8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_scmple8(int8x8_t a, int8x8_t b) {
  return __builtin_riscv_scmple8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_clo8(uint8x8_t a) {
  return __builtin_riscv_clo8_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_clz8(uint8x8_t a) {
  return __builtin_riscv_clz8_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_swap8(uint8x8_t a) {
  return __builtin_riscv_swap8_v8qi(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_srl8(uint8x8_t a, uint32_t b) {
  return __builtin_riscv_srl8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_srl8_u(uint8x8_t a, uint32_t b) {
  return __builtin_riscv_srl8_u_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_sll8(uint8x8_t a, uint32_t b) {
  return __builtin_riscv_sll8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_umin8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_umin8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_umax8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_umax8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_uradd8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_uradd8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_ukadd8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_ukadd8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_ucmple8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_ucmple8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_ursub8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_ursub8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_uksub8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_uksub8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint8x8_t __rv__v_ucmplt8(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_ucmplt8_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__v_pbsad(uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_pbsad_v8qi(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
uint64_t __rv__v_pbsada(uint64_t t, uint8x8_t a, uint8x8_t b) {
  return __builtin_riscv_pbsada_di(t, a, b);
}

#endif // __riscv_xlen == 64

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__add16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_add16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_add16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sub16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sub16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sub16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__cras16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_cras16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_cras16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__crsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_crsa16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_crsa16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__stas16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_stas16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_stas16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__stsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_stsa16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_stsa16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__add8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_add8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_add8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sub8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sub8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sub8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kabs16(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kabs16_v4hi((int16x4_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kabs16_v2hi((int16x2_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kslra16(uintXLEN_t a, int32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kslra16_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kslra16_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kslra16_u(uintXLEN_t a, int32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kslra16_u_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kslra16_u_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sclip16(uintXLEN_t a, const uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sclip16_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sclip16_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__radd16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_radd16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_radd16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rcras16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_rcras16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_rcras16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rcrsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_rcrsa16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_rcrsa16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rstas16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_rstas16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_rstas16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rstsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_rstsa16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_rstsa16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rsub16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_rsub16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_rsub16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kadd16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kadd16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kadd16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kcras16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kcras16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kcras16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kcrsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kcrsa16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kcrsa16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ksub16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ksub16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ksub16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kstas16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kstas16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kstas16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kstsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kstsa16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kstsa16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__khm16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_khm16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_khm16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__khmx16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_khmx16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_khmx16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__smax16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_smax16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_smax16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__smin16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_smin16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_smin16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sra16(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sra16_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sra16_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sra16_u(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sra16_u_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sra16_u_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ksll16(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ksll16_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ksll16_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sunpkd810(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sunpkd810_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sunpkd810_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sunpkd820(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sunpkd820_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sunpkd820_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sunpkd830(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sunpkd830_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sunpkd830_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sunpkd831(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sunpkd831_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sunpkd831_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sunpkd832(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sunpkd832_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sunpkd832_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kdmbb(uint32_t a, uint32_t b) {
  return __builtin_riscv_kdmbb((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kdmbt(uint32_t a, uint32_t b) {
  return __builtin_riscv_kdmbt((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kdmtt(uint32_t a, uint32_t b) {
  return __builtin_riscv_kdmtt((int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kdmbb(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kdmbb(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kdmbt(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kdmbt(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kdmtt(int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kdmtt(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kabsw(int32_t a) {
  return __builtin_riscv_kabsw(a);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__ksllw(int32_t a, uint32_t b) {
  return __builtin_riscv_ksllw(a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kdmabb(int32_t t, uint32_t a, uint32_t b) {
  return __builtin_riscv_kdmabb(t, (int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kdmabt(int32_t t, uint32_t a, uint32_t b) {
  return __builtin_riscv_kdmabt(t, (int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__kdmatt(int32_t t, uint32_t a, uint32_t b) {
  return __builtin_riscv_kdmatt(t, (int16x2_t)a, (int16x2_t)b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kdmabb(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kdmabb(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kdmabt(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kdmabt(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__v_kdmatt(int32_t t, int16x2_t a, int16x2_t b) {
  return __builtin_riscv_kdmatt(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__maddr32(int32_t t, int32_t a, int32_t b) {
  return __builtin_riscv_maddr32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
int32_t __rv__msubr32(int32_t t, int32_t a, int32_t b) {
  return __builtin_riscv_msubr32(t, a, b);
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smbb16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smbb16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smbb16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smbt16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smbt16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smbt16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smtt16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smtt16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smtt16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smds(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smds_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smds_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smdrs(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smdrs_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smdrs_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smxds(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smxds_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smxds_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmda(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmda_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmda_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmxda(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmxda_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmxda_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__sclip32(intXLEN_t a, const uint32_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_sclip32_v2si((int32x2_t)a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_sclip32_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smmwb(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smmwb_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smmwb_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smmwb_u(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smmwb_u_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smmwb_u_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smmwt(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smmwt_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smmwt_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smmwt_u(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smmwt_u_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smmwt_u_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmwb2(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmwb2_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmwb2_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmwb2_u(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmwb2_u_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmwb2_u_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmwt2(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmwt2_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmwt2_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmwt2_u(intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmwt2_u_v2si((int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmwt2_u_si(a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smmul(intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smmul_v2si((int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smmul_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smmul_u(intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smmul_u_v2si((int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smmul_u_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kwmmul(intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kwmmul_v2si((int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kwmmul_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kwmmul_u(intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kwmmul_u_v2si((int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kwmmul_u_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmabb(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmabb_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmabb_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmabt(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmabt_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmabt_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmatt(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmatt_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmatt_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmada(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmada_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmada_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmaxda(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmaxda_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmaxda_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmads(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmads_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmads_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmadrs(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmadrs_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmadrs_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmaxds(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmaxds_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmaxds_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmsda(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmsda_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmsda_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmsxda(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmsxda_v2si((int32x2_t)t, (int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmsxda_si(t, (int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawb(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawb_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawb_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawb_u(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawb_u_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawb_u_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawb2(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawb2_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawb2_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawb2_u(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawb2_u_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawb2_u_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawt(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawt_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawt_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawt_u(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawt_u_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawt_u_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawt2(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawt2_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawt2_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmawt2_u(intXLEN_t t, intXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmawt2_u_v2si((int32x2_t)t, (int32x2_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmawt2_u_si(t, a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmac(intXLEN_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmac_v2si((int32x2_t)t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmac_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmac_u(intXLEN_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmac_u_v2si((int32x2_t)t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmac_u_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmsb(intXLEN_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmsb_v2si((int32x2_t)t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmsb_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kmmsb_u(intXLEN_t t, intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_kmmsb_u_v2si((int32x2_t)t, (int32x2_t)a, (int32x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kmmsb_u_si(t, a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smaqa(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smaqa_v2si((int32x2_t)t, (int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smaqa_si(t, (int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__smaqa_su(intXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (int64_t) __builtin_riscv_smaqa_su_v2si((int32x2_t)t, (int8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_smaqa_su_si(t, (int8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kabs8(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kabs8_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kabs8_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kslra8(uintXLEN_t a, int32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kslra8_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kslra8_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kslra8_u(uintXLEN_t a, int32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kslra8_u_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kslra8_u_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sclip8(uintXLEN_t a, const uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sclip8_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sclip8_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__radd8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_radd8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_radd8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rsub8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_rsub8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_rsub8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__kadd8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_kadd8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_kadd8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ksub8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ksub8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ksub8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__khm8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_khm8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_khm8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__khmx8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_khmx8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_khmx8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__smin8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_smin8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_smin8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__smax8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_smax8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_smax8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sra8(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sra8_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sra8_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sra8_u(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sra8_u_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sra8_u_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ksll8(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ksll8_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ksll8_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__khmbb(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_khmbb_di((int16x2_t)a, (int16x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_khmbb_si((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__khmbt(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_khmbt_di((int16x2_t)a, (int16x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_khmbt_si((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__khmtt(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_khmtt_di((int16x2_t)a, (int16x2_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_khmtt_si((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__v_khmbb(int16x2_t a, int16x2_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_khmbb_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_khmbb_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__v_khmbt(int16x2_t a, int16x2_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_khmbt_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_khmbt_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__v_khmtt(int16x2_t a, int16x2_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_khmtt_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_khmtt_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kslraw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_kslraw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kslraw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kslraw_u(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_kslraw_u_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kslraw_u_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kaddh(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_kaddh_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kaddh_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__ksubh(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ksubh_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ksubh_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__kaddw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_kaddw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_kaddw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__ksubw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ksubw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ksubw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__raddw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_raddw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_raddw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__rsubw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_rsubw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_rsubw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__maxw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_maxw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_maxw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__minw(int32_t a, int32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_minw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_minw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__ave(intXLEN_t a, intXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ave_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ave_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
intXLEN_t __rv__sra_u(intXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_sra_u_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_sra_u_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__cmpeq16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_cmpeq16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_cmpeq16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clrs16(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clrs16_v4hi((int16x4_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_clrs16_v2hi((int16x2_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uclip16(uintXLEN_t a, const uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uclip16_v4hi((int16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_uclip16_v2hi((int16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__scmplt16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_scmplt16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_scmplt16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__scmple16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_scmple16_v4hi((int16x4_t)a, (int16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_scmple16_v2hi((int16x2_t)a, (int16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clo16(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clo16_v4hi((uint16x4_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_clo16_v2hi((uint16x2_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clz16(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clz16_v4hi((uint16x4_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_clz16_v2hi((uint16x2_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__swap16(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_swap16_v4hi((uint16x4_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_swap16_v2hi((uint16x2_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__srl16(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_srl16_v4hi((uint16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_srl16_v2hi((uint16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__srl16_u(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_srl16_u_v4hi((uint16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_srl16_u_v2hi((uint16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sll16(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sll16_v4hi((uint16x4_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sll16_v2hi((uint16x2_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__umax16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_umax16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_umax16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__umin16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_umin16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_umin16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uradd16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uradd16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_uradd16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ucmple16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ucmple16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ucmple16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ucmplt16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ucmplt16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ucmplt16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukadd16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ukadd16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ukadd16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ursub16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ursub16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ursub16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__urcras16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_urcras16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_urcras16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__urcrsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_urcrsa16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_urcrsa16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__urstas16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_urstas16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_urstas16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__urstsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_urstsa16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_urstsa16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uksub16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uksub16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_uksub16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukcras16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ukcras16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ukcras16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukcrsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ukcrsa16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ukcrsa16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukstas16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ukstas16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ukstas16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukstsa16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ukstsa16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ukstsa16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__pkbb16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_pkbb16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_pkbb16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__pkbt16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_pkbt16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_pkbt16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__pktb16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_pktb16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_pktb16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__pktt16(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_pktt16_v4hi((uint16x4_t)a, (uint16x4_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_pktt16_v2hi((uint16x2_t)a, (uint16x2_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__zunpkd810(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_zunpkd810_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_zunpkd810_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__zunpkd820(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_zunpkd820_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_zunpkd820_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__zunpkd830(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_zunpkd830_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_zunpkd830_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__zunpkd831(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_zunpkd831_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_zunpkd831_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__zunpkd832(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_zunpkd832_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_zunpkd832_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clrs32(intXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clrs32_v2si((int32x2_t)a);
#elif __riscv_xlen == 32
  return __builtin_riscv_clrs32_si(a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uclip32(intXLEN_t a, const uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uclip32_v2si((int32x2_t)a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_uclip32_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clo32(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clo32_v2si((uint32x2_t)a);
#elif __riscv_xlen == 32
  return __builtin_riscv_clo32_si(a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clz32(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clz32_v2si((uint32x2_t)a);
#elif __riscv_xlen == 32
  return __builtin_riscv_clz32_si(a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__umaqa(uintXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_umaqa_v2si((uint32x2_t)t, (uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_umaqa_si(t, (uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__cmpeq8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_cmpeq8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_cmpeq8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clrs8(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clrs8_v8qi((int8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_clrs8_v4qi((int8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uclip8(uintXLEN_t a, const uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uclip8_v8qi((int8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_uclip8_v4qi((int8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__scmplt8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_scmplt8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_scmplt8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__scmple8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_scmple8_v8qi((int8x8_t)a, (int8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_scmple8_v4qi((int8x4_t)a, (int8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clo8(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clo8_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_clo8_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__clz8(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_clz8_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_clz8_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__swap8(uintXLEN_t a) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_swap8_v8qi((uint8x8_t)a);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_swap8_v4qi((uint8x4_t)a);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__srl8(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_srl8_v8qi((uint8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_srl8_v4qi((uint8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__srl8_u(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_srl8_u_v8qi((uint8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_srl8_u_v4qi((uint8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__sll8(uintXLEN_t a, uint32_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_sll8_v8qi((uint8x8_t)a, b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_sll8_v4qi((uint8x4_t)a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__umin8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_umin8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_umin8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__umax8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_umax8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_umax8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uradd8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uradd8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_uradd8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukadd8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ukadd8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ukadd8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ucmple8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ucmple8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ucmple8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ursub8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ursub8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ursub8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uksub8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_uksub8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_uksub8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ucmplt8(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return (uint64_t) __builtin_riscv_ucmplt8_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return (uint32_t) __builtin_riscv_ucmplt8_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukaddh(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ukaddh_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ukaddh_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uksubh(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_uksubh_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_uksubh_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ukaddw(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ukaddw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ukaddw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uksubw(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_uksubw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_uksubw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__uraddw(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_uraddw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_uraddw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__ursubw(uint32_t a, uint32_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_ursubw_di(a, b);
#elif __riscv_xlen == 32
  return __builtin_riscv_ursubw_si(a, b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__pbsad(uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_pbsad_v8qi((uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_pbsad_v4qi((uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__bitrev(uintXLEN_t a, uint32_t msb) {
#if __riscv_xlen == 64
  return __builtin_riscv_bitrev_di(a, msb);
#elif __riscv_xlen == 32
  return __builtin_riscv_bitrev_si(a, msb);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__bpick(uintXLEN_t a, uintXLEN_t b, uintXLEN_t c) {
#if __riscv_xlen == 64
  return __builtin_riscv_bpick_di(a, b, c);
#elif __riscv_xlen == 32
  return __builtin_riscv_bpick_si(a, b, c);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__pbsada(uintXLEN_t t, uintXLEN_t a, uintXLEN_t b) {
#if __riscv_xlen == 64
  return __builtin_riscv_pbsada_di(t, (uint8x8_t)a, (uint8x8_t)b);
#elif __riscv_xlen == 32
  return __builtin_riscv_pbsada_si(t, (uint8x4_t)a, (uint8x4_t)b);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__insb(uintXLEN_t t, uintXLEN_t a, const uint32_t bpos) {
#if __riscv_xlen == 64
  return __builtin_riscv_insb_di(t, a, bpos);
#elif __riscv_xlen == 32
  return __builtin_riscv_insb_si(t, a, bpos);
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
uintXLEN_t __rv__rdov(void) {
#if __riscv_xlen == 64
  return __builtin_riscv_rdov_di();
#elif __riscv_xlen == 32
  return __builtin_riscv_rdov_si();
#endif
}

__extension__ static __inline __attribute__ ((__always_inline__))
void __rv__clrov(void) {
  __builtin_riscv_clrov();
}

#endif //__riscv_dsp

#endif // __GCC_RISCV_DSP_H__
