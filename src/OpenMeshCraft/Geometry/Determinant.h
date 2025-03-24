#pragma once

namespace OMC {

/*************************************************************************
 * Calculate the determinant of a matrix.
 * Support 2x2, 3x3, 4x4, 5x5, 6x6, and 7x7 matrix.
 * Reference: CGAL/determinant.h
 *************************************************************************/

// clang-format off

template <class NT>
NT determinant(
  const NT &a00, const NT &a01,
  const NT &a10, const NT &a11)
{
  // First compute the det2x2
  const NT m01 = a00*a11 - a10*a01;
  return m01;
}

template <class NT>
NT determinant(
  const NT &a00, const NT &a01, const NT &a02,
  const NT &a10, const NT &a11, const NT &a12,
  const NT &a20, const NT &a21, const NT &a22)
{
  // First compute the det2x2
  NT m01  = a00*a11 - a10*a01;
  NT m02  = a00*a21 - a20*a01;
  NT m12  = a10*a21 - a20*a11;
  // Now compute the minors of rank 3
  NT m012 = m01*a22 - m02*a12 + m12*a02;
  return m012;
}

template <class NT>
NT determinant(
  const NT &a00, const NT &a01, const NT &a02, const NT &a03,
  const NT &a10, const NT &a11, const NT &a12, const NT &a13,
  const NT &a20, const NT &a21, const NT &a22, const NT &a23,
  const NT &a30, const NT &a31, const NT &a32, const NT &a33)
{
  // First compute the det2x2
  NT m01   = a10*a01 - a00*a11;
  NT m02   = a20*a01 - a00*a21;
  NT m03   = a30*a01 - a00*a31;
  NT m12   = a20*a11 - a10*a21;
  NT m13   = a30*a11 - a10*a31;
  NT m23   = a30*a21 - a20*a31;
  // Now compute the minors of rank 3
  NT m012  = m12*a02 - m02*a12 + m01*a22;
  NT m013  = m13*a02 - m03*a12 + m01*a32;
  NT m023  = m23*a02 - m03*a22 + m02*a32;
  NT m123  = m23*a12 - m13*a22 + m12*a32;
  // Now compute the minors of rank 4
  NT m0123 = m123*a03 - m023*a13 + m013*a23 - m012*a33;
  return m0123;
}

template <class NT>
NT determinant(
  const NT &a00, const NT &a01, const NT &a02, const NT &a03, const NT &a04,
  const NT &a10, const NT &a11, const NT &a12, const NT &a13, const NT &a14,
  const NT &a20, const NT &a21, const NT &a22, const NT &a23, const NT &a24,
  const NT &a30, const NT &a31, const NT &a32, const NT &a33, const NT &a34,
  const NT &a40, const NT &a41, const NT &a42, const NT &a43, const NT &a44)
{
  // First compute the det2x2
  NT m01   = a10*a01 - a00*a11;
  NT m02   = a20*a01 - a00*a21;
  NT m03   = a30*a01 - a00*a31;
  NT m04   = a40*a01 - a00*a41;
  NT m12   = a20*a11 - a10*a21;
  NT m13   = a30*a11 - a10*a31;
  NT m14   = a40*a11 - a10*a41;
  NT m23   = a30*a21 - a20*a31;
  NT m24   = a40*a21 - a20*a41;
  NT m34   = a40*a31 - a30*a41;
  // Now compute the minors of rank 3
  NT m012  = m12*a02 - m02*a12 + m01*a22;
  NT m013  = m13*a02 - m03*a12 + m01*a32;
  NT m014  = m14*a02 - m04*a12 + m01*a42;
  NT m023  = m23*a02 - m03*a22 + m02*a32;
  NT m024  = m24*a02 - m04*a22 + m02*a42;
  NT m034  = m34*a02 - m04*a32 + m03*a42;
  NT m123  = m23*a12 - m13*a22 + m12*a32;
  NT m124  = m24*a12 - m14*a22 + m12*a42;
  NT m134  = m34*a12 - m14*a32 + m13*a42;
  NT m234  = m34*a22 - m24*a32 + m23*a42;
  // Now compute the minors of rank 4
  NT m0123 = m123*a03 - m023*a13 + m013*a23 - m012*a33;
  NT m0124 = m124*a03 - m024*a13 + m014*a23 - m012*a43;
  NT m0134 = m134*a03 - m034*a13 + m014*a33 - m013*a43;
  NT m0234 = m234*a03 - m034*a23 + m024*a33 - m023*a43;
  NT m1234 = m234*a13 - m134*a23 + m124*a33 - m123*a43;
  // Now compute the minors of rank 5
  NT m01234 = m1234*a04 - m0234*a14 + m0134*a24 - m0124*a34 + m0123*a44;
  return m01234;
}

template <class NT>
NT determinant(
  const NT &a00, const NT &a01, const NT &a02, const NT &a03, const NT &a04, const NT &a05,
  const NT &a10, const NT &a11, const NT &a12, const NT &a13, const NT &a14, const NT &a15,
  const NT &a20, const NT &a21, const NT &a22, const NT &a23, const NT &a24, const NT &a25,
  const NT &a30, const NT &a31, const NT &a32, const NT &a33, const NT &a34, const NT &a35,
  const NT &a40, const NT &a41, const NT &a42, const NT &a43, const NT &a44, const NT &a45,
  const NT &a50, const NT &a51, const NT &a52, const NT &a53, const NT &a54, const NT &a55)
{
  // First compute the det2x2
  NT m01   = a00*a11 - a10*a01;
  NT m02   = a00*a21 - a20*a01;
  NT m03   = a00*a31 - a30*a01;
  NT m04   = a00*a41 - a40*a01;
  NT m05   = a00*a51 - a50*a01;
  NT m12   = a10*a21 - a20*a11;
  NT m13   = a10*a31 - a30*a11;
  NT m14   = a10*a41 - a40*a11;
  NT m15   = a10*a51 - a50*a11;
  NT m23   = a20*a31 - a30*a21;
  NT m24   = a20*a41 - a40*a21;
  NT m25   = a20*a51 - a50*a21;
  NT m34   = a30*a41 - a40*a31;
  NT m35   = a30*a51 - a50*a31;
  NT m45   = a40*a51 - a50*a41;
  // Now compute the minors of rank 3
  NT m012  = m01*a22 - m02*a12 + m12*a02;
  NT m013  = m01*a32 - m03*a12 + m13*a02;
  NT m014  = m01*a42 - m04*a12 + m14*a02;
  NT m015  = m01*a52 - m05*a12 + m15*a02;
  NT m023  = m02*a32 - m03*a22 + m23*a02;
  NT m024  = m02*a42 - m04*a22 + m24*a02;
  NT m025  = m02*a52 - m05*a22 + m25*a02;
  NT m034  = m03*a42 - m04*a32 + m34*a02;
  NT m035  = m03*a52 - m05*a32 + m35*a02;
  NT m045  = m04*a52 - m05*a42 + m45*a02;
  NT m123  = m12*a32 - m13*a22 + m23*a12;
  NT m124  = m12*a42 - m14*a22 + m24*a12;
  NT m125  = m12*a52 - m15*a22 + m25*a12;
  NT m134  = m13*a42 - m14*a32 + m34*a12;
  NT m135  = m13*a52 - m15*a32 + m35*a12;
  NT m145  = m14*a52 - m15*a42 + m45*a12;
  NT m234  = m23*a42 - m24*a32 + m34*a22;
  NT m235  = m23*a52 - m25*a32 + m35*a22;
  NT m245  = m24*a52 - m25*a42 + m45*a22;
  NT m345  = m34*a52 - m35*a42 + m45*a32;
  // Now compute the minors of rank 4
  NT m0123 = m012*a33 - m013*a23 + m023*a13 - m123*a03;
  NT m0124 = m012*a43 - m014*a23 + m024*a13 - m124*a03;
  NT m0125 = m012*a53 - m015*a23 + m025*a13 - m125*a03;
  NT m0134 = m013*a43 - m014*a33 + m034*a13 - m134*a03;
  NT m0135 = m013*a53 - m015*a33 + m035*a13 - m135*a03;
  NT m0145 = m014*a53 - m015*a43 + m045*a13 - m145*a03;
  NT m0234 = m023*a43 - m024*a33 + m034*a23 - m234*a03;
  NT m0235 = m023*a53 - m025*a33 + m035*a23 - m235*a03;
  NT m0245 = m024*a53 - m025*a43 + m045*a23 - m245*a03;
  NT m0345 = m034*a53 - m035*a43 + m045*a33 - m345*a03;
  NT m1234 = m123*a43 - m124*a33 + m134*a23 - m234*a13;
  NT m1235 = m123*a53 - m125*a33 + m135*a23 - m235*a13;
  NT m1245 = m124*a53 - m125*a43 + m145*a23 - m245*a13;
  NT m1345 = m134*a53 - m135*a43 + m145*a33 - m345*a13;
  NT m2345 = m234*a53 - m235*a43 + m245*a33 - m345*a23;
  // Now compute the minors of rank 5
  NT m01234 = m0123*a44 - m0124*a34 + m0134*a24 - m0234*a14 + m1234*a04;
  NT m01235 = m0123*a54 - m0125*a34 + m0135*a24 - m0235*a14 + m1235*a04;
  NT m01245 = m0124*a54 - m0125*a44 + m0145*a24 - m0245*a14 + m1245*a04;
  NT m01345 = m0134*a54 - m0135*a44 + m0145*a34 - m0345*a14 + m1345*a04;
  NT m02345 = m0234*a54 - m0235*a44 + m0245*a34 - m0345*a24 + m2345*a04;
  NT m12345 = m1234*a54 - m1235*a44 + m1245*a34 - m1345*a24 + m2345*a14;
  // Now compute the minors of rank 6
  NT m012345 = m01234*a55 - m01235*a45 + m01245*a35 - m01345*a25 + m02345*a15 - m12345*a05;
  return m012345;
}

template <class NT>
NT determinant(
  const NT& a00, const NT& a01, const NT& a02, const NT& a03, const NT& a04, const NT& a05, const NT& a06,
  const NT& a10, const NT& a11, const NT& a12, const NT& a13, const NT& a14, const NT& a15, const NT& a16,
  const NT& a20, const NT& a21, const NT& a22, const NT& a23, const NT& a24, const NT& a25, const NT& a26,
  const NT& a30, const NT& a31, const NT& a32, const NT& a33, const NT& a34, const NT& a35, const NT& a36,
  const NT& a40, const NT& a41, const NT& a42, const NT& a43, const NT& a44, const NT& a45, const NT& a46,
  const NT& a50, const NT& a51, const NT& a52, const NT& a53, const NT& a54, const NT& a55, const NT& a56,
  const NT& a60, const NT& a61, const NT& a62, const NT& a63, const NT& a64, const NT& a65, const NT& a66)
{
  // First compute the det2x2
  NT m01 = a00*a11 - a10*a01;
  NT m02 = a00*a21 - a20*a01;
  NT m03 = a00*a31 - a30*a01;
  NT m04 = a00*a41 - a40*a01;
  NT m05 = a00*a51 - a50*a01;
  NT m06 = a00*a61 - a60*a01;

  NT m12 = a10*a21 - a20*a11;
  NT m13 = a10*a31 - a30*a11;
  NT m14 = a10*a41 - a40*a11;
  NT m15 = a10*a51 - a50*a11;
  NT m16 = a10*a61 - a60*a11;

  NT m23 = a20*a31 - a30*a21;
  NT m24 = a20*a41 - a40*a21;
  NT m25 = a20*a51 - a50*a21;
  NT m26 = a20*a61 - a60*a21;

  NT m34 = a30*a41 - a40*a31;
  NT m35 = a30*a51 - a50*a31;
  NT m36 = a30*a61 - a60*a31;

  NT m45 = a40*a51 - a50*a41;
  NT m46 = a40*a61 - a60*a41;

  NT m56 = a50*a61 - a60*a51;

  // Now compute the minors of rank 3
  NT m012 = m01*a22 - m02*a12 + m12*a02;
  NT m013 = m01*a32 - m03*a12 + m13*a02;
  NT m014 = m01*a42 - m04*a12 + m14*a02;
  NT m015 = m01*a52 - m05*a12 + m15*a02;
  NT m016 = m01*a62 - m06*a12 + m16*a02;

  NT m023 = m02*a32 - m03*a22 + m23*a02;
  NT m024 = m02*a42 - m04*a22 + m24*a02;
  NT m025 = m02*a52 - m05*a22 + m25*a02;
  NT m026 = m02*a62 - m06*a22 + m26*a02;
  NT m034 = m03*a42 - m04*a32 + m34*a02;
  NT m035 = m03*a52 - m05*a32 + m35*a02;
  NT m036 = m03*a62 - m06*a32 + m36*a02;

  NT m045 = m04*a52 - m05*a42 + m45*a02;
  NT m046 = m04*a62 - m06*a42 + m46*a02;

  NT m056 = m05*a62 - m06*a52 + m56*a02;

  NT m123 = m12*a32 - m13*a22 + m23*a12;
  NT m124 = m12*a42 - m14*a22 + m24*a12;
  NT m125 = m12*a52 - m15*a22 + m25*a12;
  NT m126 = m12*a62 - m16*a22 + m26*a12;

  NT m134 = m13*a42 - m14*a32 + m34*a12;
  NT m135 = m13*a52 - m15*a32 + m35*a12;
  NT m136 = m13*a62 - m16*a32 + m36*a12;

  NT m145 = m14*a52 - m15*a42 + m45*a12;
  NT m146 = m14*a62 - m16*a42 + m46*a12;

  NT m156 = m15*a62 - m16*a52 + m56*a12;

  NT m234 = m23*a42 - m24*a32 + m34*a22;
  NT m235 = m23*a52 - m25*a32 + m35*a22;
  NT m236 = m23*a62 - m26*a32 + m36*a22;

  NT m245 = m24*a52 - m25*a42 + m45*a22;
  NT m246 = m24*a62 - m26*a42 + m46*a22;

  NT m256 = m25*a62 - m26*a52 + m56*a22;

  NT m345 = m34*a52 - m35*a42 + m45*a32;
  NT m346 = m34*a62 - m36*a42 + m46*a32;

  NT m356 = m35*a62 - m36*a52 + m56*a32;

  NT m456 = m45*a62 - m46*a52 + m56*a42;

  // Now compute the minors of rank 4
  NT m0123 = m012*a33 - m013*a23 + m023*a13 - m123*a03;

  NT m0124 = m012*a43 - m014*a23 + m024*a13 - m124*a03;
  NT m0125 = m012*a53 - m015*a23 + m025*a13 - m125*a03;
  NT m0126 = m012*a63 - m016*a23 + m026*a13 - m126*a03;

  NT m0134 = m013*a43 - m014*a33 + m034*a13 - m134*a03;
  NT m0135 = m013*a53 - m015*a33 + m035*a13 - m135*a03;
  NT m0136 = m013*a63 - m016*a33 + m036*a13 - m136*a03;

  NT m0145 = m014*a53 - m015*a43 + m045*a13 - m145*a03;
  NT m0146 = m014*a63 - m016*a43 + m046*a13 - m146*a03;

  NT m0156 = m015*a63 - m016*a53 + m056*a13 - m156*a03;

  NT m0234 = m023*a43 - m024*a33 + m034*a23 - m234*a03;
  NT m0235 = m023*a53 - m025*a33 + m035*a23 - m235*a03;
  NT m0236 = m023*a63 - m026*a33 + m036*a23 - m236*a03;

  NT m0245 = m024*a53 - m025*a43 + m045*a23 - m245*a03;
  NT m0246 = m024*a63 - m026*a43 + m046*a23 - m246*a03;

  NT m0256 = m025*a63 - m026*a53 + m056*a23 - m256*a03;

  NT m0345 = m034*a53 - m035*a43 + m045*a33 - m345*a03;
  NT m0346 = m034*a63 - m036*a43 + m046*a33 - m346*a03;

  NT m0356 = m035*a63 - m036*a53 + m056*a33 - m356*a03;

  NT m0456 = m045*a63 - m046*a53 + m056*a43 - m456*a03;

  NT m1234 = m123*a43 - m124*a33 + m134*a23 - m234*a13;
  NT m1235 = m123*a53 - m125*a33 + m135*a23 - m235*a13;
  NT m1236 = m123*a63 - m126*a33 + m136*a23 - m236*a13;

  NT m1245 = m124*a53 - m125*a43 + m145*a23 - m245*a13;
  NT m1246 = m124*a63 - m126*a43 + m146*a23 - m246*a13;

  NT m1256 = m125*a63 - m126*a53 + m156*a23 - m256*a13;

  NT m1345 = m134*a53 - m135*a43 + m145*a33 - m345*a13;
  NT m1346 = m134*a63 - m136*a43 + m146*a33 - m346*a13;

  NT m1356 = m135*a63 - m136*a53 + m156*a33 - m356*a13;
  NT m1456 = m145*a63 - m146*a53 + m156*a43 - m456*a13;

  NT m2345 = m234*a53 - m235*a43 + m245*a33 - m345*a23;
  NT m2346 = m234*a63 - m236*a43 + m246*a33 - m346*a23;

  NT m2356 = m235*a63 - m236*a53 + m256*a33 - m356*a23;
  NT m2456 = m245*a63 - m246*a53 + m256*a43 - m456*a23;

  NT m3456 = m345*a63 - m346*a53 + m356*a43 - m456*a33;

  // Now compute the minors of rank 5
  NT m01234 = m0123*a44 - m0124*a34 + m0134*a24 - m0234*a14 + m1234*a04;

  NT m01235 = m0123*a54 - m0125*a34 + m0135*a24 - m0235*a14 + m1235*a04;

  NT m01236 = m0123*a64 - m0126*a34 + m0136*a24 - m0236*a14 + m1236*a04;

  NT m01245 = m0124*a54 - m0125*a44 + m0145*a24 - m0245*a14 + m1245*a04;
  NT m01246 = m0124*a64 - m0126*a44 + m0146*a24 - m0246*a14 + m1246*a04;

  NT m01256 = m0125*a64 - m0126*a54 + m0156*a24 - m0256*a14 + m1256*a04;

  NT m01345 = m0134*a54 - m0135*a44 + m0145*a34 - m0345*a14 + m1345*a04;
  NT m01346 = m0134*a64 - m0136*a44 + m0146*a34 - m0346*a14 + m1346*a04;

  NT m01356 = m0135*a64 - m0136*a54 + m0156*a34 - m0356*a14 + m1356*a04;
  NT m01456 = m0145*a64 - m0146*a54 + m0156*a44 - m0456*a14 + m1456*a04;

  NT m02345 = m0234*a54 - m0235*a44 + m0245*a34 - m0345*a24 + m2345*a04;
  NT m02346 = m0234*a64 - m0236*a44 + m0246*a34 - m0346*a24 + m2346*a04;

  NT m02356 = m0235*a64 - m0236*a54 + m0256*a34 - m0356*a24 + m2356*a04;
  NT m02456 = m0245*a64 - m0246*a54 + m0256*a44 - m0456*a24 + m2456*a04;
  NT m03456 = m0345*a64 - m0346*a54 + m0356*a44 - m0456*a34 + m3456*a04;

  NT m12345 = m1234*a54 - m1235*a44 + m1245*a34 - m1345*a24 + m2345*a14;
  NT m12346 = m1234*a64 - m1236*a44 + m1246*a34 - m1346*a24 + m2346*a14;

  NT m12356 = m1235*a64 - m1236*a54 + m1256*a34 - m1356*a24 + m2356*a14;
  NT m12456 = m1245*a64 - m1246*a54 + m1256*a44 - m1456*a24 + m2456*a14;
  NT m13456 = m1345*a64 - m1346*a54 + m1356*a44 - m1456*a34 + m3456*a14;

  NT m23456 = m2345*a64 - m2346*a54 + m2356*a44 - m2456*a34 + m3456*a24;

  // Now compute the minors of rank 6
  NT m012345 = m01234*a55 - m01235*a45 + m01245*a35 - m01345*a25 + m02345*a15 - m12345*a05;
  NT m012346 = m01234*a65 - m01236*a45 + m01246*a35 - m01346*a25 + m02346*a15 - m12346*a05;
  NT m012356 = m01235*a65 - m01236*a55 + m01256*a35 - m01356*a25 + m02356*a15 - m12356*a05;
  NT m012456 = m01245*a65 - m01246*a55 + m01256*a45 - m01456*a25 + m02456*a15 - m12456*a05;
  NT m013456 = m01345*a65 - m01346*a55 + m01356*a45 - m01456*a35 + m03456*a15 - m13456*a05;
  NT m023456 = m02345*a65 - m02346*a55 + m02356*a45 - m02456*a35 + m03456*a25 - m23456*a05;
  NT m123456 = m12345*a65 - m12346*a55 + m12356*a45 - m12456*a35 + m13456*a25 - m23456*a15;

  // Now compute the minors of rank 7
  NT m0123456 = m012345*a66 - m012346*a56 + m012356*a46 - m012456*a36 + m013456*a26 - m023456*a16 + m123456*a06;

  return m0123456;
}

/***************************************************************************
 * Calculate determinants for (weighted) circumcenter
 * Reference: CGAL/constructions/kernel_ftC3.h
 ***************************************************************************/

/**
 * @brief Compute determinants for circumcenter of three points.
 * The numerator and denominator are partial of the circumcenter.
 * circumcenter = px + numx/den, py - numy/den, pz + numz/den.
 */
template <class NT>
void determinants_for_circumcenter(
  const NT &px, const NT &py, const NT &pz,
  const NT &qx, const NT &qy, const NT &qz,
  const NT &rx, const NT &ry, const NT &rz,
  NT &num_x, NT &num_y, NT &num_z, NT &den)
{
  // translate p to origin
  NT qpx = qx - px;
  NT qpy = qy - py;
  NT qpz = qz - pz;

  NT rpx = rx - px;
  NT rpy = ry - py;
  NT rpz = rz - pz;

  // Solve a linear system composed of two bisectors and triangle's support plane.
  NT qp2 = (qpx * qpx) + (qpy * qpy) + (qpz * qpz);
  NT rp2 = (rpx * rpx) + (rpy * rpy) + (rpz * rpz);

  NT sx = qpy * rpz - qpz * rpy;
  NT sy = qpz * rpx - qpx * rpz;
  NT sz = qpx * rpy - qpy * rpx;

  // The following determinants can be developed and simplified.
  //
  //  NT num_x = determinant(qpy,qpz,qp2,
  //                         rpy,rpz,rp2,
  //                         sy,sz,NT(0));
  //  NT num_y = determinant(qpx,qpz,qp2,
  //                         rpx,rpz,rp2,
  //                         sx,sz,NT(0));
  //  NT num_z = determinant(qpx,qpy,qp2,
  //                         rpx,rpy,rp2,
  //                         sx,sy,NT(0));

  num_x = qp2 * determinant(rpy, rpz, sy, sz) - rp2 * determinant(qpy, qpz, sy, sz);
  num_y = qp2 * determinant(rpx, rpz, sx, sz) - rp2 * determinant(qpx, qpz, sx, sz);
  num_z = qp2 * determinant(rpx, rpy, sx, sy) - rp2 * determinant(qpx, qpy, sx, sy);
  den = determinant(qpx, qpy, qpz, rpx, rpy, rpz, sx, sy, sz);
}

/**
 * @brief Compute determinants for circumcenter of four points.
 * The numerator and denominator are partial of the circumcenter.
 * circumcenter = px + numx/den, py - numy/den, pz + numz/den.
 */
template <class NT>
void determinants_for_circumcenter(
  const NT &px, const NT &py, const NT &pz,
  const NT &qx, const NT &qy, const NT &qz,
  const NT &rx, const NT &ry, const NT &rz,
  const NT &sx, const NT &sy, const NT &sz,
  NT &num_x, NT &num_y, NT &num_z, NT &den)
{
  // translate p to origin
  NT qpx = qx - px;
  NT qpy = qy - py;
  NT qpz = qz - pz;

  NT rpx = rx - px;
  NT rpy = ry - py;
  NT rpz = rz - pz;

  NT spx = sx - px;
  NT spy = sy - py;
  NT spz = sz - pz;

  // Solve a linear system composed of three bisectors.
  NT qp2 = (qpx * qpx) + (qpy * qpy) + (qpz * qpz);
  NT rp2 = (rpx * rpx) + (rpy * rpy) + (rpz * rpz);
  NT sp2 = (spx * spx) + (spy * spy) + (spz * spz);

  num_x = determinant(qpy, qpz, qp2, rpy, rpz, rp2, spy, spz, sp2);
  num_y = determinant(qpx, qpz, qp2, rpx, rpz, rp2, spx, spz, sp2);
  num_z = determinant(qpx, qpy, qp2, rpx, rpy, rp2, spx, spy, sp2);
  den   = determinant(qpx, qpy, qpz, rpx, rpy, rpz, spx, spy, spz);
}

/**
 * @brief compute determinants for circumcenter of three weighted points.
 * The numerator and denominator are partial of the circumcenter.
 * circumcenter = px + numx/den, py - numy/den, pz + numz/den.
 */
template <class NT>
void determinants_for_weighted_circumcenter(
  const NT &px, const NT &py, const NT &pz, const NT &pw,
  const NT &qx, const NT &qy, const NT &qz, const NT &qw,
  const NT &rx, const NT &ry, const NT &rz, const NT &rw,
  NT &num_x, NT &num_y, NT &num_z, NT &den)
{
  // translate p to origin
  NT qpx = qx - px;
  NT qpy = qy - py;
  NT qpz = qz - pz;
  NT rpx = rx - px;
  NT rpy = ry - py;
  NT rpz = rz - pz;

  // Solve a linear system composed of two bisectors and triangle's support plane.
  NT qp2 = (qpx * qpx) + (qpy * qpy) + (qpz * qpz) - qw + pw;
  NT rp2 = (rpx * rpx) + (rpy * rpy) + (rpz * rpz) - rw + pw;

  NT sx = qpy * rpz - qpz * rpy;
  NT sy = qpz * rpx - qpx * rpz;
  NT sz = qpx * rpy - qpy * rpx;

  // The following determinants can be developed and simplified.
  //
  //  NT num_x = determinant(qpy,qpz,qp2,
  //                         rpy,rpz,rp2,
  //                         sy,sz,NT(0));
  //  NT num_y = determinant(qpx,qpz,qp2,
  //                         rpx,rpz,rp2,
  //                         sx,sz,NT(0));
  //  NT num_z = determinant(qpx,qpy,qp2,
  //                         rpx,rpy,rp2,
  //                         sx,sy,NT(0));

  num_x = qp2 * determinant(rpy, rpz, sy, sz) - rp2 * determinant(qpy, qpz, sy, sz);
  num_y = qp2 * determinant(rpx, rpz, sx, sz) - rp2 * determinant(qpx, qpz, sx, sz);
  num_z = qp2 * determinant(rpx, rpy, sx, sy) - rp2 * determinant(qpx, qpy, sx, sy);
  den = determinant(qpx, qpy, qpz, rpx, rpy, rpz, sx, sy, sz);
}

/**
 * @brief compute determinants for circumcenter of four weighted points.
 * The numerator and denominator are partial of the circumcenter.
 * circumcenter = px + numx/den, py - numy/den, pz + numz/den.
 */
template <class NT>
void determinants_for_weighted_circumcenter(
  const NT &px, const NT &py, const NT &pz, const NT &pw,
  const NT &qx, const NT &qy, const NT &qz, const NT &qw,
  const NT &rx, const NT &ry, const NT &rz, const NT &rw,
  const NT &sx, const NT &sy, const NT &sz, const NT &sw,
  NT &num_x, NT &num_y, NT &num_z, NT &den)
{
  // translate origin to p
  NT qpx = qx - px;
  NT qpy = qy - py;
  NT qpz = qz - pz;

  NT rpx = rx - px;
  NT rpy = ry - py;
  NT rpz = rz - pz;

  NT spx = sx - px;
  NT spy = sy - py;
  NT spz = sz - pz;

  // Solve a linear system composed of three bisectors.
  NT qp2 = (qpx * qpx) + (qpy * qpy) + (qpz * qpz) - qw + pw;
  NT rp2 = (rpx * rpx) + (rpy * rpy) + (rpz * rpz) - rw + pw;
  NT sp2 = (spx * spx) + (spy * spy) + (spz * spz) - sw + pw;

  num_x = determinant(qpy, qpz, qp2, rpy, rpz, rp2, spy, spz, sp2);
  num_y = determinant(qpx, qpz, qp2, rpx, rpz, rp2, spx, spz, sp2);
  num_z = determinant(qpx, qpy, qp2, rpx, rpy, rp2, spx, spy, sp2);
  den   = determinant(qpx, qpy, qpz, rpx, rpy, rpz, spx, spy, spz);
}

// clang-format on

} // namespace OMC