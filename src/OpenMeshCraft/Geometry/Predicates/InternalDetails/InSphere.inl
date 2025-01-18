#pragma once

#include "Shewchuk.h"

#include "OpenMeshCraft/Geometry/Predicates/IndirectDefinitions.h"

#include "OpenMeshCraft/NumberTypes/ExpansionObject.h"
#include "OpenMeshCraft/NumberTypes/IntervalNumber.h"
#include "OpenMeshCraft/NumberTypes/LazyNumber.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
#define CHECK_FOR_XYZERFLOWS

namespace OMC {

/*********************************************************************/
/* Forward Declarations (hand)****************************************/
/*********************************************************************/

/* On explicit points ************************************************/

inline Sign inSphere(const double *a, const double *b, const double *c,
                     const double *d, const double *e);

template <typename IT, typename ET>
Sign inSphere(const GenericPoint3T<IT, ET> &pa,
              const GenericPoint3T<IT, ET> &pb,
              const GenericPoint3T<IT, ET> &pc,
              const GenericPoint3T<IT, ET> &pd,
              const GenericPoint3T<IT, ET> &pe);

/*********************************************************************/
/* Forward Declarations (mostly auto-generated)***********************/
/*********************************************************************/

inline Sign inSphere_filtered(double pax, double pay, double paz, double pbx,
                              double pby, double pbz, double pcx, double pcy,
                              double pcz, double pdx, double pdy, double pdz,
                              double pex, double pey, double pez);

template <typename IT>
Sign inSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby, IT pbz, IT pcx,
                       IT pcy, IT pcz, IT pdx, IT pdy, IT pdz, IT pex, IT pey,
                       IT pez);

template <typename ET>
Sign inSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby, ET pbz, ET pcx,
                    ET pcy, ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                    ET pez);

inline Sign inSphere_expansion(double pax, double pay, double paz, double pbx,
                               double pby, double pbz, double pcx, double pcy,
                               double pcz, double pdx, double pdy, double pdz,
                               double pex, double pey, double pez);

template <typename IT, typename ET>
Sign inSphere(double pax, double pay, double paz, double pbx, double pby,
              double pbz, double pcx, double pcy, double pcz, double pdx,
              double pdy, double pdz, double pex, double pey, double pez);

template <typename IT, typename ET>
Sign inSphere(const GenericPoint3T<IT, ET> &pa,
              const GenericPoint3T<IT, ET> &pb,
              const GenericPoint3T<IT, ET> &pc,
              const GenericPoint3T<IT, ET> &pd,
              const GenericPoint3T<IT, ET> &pe);

/*===================================================================*/

template <typename IT, typename ET>
Sign inSphere_IEEEE_interval(const GenericPoint3T<IT, ET> &p1, IT pbx, IT pby,
                             IT pbz, IT pcx, IT pcy, IT pcz, IT pdx, IT pdy,
                             IT pdz, IT pex, IT pey, IT pez);

template <typename IT, typename ET>
Sign inSphere_IEEEE_exact(const GenericPoint3T<IT, ET> &p1, ET pbx, ET pby,
                          ET pbz, ET pcx, ET pcy, ET pcz, ET pdx, ET pdy,
                          ET pdz, ET pex, ET pey, ET pez);

template <typename IT, typename ET>
Sign inSphere_IEEEE_expansion(const GenericPoint3T<IT, ET> &p1, double pbx,
                              double pby, double pbz, double pcx, double pcy,
                              double pcz, double pdx, double pdy, double pdz,
                              double pex, double pey, double pez);

template <typename IT, typename ET>
Sign inSphere_IEEEE(const GenericPoint3T<IT, ET> &p1, double pbx, double pby,
                    double pbz, double pcx, double pcy, double pcz, double pdx,
                    double pdy, double pdz, double pex, double pey, double pez);

template <typename IT, typename ET>
Sign inSphere_IEEEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &pb,
                    const GenericPoint3T<IT, ET> &pc,
                    const GenericPoint3T<IT, ET> &pd,
                    const GenericPoint3T<IT, ET> &pe);

/*===================================================================*/

template <typename IT, typename ET>
Sign inSphere_IIEEE_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2, IT pcx, IT pcy,
                             IT pcz, IT pdx, IT pdy, IT pdz, IT pex, IT pey,
                             IT pez);

template <typename IT, typename ET>
Sign inSphere_IIEEE_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2, ET pcx, ET pcy,
                          ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                          ET pez);

template <typename IT, typename ET>
Sign inSphere_IIEEE_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2, double pcx,
                              double pcy, double pcz, double pdx, double pdy,
                              double pdz, double pex, double pey, double pez);

template <typename IT, typename ET>
Sign inSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2, double pcx, double pcy,
                    double pcz, double pdx, double pdy, double pdz, double pex,
                    double pey, double pez);

template <typename IT, typename ET>
Sign inSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &pc,
                    const GenericPoint3T<IT, ET> &pd,
                    const GenericPoint3T<IT, ET> &pe);

/*===================================================================*/

template <typename IT, typename ET>
Sign inSphere_IIIEE_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3, IT pdx, IT pdy,
                             IT pdz, IT pex, IT pey, IT pez);

template <typename IT, typename ET>
Sign inSphere_IIIEE_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2,
                          const GenericPoint3T<IT, ET> &p3, ET pdx, ET pdy,
                          ET pdz, ET pex, ET pey, ET pez);

template <typename IT, typename ET>
Sign inSphere_IIIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3, double pdx,
                              double pdy, double pdz, double pex, double pey,
                              double pez);

template <typename IT, typename ET>
Sign inSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3, double pdx, double pdy,
                    double pdz, double pex, double pey, double pez);

template <typename IT, typename ET>
Sign inSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &pd,
                    const GenericPoint3T<IT, ET> &pe);

/*===================================================================*/

template <typename IT, typename ET>
Sign inSphere_IIIIE_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3,
                             const GenericPoint3T<IT, ET> &p4, IT pex, IT pey,
                             IT pez);

template <typename IT, typename ET>
Sign inSphere_IIIIE_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2,
                          const GenericPoint3T<IT, ET> &p3,
                          const GenericPoint3T<IT, ET> &p4, ET pex, ET pey,
                          ET pez);

template <typename IT, typename ET>
Sign inSphere_IIIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3,
                              const GenericPoint3T<IT, ET> &p4, double pex,
                              double pey, double pez);

template <typename IT, typename ET>
Sign inSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &p4, double pex, double pey,
                    double pez);

template <typename IT, typename ET>
Sign inSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &p4,
                    const GenericPoint3T<IT, ET> &pe);

/*===================================================================*/

template <typename IT, typename ET>
Sign inSphere_IIIII_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3,
                             const GenericPoint3T<IT, ET> &p4,
                             const GenericPoint3T<IT, ET> &p5);

template <typename IT, typename ET>
Sign inSphere_IIIII_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2,
                          const GenericPoint3T<IT, ET> &p3,
                          const GenericPoint3T<IT, ET> &p4,
                          const GenericPoint3T<IT, ET> &p5);

template <typename IT, typename ET>
Sign inSphere_IIIII_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3,
                              const GenericPoint3T<IT, ET> &p4,
                              const GenericPoint3T<IT, ET> &p5);

template <typename IT, typename ET>
Sign inSphere_IIIII(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &p4,
                    const GenericPoint3T<IT, ET> &p5);

/*===================================================================*/

inline Sign inPowerSphere_filtered(double pax, double pay, double paz,
                                   double pbx, double pby, double pbz,
                                   double pcx, double pcy, double pcz,
                                   double pdx, double pdy, double pdz,
                                   double pex, double pey, double pez,
                                   double wa, double wb, double wc, double wd,
                                   double we);

template <typename IT>
Sign inPowerSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby, IT pbz,
                            IT pcx, IT pcy, IT pcz, IT pdx, IT pdy, IT pdz,
                            IT pex, IT pey, IT pez, IT wa, IT wb, IT wc, IT wd,
                            IT we);

template <typename ET>
Sign inPowerSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby, ET pbz, ET pcx,
                         ET pcy, ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                         ET pez, ET wa, ET wb, ET wc, ET wd, ET we);

inline Sign inPowerSphere_expansion(double pax, double pay, double paz,
                                    double pbx, double pby, double pbz,
                                    double pcx, double pcy, double pcz,
                                    double pdx, double pdy, double pdz,
                                    double pex, double pey, double pez,
                                    double wa, double wb, double wc, double wd,
                                    double we);

template <typename IT, typename ET>
Sign inPowerSphere(double pax, double pay, double paz, double pbx, double pby,
                   double pbz, double pcx, double pcy, double pcz, double pdx,
                   double pdy, double pdz, double pex, double pey, double pez,
                   double wa, double wb, double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere(const GenericPoint3T<IT, ET> &pa,
                   const GenericPoint3T<IT, ET> &pb,
                   const GenericPoint3T<IT, ET> &pc,
                   const GenericPoint3T<IT, ET> &pd,
                   const GenericPoint3T<IT, ET> &pe, double wa, double wb,
                   double wc, double wd, double we);

/*===================================================================*/

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE_interval(const GenericPoint3T<IT, ET> &p1, IT pbx,
                                  IT pby, IT pbz, IT pcx, IT pcy, IT pcz,
                                  IT pdx, IT pdy, IT pdz, IT pex, IT pey,
                                  IT pez, IT w1, IT wb, IT wc, IT wd, IT we);

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE_exact(const GenericPoint3T<IT, ET> &p1, ET pbx, ET pby,
                               ET pbz, ET pcx, ET pcy, ET pcz, ET pdx, ET pdy,
                               ET pdz, ET pex, ET pey, ET pez, ET w1, ET wb,
                               ET wc, ET wd, ET we);

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE_expansion(const GenericPoint3T<IT, ET> &p1, double pbx,
                                   double pby, double pbz, double pcx,
                                   double pcy, double pcz, double pdx,
                                   double pdy, double pdz, double pex,
                                   double pey, double pez, double w1, double wb,
                                   double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE(const GenericPoint3T<IT, ET> &p1, double pbx,
                         double pby, double pbz, double pcx, double pcy,
                         double pcz, double pdx, double pdy, double pdz,
                         double pex, double pey, double pez, double w1,
                         double wb, double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &pb,
                         const GenericPoint3T<IT, ET> &pc,
                         const GenericPoint3T<IT, ET> &pd,
                         const GenericPoint3T<IT, ET> &pe, double w1, double wb,
                         double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2, IT pcx,
                                  IT pcy, IT pcz, IT pdx, IT pdy, IT pdz,
                                  IT pex, IT pey, IT pez, IT w1, IT w2, IT wc,
                                  IT wd, IT we);

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, ET pcx, ET pcy,
                               ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                               ET pez, ET w1, ET w2, ET wc, ET wd, ET we);

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2, double pcx,
                                   double pcy, double pcz, double pdx,
                                   double pdy, double pdz, double pex,
                                   double pey, double pez, double w1, double w2,
                                   double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2, double pcx,
                         double pcy, double pcz, double pdx, double pdy,
                         double pdz, double pex, double pey, double pez,
                         double w1, double w2, double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &pc,
                         const GenericPoint3T<IT, ET> &pd,
                         const GenericPoint3T<IT, ET> &pe, double w1, double w2,
                         double wc, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2,
                                  const GenericPoint3T<IT, ET> &p3, IT pdx,
                                  IT pdy, IT pdz, IT pex, IT pey, IT pez, IT w1,
                                  IT w2, IT w3, IT wd, IT we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3, ET pdx, ET pdy,
                               ET pdz, ET pex, ET pey, ET pez, ET w1, ET w2,
                               ET w3, ET wd, ET we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2,
                                   const GenericPoint3T<IT, ET> &p3, double pdx,
                                   double pdy, double pdz, double pex,
                                   double pey, double pez, double w1, double w2,
                                   double w3, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3, double pdx,
                         double pdy, double pdz, double pex, double pey,
                         double pez, double w1, double w2, double w3, double wd,
                         double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &pd,
                         const GenericPoint3T<IT, ET> &pe, double w1, double w2,
                         double w3, double wd, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2,
                                  const GenericPoint3T<IT, ET> &p3,
                                  const GenericPoint3T<IT, ET> &p4, IT pex,
                                  IT pey, IT pez, IT w1, IT w2, IT w3, IT w4,
                                  IT we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3,
                               const GenericPoint3T<IT, ET> &p4, ET pex, ET pey,
                               ET pez, ET w1, ET w2, ET w3, ET w4, ET we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2,
                                   const GenericPoint3T<IT, ET> &p3,
                                   const GenericPoint3T<IT, ET> &p4, double pex,
                                   double pey, double pez, double w1, double w2,
                                   double w3, double w4, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4, double pex,
                         double pey, double pez, double w1, double w2,
                         double w3, double w4, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4,
                         const GenericPoint3T<IT, ET> &pe, double w1, double w2,
                         double w3, double w4, double we);

template <typename IT, typename ET>
Sign inPowerSphere_IIIII_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2,
                                  const GenericPoint3T<IT, ET> &p3,
                                  const GenericPoint3T<IT, ET> &p4,
                                  const GenericPoint3T<IT, ET> &p5, IT w1,
                                  IT w2, IT w3, IT w4, IT w5);

template <typename IT, typename ET>
Sign inPowerSphere_IIIII_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3,
                               const GenericPoint3T<IT, ET> &p4,
                               const GenericPoint3T<IT, ET> &p5, ET w1, ET w2,
                               ET w3, ET w4, ET w5);

template <typename IT, typename ET>
Sign inPowerSphere_IIIII_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2,
                                   const GenericPoint3T<IT, ET> &p3,
                                   const GenericPoint3T<IT, ET> &p4,
                                   const GenericPoint3T<IT, ET> &p5, double w1,
                                   double w2, double w3, double w4, double w5);

template <typename IT, typename ET>
Sign inPowerSphere_IIIII(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4,
                         const GenericPoint3T<IT, ET> &p5, double w1, double w2,
                         double w3, double w4, double w5);

/*===================================================================*/

template <typename IT>
Sign inSegmentDiametricalSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby,
                                         IT pbz, IT pcx, IT pcy, IT pcz);

template <typename ET>
Sign inSegmentDiametricalSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby,
                                      ET pbz, ET pcx, ET pcy, ET pcz);

inline Sign inSegmentDiametricalSphere_expansion(double pax, double pay,
                                                 double paz, double pbx,
                                                 double pby, double pbz,
                                                 double pcx, double pcy,
                                                 double pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere(double pax, double pay, double paz, double pbx,
                                double pby, double pbz, double pcx, double pcy,
                                double pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere(const GenericPoint3T<IT, ET> &pa,
                                const GenericPoint3T<IT, ET> &pb,
                                const GenericPoint3T<IT, ET> &pc);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI_interval(const GenericPoint3T<IT, ET> &pc,
                                             IT pax, IT pay, IT paz, IT pbx,
                                             IT pby, IT pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI_exact(const GenericPoint3T<IT, ET> &pc,
                                          ET pax, ET pay, ET paz, ET pbx,
                                          ET pby, ET pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI_expansion(const GenericPoint3T<IT, ET> &pc,
                                              double pax, double pay,
                                              double paz, double pbx,
                                              double pby, double pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI(const GenericPoint3T<IT, ET> &pc,
                                    double pax, double pay, double paz,
                                    double pbx, double pby, double pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI(const GenericPoint3T<IT, ET> &pc,
                                    const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE_interval(const GenericPoint3T<IT, ET> &pa,
                                             IT pbx, IT pby, IT pbz, IT pcx,
                                             IT pcy, IT pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE_exact(const GenericPoint3T<IT, ET> &pa,
                                          ET pbx, ET pby, ET pbz, ET pcx,
                                          ET pcy, ET pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE_expansion(const GenericPoint3T<IT, ET> &pa,
                                              double pbx, double pby,
                                              double pbz, double pcx,
                                              double pcy, double pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE(const GenericPoint3T<IT, ET> &pa,
                                    double pbx, double pby, double pbz,
                                    double pcx, double pcy, double pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    const GenericPoint3T<IT, ET> &pc);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI_interval(const GenericPoint3T<IT, ET> &pa,
                                             const GenericPoint3T<IT, ET> &pc,
                                             IT pbx, IT pby, IT pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI_exact(const GenericPoint3T<IT, ET> &pa,
                                          const GenericPoint3T<IT, ET> &pc,
                                          ET pbx, ET pby, ET pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI_expansion(const GenericPoint3T<IT, ET> &pa,
                                              const GenericPoint3T<IT, ET> &pc,
                                              double pbx, double pby,
                                              double pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pc,
                                    double pbx, double pby, double pbz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pc,
                                    const GenericPoint3T<IT, ET> &pb);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE_exact(const GenericPoint3T<IT, ET> &pa,
                                          const GenericPoint3T<IT, ET> &pb,
                                          ET pcx, ET pcy, ET pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE_expansion(const GenericPoint3T<IT, ET> &pa,
                                              const GenericPoint3T<IT, ET> &pb,
                                              double pcx, double pcy,
                                              double pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    double pcx, double pcy, double pcz);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    const GenericPoint3T<IT, ET> &pc);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III_interval(const GenericPoint3T<IT, ET> &pa,
                                             const GenericPoint3T<IT, ET> &pb,
                                             const GenericPoint3T<IT, ET> &pc);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III_exact(const GenericPoint3T<IT, ET> &pa,
                                          const GenericPoint3T<IT, ET> &pb,
                                          const GenericPoint3T<IT, ET> &pc);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III_expansion(const GenericPoint3T<IT, ET> &pa,
                                              const GenericPoint3T<IT, ET> &pb,
                                              const GenericPoint3T<IT, ET> &pc);

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    const GenericPoint3T<IT, ET> &pc);

/*===================================================================*/

template <typename IT>
Sign largerTriangleCircumSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby,
                                         IT pbz, IT pcx, IT pcy, IT pcz, IT pdx,
                                         IT pdy, IT pdz);

template <typename ET>
Sign largerTriangleCircumSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby,
                                      ET pbz, ET pcx, ET pcy, ET pcz, ET pdx,
                                      ET pdy, ET pdz);

inline Sign largerTriangleCircumSphere_expansion(
  double pax, double pay, double paz, double pbx, double pby, double pbz,
  double pcx, double pcy, double pcz, double pdx, double pdy, double pdz);

template <typename IT, typename ET>
Sign largerTriangleCircumSphere(double pax, double pay, double paz, double pbx,
                                double pby, double pbz, double pcx, double pcy,
                                double pcz, double pdx, double pdy, double pdz);

template <typename IT, typename ET>
Sign largerTriangleCircumSphere(const GenericPoint3T<IT, ET> &pa,
                                const GenericPoint3T<IT, ET> &pb,
                                const GenericPoint3T<IT, ET> &pc,
                                const GenericPoint3T<IT, ET> &pd);

/*********************************************************************/
/* Implementations (hand)*********************************************/
/*********************************************************************/

inline Sign inSphere(const double *a, const double *b, const double *c,
                     const double *d, const double *e)
{
#ifdef OMC_NO_SHEWCHUK
	return inSphere(a[0], a[1], a[2], b[0], b[1], b[2], c[0], c[1], c[2], d[0],
	                d[1], d[2], e[0], e[1], e[2]);
#else
	return OMC::sign(::insphere(a, b, c, d, e));
#endif
}

template <typename IT, typename ET>
Sign inSphere(const GenericPoint3T<IT, ET> &pa,
              const GenericPoint3T<IT, ET> &pb,
              const GenericPoint3T<IT, ET> &pc,
              const GenericPoint3T<IT, ET> &pd,
              const GenericPoint3T<IT, ET> &pe)
{
#ifdef OMC_NO_SHEWCHUK
	return inSphere<IT, ET>(pa.x(), pa.y(), pa.z(), pb.x(), pb.y(), pb.z(),
	                        pc.x(), pc.y(), pc.z(), pd.x(), pd.y(), pd.z(),
	                        pe.x(), pe.y(), pe.z());
#else
	return OMC::sign(
	  ::insphere(pd.data(), pb.data(), pc.data(), pa.data(), pe.data()));
#endif
}

/*********************************************************************/
/* Implementations (mostly auto-generated)****************************/
/*********************************************************************/

inline Sign inSphere_filtered(double pax, double pay, double paz, double pbx,
                              double pby, double pbz, double pcx, double pcy,
                              double pcz, double pdx, double pdy, double pdz,
                              double pex, double pey, double pez)
{
	double aex    = pax - pex;
	double aey    = pay - pey;
	double aez    = paz - pez;
	double bex    = pbx - pex;
	double bey    = pby - pey;
	double bez    = pbz - pez;
	double cex    = pcx - pex;
	double cey    = pcy - pey;
	double cez    = pcz - pez;
	double dex    = pdx - pex;
	double dey    = pdy - pey;
	double dez    = pdz - pez;
	double aexbey = aex * bey;
	double bexaey = bex * aey;
	double ab     = aexbey - bexaey;
	double bexcey = bex * cey;
	double cexbey = cex * bey;
	double bc     = bexcey - cexbey;
	double cexdey = cex * dey;
	double dexcey = dex * cey;
	double cd     = cexdey - dexcey;
	double dexaey = dex * aey;
	double aexdey = aex * dey;
	double da     = dexaey - aexdey;
	double aexcey = aex * cey;
	double cexaey = cex * aey;
	double ac     = aexcey - cexaey;
	double bexdey = bex * dey;
	double dexbey = dex * bey;
	double bd     = bexdey - dexbey;
	double abc1   = aez * bc;
	double abc2   = bez * ac;
	double abc3   = cez * ab;
	double abc4   = abc1 + abc3;
	double abc    = abc4 - abc2;
	double bcd1   = bez * cd;
	double bcd2   = cez * bd;
	double bcd3   = dez * bc;
	double bcd4   = bcd1 + bcd3;
	double bcd    = bcd4 - bcd2;
	double cda1   = cez * da;
	double cda2   = dez * ac;
	double cda3   = aez * cd;
	double cda4   = cda1 + cda3;
	double cda    = cda4 + cda2;
	double dab1   = dez * ab;
	double dab2   = aez * bd;
	double dab3   = bez * da;
	double dab4   = dab1 + dab3;
	double dab    = dab4 + dab2;
	double al1    = aex * aex;
	double al2    = aey * aey;
	double al3    = aez * aez;
	double al4    = al1 + al2;
	double alift  = al4 + al3;
	double bl1    = bex * bex;
	double bl2    = bey * bey;
	double bl3    = bez * bez;
	double bl4    = bl1 + bl2;
	double blift  = bl4 + bl3;
	double cl1    = cex * cex;
	double cl2    = cey * cey;
	double cl3    = cez * cez;
	double cl4    = cl1 + cl2;
	double clift  = cl4 + cl3;
	double dl1    = dex * dex;
	double dl2    = dey * dey;
	double dl3    = dez * dez;
	double dl4    = dl1 + dl2;
	double dlift  = dl4 + dl3;
	double ds1    = dlift * abc;
	double ds2    = clift * dab;
	double dl     = ds2 - ds1;
	double dr1    = blift * cda;
	double dr2    = alift * bcd;
	double dr     = dr2 - dr1;
	double det    = dl + dr;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(aex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(aey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(aez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(dex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(dey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(dez)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= epsilon;
	epsilon *= max_var;
	epsilon *= 1.1457501614131623e-13;

	return filter_sign(det, epsilon);
}

template <typename IT>
Sign inSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby, IT pbz, IT pcx,
                       IT pcy, IT pcz, IT pdx, IT pdy, IT pdz, IT pex, IT pey,
                       IT pez)
{
	typename IT::Protector P;

	IT aex    = pax - pex;
	IT aey    = pay - pey;
	IT aez    = paz - pez;
	IT bex    = pbx - pex;
	IT bey    = pby - pey;
	IT bez    = pbz - pez;
	IT cex    = pcx - pex;
	IT cey    = pcy - pey;
	IT cez    = pcz - pez;
	IT dex    = pdx - pex;
	IT dey    = pdy - pey;
	IT dez    = pdz - pez;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT ds1    = dlift * abc;
	IT ds2    = clift * dab;
	IT dl     = ds2 - ds1;
	IT dr1    = blift * cda;
	IT dr2    = alift * bcd;
	IT dr     = dr2 - dr1;
	IT det    = dl + dr;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename ET>
Sign inSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby, ET pbz, ET pcx,
                    ET pcy, ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                    ET pez)
{
	ET aex    = pax - pex;
	ET aey    = pay - pey;
	ET aez    = paz - pez;
	ET bex    = pbx - pex;
	ET bey    = pby - pey;
	ET bez    = pbz - pez;
	ET cex    = pcx - pex;
	ET cey    = pcy - pey;
	ET cez    = pcz - pez;
	ET dex    = pdx - pex;
	ET dey    = pdy - pey;
	ET dez    = pdz - pez;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET ds1    = dlift * abc;
	ET ds2    = clift * dab;
	ET dl     = ds2 - ds1;
	ET dr1    = blift * cda;
	ET dr2    = alift * bcd;
	ET dr     = dr2 - dr1;
	ET det    = dl + dr;
	return OMC::sign(det);
}

Sign inSphere_expansion(double pax, double pay, double paz, double pbx,
                        double pby, double pbz, double pcx, double pcy,
                        double pcz, double pdx, double pdy, double pdz,
                        double pex, double pey, double pez)
{
	expansionObject o;
	double          aex[2];
	o.Two_Diff(pax, pex, aex);
	double aey[2];
	o.Two_Diff(pay, pey, aey);
	double aez[2];
	o.Two_Diff(paz, pez, aez);
	double bex[2];
	o.Two_Diff(pbx, pex, bex);
	double bey[2];
	o.Two_Diff(pby, pey, bey);
	double bez[2];
	o.Two_Diff(pbz, pez, bez);
	double cex[2];
	o.Two_Diff(pcx, pex, cex);
	double cey[2];
	o.Two_Diff(pcy, pey, cey);
	double cez[2];
	o.Two_Diff(pcz, pez, cez);
	double dex[2];
	o.Two_Diff(pdx, pex, dex);
	double dey[2];
	o.Two_Diff(pdy, pey, dey);
	double dez[2];
	o.Two_Diff(pdz, pez, dez);
	double aexbey[8];
	int    aexbey_len = o.Gen_Product(2, aex, 2, bey, aexbey);
	double bexaey[8];
	int    bexaey_len = o.Gen_Product(2, bex, 2, aey, bexaey);
	double ab[16];
	int    ab_len = o.Gen_Diff(aexbey_len, aexbey, bexaey_len, bexaey, ab);
	double bexcey[8];
	int    bexcey_len = o.Gen_Product(2, bex, 2, cey, bexcey);
	double cexbey[8];
	int    cexbey_len = o.Gen_Product(2, cex, 2, bey, cexbey);
	double bc[16];
	int    bc_len = o.Gen_Diff(bexcey_len, bexcey, cexbey_len, cexbey, bc);
	double cexdey[8];
	int    cexdey_len = o.Gen_Product(2, cex, 2, dey, cexdey);
	double dexcey[8];
	int    dexcey_len = o.Gen_Product(2, dex, 2, cey, dexcey);
	double cd[16];
	int    cd_len = o.Gen_Diff(cexdey_len, cexdey, dexcey_len, dexcey, cd);
	double dexaey[8];
	int    dexaey_len = o.Gen_Product(2, dex, 2, aey, dexaey);
	double aexdey[8];
	int    aexdey_len = o.Gen_Product(2, aex, 2, dey, aexdey);
	double da[16];
	int    da_len = o.Gen_Diff(dexaey_len, dexaey, aexdey_len, aexdey, da);
	double aexcey[8];
	int    aexcey_len = o.Gen_Product(2, aex, 2, cey, aexcey);
	double cexaey[8];
	int    cexaey_len = o.Gen_Product(2, cex, 2, aey, cexaey);
	double ac[16];
	int    ac_len = o.Gen_Diff(aexcey_len, aexcey, cexaey_len, cexaey, ac);
	double bexdey[8];
	int    bexdey_len = o.Gen_Product(2, bex, 2, dey, bexdey);
	double dexbey[8];
	int    dexbey_len = o.Gen_Product(2, dex, 2, bey, dexbey);
	double bd[16];
	int    bd_len = o.Gen_Diff(bexdey_len, bexdey, dexbey_len, dexbey, bd);
	double abc1_p[32], *abc1 = abc1_p;
	int    abc1_len = o.Gen_Product_With_PreAlloc(2, aez, bc_len, bc, &abc1, 32);
	double abc2_p[32], *abc2 = abc2_p;
	int    abc2_len = o.Gen_Product_With_PreAlloc(2, bez, ac_len, ac, &abc2, 32);
	double abc3_p[32], *abc3 = abc3_p;
	int    abc3_len = o.Gen_Product_With_PreAlloc(2, cez, ab_len, ab, &abc3, 32);
	double abc4_p[32], *abc4 = abc4_p;
	int    abc4_len =
	  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 32);
	double abc_p[32], *abc = abc_p;
	int    abc_len =
	  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 32);
	double bcd1_p[32], *bcd1 = bcd1_p;
	int    bcd1_len = o.Gen_Product_With_PreAlloc(2, bez, cd_len, cd, &bcd1, 32);
	double bcd2_p[32], *bcd2 = bcd2_p;
	int    bcd2_len = o.Gen_Product_With_PreAlloc(2, cez, bd_len, bd, &bcd2, 32);
	double bcd3_p[32], *bcd3 = bcd3_p;
	int    bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 32);
	double bcd4_p[32], *bcd4 = bcd4_p;
	int    bcd4_len =
	  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 32);
	double bcd_p[32], *bcd = bcd_p;
	int    bcd_len =
	  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 32);
	double cda1_p[32], *cda1 = cda1_p;
	int    cda1_len = o.Gen_Product_With_PreAlloc(2, cez, da_len, da, &cda1, 32);
	double cda2_p[32], *cda2 = cda2_p;
	int    cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 32);
	double cda3_p[32], *cda3 = cda3_p;
	int    cda3_len = o.Gen_Product_With_PreAlloc(2, aez, cd_len, cd, &cda3, 32);
	double cda4_p[32], *cda4 = cda4_p;
	int    cda4_len =
	  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 32);
	double cda_p[32], *cda = cda_p;
	int    cda_len =
	  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 32);
	double dab1_p[32], *dab1 = dab1_p;
	int    dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 32);
	double dab2_p[32], *dab2 = dab2_p;
	int    dab2_len = o.Gen_Product_With_PreAlloc(2, aez, bd_len, bd, &dab2, 32);
	double dab3_p[32], *dab3 = dab3_p;
	int    dab3_len = o.Gen_Product_With_PreAlloc(2, bez, da_len, da, &dab3, 32);
	double dab4_p[32], *dab4 = dab4_p;
	int    dab4_len =
	  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 32);
	double dab_p[32], *dab = dab_p;
	int    dab_len =
	  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 32);
	double al1[8];
	int    al1_len = o.Gen_Product(2, aex, 2, aex, al1);
	double al2[8];
	int    al2_len = o.Gen_Product(2, aey, 2, aey, al2);
	double al3[8];
	int    al3_len = o.Gen_Product(2, aez, 2, aez, al3);
	double al4[16];
	int    al4_len = o.Gen_Sum(al1_len, al1, al2_len, al2, al4);
	double alift[24];
	int    alift_len = o.Gen_Sum(al4_len, al4, al3_len, al3, alift);
	double bl1[8];
	int    bl1_len = o.Gen_Product(2, bex, 2, bex, bl1);
	double bl2[8];
	int    bl2_len = o.Gen_Product(2, bey, 2, bey, bl2);
	double bl3[8];
	int    bl3_len = o.Gen_Product(2, bez, 2, bez, bl3);
	double bl4[16];
	int    bl4_len = o.Gen_Sum(bl1_len, bl1, bl2_len, bl2, bl4);
	double blift[24];
	int    blift_len = o.Gen_Sum(bl4_len, bl4, bl3_len, bl3, blift);
	double cl1[8];
	int    cl1_len = o.Gen_Product(2, cex, 2, cex, cl1);
	double cl2[8];
	int    cl2_len = o.Gen_Product(2, cey, 2, cey, cl2);
	double cl3[8];
	int    cl3_len = o.Gen_Product(2, cez, 2, cez, cl3);
	double cl4[16];
	int    cl4_len = o.Gen_Sum(cl1_len, cl1, cl2_len, cl2, cl4);
	double clift[24];
	int    clift_len = o.Gen_Sum(cl4_len, cl4, cl3_len, cl3, clift);
	double dl1[8];
	int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
	double dl2[8];
	int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
	double dl3[8];
	int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
	double dl4[16];
	int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
	double dlift[24];
	int    dlift_len = o.Gen_Sum(dl4_len, dl4, dl3_len, dl3, dlift);
	double ds1_p[32], *ds1 = ds1_p;
	int    ds1_len =
	  o.Gen_Product_With_PreAlloc(dlift_len, dlift, abc_len, abc, &ds1, 32);
	double ds2_p[32], *ds2 = ds2_p;
	int    ds2_len =
	  o.Gen_Product_With_PreAlloc(clift_len, clift, dab_len, dab, &ds2, 32);
	double dl_p[32], *dl = dl_p;
	int    dl_len = o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1_len, ds1, &dl, 32);
	double dr1_p[32], *dr1 = dr1_p;
	int    dr1_len =
	  o.Gen_Product_With_PreAlloc(blift_len, blift, cda_len, cda, &dr1, 32);
	double dr2_p[32], *dr2 = dr2_p;
	int    dr2_len =
	  o.Gen_Product_With_PreAlloc(alift_len, alift, bcd_len, bcd, &dr2, 32);
	double dr_p[32], *dr = dr_p;
	int    dr_len = o.Gen_Diff_With_PreAlloc(dr2_len, dr2, dr1_len, dr1, &dr, 32);
	double det_p[32], *det = det_p;
	int    det_len = o.Gen_Sum_With_PreAlloc(dl_len, dl, dr_len, dr, &det, 32);

	double return_value = det[det_len - 1];
	if (det_p != det)
		FreeDoubles(det);
	if (dr_p != dr)
		FreeDoubles(dr);
	if (dr2_p != dr2)
		FreeDoubles(dr2);
	if (dr1_p != dr1)
		FreeDoubles(dr1);
	if (dl_p != dl)
		FreeDoubles(dl);
	if (ds2_p != ds2)
		FreeDoubles(ds2);
	if (ds1_p != ds1)
		FreeDoubles(ds1);
	if (dab_p != dab)
		FreeDoubles(dab);
	if (dab4_p != dab4)
		FreeDoubles(dab4);
	if (dab3_p != dab3)
		FreeDoubles(dab3);
	if (dab2_p != dab2)
		FreeDoubles(dab2);
	if (dab1_p != dab1)
		FreeDoubles(dab1);
	if (cda_p != cda)
		FreeDoubles(cda);
	if (cda4_p != cda4)
		FreeDoubles(cda4);
	if (cda3_p != cda3)
		FreeDoubles(cda3);
	if (cda2_p != cda2)
		FreeDoubles(cda2);
	if (cda1_p != cda1)
		FreeDoubles(cda1);
	if (bcd_p != bcd)
		FreeDoubles(bcd);
	if (bcd4_p != bcd4)
		FreeDoubles(bcd4);
	if (bcd3_p != bcd3)
		FreeDoubles(bcd3);
	if (bcd2_p != bcd2)
		FreeDoubles(bcd2);
	if (bcd1_p != bcd1)
		FreeDoubles(bcd1);
	if (abc_p != abc)
		FreeDoubles(abc);
	if (abc4_p != abc4)
		FreeDoubles(abc4);
	if (abc3_p != abc3)
		FreeDoubles(abc3);
	if (abc2_p != abc2)
		FreeDoubles(abc2);
	if (abc1_p != abc1)
		FreeDoubles(abc1);

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSphere(double pax, double pay, double paz, double pbx, double pby,
              double pbz, double pcx, double pcy, double pcz, double pdx,
              double pdy, double pdz, double pex, double pey, double pez)
{
	Sign ret;
	ret = inSphere_filtered(pax, pay, paz, pbx, pby, pbz, pcx, pcy, pcz, pdx, pdy,
	                        pdz, pex, pey, pez);
	if (is_sign_reliable(ret))
		return ret;
	ret = inSphere_interval<IT>(pax, pay, paz, pbx, pby, pbz, pcx, pcy, pcz, pdx,
	                            pdy, pdz, pex, pey, pez);
	if (is_sign_reliable(ret))
		return ret;
	return inSphere_expansion(pax, pay, paz, pbx, pby, pbz, pcx, pcy, pcz, pdx,
	                          pdy, pdz, pex, pey, pez);
}

template <typename IT, typename ET>
Sign inSphere_IEEEE_interval(const GenericPoint3T<IT, ET> &p1, IT pbx, IT pby,
                             IT pbz, IT pcx, IT pcy, IT pcz, IT pdx, IT pdy,
                             IT pdz, IT pex, IT pey, IT pez)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd   = pex * d1;
	IT peyd   = pey * d1;
	IT pezd   = pez * d1;
	IT aex    = l1x - pexd;
	IT aey    = l1y - peyd;
	IT aez    = l1z - pezd;
	IT bex    = pbx - pex;
	IT bey    = pby - pey;
	IT bez    = pbz - pez;
	IT cex    = pcx - pex;
	IT cey    = pcy - pey;
	IT cez    = pcz - pez;
	IT dex    = pdx - pex;
	IT dey    = pdy - pey;
	IT dez    = pdz - pez;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT ds1    = dlift * abc;
	IT ds2    = clift * dab;
	IT dlp    = ds2 - ds1;
	IT dl     = dlp * d1;
	IT dr1p   = blift * cda;
	IT dr1    = dr1p * d1;
	IT dr2    = alift * bcd;
	IT dr     = dr2 - dr1;
	IT det    = dl + dr;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IEEEE_exact(const GenericPoint3T<IT, ET> &p1, ET pbx, ET pby,
                          ET pbz, ET pcx, ET pcy, ET pcz, ET pdx, ET pdy,
                          ET pdz, ET pex, ET pey, ET pez)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET pexd   = pex * d1;
	ET peyd   = pey * d1;
	ET pezd   = pez * d1;
	ET aex    = l1x - pexd;
	ET aey    = l1y - peyd;
	ET aez    = l1z - pezd;
	ET bex    = pbx - pex;
	ET bey    = pby - pey;
	ET bez    = pbz - pez;
	ET cex    = pcx - pex;
	ET cey    = pcy - pey;
	ET cez    = pcz - pez;
	ET dex    = pdx - pex;
	ET dey    = pdy - pey;
	ET dez    = pdz - pez;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET ds1    = dlift * abc;
	ET ds2    = clift * dab;
	ET dlp    = ds2 - ds1;
	ET dl     = dlp * d1;
	ET dr1p   = blift * cda;
	ET dr1    = dr1p * d1;
	ET dr2    = alift * bcd;
	ET dr     = dr2 - dr1;
	ET det    = dl + dr;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IEEEE_expansion(const GenericPoint3T<IT, ET> &p1, double pbx,
                              double pby, double pbz, double pcx, double pcy,
                              double pcz, double pdx, double pdy, double pdz,
                              double pex, double pey, double pez)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16], *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16],
	                  *l1z = l1z_p, d1_p[16], *d1 = d1_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double bex[2];
		o.Two_Diff(pbx, pex, bex);
		double bey[2];
		o.Two_Diff(pby, pey, bey);
		double bez[2];
		o.Two_Diff(pbz, pez, bez);
		double cex[2];
		o.Two_Diff(pcx, pex, cex);
		double cey[2];
		o.Two_Diff(pcy, pey, cey);
		double cez[2];
		o.Two_Diff(pcz, pez, cez);
		double dex[2];
		o.Two_Diff(pdx, pex, dex);
		double dey[2];
		o.Two_Diff(pdy, pey, dey);
		double dez[2];
		o.Two_Diff(pdz, pez, dez);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(2, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey[8];
		int    bexcey_len = o.Gen_Product(2, bex, 2, cey, bexcey);
		double cexbey[8];
		int    cexbey_len = o.Gen_Product(2, cex, 2, bey, cexbey);
		double bc[16];
		int    bc_len = o.Gen_Diff(bexcey_len, bexcey, cexbey_len, cexbey, bc);
		double cexdey[8];
		int    cexdey_len = o.Gen_Product(2, cex, 2, dey, cexdey);
		double dexcey[8];
		int    dexcey_len = o.Gen_Product(2, dex, 2, cey, dexcey);
		double cd[16];
		int    cd_len = o.Gen_Diff(cexdey_len, cexdey, dexcey_len, dexcey, cd);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(2, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey[8];
		int    bexdey_len = o.Gen_Product(2, bex, 2, dey, bexdey);
		double dexbey[8];
		int    dexbey_len = o.Gen_Product(2, dex, 2, bey, dexbey);
		double bd[16];
		int    bd_len = o.Gen_Diff(bexdey_len, bexdey, dexbey_len, dexbey, bd);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int abc2_len = o.Gen_Product_With_PreAlloc(2, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int abc3_len = o.Gen_Product_With_PreAlloc(2, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int bcd1_len = o.Gen_Product_With_PreAlloc(2, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int bcd2_len = o.Gen_Product_With_PreAlloc(2, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int cda1_len = o.Gen_Product_With_PreAlloc(2, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int dab3_len = o.Gen_Product_With_PreAlloc(2, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double bl1[8];
		int    bl1_len = o.Gen_Product(2, bex, 2, bex, bl1);
		double bl2[8];
		int    bl2_len = o.Gen_Product(2, bey, 2, bey, bl2);
		double bl3[8];
		int    bl3_len = o.Gen_Product(2, bez, 2, bez, bl3);
		double bl4[16];
		int    bl4_len = o.Gen_Sum(bl1_len, bl1, bl2_len, bl2, bl4);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double cl1[8];
		int    cl1_len = o.Gen_Product(2, cex, 2, cex, cl1);
		double cl2[8];
		int    cl2_len = o.Gen_Product(2, cey, 2, cey, cl2);
		double cl3[8];
		int    cl3_len = o.Gen_Product(2, cez, 2, cez, cl3);
		double cl4[16];
		int    cl4_len = o.Gen_Sum(cl1_len, cl1, cl2_len, cl2, cl4);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double dl1[8];
		int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
		double dl2[8];
		int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
		double dl3[8];
		int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
		double dl4[16];
		int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(dlift_len, dlift, abc_len, abc, &ds1, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, dab_len, dab, &ds2, 16);
		double dlp_p[16], *dlp = dlp_p;
		int    dlp_len =
		  o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1_len, ds1, &dlp, 16);
		double dl_p[16], *dl = dl_p;
		int dl_len = o.Gen_Product_With_PreAlloc(dlp_len, dlp, d1_len, d1, &dl, 16);
		double dr1p_p[16], *dr1p = dr1p_p;
		int    dr1p_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cda_len, cda, &dr1p, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(dr1p_len, dr1p, d1_len, d1, &dr1, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcd_len, bcd, &dr2, 16);
		double dr_p[16], *dr = dr_p;
		int dr_len = o.Gen_Diff_With_PreAlloc(dr2_len, dr2, dr1_len, dr1, &dr, 16);
		double det_p[16], *det = det_p;
		int    det_len = o.Gen_Sum_With_PreAlloc(dl_len, dl, dr_len, dr, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dr1p_p != dr1p)
			FreeDoubles(dr1p);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (dlp_p != dlp)
			FreeDoubles(dlp);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSphere_IEEEE_exact<IT, ET>(p1, pbx, pby, pbz, pcx, pcy, pcz, pdx,
		                                    pdy, pdz, pex, pey, pez);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSphere_IEEEE(const GenericPoint3T<IT, ET> &p1, double pbx, double pby,
                    double pbz, double pcx, double pcy, double pcz, double pdx,
                    double pdy, double pdz, double pex, double pey, double pez)
{
	Sign ret;
	ret = inSphere_IEEEE_interval<IT, ET>(p1, pbx, pby, pbz, pcx, pcy, pcz, pdx,
	                                      pdy, pdz, pex, pey, pez);
	if (is_sign_reliable(ret))
		return ret;
	return inSphere_IEEEE_expansion<IT, ET>(p1, pbx, pby, pbz, pcx, pcy, pcz, pdx,
	                                        pdy, pdz, pex, pey, pez);
}

template <typename IT, typename ET>
Sign inSphere_IEEEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &pb,
                    const GenericPoint3T<IT, ET> &pc,
                    const GenericPoint3T<IT, ET> &pd,
                    const GenericPoint3T<IT, ET> &pe)
{
	return inSphere_IEEEE<IT, ET>(p1, pb.x(), pb.y(), pb.z(), pc.x(), pc.y(),
	                              pc.z(), pd.x(), pd.y(), pd.z(), pe.x(), pe.y(),
	                              pe.z());
}

template <typename IT, typename ET>
Sign inSphere_IIEEE_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2, IT pcx, IT pcy,
                             IT pcz, IT pdx, IT pdy, IT pdz, IT pex, IT pey,
                             IT pez)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd   = pex * d1;
	IT peyd   = pey * d1;
	IT pezd   = pez * d1;
	IT aex    = l1x - pexd;
	IT aey    = l1y - peyd;
	IT aez    = l1z - pezd;
	IT pexd2  = pex * d2;
	IT peyd2  = pey * d2;
	IT pezd2  = pez * d2;
	IT bex    = l2x - pexd2;
	IT bey    = l2y - peyd2;
	IT bez    = l2z - pezd2;
	IT cex    = pcx - pex;
	IT cey    = pcy - pey;
	IT cez    = pcz - pez;
	IT dex    = pdx - pex;
	IT dey    = pdy - pey;
	IT dez    = pdz - pez;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT ds1    = dlift * abc;
	IT ds2    = clift * dab;
	IT dl     = ds2 - ds1;
	IT dll    = dl * d1;
	IT dlll   = dll * d2;
	IT dr1    = blift * cda;
	IT dr12   = dr1 * d1;
	IT dr2    = alift * bcd;
	IT dr22   = dr2 * d2;
	IT dr     = dr22 - dr12;
	IT det    = dlll + dr;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIEEE_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2, ET pcx, ET pcy,
                          ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                          ET pez)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET pexd   = pex * d1;
	ET peyd   = pey * d1;
	ET pezd   = pez * d1;
	ET aex    = l1x - pexd;
	ET aey    = l1y - peyd;
	ET aez    = l1z - pezd;
	ET pexd2  = pex * d2;
	ET peyd2  = pey * d2;
	ET pezd2  = pez * d2;
	ET bex    = l2x - pexd2;
	ET bey    = l2y - peyd2;
	ET bez    = l2z - pezd2;
	ET cex    = pcx - pex;
	ET cey    = pcy - pey;
	ET cez    = pcz - pez;
	ET dex    = pdx - pex;
	ET dey    = pdy - pey;
	ET dez    = pdz - pez;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET ds1    = dlift * abc;
	ET ds2    = clift * dab;
	ET dl     = ds2 - ds1;
	ET dll    = dl * d1;
	ET dlll   = dll * d2;
	ET dr1    = blift * cda;
	ET dr12   = dr1 * d1;
	ET dr2    = alift * bcd;
	ET dr22   = dr2 * d2;
	ET dr     = dr22 - dr12;
	ET det    = dlll + dr;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIEEE_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2, double pcx,
                              double pcy, double pcz, double pdx, double pdy,
                              double pdz, double pex, double pey, double pez)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16], *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16],
	                  *l1z = l1z_p, d1_p[16], *d1 = d1_p, l2x_p[16], *l2x = l2x_p,
	                  l2y_p[16], *l2y = l2y_p, l2z_p[16], *l2z = l2z_p, d2_p[16],
	                  *d2 = d2_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16, l2x_len = 16,
	    l2y_len = 16, l2z_len = 16, d2_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double pexd2_p[16], *pexd2 = pexd2_p;
		int    pexd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pex, &pexd2, 16);
		double peyd2_p[16], *peyd2 = peyd2_p;
		int    peyd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pey, &peyd2, 16);
		double pezd2_p[16], *pezd2 = pezd2_p;
		int    pezd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pez, &pezd2, 16);
		double bex_p[16], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pexd2_len, pexd2, &bex, 16);
		double bey_p[16], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, peyd2_len, peyd2, &bey, 16);
		double bez_p[16], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, pezd2_len, pezd2, &bez, 16);
		double cex[2];
		o.Two_Diff(pcx, pex, cex);
		double cey[2];
		o.Two_Diff(pcy, pey, cey);
		double cez[2];
		o.Two_Diff(pcz, pez, cez);
		double dex[2];
		o.Two_Diff(pdx, pex, dex);
		double dey[2];
		o.Two_Diff(pdy, pey, dey);
		double dez[2];
		o.Two_Diff(pdz, pez, dez);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey_p[16], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, 2, cey, &bexcey, 16);
		double cexbey_p[16], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(2, cex, bey_len, bey, &cexbey, 16);
		double bc_p[16], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 16);
		double cexdey[8];
		int    cexdey_len = o.Gen_Product(2, cex, 2, dey, cexdey);
		double dexcey[8];
		int    dexcey_len = o.Gen_Product(2, dex, 2, cey, dexcey);
		double cd[16];
		int    cd_len = o.Gen_Diff(cexdey_len, cexdey, dexcey_len, dexcey, cd);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(2, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey_p[16], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, 2, dey, &bexdey, 16);
		double dexbey_p[16], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, bey_len, bey, &dexbey, 16);
		double bd_p[16], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 16);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int abc3_len = o.Gen_Product_With_PreAlloc(2, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int bcd2_len = o.Gen_Product_With_PreAlloc(2, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int cda1_len = o.Gen_Product_With_PreAlloc(2, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double bl1_p[16], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 16);
		double bl2_p[16], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 16);
		double bl3_p[16], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 16);
		double bl4_p[16], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 16);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double cl1[8];
		int    cl1_len = o.Gen_Product(2, cex, 2, cex, cl1);
		double cl2[8];
		int    cl2_len = o.Gen_Product(2, cey, 2, cey, cl2);
		double cl3[8];
		int    cl3_len = o.Gen_Product(2, cez, 2, cez, cl3);
		double cl4[16];
		int    cl4_len = o.Gen_Sum(cl1_len, cl1, cl2_len, cl2, cl4);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double dl1[8];
		int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
		double dl2[8];
		int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
		double dl3[8];
		int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
		double dl4[16];
		int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(dlift_len, dlift, abc_len, abc, &ds1, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, dab_len, dab, &ds2, 16);
		double dl_p[16], *dl = dl_p;
		int dl_len = o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1_len, ds1, &dl, 16);
		double dll_p[16], *dll = dll_p;
		int dll_len = o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dll, 16);
		double dlll_p[16], *dlll = dlll_p;
		int    dlll_len =
		  o.Gen_Product_With_PreAlloc(dll_len, dll, d2_len, d2, &dlll, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cda_len, cda, &dr1, 16);
		double dr12_p[16], *dr12 = dr12_p;
		int    dr12_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr12, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcd_len, bcd, &dr2, 16);
		double dr22_p[16], *dr22 = dr22_p;
		int    dr22_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr22, 16);
		double dr_p[16], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr22_len, dr22, dr12_len, dr12, &dr, 16);
		double det_p[16], *det = det_p;
		int det_len = o.Gen_Sum_With_PreAlloc(dlll_len, dlll, dr_len, dr, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr22_p != dr22)
			FreeDoubles(dr22);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr12_p != dr12)
			FreeDoubles(dr12);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dlll_p != dlll)
			FreeDoubles(dlll);
		if (dll_p != dll)
			FreeDoubles(dll);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSphere_IIEEE_exact<IT, ET>(p1, p2, pcx, pcy, pcz, pdx, pdy, pdz,
		                                    pex, pey, pez);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2, double pcx, double pcy,
                    double pcz, double pdx, double pdy, double pdz, double pex,
                    double pey, double pez)
{
	Sign ret;
	ret = inSphere_IIEEE_interval<IT, ET>(p1, p2, pcx, pcy, pcz, pdx, pdy, pdz,
	                                      pex, pey, pez);
	if (is_sign_reliable(ret))
		return ret;
	return inSphere_IIEEE_expansion<IT, ET>(p1, p2, pcx, pcy, pcz, pdx, pdy, pdz,
	                                        pex, pey, pez);
}

template <typename IT, typename ET>
Sign inSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &pc,
                    const GenericPoint3T<IT, ET> &pd,
                    const GenericPoint3T<IT, ET> &pe)
{
	return inSphere_IIEEE<IT, ET>(p1, p2, pc.x(), pc.y(), pc.z(), pd.x(), pd.y(),
	                              pd.z(), pe.x(), pe.y(), pe.z());
}

template <typename IT, typename ET>
Sign inSphere_IIIEE_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3, IT pdx, IT pdy,
                             IT pdz, IT pex, IT pey, IT pez)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd   = pex * d1;
	IT peyd   = pey * d1;
	IT pezd   = pez * d1;
	IT aex    = l1x - pexd;
	IT aey    = l1y - peyd;
	IT aez    = l1z - pezd;
	IT pexd2  = pex * d2;
	IT peyd2  = pey * d2;
	IT pezd2  = pez * d2;
	IT bex    = l2x - pexd2;
	IT bey    = l2y - peyd2;
	IT bez    = l2z - pezd2;
	IT pexd3  = pex * d3;
	IT peyd3  = pey * d3;
	IT pezd3  = pez * d3;
	IT cex    = l3x - pexd3;
	IT cey    = l3y - peyd3;
	IT cez    = l3z - pezd3;
	IT dex    = pdx - pex;
	IT dey    = pdy - pey;
	IT dez    = pdz - pez;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT ds1    = dlift * abc;
	IT ds1n   = ds1 * d3;
	IT ds2    = clift * dab;
	IT dl     = ds2 - ds1n;
	IT dlm    = dl * d1;
	IT dln    = dlm * d2;
	IT dr1    = blift * cda;
	IT dr1n   = dr1 * d1;
	IT dr2    = alift * bcd;
	IT dr2n   = dr2 * d2;
	IT dr     = dr2n - dr1n;
	IT drn    = dr * d3;
	IT det    = dln + drn;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIIEE_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2,
                          const GenericPoint3T<IT, ET> &p3, ET pdx, ET pdy,
                          ET pdz, ET pex, ET pey, ET pez)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET pexd   = pex * d1;
	ET peyd   = pey * d1;
	ET pezd   = pez * d1;
	ET aex    = l1x - pexd;
	ET aey    = l1y - peyd;
	ET aez    = l1z - pezd;
	ET pexd2  = pex * d2;
	ET peyd2  = pey * d2;
	ET pezd2  = pez * d2;
	ET bex    = l2x - pexd2;
	ET bey    = l2y - peyd2;
	ET bez    = l2z - pezd2;
	ET pexd3  = pex * d3;
	ET peyd3  = pey * d3;
	ET pezd3  = pez * d3;
	ET cex    = l3x - pexd3;
	ET cey    = l3y - peyd3;
	ET cez    = l3z - pezd3;
	ET dex    = pdx - pex;
	ET dey    = pdy - pey;
	ET dez    = pdz - pez;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET ds1    = dlift * abc;
	ET ds1n   = ds1 * d3;
	ET ds2    = clift * dab;
	ET dl     = ds2 - ds1n;
	ET dlm    = dl * d1;
	ET dln    = dlm * d2;
	ET dr1    = blift * cda;
	ET dr1n   = dr1 * d1;
	ET dr2    = alift * bcd;
	ET dr2n   = dr2 * d2;
	ET dr     = dr2n - dr1n;
	ET drn    = dr * d3;
	ET det    = dln + drn;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3, double pdx,
                              double pdy, double pdz, double pex, double pey,
                              double pez)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16], *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16],
	                  *l1z = l1z_p, d1_p[16], *d1 = d1_p, l2x_p[16], *l2x = l2x_p,
	                  l2y_p[16], *l2y = l2y_p, l2z_p[16], *l2z = l2z_p, d2_p[16],
	                  *d2 = d2_p, l3x_p[16], *l3x = l3x_p, l3y_p[16],
	                  *l3y = l3y_p, l3z_p[16], *l3z = l3z_p, d3_p[16], *d3 = d3_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16, l2x_len = 16,
	    l2y_len = 16, l2z_len = 16, d2_len = 16, l3x_len = 16, l3y_len = 16,
	    l3z_len = 16, d3_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double pexd2_p[16], *pexd2 = pexd2_p;
		int    pexd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pex, &pexd2, 16);
		double peyd2_p[16], *peyd2 = peyd2_p;
		int    peyd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pey, &peyd2, 16);
		double pezd2_p[16], *pezd2 = pezd2_p;
		int    pezd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pez, &pezd2, 16);
		double bex_p[16], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pexd2_len, pexd2, &bex, 16);
		double bey_p[16], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, peyd2_len, peyd2, &bey, 16);
		double bez_p[16], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, pezd2_len, pezd2, &bez, 16);
		double pexd3_p[16], *pexd3 = pexd3_p;
		int    pexd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pex, &pexd3, 16);
		double peyd3_p[16], *peyd3 = peyd3_p;
		int    peyd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pey, &peyd3, 16);
		double pezd3_p[16], *pezd3 = pezd3_p;
		int    pezd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pez, &pezd3, 16);
		double cex_p[16], *cex = cex_p;
		int    cex_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, pexd3_len, pexd3, &cex, 16);
		double cey_p[16], *cey = cey_p;
		int    cey_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, peyd3_len, peyd3, &cey, 16);
		double cez_p[16], *cez = cez_p;
		int    cez_len =
		  o.Gen_Diff_With_PreAlloc(l3z_len, l3z, pezd3_len, pezd3, &cez, 16);
		double dex[2];
		o.Two_Diff(pdx, pex, dex);
		double dey[2];
		o.Two_Diff(pdy, pey, dey);
		double dez[2];
		o.Two_Diff(pdz, pez, dez);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey_p[16], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, cey_len, cey, &bexcey, 16);
		double cexbey_p[16], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, bey_len, bey, &cexbey, 16);
		double bc_p[16], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 16);
		double cexdey_p[16], *cexdey = cexdey_p;
		int    cexdey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, 2, dey, &cexdey, 16);
		double dexcey_p[16], *dexcey = dexcey_p;
		int    dexcey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, cey_len, cey, &dexcey, 16);
		double cd_p[16], *cd = cd_p;
		int    cd_len =
		  o.Gen_Diff_With_PreAlloc(cexdey_len, cexdey, dexcey_len, dexcey, &cd, 16);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, cey_len, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey_p[16], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, 2, dey, &bexdey, 16);
		double dexbey_p[16], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, bey_len, bey, &dexbey, 16);
		double bd_p[16], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 16);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int    abc3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int    bcd2_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int    cda1_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double bl1_p[16], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 16);
		double bl2_p[16], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 16);
		double bl3_p[16], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 16);
		double bl4_p[16], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 16);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double cl1_p[16], *cl1 = cl1_p;
		int    cl1_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, cex_len, cex, &cl1, 16);
		double cl2_p[16], *cl2 = cl2_p;
		int    cl2_len =
		  o.Gen_Product_With_PreAlloc(cey_len, cey, cey_len, cey, &cl2, 16);
		double cl3_p[16], *cl3 = cl3_p;
		int    cl3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, cez_len, cez, &cl3, 16);
		double cl4_p[16], *cl4 = cl4_p;
		int cl4_len = o.Gen_Sum_With_PreAlloc(cl1_len, cl1, cl2_len, cl2, &cl4, 16);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double dl1[8];
		int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
		double dl2[8];
		int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
		double dl3[8];
		int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
		double dl4[16];
		int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(dlift_len, dlift, abc_len, abc, &ds1, 16);
		double ds1n_p[16], *ds1n = ds1n_p;
		int    ds1n_len =
		  o.Gen_Product_With_PreAlloc(ds1_len, ds1, d3_len, d3, &ds1n, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, dab_len, dab, &ds2, 16);
		double dl_p[16], *dl = dl_p;
		int    dl_len =
		  o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1n_len, ds1n, &dl, 16);
		double dlm_p[16], *dlm = dlm_p;
		int dlm_len = o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dlm, 16);
		double dln_p[16], *dln = dln_p;
		int    dln_len =
		  o.Gen_Product_With_PreAlloc(dlm_len, dlm, d2_len, d2, &dln, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cda_len, cda, &dr1, 16);
		double dr1n_p[16], *dr1n = dr1n_p;
		int    dr1n_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr1n, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcd_len, bcd, &dr2, 16);
		double dr2n_p[16], *dr2n = dr2n_p;
		int    dr2n_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr2n, 16);
		double dr_p[16], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr2n_len, dr2n, dr1n_len, dr1n, &dr, 16);
		double drn_p[16], *drn = drn_p;
		int drn_len = o.Gen_Product_With_PreAlloc(dr_len, dr, d3_len, d3, &drn, 16);
		double det_p[16], *det = det_p;
		int det_len = o.Gen_Sum_With_PreAlloc(dln_len, dln, drn_len, drn, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (drn_p != drn)
			FreeDoubles(drn);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr2n_p != dr2n)
			FreeDoubles(dr2n);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr1n_p != dr1n)
			FreeDoubles(dr1n);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dln_p != dln)
			FreeDoubles(dln);
		if (dlm_p != dlm)
			FreeDoubles(dlm);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1n_p != ds1n)
			FreeDoubles(ds1n);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cl4_p != cl4)
			FreeDoubles(cl4);
		if (cl3_p != cl3)
			FreeDoubles(cl3);
		if (cl2_p != cl2)
			FreeDoubles(cl2);
		if (cl1_p != cl1)
			FreeDoubles(cl1);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (dexcey_p != dexcey)
			FreeDoubles(dexcey);
		if (cexdey_p != cexdey)
			FreeDoubles(cexdey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (cez_p != cez)
			FreeDoubles(cez);
		if (cey_p != cey)
			FreeDoubles(cey);
		if (cex_p != cex)
			FreeDoubles(cex);
		if (pezd3_p != pezd3)
			FreeDoubles(pezd3);
		if (peyd3_p != peyd3)
			FreeDoubles(peyd3);
		if (pexd3_p != pexd3)
			FreeDoubles(pexd3);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSphere_IIIEE_exact<IT, ET>(p1, p2, p3, pdx, pdy, pdz, pex, pey,
		                                    pez);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3, double pdx, double pdy,
                    double pdz, double pex, double pey, double pez)
{
	Sign ret;
	ret =
	  inSphere_IIIEE_interval<IT, ET>(p1, p2, p3, pdx, pdy, pdz, pex, pey, pez);
	if (is_sign_reliable(ret))
		return ret;
	return inSphere_IIIEE_expansion<IT, ET>(p1, p2, p3, pdx, pdy, pdz, pex, pey,
	                                        pez);
}

template <typename IT, typename ET>
Sign inSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &pd,
                    const GenericPoint3T<IT, ET> &pe)
{
	return inSphere_IIIEE<IT, ET>(p1, p2, p3, pd.x(), pd.y(), pd.z(), pe.x(),
	                              pe.y(), pe.z());
}

template <typename IT, typename ET>
Sign inSphere_IIIIE_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3,
                             const GenericPoint3T<IT, ET> &p4, IT pex, IT pey,
                             IT pez)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3) ||
	    !p4.getIntervalLambda(l4x, l4y, l4z, d4))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd   = pex * d1;
	IT peyd   = pey * d1;
	IT pezd   = pez * d1;
	IT aex    = l1x - pexd;
	IT aey    = l1y - peyd;
	IT aez    = l1z - pezd;
	IT pexd2  = pex * d2;
	IT peyd2  = pey * d2;
	IT pezd2  = pez * d2;
	IT bex    = l2x - pexd2;
	IT bey    = l2y - peyd2;
	IT bez    = l2z - pezd2;
	IT pexd3  = pex * d3;
	IT peyd3  = pey * d3;
	IT pezd3  = pez * d3;
	IT cex    = l3x - pexd3;
	IT cey    = l3y - peyd3;
	IT cez    = l3z - pezd3;
	IT pexd4  = pex * d4;
	IT peyd4  = pey * d4;
	IT pezd4  = pez * d4;
	IT dex    = l4x - pexd4;
	IT dey    = l4y - peyd4;
	IT dez    = l4z - pezd4;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT ds1    = dlift * abc;
	IT ds12   = ds1 * d3;
	IT ds2    = clift * dab;
	IT ds22   = ds2 * d4;
	IT dl     = ds22 - ds12;
	IT dlx1   = dl * d1;
	IT dlx2   = dlx1 * d2;
	IT dr1    = blift * cda;
	IT dr12   = dr1 * d1;
	IT dr2    = alift * bcd;
	IT dr22   = dr2 * d2;
	IT dr     = dr22 - dr12;
	IT drx1   = dr * d3;
	IT drx2   = drx1 * d4;
	IT det    = dlx2 + drx2;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIIIE_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2,
                          const GenericPoint3T<IT, ET> &p3,
                          const GenericPoint3T<IT, ET> &p4, ET pex, ET pey,
                          ET pez)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	p4.getExactLambda(l4x, l4y, l4z, d4);
	ET pexd   = pex * d1;
	ET peyd   = pey * d1;
	ET pezd   = pez * d1;
	ET aex    = l1x - pexd;
	ET aey    = l1y - peyd;
	ET aez    = l1z - pezd;
	ET pexd2  = pex * d2;
	ET peyd2  = pey * d2;
	ET pezd2  = pez * d2;
	ET bex    = l2x - pexd2;
	ET bey    = l2y - peyd2;
	ET bez    = l2z - pezd2;
	ET pexd3  = pex * d3;
	ET peyd3  = pey * d3;
	ET pezd3  = pez * d3;
	ET cex    = l3x - pexd3;
	ET cey    = l3y - peyd3;
	ET cez    = l3z - pezd3;
	ET pexd4  = pex * d4;
	ET peyd4  = pey * d4;
	ET pezd4  = pez * d4;
	ET dex    = l4x - pexd4;
	ET dey    = l4y - peyd4;
	ET dez    = l4z - pezd4;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET ds1    = dlift * abc;
	ET ds12   = ds1 * d3;
	ET ds2    = clift * dab;
	ET ds22   = ds2 * d4;
	ET dl     = ds22 - ds12;
	ET dlx1   = dl * d1;
	ET dlx2   = dlx1 * d2;
	ET dr1    = blift * cda;
	ET dr12   = dr1 * d1;
	ET dr2    = alift * bcd;
	ET dr22   = dr2 * d2;
	ET dr     = dr22 - dr12;
	ET drx1   = dr * d3;
	ET drx2   = drx1 * d4;
	ET det    = dlx2 + drx2;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3,
                              const GenericPoint3T<IT, ET> &p4, double pex,
                              double pey, double pez)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16],
	  *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16], *l1z = l1z_p, d1_p[16],
	  *d1 = d1_p, l2x_p[16], *l2x = l2x_p, l2y_p[16], *l2y = l2y_p, l2z_p[16],
	  *l2z = l2z_p, d2_p[16], *d2 = d2_p, l3x_p[16], *l3x = l3x_p, l3y_p[16],
	  *l3y = l3y_p, l3z_p[16], *l3z = l3z_p, d3_p[16], *d3 = d3_p, l4x_p[16],
	  *l4x = l4x_p, l4y_p[16], *l4y = l4y_p, l4z_p[16], *l4z = l4z_p, d4_p[16],
	  *d4       = d4_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16, l2x_len = 16,
	    l2y_len = 16, l2z_len = 16, d2_len = 16, l3x_len = 16, l3y_len = 16,
	    l3z_len = 16, d3_len = 16, l4x_len = 16, l4y_len = 16, l4z_len = 16,
	    d4_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	p4.getExpansionLambda(&l4x, l4x_len, &l4y, l4y_len, &l4z, l4z_len, &d4,
	                      d4_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0) &&
	    (d4[d4_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double pexd2_p[16], *pexd2 = pexd2_p;
		int    pexd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pex, &pexd2, 16);
		double peyd2_p[16], *peyd2 = peyd2_p;
		int    peyd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pey, &peyd2, 16);
		double pezd2_p[16], *pezd2 = pezd2_p;
		int    pezd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pez, &pezd2, 16);
		double bex_p[16], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pexd2_len, pexd2, &bex, 16);
		double bey_p[16], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, peyd2_len, peyd2, &bey, 16);
		double bez_p[16], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, pezd2_len, pezd2, &bez, 16);
		double pexd3_p[16], *pexd3 = pexd3_p;
		int    pexd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pex, &pexd3, 16);
		double peyd3_p[16], *peyd3 = peyd3_p;
		int    peyd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pey, &peyd3, 16);
		double pezd3_p[16], *pezd3 = pezd3_p;
		int    pezd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pez, &pezd3, 16);
		double cex_p[16], *cex = cex_p;
		int    cex_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, pexd3_len, pexd3, &cex, 16);
		double cey_p[16], *cey = cey_p;
		int    cey_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, peyd3_len, peyd3, &cey, 16);
		double cez_p[16], *cez = cez_p;
		int    cez_len =
		  o.Gen_Diff_With_PreAlloc(l3z_len, l3z, pezd3_len, pezd3, &cez, 16);
		double pexd4_p[16], *pexd4 = pexd4_p;
		int    pexd4_len = o.Gen_Scale_With_PreAlloc(d4_len, d4, pex, &pexd4, 16);
		double peyd4_p[16], *peyd4 = peyd4_p;
		int    peyd4_len = o.Gen_Scale_With_PreAlloc(d4_len, d4, pey, &peyd4, 16);
		double pezd4_p[16], *pezd4 = pezd4_p;
		int    pezd4_len = o.Gen_Scale_With_PreAlloc(d4_len, d4, pez, &pezd4, 16);
		double dex_p[16], *dex = dex_p;
		int    dex_len =
		  o.Gen_Diff_With_PreAlloc(l4x_len, l4x, pexd4_len, pexd4, &dex, 16);
		double dey_p[16], *dey = dey_p;
		int    dey_len =
		  o.Gen_Diff_With_PreAlloc(l4y_len, l4y, peyd4_len, peyd4, &dey, 16);
		double dez_p[16], *dez = dez_p;
		int    dez_len =
		  o.Gen_Diff_With_PreAlloc(l4z_len, l4z, pezd4_len, pezd4, &dez, 16);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey_p[16], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, cey_len, cey, &bexcey, 16);
		double cexbey_p[16], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, bey_len, bey, &cexbey, 16);
		double bc_p[16], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 16);
		double cexdey_p[16], *cexdey = cexdey_p;
		int    cexdey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, dey_len, dey, &cexdey, 16);
		double dexcey_p[16], *dexcey = dexcey_p;
		int    dexcey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, cey_len, cey, &dexcey, 16);
		double cd_p[16], *cd = cd_p;
		int    cd_len =
		  o.Gen_Diff_With_PreAlloc(cexdey_len, cexdey, dexcey_len, dexcey, &cd, 16);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, dey_len, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, cey_len, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey_p[16], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, dey_len, dey, &bexdey, 16);
		double dexbey_p[16], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, bey_len, bey, &dexbey, 16);
		double bd_p[16], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 16);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int    abc3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int    bcd2_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int    bcd3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int    cda1_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int    cda2_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int    dab1_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double bl1_p[16], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 16);
		double bl2_p[16], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 16);
		double bl3_p[16], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 16);
		double bl4_p[16], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 16);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double cl1_p[16], *cl1 = cl1_p;
		int    cl1_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, cex_len, cex, &cl1, 16);
		double cl2_p[16], *cl2 = cl2_p;
		int    cl2_len =
		  o.Gen_Product_With_PreAlloc(cey_len, cey, cey_len, cey, &cl2, 16);
		double cl3_p[16], *cl3 = cl3_p;
		int    cl3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, cez_len, cez, &cl3, 16);
		double cl4_p[16], *cl4 = cl4_p;
		int cl4_len = o.Gen_Sum_With_PreAlloc(cl1_len, cl1, cl2_len, cl2, &cl4, 16);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double dl1_p[16], *dl1 = dl1_p;
		int    dl1_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, dex_len, dex, &dl1, 16);
		double dl2_p[16], *dl2 = dl2_p;
		int    dl2_len =
		  o.Gen_Product_With_PreAlloc(dey_len, dey, dey_len, dey, &dl2, 16);
		double dl3_p[16], *dl3 = dl3_p;
		int    dl3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, dez_len, dez, &dl3, 16);
		double dl4_p[16], *dl4 = dl4_p;
		int dl4_len = o.Gen_Sum_With_PreAlloc(dl1_len, dl1, dl2_len, dl2, &dl4, 16);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(dlift_len, dlift, abc_len, abc, &ds1, 16);
		double ds12_p[16], *ds12 = ds12_p;
		int    ds12_len =
		  o.Gen_Product_With_PreAlloc(ds1_len, ds1, d3_len, d3, &ds12, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, dab_len, dab, &ds2, 16);
		double ds22_p[16], *ds22 = ds22_p;
		int    ds22_len =
		  o.Gen_Product_With_PreAlloc(ds2_len, ds2, d4_len, d4, &ds22, 16);
		double dl_p[16], *dl = dl_p;
		int    dl_len =
		  o.Gen_Diff_With_PreAlloc(ds22_len, ds22, ds12_len, ds12, &dl, 16);
		double dlx1_p[16], *dlx1 = dlx1_p;
		int    dlx1_len =
		  o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dlx1, 16);
		double dlx2_p[16], *dlx2 = dlx2_p;
		int    dlx2_len =
		  o.Gen_Product_With_PreAlloc(dlx1_len, dlx1, d2_len, d2, &dlx2, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cda_len, cda, &dr1, 16);
		double dr12_p[16], *dr12 = dr12_p;
		int    dr12_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr12, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcd_len, bcd, &dr2, 16);
		double dr22_p[16], *dr22 = dr22_p;
		int    dr22_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr22, 16);
		double dr_p[16], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr22_len, dr22, dr12_len, dr12, &dr, 16);
		double drx1_p[16], *drx1 = drx1_p;
		int    drx1_len =
		  o.Gen_Product_With_PreAlloc(dr_len, dr, d3_len, d3, &drx1, 16);
		double drx2_p[16], *drx2 = drx2_p;
		int    drx2_len =
		  o.Gen_Product_With_PreAlloc(drx1_len, drx1, d4_len, d4, &drx2, 16);
		double det_p[16], *det = det_p;
		int    det_len =
		  o.Gen_Sum_With_PreAlloc(dlx2_len, dlx2, drx2_len, drx2, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (drx2_p != drx2)
			FreeDoubles(drx2);
		if (drx1_p != drx1)
			FreeDoubles(drx1);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr22_p != dr22)
			FreeDoubles(dr22);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr12_p != dr12)
			FreeDoubles(dr12);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dlx2_p != dlx2)
			FreeDoubles(dlx2);
		if (dlx1_p != dlx1)
			FreeDoubles(dlx1);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds22_p != ds22)
			FreeDoubles(ds22);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds12_p != ds12)
			FreeDoubles(ds12);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (dl4_p != dl4)
			FreeDoubles(dl4);
		if (dl3_p != dl3)
			FreeDoubles(dl3);
		if (dl2_p != dl2)
			FreeDoubles(dl2);
		if (dl1_p != dl1)
			FreeDoubles(dl1);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cl4_p != cl4)
			FreeDoubles(cl4);
		if (cl3_p != cl3)
			FreeDoubles(cl3);
		if (cl2_p != cl2)
			FreeDoubles(cl2);
		if (cl1_p != cl1)
			FreeDoubles(cl1);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (dexcey_p != dexcey)
			FreeDoubles(dexcey);
		if (cexdey_p != cexdey)
			FreeDoubles(cexdey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (dez_p != dez)
			FreeDoubles(dez);
		if (dey_p != dey)
			FreeDoubles(dey);
		if (dex_p != dex)
			FreeDoubles(dex);
		if (pezd4_p != pezd4)
			FreeDoubles(pezd4);
		if (peyd4_p != peyd4)
			FreeDoubles(peyd4);
		if (pexd4_p != pexd4)
			FreeDoubles(pexd4);
		if (cez_p != cez)
			FreeDoubles(cez);
		if (cey_p != cey)
			FreeDoubles(cey);
		if (cex_p != cex)
			FreeDoubles(cex);
		if (pezd3_p != pezd3)
			FreeDoubles(pezd3);
		if (peyd3_p != peyd3)
			FreeDoubles(peyd3);
		if (pexd3_p != pexd3)
			FreeDoubles(pexd3);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
		if (l4x_p != l4x)
			FreeDoubles(l4x);
		if (l4y_p != l4y)
			FreeDoubles(l4y);
		if (l4z_p != l4z)
			FreeDoubles(l4z);
		if (d4_p != d4)
			FreeDoubles(d4);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSphere_IIIIE_exact<IT, ET>(p1, p2, p3, p4, pex, pey, pez);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &p4, double pex, double pey,
                    double pez)
{
	Sign ret;
	ret = inSphere_IIIIE_interval<IT, ET>(p1, p2, p3, p4, pex, pey, pez);
	if (is_sign_reliable(ret))
		return ret;
	return inSphere_IIIIE_expansion<IT, ET>(p1, p2, p3, p4, pex, pey, pez);
}

template <typename IT, typename ET>
Sign inSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &p4,
                    const GenericPoint3T<IT, ET> &pe)
{
	return inSphere_IIIIE<IT, ET>(p1, p2, p3, p4, pe.x(), pe.y(), pe.z());
}

template <typename IT, typename ET>
Sign inSphere_IIIII_interval(const GenericPoint3T<IT, ET> &p1,
                             const GenericPoint3T<IT, ET> &p2,
                             const GenericPoint3T<IT, ET> &p3,
                             const GenericPoint3T<IT, ET> &p4,
                             const GenericPoint3T<IT, ET> &p5)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4,
	  l5x, l5y, l5z, d5;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3) ||
	    !p4.getIntervalLambda(l4x, l4y, l4z, d4) ||
	    !p5.getIntervalLambda(l5x, l5y, l5z, d5))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd   = l5x * d1;
	IT peyd   = l5y * d1;
	IT pezd   = l5z * d1;
	IT ll1x   = l1x * d5;
	IT ll1y   = l1y * d5;
	IT ll1z   = l1z * d5;
	IT aex    = ll1x - pexd;
	IT aey    = ll1y - peyd;
	IT aez    = ll1z - pezd;
	IT pexd2  = l5x * d2;
	IT peyd2  = l5y * d2;
	IT pezd2  = l5z * d2;
	IT ll2x   = l2x * d5;
	IT ll2y   = l2y * d5;
	IT ll2z   = l2z * d5;
	IT bex    = ll2x - pexd2;
	IT bey    = ll2y - peyd2;
	IT bez    = ll2z - pezd2;
	IT pexd3  = l5x * d3;
	IT peyd3  = l5y * d3;
	IT pezd3  = l5z * d3;
	IT ll3x   = l3x * d5;
	IT ll3y   = l3y * d5;
	IT ll3z   = l3z * d5;
	IT cex    = ll3x - pexd3;
	IT cey    = ll3y - peyd3;
	IT cez    = ll3z - pezd3;
	IT pexd4  = l5x * d4;
	IT peyd4  = l5y * d4;
	IT pezd4  = l5z * d4;
	IT ll4x   = l4x * d5;
	IT ll4y   = l4y * d5;
	IT ll4z   = l4z * d5;
	IT dex    = ll4x - pexd4;
	IT dey    = ll4y - peyd4;
	IT dez    = ll4z - pezd4;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT ds1    = dlift * abc;
	IT ds1n   = ds1 * d3;
	IT ds2    = clift * dab;
	IT ds2n   = ds2 * d4;
	IT dl     = ds2n - ds1n;
	IT dla    = dl * d1;
	IT dlb    = dla * d2;
	IT dr1    = blift * cda;
	IT dr1n   = dr1 * d1;
	IT dr2    = alift * bcd;
	IT dr2n   = dr2 * d2;
	IT dr     = dr2n - dr1n;
	IT dra    = dr * d3;
	IT drb    = dra * d4;
	IT det    = dlb + drb;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIIII_exact(const GenericPoint3T<IT, ET> &p1,
                          const GenericPoint3T<IT, ET> &p2,
                          const GenericPoint3T<IT, ET> &p3,
                          const GenericPoint3T<IT, ET> &p4,
                          const GenericPoint3T<IT, ET> &p5)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4,
	  l5x, l5y, l5z, d5;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	p4.getExactLambda(l4x, l4y, l4z, d4);
	p5.getExactLambda(l5x, l5y, l5z, d5);
	ET pexd   = l5x * d1;
	ET peyd   = l5y * d1;
	ET pezd   = l5z * d1;
	ET ll1x   = l1x * d5;
	ET ll1y   = l1y * d5;
	ET ll1z   = l1z * d5;
	ET aex    = ll1x - pexd;
	ET aey    = ll1y - peyd;
	ET aez    = ll1z - pezd;
	ET pexd2  = l5x * d2;
	ET peyd2  = l5y * d2;
	ET pezd2  = l5z * d2;
	ET ll2x   = l2x * d5;
	ET ll2y   = l2y * d5;
	ET ll2z   = l2z * d5;
	ET bex    = ll2x - pexd2;
	ET bey    = ll2y - peyd2;
	ET bez    = ll2z - pezd2;
	ET pexd3  = l5x * d3;
	ET peyd3  = l5y * d3;
	ET pezd3  = l5z * d3;
	ET ll3x   = l3x * d5;
	ET ll3y   = l3y * d5;
	ET ll3z   = l3z * d5;
	ET cex    = ll3x - pexd3;
	ET cey    = ll3y - peyd3;
	ET cez    = ll3z - pezd3;
	ET pexd4  = l5x * d4;
	ET peyd4  = l5y * d4;
	ET pezd4  = l5z * d4;
	ET ll4x   = l4x * d5;
	ET ll4y   = l4y * d5;
	ET ll4z   = l4z * d5;
	ET dex    = ll4x - pexd4;
	ET dey    = ll4y - peyd4;
	ET dez    = ll4z - pezd4;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET ds1    = dlift * abc;
	ET ds1n   = ds1 * d3;
	ET ds2    = clift * dab;
	ET ds2n   = ds2 * d4;
	ET dl     = ds2n - ds1n;
	ET dla    = dl * d1;
	ET dlb    = dla * d2;
	ET dr1    = blift * cda;
	ET dr1n   = dr1 * d1;
	ET dr2    = alift * bcd;
	ET dr2n   = dr2 * d2;
	ET dr     = dr2n - dr1n;
	ET dra    = dr * d3;
	ET drb    = dra * d4;
	ET det    = dlb + drb;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inSphere_IIIII_expansion(const GenericPoint3T<IT, ET> &p1,
                              const GenericPoint3T<IT, ET> &p2,
                              const GenericPoint3T<IT, ET> &p3,
                              const GenericPoint3T<IT, ET> &p4,
                              const GenericPoint3T<IT, ET> &p5)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[8],
	  *l1x = l1x_p, l1y_p[8], *l1y = l1y_p, l1z_p[8], *l1z = l1z_p, d1_p[8],
	  *d1 = d1_p, l2x_p[8], *l2x = l2x_p, l2y_p[8], *l2y = l2y_p, l2z_p[8],
	  *l2z = l2z_p, d2_p[8], *d2 = d2_p, l3x_p[8], *l3x = l3x_p, l3y_p[8],
	  *l3y = l3y_p, l3z_p[8], *l3z = l3z_p, d3_p[8], *d3 = d3_p, l4x_p[8],
	  *l4x = l4x_p, l4y_p[8], *l4y = l4y_p, l4z_p[8], *l4z = l4z_p, d4_p[8],
	  *d4 = d4_p, l5x_p[8], *l5x = l5x_p, l5y_p[8], *l5y = l5y_p, l5z_p[8],
	  *l5z = l5z_p, d5_p[8], *d5 = d5_p;
	int l1x_len = 8, l1y_len = 8, l1z_len = 8, d1_len = 8, l2x_len = 8,
	    l2y_len = 8, l2z_len = 8, d2_len = 8, l3x_len = 8, l3y_len = 8,
	    l3z_len = 8, d3_len = 8, l4x_len = 8, l4y_len = 8, l4z_len = 8,
	    d4_len = 8, l5x_len = 8, l5y_len = 8, l5z_len = 8, d5_len = 8;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	p4.getExpansionLambda(&l4x, l4x_len, &l4y, l4y_len, &l4z, l4z_len, &d4,
	                      d4_len);
	p5.getExpansionLambda(&l5x, l5x_len, &l5y, l5y_len, &l5z, l5z_len, &d5,
	                      d5_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0) &&
	    (d4[d4_len - 1] != 0) && (d5[d5_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[8], *pexd = pexd_p;
		int             pexd_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d1_len, d1, &pexd, 8);
		double peyd_p[8], *peyd = peyd_p;
		int    peyd_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d1_len, d1, &peyd, 8);
		double pezd_p[8], *pezd = pezd_p;
		int    pezd_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d1_len, d1, &pezd, 8);
		double ll1x_p[8], *ll1x = ll1x_p;
		int    ll1x_len =
		  o.Gen_Product_With_PreAlloc(l1x_len, l1x, d5_len, d5, &ll1x, 8);
		double ll1y_p[8], *ll1y = ll1y_p;
		int    ll1y_len =
		  o.Gen_Product_With_PreAlloc(l1y_len, l1y, d5_len, d5, &ll1y, 8);
		double ll1z_p[8], *ll1z = ll1z_p;
		int    ll1z_len =
		  o.Gen_Product_With_PreAlloc(l1z_len, l1z, d5_len, d5, &ll1z, 8);
		double aex_p[8], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(ll1x_len, ll1x, pexd_len, pexd, &aex, 8);
		double aey_p[8], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(ll1y_len, ll1y, peyd_len, peyd, &aey, 8);
		double aez_p[8], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(ll1z_len, ll1z, pezd_len, pezd, &aez, 8);
		double pexd2_p[8], *pexd2 = pexd2_p;
		int    pexd2_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d2_len, d2, &pexd2, 8);
		double peyd2_p[8], *peyd2 = peyd2_p;
		int    peyd2_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d2_len, d2, &peyd2, 8);
		double pezd2_p[8], *pezd2 = pezd2_p;
		int    pezd2_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d2_len, d2, &pezd2, 8);
		double ll2x_p[8], *ll2x = ll2x_p;
		int    ll2x_len =
		  o.Gen_Product_With_PreAlloc(l2x_len, l2x, d5_len, d5, &ll2x, 8);
		double ll2y_p[8], *ll2y = ll2y_p;
		int    ll2y_len =
		  o.Gen_Product_With_PreAlloc(l2y_len, l2y, d5_len, d5, &ll2y, 8);
		double ll2z_p[8], *ll2z = ll2z_p;
		int    ll2z_len =
		  o.Gen_Product_With_PreAlloc(l2z_len, l2z, d5_len, d5, &ll2z, 8);
		double bex_p[8], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(ll2x_len, ll2x, pexd2_len, pexd2, &bex, 8);
		double bey_p[8], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(ll2y_len, ll2y, peyd2_len, peyd2, &bey, 8);
		double bez_p[8], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(ll2z_len, ll2z, pezd2_len, pezd2, &bez, 8);
		double pexd3_p[8], *pexd3 = pexd3_p;
		int    pexd3_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d3_len, d3, &pexd3, 8);
		double peyd3_p[8], *peyd3 = peyd3_p;
		int    peyd3_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d3_len, d3, &peyd3, 8);
		double pezd3_p[8], *pezd3 = pezd3_p;
		int    pezd3_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d3_len, d3, &pezd3, 8);
		double ll3x_p[8], *ll3x = ll3x_p;
		int    ll3x_len =
		  o.Gen_Product_With_PreAlloc(l3x_len, l3x, d5_len, d5, &ll3x, 8);
		double ll3y_p[8], *ll3y = ll3y_p;
		int    ll3y_len =
		  o.Gen_Product_With_PreAlloc(l3y_len, l3y, d5_len, d5, &ll3y, 8);
		double ll3z_p[8], *ll3z = ll3z_p;
		int    ll3z_len =
		  o.Gen_Product_With_PreAlloc(l3z_len, l3z, d5_len, d5, &ll3z, 8);
		double cex_p[8], *cex = cex_p;
		int    cex_len =
		  o.Gen_Diff_With_PreAlloc(ll3x_len, ll3x, pexd3_len, pexd3, &cex, 8);
		double cey_p[8], *cey = cey_p;
		int    cey_len =
		  o.Gen_Diff_With_PreAlloc(ll3y_len, ll3y, peyd3_len, peyd3, &cey, 8);
		double cez_p[8], *cez = cez_p;
		int    cez_len =
		  o.Gen_Diff_With_PreAlloc(ll3z_len, ll3z, pezd3_len, pezd3, &cez, 8);
		double pexd4_p[8], *pexd4 = pexd4_p;
		int    pexd4_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d4_len, d4, &pexd4, 8);
		double peyd4_p[8], *peyd4 = peyd4_p;
		int    peyd4_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d4_len, d4, &peyd4, 8);
		double pezd4_p[8], *pezd4 = pezd4_p;
		int    pezd4_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d4_len, d4, &pezd4, 8);
		double ll4x_p[8], *ll4x = ll4x_p;
		int    ll4x_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d5_len, d5, &ll4x, 8);
		double ll4y_p[8], *ll4y = ll4y_p;
		int    ll4y_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d5_len, d5, &ll4y, 8);
		double ll4z_p[8], *ll4z = ll4z_p;
		int    ll4z_len =
		  o.Gen_Product_With_PreAlloc(l4z_len, l4z, d5_len, d5, &ll4z, 8);
		double dex_p[8], *dex = dex_p;
		int    dex_len =
		  o.Gen_Diff_With_PreAlloc(ll4x_len, ll4x, pexd4_len, pexd4, &dex, 8);
		double dey_p[8], *dey = dey_p;
		int    dey_len =
		  o.Gen_Diff_With_PreAlloc(ll4y_len, ll4y, peyd4_len, peyd4, &dey, 8);
		double dez_p[8], *dez = dez_p;
		int    dez_len =
		  o.Gen_Diff_With_PreAlloc(ll4z_len, ll4z, pezd4_len, pezd4, &dez, 8);
		double aexbey_p[8], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 8);
		double bexaey_p[8], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 8);
		double ab_p[8], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 8);
		double bexcey_p[8], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, cey_len, cey, &bexcey, 8);
		double cexbey_p[8], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, bey_len, bey, &cexbey, 8);
		double bc_p[8], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 8);
		double cexdey_p[8], *cexdey = cexdey_p;
		int    cexdey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, dey_len, dey, &cexdey, 8);
		double dexcey_p[8], *dexcey = dexcey_p;
		int    dexcey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, cey_len, cey, &dexcey, 8);
		double cd_p[8], *cd = cd_p;
		int    cd_len =
		  o.Gen_Diff_With_PreAlloc(cexdey_len, cexdey, dexcey_len, dexcey, &cd, 8);
		double dexaey_p[8], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, aey_len, aey, &dexaey, 8);
		double aexdey_p[8], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, dey_len, dey, &aexdey, 8);
		double da_p[8], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 8);
		double aexcey_p[8], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, cey_len, cey, &aexcey, 8);
		double cexaey_p[8], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, aey_len, aey, &cexaey, 8);
		double ac_p[8], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 8);
		double bexdey_p[8], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, dey_len, dey, &bexdey, 8);
		double dexbey_p[8], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, bey_len, bey, &dexbey, 8);
		double bd_p[8], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 8);
		double abc1_p[8], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 8);
		double abc2_p[8], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 8);
		double abc3_p[8], *abc3 = abc3_p;
		int    abc3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, ab_len, ab, &abc3, 8);
		double abc4_p[8], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 8);
		double abc_p[8], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 8);
		double bcd1_p[8], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 8);
		double bcd2_p[8], *bcd2 = bcd2_p;
		int    bcd2_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, bd_len, bd, &bcd2, 8);
		double bcd3_p[8], *bcd3 = bcd3_p;
		int    bcd3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, bc_len, bc, &bcd3, 8);
		double bcd4_p[8], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 8);
		double bcd_p[8], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 8);
		double cda1_p[8], *cda1 = cda1_p;
		int    cda1_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, da_len, da, &cda1, 8);
		double cda2_p[8], *cda2 = cda2_p;
		int    cda2_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ac_len, ac, &cda2, 8);
		double cda3_p[8], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 8);
		double cda4_p[8], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 8);
		double cda_p[8], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 8);
		double dab1_p[8], *dab1 = dab1_p;
		int    dab1_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ab_len, ab, &dab1, 8);
		double dab2_p[8], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 8);
		double dab3_p[8], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 8);
		double dab4_p[8], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 8);
		double dab_p[8], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 8);
		double al1_p[8], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 8);
		double al2_p[8], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 8);
		double al3_p[8], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 8);
		double al4_p[8], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 8);
		double alift_p[8], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 8);
		double bl1_p[8], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 8);
		double bl2_p[8], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 8);
		double bl3_p[8], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 8);
		double bl4_p[8], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 8);
		double blift_p[8], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 8);
		double cl1_p[8], *cl1 = cl1_p;
		int    cl1_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, cex_len, cex, &cl1, 8);
		double cl2_p[8], *cl2 = cl2_p;
		int    cl2_len =
		  o.Gen_Product_With_PreAlloc(cey_len, cey, cey_len, cey, &cl2, 8);
		double cl3_p[8], *cl3 = cl3_p;
		int    cl3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, cez_len, cez, &cl3, 8);
		double cl4_p[8], *cl4 = cl4_p;
		int cl4_len = o.Gen_Sum_With_PreAlloc(cl1_len, cl1, cl2_len, cl2, &cl4, 8);
		double clift_p[8], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 8);
		double dl1_p[8], *dl1 = dl1_p;
		int    dl1_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, dex_len, dex, &dl1, 8);
		double dl2_p[8], *dl2 = dl2_p;
		int    dl2_len =
		  o.Gen_Product_With_PreAlloc(dey_len, dey, dey_len, dey, &dl2, 8);
		double dl3_p[8], *dl3 = dl3_p;
		int    dl3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, dez_len, dez, &dl3, 8);
		double dl4_p[8], *dl4 = dl4_p;
		int dl4_len = o.Gen_Sum_With_PreAlloc(dl1_len, dl1, dl2_len, dl2, &dl4, 8);
		double dlift_p[8], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 8);
		double ds1_p[8], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(dlift_len, dlift, abc_len, abc, &ds1, 8);
		double ds1n_p[8], *ds1n = ds1n_p;
		int    ds1n_len =
		  o.Gen_Product_With_PreAlloc(ds1_len, ds1, d3_len, d3, &ds1n, 8);
		double ds2_p[8], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(clift_len, clift, dab_len, dab, &ds2, 8);
		double ds2n_p[8], *ds2n = ds2n_p;
		int    ds2n_len =
		  o.Gen_Product_With_PreAlloc(ds2_len, ds2, d4_len, d4, &ds2n, 8);
		double dl_p[8], *dl = dl_p;
		int    dl_len =
		  o.Gen_Diff_With_PreAlloc(ds2n_len, ds2n, ds1n_len, ds1n, &dl, 8);
		double dla_p[8], *dla = dla_p;
		int dla_len = o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dla, 8);
		double dlb_p[8], *dlb = dlb_p;
		int    dlb_len =
		  o.Gen_Product_With_PreAlloc(dla_len, dla, d2_len, d2, &dlb, 8);
		double dr1_p[8], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(blift_len, blift, cda_len, cda, &dr1, 8);
		double dr1n_p[8], *dr1n = dr1n_p;
		int    dr1n_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr1n, 8);
		double dr2_p[8], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(alift_len, alift, bcd_len, bcd, &dr2, 8);
		double dr2n_p[8], *dr2n = dr2n_p;
		int    dr2n_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr2n, 8);
		double dr_p[8], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr2n_len, dr2n, dr1n_len, dr1n, &dr, 8);
		double dra_p[8], *dra = dra_p;
		int dra_len = o.Gen_Product_With_PreAlloc(dr_len, dr, d3_len, d3, &dra, 8);
		double drb_p[8], *drb = drb_p;
		int    drb_len =
		  o.Gen_Product_With_PreAlloc(dra_len, dra, d4_len, d4, &drb, 8);
		double det_p[8], *det = det_p;
		int det_len = o.Gen_Sum_With_PreAlloc(dlb_len, dlb, drb_len, drb, &det, 8);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (drb_p != drb)
			FreeDoubles(drb);
		if (dra_p != dra)
			FreeDoubles(dra);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr2n_p != dr2n)
			FreeDoubles(dr2n);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr1n_p != dr1n)
			FreeDoubles(dr1n);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dlb_p != dlb)
			FreeDoubles(dlb);
		if (dla_p != dla)
			FreeDoubles(dla);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds2n_p != ds2n)
			FreeDoubles(ds2n);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1n_p != ds1n)
			FreeDoubles(ds1n);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (dl4_p != dl4)
			FreeDoubles(dl4);
		if (dl3_p != dl3)
			FreeDoubles(dl3);
		if (dl2_p != dl2)
			FreeDoubles(dl2);
		if (dl1_p != dl1)
			FreeDoubles(dl1);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cl4_p != cl4)
			FreeDoubles(cl4);
		if (cl3_p != cl3)
			FreeDoubles(cl3);
		if (cl2_p != cl2)
			FreeDoubles(cl2);
		if (cl1_p != cl1)
			FreeDoubles(cl1);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (dexcey_p != dexcey)
			FreeDoubles(dexcey);
		if (cexdey_p != cexdey)
			FreeDoubles(cexdey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (dez_p != dez)
			FreeDoubles(dez);
		if (dey_p != dey)
			FreeDoubles(dey);
		if (dex_p != dex)
			FreeDoubles(dex);
		if (ll4z_p != ll4z)
			FreeDoubles(ll4z);
		if (ll4y_p != ll4y)
			FreeDoubles(ll4y);
		if (ll4x_p != ll4x)
			FreeDoubles(ll4x);
		if (pezd4_p != pezd4)
			FreeDoubles(pezd4);
		if (peyd4_p != peyd4)
			FreeDoubles(peyd4);
		if (pexd4_p != pexd4)
			FreeDoubles(pexd4);
		if (cez_p != cez)
			FreeDoubles(cez);
		if (cey_p != cey)
			FreeDoubles(cey);
		if (cex_p != cex)
			FreeDoubles(cex);
		if (ll3z_p != ll3z)
			FreeDoubles(ll3z);
		if (ll3y_p != ll3y)
			FreeDoubles(ll3y);
		if (ll3x_p != ll3x)
			FreeDoubles(ll3x);
		if (pezd3_p != pezd3)
			FreeDoubles(pezd3);
		if (peyd3_p != peyd3)
			FreeDoubles(peyd3);
		if (pexd3_p != pexd3)
			FreeDoubles(pexd3);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (ll2z_p != ll2z)
			FreeDoubles(ll2z);
		if (ll2y_p != ll2y)
			FreeDoubles(ll2y);
		if (ll2x_p != ll2x)
			FreeDoubles(ll2x);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (ll1z_p != ll1z)
			FreeDoubles(ll1z);
		if (ll1y_p != ll1y)
			FreeDoubles(ll1y);
		if (ll1x_p != ll1x)
			FreeDoubles(ll1x);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
		if (l4x_p != l4x)
			FreeDoubles(l4x);
		if (l4y_p != l4y)
			FreeDoubles(l4y);
		if (l4z_p != l4z)
			FreeDoubles(l4z);
		if (d4_p != d4)
			FreeDoubles(d4);
		if (l5x_p != l5x)
			FreeDoubles(l5x);
		if (l5y_p != l5y)
			FreeDoubles(l5y);
		if (l5z_p != l5z)
			FreeDoubles(l5z);
		if (d5_p != d5)
			FreeDoubles(d5);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSphere_IIIII_exact<IT, ET>(p1, p2, p3, p4, p5);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSphere_IIIII(const GenericPoint3T<IT, ET> &p1,
                    const GenericPoint3T<IT, ET> &p2,
                    const GenericPoint3T<IT, ET> &p3,
                    const GenericPoint3T<IT, ET> &p4,
                    const GenericPoint3T<IT, ET> &p5)
{
	Sign ret;
	ret = inSphere_IIIII_interval<IT, ET>(p1, p2, p3, p4, p5);
	if (is_sign_reliable(ret))
		return ret;
	return inSphere_IIIII_expansion<IT, ET>(p1, p2, p3, p4, p5);
}

inline Sign inPowerSphere_filtered(double pax, double pay, double paz,
                                   double pbx, double pby, double pbz,
                                   double pcx, double pcy, double pcz,
                                   double pdx, double pdy, double pdz,
                                   double pex, double pey, double pez,
                                   double wa, double wb, double wc, double wd,
                                   double we)
{
	double aex    = pax - pex;
	double aey    = pay - pey;
	double aez    = paz - pez;
	double bex    = pbx - pex;
	double bey    = pby - pey;
	double bez    = pbz - pez;
	double cex    = pcx - pex;
	double cey    = pcy - pey;
	double cez    = pcz - pez;
	double dex    = pdx - pex;
	double dey    = pdy - pey;
	double dez    = pdz - pez;
	double wae    = wa - we;
	double wbe    = wb - we;
	double wce    = wc - we;
	double wde    = wd - we;
	double aexbey = aex * bey;
	double bexaey = bex * aey;
	double ab     = aexbey - bexaey;
	double bexcey = bex * cey;
	double cexbey = cex * bey;
	double bc     = bexcey - cexbey;
	double cexdey = cex * dey;
	double dexcey = dex * cey;
	double cd     = cexdey - dexcey;
	double dexaey = dex * aey;
	double aexdey = aex * dey;
	double da     = dexaey - aexdey;
	double aexcey = aex * cey;
	double cexaey = cex * aey;
	double ac     = aexcey - cexaey;
	double bexdey = bex * dey;
	double dexbey = dex * bey;
	double bd     = bexdey - dexbey;
	double abc1   = aez * bc;
	double abc2   = bez * ac;
	double abc3   = cez * ab;
	double abc4   = abc1 + abc3;
	double abc    = abc4 - abc2;
	double bcd1   = bez * cd;
	double bcd2   = cez * bd;
	double bcd3   = dez * bc;
	double bcd4   = bcd1 + bcd3;
	double bcd    = bcd4 - bcd2;
	double cda1   = cez * da;
	double cda2   = dez * ac;
	double cda3   = aez * cd;
	double cda4   = cda1 + cda3;
	double cda    = cda4 + cda2;
	double dab1   = dez * ab;
	double dab2   = aez * bd;
	double dab3   = bez * da;
	double dab4   = dab1 + dab3;
	double dab    = dab4 + dab2;
	double al1    = aex * aex;
	double al2    = aey * aey;
	double al3    = aez * aez;
	double al4    = al1 + al2;
	double alift  = al4 + al3;
	double walift = alift - wae;
	double bl1    = bex * bex;
	double bl2    = bey * bey;
	double bl3    = bez * bez;
	double bl4    = bl1 + bl2;
	double blift  = bl4 + bl3;
	double wblift = blift - wbe;
	double cl1    = cex * cex;
	double cl2    = cey * cey;
	double cl3    = cez * cez;
	double cl4    = cl1 + cl2;
	double clift  = cl4 + cl3;
	double wclift = clift - wce;
	double dl1    = dex * dex;
	double dl2    = dey * dey;
	double dl3    = dez * dez;
	double dl4    = dl1 + dl2;
	double dlift  = dl4 + dl3;
	double wdlift = dlift - wde;
	double ds1    = wdlift * abc;
	double ds2    = wclift * dab;
	double dl     = ds2 - ds1;
	double dr1    = wblift * cda;
	double dr2    = walift * bcd;
	double dr     = dr2 - dr1;
	double det    = dl + dr;

	double _tmp_fabs;

	double max_var = 0.0;
	if ((_tmp_fabs = fabs(aex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(aey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(aez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(bez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(cez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(dex)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(dey)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(dez)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(wae)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(wbe)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(wce)) > max_var)
		max_var = _tmp_fabs;
	if ((_tmp_fabs = fabs(wde)) > max_var)
		max_var = _tmp_fabs;
	double epsilon = max_var;
	epsilon *= epsilon;
	epsilon *= epsilon;
	epsilon *= max_var;
	epsilon *= 1.474376176702209e-13;

	return filter_sign(det, epsilon);
}

template <typename IT>
Sign inPowerSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby, IT pbz,
                            IT pcx, IT pcy, IT pcz, IT pdx, IT pdy, IT pdz,
                            IT pex, IT pey, IT pez, IT wa, IT wb, IT wc, IT wd,
                            IT we)
{
	typename IT::Protector P;

	IT aex    = pax - pex;
	IT aey    = pay - pey;
	IT aez    = paz - pez;
	IT bex    = pbx - pex;
	IT bey    = pby - pey;
	IT bez    = pbz - pez;
	IT cex    = pcx - pex;
	IT cey    = pcy - pey;
	IT cez    = pcz - pez;
	IT dex    = pdx - pex;
	IT dey    = pdy - pey;
	IT dez    = pdz - pez;
	IT wae    = wa - we;
	IT wbe    = wb - we;
	IT wce    = wc - we;
	IT wde    = wd - we;
	IT aexbey = aex * bey;
	IT bexaey = bex * aey;
	IT ab     = aexbey - bexaey;
	IT bexcey = bex * cey;
	IT cexbey = cex * bey;
	IT bc     = bexcey - cexbey;
	IT cexdey = cex * dey;
	IT dexcey = dex * cey;
	IT cd     = cexdey - dexcey;
	IT dexaey = dex * aey;
	IT aexdey = aex * dey;
	IT da     = dexaey - aexdey;
	IT aexcey = aex * cey;
	IT cexaey = cex * aey;
	IT ac     = aexcey - cexaey;
	IT bexdey = bex * dey;
	IT dexbey = dex * bey;
	IT bd     = bexdey - dexbey;
	IT abc1   = aez * bc;
	IT abc2   = bez * ac;
	IT abc3   = cez * ab;
	IT abc4   = abc1 + abc3;
	IT abc    = abc4 - abc2;
	IT bcd1   = bez * cd;
	IT bcd2   = cez * bd;
	IT bcd3   = dez * bc;
	IT bcd4   = bcd1 + bcd3;
	IT bcd    = bcd4 - bcd2;
	IT cda1   = cez * da;
	IT cda2   = dez * ac;
	IT cda3   = aez * cd;
	IT cda4   = cda1 + cda3;
	IT cda    = cda4 + cda2;
	IT dab1   = dez * ab;
	IT dab2   = aez * bd;
	IT dab3   = bez * da;
	IT dab4   = dab1 + dab3;
	IT dab    = dab4 + dab2;
	IT al1    = aex * aex;
	IT al2    = aey * aey;
	IT al3    = aez * aez;
	IT al4    = al1 + al2;
	IT alift  = al4 + al3;
	IT walift = alift - wae;
	IT bl1    = bex * bex;
	IT bl2    = bey * bey;
	IT bl3    = bez * bez;
	IT bl4    = bl1 + bl2;
	IT blift  = bl4 + bl3;
	IT wblift = blift - wbe;
	IT cl1    = cex * cex;
	IT cl2    = cey * cey;
	IT cl3    = cez * cez;
	IT cl4    = cl1 + cl2;
	IT clift  = cl4 + cl3;
	IT wclift = clift - wce;
	IT dl1    = dex * dex;
	IT dl2    = dey * dey;
	IT dl3    = dez * dez;
	IT dl4    = dl1 + dl2;
	IT dlift  = dl4 + dl3;
	IT wdlift = dlift - wde;
	IT ds1    = wdlift * abc;
	IT ds2    = wclift * dab;
	IT dl     = ds2 - ds1;
	IT dr1    = wblift * cda;
	IT dr2    = walift * bcd;
	IT dr     = dr2 - dr1;
	IT det    = dl + dr;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename ET>
Sign inPowerSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby, ET pbz, ET pcx,
                         ET pcy, ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                         ET pez, ET wa, ET wb, ET wc, ET wd, ET we)
{
	ET aex    = pax - pex;
	ET aey    = pay - pey;
	ET aez    = paz - pez;
	ET bex    = pbx - pex;
	ET bey    = pby - pey;
	ET bez    = pbz - pez;
	ET cex    = pcx - pex;
	ET cey    = pcy - pey;
	ET cez    = pcz - pez;
	ET dex    = pdx - pex;
	ET dey    = pdy - pey;
	ET dez    = pdz - pez;
	ET wae    = wa - we;
	ET wbe    = wb - we;
	ET wce    = wc - we;
	ET wde    = wd - we;
	ET aexbey = aex * bey;
	ET bexaey = bex * aey;
	ET ab     = aexbey - bexaey;
	ET bexcey = bex * cey;
	ET cexbey = cex * bey;
	ET bc     = bexcey - cexbey;
	ET cexdey = cex * dey;
	ET dexcey = dex * cey;
	ET cd     = cexdey - dexcey;
	ET dexaey = dex * aey;
	ET aexdey = aex * dey;
	ET da     = dexaey - aexdey;
	ET aexcey = aex * cey;
	ET cexaey = cex * aey;
	ET ac     = aexcey - cexaey;
	ET bexdey = bex * dey;
	ET dexbey = dex * bey;
	ET bd     = bexdey - dexbey;
	ET abc1   = aez * bc;
	ET abc2   = bez * ac;
	ET abc3   = cez * ab;
	ET abc4   = abc1 + abc3;
	ET abc    = abc4 - abc2;
	ET bcd1   = bez * cd;
	ET bcd2   = cez * bd;
	ET bcd3   = dez * bc;
	ET bcd4   = bcd1 + bcd3;
	ET bcd    = bcd4 - bcd2;
	ET cda1   = cez * da;
	ET cda2   = dez * ac;
	ET cda3   = aez * cd;
	ET cda4   = cda1 + cda3;
	ET cda    = cda4 + cda2;
	ET dab1   = dez * ab;
	ET dab2   = aez * bd;
	ET dab3   = bez * da;
	ET dab4   = dab1 + dab3;
	ET dab    = dab4 + dab2;
	ET al1    = aex * aex;
	ET al2    = aey * aey;
	ET al3    = aez * aez;
	ET al4    = al1 + al2;
	ET alift  = al4 + al3;
	ET walift = alift - wae;
	ET bl1    = bex * bex;
	ET bl2    = bey * bey;
	ET bl3    = bez * bez;
	ET bl4    = bl1 + bl2;
	ET blift  = bl4 + bl3;
	ET wblift = blift - wbe;
	ET cl1    = cex * cex;
	ET cl2    = cey * cey;
	ET cl3    = cez * cez;
	ET cl4    = cl1 + cl2;
	ET clift  = cl4 + cl3;
	ET wclift = clift - wce;
	ET dl1    = dex * dex;
	ET dl2    = dey * dey;
	ET dl3    = dez * dez;
	ET dl4    = dl1 + dl2;
	ET dlift  = dl4 + dl3;
	ET wdlift = dlift - wde;
	ET ds1    = wdlift * abc;
	ET ds2    = wclift * dab;
	ET dl     = ds2 - ds1;
	ET dr1    = wblift * cda;
	ET dr2    = walift * bcd;
	ET dr     = dr2 - dr1;
	ET det    = dl + dr;
	return OMC::sign(det);
}

Sign inPowerSphere_expansion(double pax, double pay, double paz, double pbx,
                             double pby, double pbz, double pcx, double pcy,
                             double pcz, double pdx, double pdy, double pdz,
                             double pex, double pey, double pez, double wa,
                             double wb, double wc, double wd, double we)
{
	expansionObject o;
	double          aex[2];
	o.Two_Diff(pax, pex, aex);
	double aey[2];
	o.Two_Diff(pay, pey, aey);
	double aez[2];
	o.Two_Diff(paz, pez, aez);
	double bex[2];
	o.Two_Diff(pbx, pex, bex);
	double bey[2];
	o.Two_Diff(pby, pey, bey);
	double bez[2];
	o.Two_Diff(pbz, pez, bez);
	double cex[2];
	o.Two_Diff(pcx, pex, cex);
	double cey[2];
	o.Two_Diff(pcy, pey, cey);
	double cez[2];
	o.Two_Diff(pcz, pez, cez);
	double dex[2];
	o.Two_Diff(pdx, pex, dex);
	double dey[2];
	o.Two_Diff(pdy, pey, dey);
	double dez[2];
	o.Two_Diff(pdz, pez, dez);
	double wae[2];
	o.Two_Diff(wa, we, wae);
	double wbe[2];
	o.Two_Diff(wb, we, wbe);
	double wce[2];
	o.Two_Diff(wc, we, wce);
	double wde[2];
	o.Two_Diff(wd, we, wde);
	double aexbey[8];
	int    aexbey_len = o.Gen_Product(2, aex, 2, bey, aexbey);
	double bexaey[8];
	int    bexaey_len = o.Gen_Product(2, bex, 2, aey, bexaey);
	double ab[16];
	int    ab_len = o.Gen_Diff(aexbey_len, aexbey, bexaey_len, bexaey, ab);
	double bexcey[8];
	int    bexcey_len = o.Gen_Product(2, bex, 2, cey, bexcey);
	double cexbey[8];
	int    cexbey_len = o.Gen_Product(2, cex, 2, bey, cexbey);
	double bc[16];
	int    bc_len = o.Gen_Diff(bexcey_len, bexcey, cexbey_len, cexbey, bc);
	double cexdey[8];
	int    cexdey_len = o.Gen_Product(2, cex, 2, dey, cexdey);
	double dexcey[8];
	int    dexcey_len = o.Gen_Product(2, dex, 2, cey, dexcey);
	double cd[16];
	int    cd_len = o.Gen_Diff(cexdey_len, cexdey, dexcey_len, dexcey, cd);
	double dexaey[8];
	int    dexaey_len = o.Gen_Product(2, dex, 2, aey, dexaey);
	double aexdey[8];
	int    aexdey_len = o.Gen_Product(2, aex, 2, dey, aexdey);
	double da[16];
	int    da_len = o.Gen_Diff(dexaey_len, dexaey, aexdey_len, aexdey, da);
	double aexcey[8];
	int    aexcey_len = o.Gen_Product(2, aex, 2, cey, aexcey);
	double cexaey[8];
	int    cexaey_len = o.Gen_Product(2, cex, 2, aey, cexaey);
	double ac[16];
	int    ac_len = o.Gen_Diff(aexcey_len, aexcey, cexaey_len, cexaey, ac);
	double bexdey[8];
	int    bexdey_len = o.Gen_Product(2, bex, 2, dey, bexdey);
	double dexbey[8];
	int    dexbey_len = o.Gen_Product(2, dex, 2, bey, dexbey);
	double bd[16];
	int    bd_len = o.Gen_Diff(bexdey_len, bexdey, dexbey_len, dexbey, bd);
	double abc1_p[32], *abc1 = abc1_p;
	int    abc1_len = o.Gen_Product_With_PreAlloc(2, aez, bc_len, bc, &abc1, 32);
	double abc2_p[32], *abc2 = abc2_p;
	int    abc2_len = o.Gen_Product_With_PreAlloc(2, bez, ac_len, ac, &abc2, 32);
	double abc3_p[32], *abc3 = abc3_p;
	int    abc3_len = o.Gen_Product_With_PreAlloc(2, cez, ab_len, ab, &abc3, 32);
	double abc4_p[32], *abc4 = abc4_p;
	int    abc4_len =
	  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 32);
	double abc_p[32], *abc = abc_p;
	int    abc_len =
	  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 32);
	double bcd1_p[32], *bcd1 = bcd1_p;
	int    bcd1_len = o.Gen_Product_With_PreAlloc(2, bez, cd_len, cd, &bcd1, 32);
	double bcd2_p[32], *bcd2 = bcd2_p;
	int    bcd2_len = o.Gen_Product_With_PreAlloc(2, cez, bd_len, bd, &bcd2, 32);
	double bcd3_p[32], *bcd3 = bcd3_p;
	int    bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 32);
	double bcd4_p[32], *bcd4 = bcd4_p;
	int    bcd4_len =
	  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 32);
	double bcd_p[32], *bcd = bcd_p;
	int    bcd_len =
	  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 32);
	double cda1_p[32], *cda1 = cda1_p;
	int    cda1_len = o.Gen_Product_With_PreAlloc(2, cez, da_len, da, &cda1, 32);
	double cda2_p[32], *cda2 = cda2_p;
	int    cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 32);
	double cda3_p[32], *cda3 = cda3_p;
	int    cda3_len = o.Gen_Product_With_PreAlloc(2, aez, cd_len, cd, &cda3, 32);
	double cda4_p[32], *cda4 = cda4_p;
	int    cda4_len =
	  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 32);
	double cda_p[32], *cda = cda_p;
	int    cda_len =
	  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 32);
	double dab1_p[32], *dab1 = dab1_p;
	int    dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 32);
	double dab2_p[32], *dab2 = dab2_p;
	int    dab2_len = o.Gen_Product_With_PreAlloc(2, aez, bd_len, bd, &dab2, 32);
	double dab3_p[32], *dab3 = dab3_p;
	int    dab3_len = o.Gen_Product_With_PreAlloc(2, bez, da_len, da, &dab3, 32);
	double dab4_p[32], *dab4 = dab4_p;
	int    dab4_len =
	  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 32);
	double dab_p[32], *dab = dab_p;
	int    dab_len =
	  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 32);
	double al1[8];
	int    al1_len = o.Gen_Product(2, aex, 2, aex, al1);
	double al2[8];
	int    al2_len = o.Gen_Product(2, aey, 2, aey, al2);
	double al3[8];
	int    al3_len = o.Gen_Product(2, aez, 2, aez, al3);
	double al4[16];
	int    al4_len = o.Gen_Sum(al1_len, al1, al2_len, al2, al4);
	double alift[24];
	int    alift_len = o.Gen_Sum(al4_len, al4, al3_len, al3, alift);
	double walift[26];
	int    walift_len = o.Gen_Diff(alift_len, alift, 2, wae, walift);
	double bl1[8];
	int    bl1_len = o.Gen_Product(2, bex, 2, bex, bl1);
	double bl2[8];
	int    bl2_len = o.Gen_Product(2, bey, 2, bey, bl2);
	double bl3[8];
	int    bl3_len = o.Gen_Product(2, bez, 2, bez, bl3);
	double bl4[16];
	int    bl4_len = o.Gen_Sum(bl1_len, bl1, bl2_len, bl2, bl4);
	double blift[24];
	int    blift_len = o.Gen_Sum(bl4_len, bl4, bl3_len, bl3, blift);
	double wblift[26];
	int    wblift_len = o.Gen_Diff(blift_len, blift, 2, wbe, wblift);
	double cl1[8];
	int    cl1_len = o.Gen_Product(2, cex, 2, cex, cl1);
	double cl2[8];
	int    cl2_len = o.Gen_Product(2, cey, 2, cey, cl2);
	double cl3[8];
	int    cl3_len = o.Gen_Product(2, cez, 2, cez, cl3);
	double cl4[16];
	int    cl4_len = o.Gen_Sum(cl1_len, cl1, cl2_len, cl2, cl4);
	double clift[24];
	int    clift_len = o.Gen_Sum(cl4_len, cl4, cl3_len, cl3, clift);
	double wclift[26];
	int    wclift_len = o.Gen_Diff(clift_len, clift, 2, wce, wclift);
	double dl1[8];
	int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
	double dl2[8];
	int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
	double dl3[8];
	int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
	double dl4[16];
	int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
	double dlift[24];
	int    dlift_len = o.Gen_Sum(dl4_len, dl4, dl3_len, dl3, dlift);
	double wdlift[26];
	int    wdlift_len = o.Gen_Diff(dlift_len, dlift, 2, wde, wdlift);
	double ds1_p[32], *ds1 = ds1_p;
	int    ds1_len =
	  o.Gen_Product_With_PreAlloc(wdlift_len, wdlift, abc_len, abc, &ds1, 32);
	double ds2_p[32], *ds2 = ds2_p;
	int    ds2_len =
	  o.Gen_Product_With_PreAlloc(wclift_len, wclift, dab_len, dab, &ds2, 32);
	double dl_p[32], *dl = dl_p;
	int    dl_len = o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1_len, ds1, &dl, 32);
	double dr1_p[32], *dr1 = dr1_p;
	int    dr1_len =
	  o.Gen_Product_With_PreAlloc(wblift_len, wblift, cda_len, cda, &dr1, 32);
	double dr2_p[32], *dr2 = dr2_p;
	int    dr2_len =
	  o.Gen_Product_With_PreAlloc(walift_len, walift, bcd_len, bcd, &dr2, 32);
	double dr_p[32], *dr = dr_p;
	int    dr_len = o.Gen_Diff_With_PreAlloc(dr2_len, dr2, dr1_len, dr1, &dr, 32);
	double det_p[32], *det = det_p;
	int    det_len = o.Gen_Sum_With_PreAlloc(dl_len, dl, dr_len, dr, &det, 32);

	double return_value = det[det_len - 1];
	if (det_p != det)
		FreeDoubles(det);
	if (dr_p != dr)
		FreeDoubles(dr);
	if (dr2_p != dr2)
		FreeDoubles(dr2);
	if (dr1_p != dr1)
		FreeDoubles(dr1);
	if (dl_p != dl)
		FreeDoubles(dl);
	if (ds2_p != ds2)
		FreeDoubles(ds2);
	if (ds1_p != ds1)
		FreeDoubles(ds1);
	if (dab_p != dab)
		FreeDoubles(dab);
	if (dab4_p != dab4)
		FreeDoubles(dab4);
	if (dab3_p != dab3)
		FreeDoubles(dab3);
	if (dab2_p != dab2)
		FreeDoubles(dab2);
	if (dab1_p != dab1)
		FreeDoubles(dab1);
	if (cda_p != cda)
		FreeDoubles(cda);
	if (cda4_p != cda4)
		FreeDoubles(cda4);
	if (cda3_p != cda3)
		FreeDoubles(cda3);
	if (cda2_p != cda2)
		FreeDoubles(cda2);
	if (cda1_p != cda1)
		FreeDoubles(cda1);
	if (bcd_p != bcd)
		FreeDoubles(bcd);
	if (bcd4_p != bcd4)
		FreeDoubles(bcd4);
	if (bcd3_p != bcd3)
		FreeDoubles(bcd3);
	if (bcd2_p != bcd2)
		FreeDoubles(bcd2);
	if (bcd1_p != bcd1)
		FreeDoubles(bcd1);
	if (abc_p != abc)
		FreeDoubles(abc);
	if (abc4_p != abc4)
		FreeDoubles(abc4);
	if (abc3_p != abc3)
		FreeDoubles(abc3);
	if (abc2_p != abc2)
		FreeDoubles(abc2);
	if (abc1_p != abc1)
		FreeDoubles(abc1);

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inPowerSphere(double pax, double pay, double paz, double pbx, double pby,
                   double pbz, double pcx, double pcy, double pcz, double pdx,
                   double pdy, double pdz, double pex, double pey, double pez,
                   double wa, double wb, double wc, double wd, double we)
{
	Sign ret;
	ret = inPowerSphere_filtered(pax, pay, paz, pbx, pby, pbz, pcx, pcy, pcz, pdx,
	                             pdy, pdz, pex, pey, pez, wa, wb, wc, wd, we);
	if (is_sign_reliable(ret))
		return ret;
	ret =
	  inPowerSphere_interval<IT>(pax, pay, paz, pbx, pby, pbz, pcx, pcy, pcz, pdx,
	                             pdy, pdz, pex, pey, pez, wa, wb, wc, wd, we);
	if (is_sign_reliable(ret))
		return ret;
	return inPowerSphere_expansion(pax, pay, paz, pbx, pby, pbz, pcx, pcy, pcz,
	                               pdx, pdy, pdz, pex, pey, pez, wa, wb, wc, wd,
	                               we);
}

template <typename IT, typename ET>
Sign inPowerSphere(const GenericPoint3T<IT, ET> &pa,
                   const GenericPoint3T<IT, ET> &pb,
                   const GenericPoint3T<IT, ET> &pc,
                   const GenericPoint3T<IT, ET> &pd,
                   const GenericPoint3T<IT, ET> &pe, double wa, double wb,
                   double wc, double wd, double we)
{
	return inPowerSphere<IT, ET>(pa.x(), pa.y(), pa.z(), pb.x(), pb.y(), pb.z(),
	                             pc.x(), pc.y(), pc.z(), pd.x(), pd.y(), pd.z(),
	                             pe.x(), pe.y(), pe.z(), wa, wb, wc, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE_interval(const GenericPoint3T<IT, ET> &p1, IT pbx,
                                  IT pby, IT pbz, IT pcx, IT pcy, IT pcz,
                                  IT pdx, IT pdy, IT pdz, IT pex, IT pey,
                                  IT pez, IT w1, IT wb, IT wc, IT wd, IT we)
{
	IT l1x, l1y, l1z, d1;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd      = pex * d1;
	IT peyd      = pey * d1;
	IT pezd      = pez * d1;
	IT aex       = l1x - pexd;
	IT aey       = l1y - peyd;
	IT aez       = l1z - pezd;
	IT bex       = pbx - pex;
	IT bey       = pby - pey;
	IT bez       = pbz - pez;
	IT cex       = pcx - pex;
	IT cey       = pcy - pey;
	IT cez       = pcz - pez;
	IT dex       = pdx - pex;
	IT dey       = pdy - pey;
	IT dez       = pdz - pez;
	IT w1e       = w1 - we;
	IT wbe       = wb - we;
	IT wce       = wc - we;
	IT wde       = wd - we;
	IT d1sqr     = d1 * d1;
	IT w1e_d1sqr = w1e * d1sqr;
	IT aexbey    = aex * bey;
	IT bexaey    = bex * aey;
	IT ab        = aexbey - bexaey;
	IT bexcey    = bex * cey;
	IT cexbey    = cex * bey;
	IT bc        = bexcey - cexbey;
	IT cexdey    = cex * dey;
	IT dexcey    = dex * cey;
	IT cd        = cexdey - dexcey;
	IT dexaey    = dex * aey;
	IT aexdey    = aex * dey;
	IT da        = dexaey - aexdey;
	IT aexcey    = aex * cey;
	IT cexaey    = cex * aey;
	IT ac        = aexcey - cexaey;
	IT bexdey    = bex * dey;
	IT dexbey    = dex * bey;
	IT bd        = bexdey - dexbey;
	IT abc1      = aez * bc;
	IT abc2      = bez * ac;
	IT abc3      = cez * ab;
	IT abc4      = abc1 + abc3;
	IT abc       = abc4 - abc2;
	IT bcd1      = bez * cd;
	IT bcd2      = cez * bd;
	IT bcd3      = dez * bc;
	IT bcd4      = bcd1 + bcd3;
	IT bcd       = bcd4 - bcd2;
	IT cda1      = cez * da;
	IT cda2      = dez * ac;
	IT cda3      = aez * cd;
	IT cda4      = cda1 + cda3;
	IT cda       = cda4 + cda2;
	IT dab1      = dez * ab;
	IT dab2      = aez * bd;
	IT dab3      = bez * da;
	IT dab4      = dab1 + dab3;
	IT dab       = dab4 + dab2;
	IT al1       = aex * aex;
	IT al2       = aey * aey;
	IT al3       = aez * aez;
	IT al4       = al1 + al2;
	IT alift     = al4 + al3;
	IT walift    = alift - w1e_d1sqr;
	IT bl1       = bex * bex;
	IT bl2       = bey * bey;
	IT bl3       = bez * bez;
	IT bl4       = bl1 + bl2;
	IT blift     = bl4 + bl3;
	IT wblift    = blift - wbe;
	IT cl1       = cex * cex;
	IT cl2       = cey * cey;
	IT cl3       = cez * cez;
	IT cl4       = cl1 + cl2;
	IT clift     = cl4 + cl3;
	IT wclift    = clift - wce;
	IT dl1       = dex * dex;
	IT dl2       = dey * dey;
	IT dl3       = dez * dez;
	IT dl4       = dl1 + dl2;
	IT dlift     = dl4 + dl3;
	IT wdlift    = dlift - wde;
	IT ds1       = wdlift * abc;
	IT ds2       = wclift * dab;
	IT dlp       = ds2 - ds1;
	IT dl        = dlp * d1;
	IT dr1p      = wblift * cda;
	IT dr1       = dr1p * d1;
	IT dr2       = walift * bcd;
	IT dr        = dr2 - dr1;
	IT det       = dl + dr;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE_exact(const GenericPoint3T<IT, ET> &p1, ET pbx, ET pby,
                               ET pbz, ET pcx, ET pcy, ET pcz, ET pdx, ET pdy,
                               ET pdz, ET pex, ET pey, ET pez, ET w1, ET wb,
                               ET wc, ET wd, ET we)
{
	ET l1x, l1y, l1z, d1;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	ET pexd      = pex * d1;
	ET peyd      = pey * d1;
	ET pezd      = pez * d1;
	ET aex       = l1x - pexd;
	ET aey       = l1y - peyd;
	ET aez       = l1z - pezd;
	ET bex       = pbx - pex;
	ET bey       = pby - pey;
	ET bez       = pbz - pez;
	ET cex       = pcx - pex;
	ET cey       = pcy - pey;
	ET cez       = pcz - pez;
	ET dex       = pdx - pex;
	ET dey       = pdy - pey;
	ET dez       = pdz - pez;
	ET w1e       = w1 - we;
	ET wbe       = wb - we;
	ET wce       = wc - we;
	ET wde       = wd - we;
	ET d1sqr     = d1 * d1;
	ET w1e_d1sqr = w1e * d1sqr;
	ET aexbey    = aex * bey;
	ET bexaey    = bex * aey;
	ET ab        = aexbey - bexaey;
	ET bexcey    = bex * cey;
	ET cexbey    = cex * bey;
	ET bc        = bexcey - cexbey;
	ET cexdey    = cex * dey;
	ET dexcey    = dex * cey;
	ET cd        = cexdey - dexcey;
	ET dexaey    = dex * aey;
	ET aexdey    = aex * dey;
	ET da        = dexaey - aexdey;
	ET aexcey    = aex * cey;
	ET cexaey    = cex * aey;
	ET ac        = aexcey - cexaey;
	ET bexdey    = bex * dey;
	ET dexbey    = dex * bey;
	ET bd        = bexdey - dexbey;
	ET abc1      = aez * bc;
	ET abc2      = bez * ac;
	ET abc3      = cez * ab;
	ET abc4      = abc1 + abc3;
	ET abc       = abc4 - abc2;
	ET bcd1      = bez * cd;
	ET bcd2      = cez * bd;
	ET bcd3      = dez * bc;
	ET bcd4      = bcd1 + bcd3;
	ET bcd       = bcd4 - bcd2;
	ET cda1      = cez * da;
	ET cda2      = dez * ac;
	ET cda3      = aez * cd;
	ET cda4      = cda1 + cda3;
	ET cda       = cda4 + cda2;
	ET dab1      = dez * ab;
	ET dab2      = aez * bd;
	ET dab3      = bez * da;
	ET dab4      = dab1 + dab3;
	ET dab       = dab4 + dab2;
	ET al1       = aex * aex;
	ET al2       = aey * aey;
	ET al3       = aez * aez;
	ET al4       = al1 + al2;
	ET alift     = al4 + al3;
	ET walift    = alift - w1e_d1sqr;
	ET bl1       = bex * bex;
	ET bl2       = bey * bey;
	ET bl3       = bez * bez;
	ET bl4       = bl1 + bl2;
	ET blift     = bl4 + bl3;
	ET wblift    = blift - wbe;
	ET cl1       = cex * cex;
	ET cl2       = cey * cey;
	ET cl3       = cez * cez;
	ET cl4       = cl1 + cl2;
	ET clift     = cl4 + cl3;
	ET wclift    = clift - wce;
	ET dl1       = dex * dex;
	ET dl2       = dey * dey;
	ET dl3       = dez * dez;
	ET dl4       = dl1 + dl2;
	ET dlift     = dl4 + dl3;
	ET wdlift    = dlift - wde;
	ET ds1       = wdlift * abc;
	ET ds2       = wclift * dab;
	ET dlp       = ds2 - ds1;
	ET dl        = dlp * d1;
	ET dr1p      = wblift * cda;
	ET dr1       = dr1p * d1;
	ET dr2       = walift * bcd;
	ET dr        = dr2 - dr1;
	ET det       = dl + dr;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE_expansion(const GenericPoint3T<IT, ET> &p1, double pbx,
                                   double pby, double pbz, double pcx,
                                   double pcy, double pcz, double pdx,
                                   double pdy, double pdz, double pex,
                                   double pey, double pez, double w1, double wb,
                                   double wc, double wd, double we)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16], *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16],
	                  *l1z = l1z_p, d1_p[16], *d1 = d1_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	if ((d1[d1_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double bex[2];
		o.Two_Diff(pbx, pex, bex);
		double bey[2];
		o.Two_Diff(pby, pey, bey);
		double bez[2];
		o.Two_Diff(pbz, pez, bez);
		double cex[2];
		o.Two_Diff(pcx, pex, cex);
		double cey[2];
		o.Two_Diff(pcy, pey, cey);
		double cez[2];
		o.Two_Diff(pcz, pez, cez);
		double dex[2];
		o.Two_Diff(pdx, pex, dex);
		double dey[2];
		o.Two_Diff(pdy, pey, dey);
		double dez[2];
		o.Two_Diff(pdz, pez, dez);
		double w1e[2];
		o.Two_Diff(w1, we, w1e);
		double wbe[2];
		o.Two_Diff(wb, we, wbe);
		double wce[2];
		o.Two_Diff(wc, we, wce);
		double wde[2];
		o.Two_Diff(wd, we, wde);
		double d1sqr_p[16], *d1sqr = d1sqr_p;
		int    d1sqr_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, d1_len, d1, &d1sqr, 16);
		double w1e_d1sqr_p[16], *w1e_d1sqr = w1e_d1sqr_p;
		int    w1e_d1sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w1e, d1sqr_len, d1sqr, &w1e_d1sqr, 16);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(2, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey[8];
		int    bexcey_len = o.Gen_Product(2, bex, 2, cey, bexcey);
		double cexbey[8];
		int    cexbey_len = o.Gen_Product(2, cex, 2, bey, cexbey);
		double bc[16];
		int    bc_len = o.Gen_Diff(bexcey_len, bexcey, cexbey_len, cexbey, bc);
		double cexdey[8];
		int    cexdey_len = o.Gen_Product(2, cex, 2, dey, cexdey);
		double dexcey[8];
		int    dexcey_len = o.Gen_Product(2, dex, 2, cey, dexcey);
		double cd[16];
		int    cd_len = o.Gen_Diff(cexdey_len, cexdey, dexcey_len, dexcey, cd);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(2, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey[8];
		int    bexdey_len = o.Gen_Product(2, bex, 2, dey, bexdey);
		double dexbey[8];
		int    dexbey_len = o.Gen_Product(2, dex, 2, bey, dexbey);
		double bd[16];
		int    bd_len = o.Gen_Diff(bexdey_len, bexdey, dexbey_len, dexbey, bd);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int abc2_len = o.Gen_Product_With_PreAlloc(2, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int abc3_len = o.Gen_Product_With_PreAlloc(2, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int bcd1_len = o.Gen_Product_With_PreAlloc(2, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int bcd2_len = o.Gen_Product_With_PreAlloc(2, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int cda1_len = o.Gen_Product_With_PreAlloc(2, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int dab3_len = o.Gen_Product_With_PreAlloc(2, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double walift_p[16], *walift = walift_p;
		int walift_len = o.Gen_Diff_With_PreAlloc(alift_len, alift, w1e_d1sqr_len,
		                                          w1e_d1sqr, &walift, 16);
		double bl1[8];
		int    bl1_len = o.Gen_Product(2, bex, 2, bex, bl1);
		double bl2[8];
		int    bl2_len = o.Gen_Product(2, bey, 2, bey, bl2);
		double bl3[8];
		int    bl3_len = o.Gen_Product(2, bez, 2, bez, bl3);
		double bl4[16];
		int    bl4_len = o.Gen_Sum(bl1_len, bl1, bl2_len, bl2, bl4);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double wblift_p[16], *wblift = wblift_p;
		int    wblift_len =
		  o.Gen_Diff_With_PreAlloc(blift_len, blift, 2, wbe, &wblift, 16);
		double cl1[8];
		int    cl1_len = o.Gen_Product(2, cex, 2, cex, cl1);
		double cl2[8];
		int    cl2_len = o.Gen_Product(2, cey, 2, cey, cl2);
		double cl3[8];
		int    cl3_len = o.Gen_Product(2, cez, 2, cez, cl3);
		double cl4[16];
		int    cl4_len = o.Gen_Sum(cl1_len, cl1, cl2_len, cl2, cl4);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double wclift_p[16], *wclift = wclift_p;
		int    wclift_len =
		  o.Gen_Diff_With_PreAlloc(clift_len, clift, 2, wce, &wclift, 16);
		double dl1[8];
		int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
		double dl2[8];
		int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
		double dl3[8];
		int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
		double dl4[16];
		int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double wdlift_p[16], *wdlift = wdlift_p;
		int    wdlift_len =
		  o.Gen_Diff_With_PreAlloc(dlift_len, dlift, 2, wde, &wdlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(wdlift_len, wdlift, abc_len, abc, &ds1, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(wclift_len, wclift, dab_len, dab, &ds2, 16);
		double dlp_p[16], *dlp = dlp_p;
		int    dlp_len =
		  o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1_len, ds1, &dlp, 16);
		double dl_p[16], *dl = dl_p;
		int dl_len = o.Gen_Product_With_PreAlloc(dlp_len, dlp, d1_len, d1, &dl, 16);
		double dr1p_p[16], *dr1p = dr1p_p;
		int    dr1p_len =
		  o.Gen_Product_With_PreAlloc(wblift_len, wblift, cda_len, cda, &dr1p, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(dr1p_len, dr1p, d1_len, d1, &dr1, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(walift_len, walift, bcd_len, bcd, &dr2, 16);
		double dr_p[16], *dr = dr_p;
		int dr_len = o.Gen_Diff_With_PreAlloc(dr2_len, dr2, dr1_len, dr1, &dr, 16);
		double det_p[16], *det = det_p;
		int    det_len = o.Gen_Sum_With_PreAlloc(dl_len, dl, dr_len, dr, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dr1p_p != dr1p)
			FreeDoubles(dr1p);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (dlp_p != dlp)
			FreeDoubles(dlp);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (wdlift_p != wdlift)
			FreeDoubles(wdlift);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (wclift_p != wclift)
			FreeDoubles(wclift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (wblift_p != wblift)
			FreeDoubles(wblift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (walift_p != walift)
			FreeDoubles(walift);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (w1e_d1sqr_p != w1e_d1sqr)
			FreeDoubles(w1e_d1sqr);
		if (d1sqr_p != d1sqr)
			FreeDoubles(d1sqr);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inPowerSphere_IEEEE_exact<IT, ET>(p1, pbx, pby, pbz, pcx, pcy, pcz,
		                                         pdx, pdy, pdz, pex, pey, pez, w1,
		                                         wb, wc, wd, we);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE(const GenericPoint3T<IT, ET> &p1, double pbx,
                         double pby, double pbz, double pcx, double pcy,
                         double pcz, double pdx, double pdy, double pdz,
                         double pex, double pey, double pez, double w1,
                         double wb, double wc, double wd, double we)
{
	Sign ret;
	ret = inPowerSphere_IEEEE_interval<IT, ET>(p1, pbx, pby, pbz, pcx, pcy, pcz,
	                                           pdx, pdy, pdz, pex, pey, pez, w1,
	                                           wb, wc, wd, we);
	if (is_sign_reliable(ret))
		return ret;
	return inPowerSphere_IEEEE_expansion<IT, ET>(p1, pbx, pby, pbz, pcx, pcy, pcz,
	                                             pdx, pdy, pdz, pex, pey, pez, w1,
	                                             wb, wc, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IEEEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &pb,
                         const GenericPoint3T<IT, ET> &pc,
                         const GenericPoint3T<IT, ET> &pd,
                         const GenericPoint3T<IT, ET> &pe, double w1, double wb,
                         double wc, double wd, double we)
{
	return inPowerSphere_IEEEE<IT, ET>(p1, pb.x(), pb.y(), pb.z(), pc.x(), pc.y(),
	                                   pc.z(), pd.x(), pd.y(), pd.z(), pe.x(),
	                                   pe.y(), pe.z(), w1, wb, wc, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2, IT pcx,
                                  IT pcy, IT pcz, IT pdx, IT pdy, IT pdz,
                                  IT pex, IT pey, IT pez, IT w1, IT w2, IT wc,
                                  IT wd, IT we)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd      = pex * d1;
	IT peyd      = pey * d1;
	IT pezd      = pez * d1;
	IT aex       = l1x - pexd;
	IT aey       = l1y - peyd;
	IT aez       = l1z - pezd;
	IT pexd2     = pex * d2;
	IT peyd2     = pey * d2;
	IT pezd2     = pez * d2;
	IT bex       = l2x - pexd2;
	IT bey       = l2y - peyd2;
	IT bez       = l2z - pezd2;
	IT cex       = pcx - pex;
	IT cey       = pcy - pey;
	IT cez       = pcz - pez;
	IT dex       = pdx - pex;
	IT dey       = pdy - pey;
	IT dez       = pdz - pez;
	IT w1e       = w1 - we;
	IT w2e       = w2 - we;
	IT wce       = wc - we;
	IT wde       = wd - we;
	IT d1sqr     = d1 * d1;
	IT d2sqr     = d2 * d2;
	IT w1e_d1sqr = w1e * d1sqr;
	IT w2e_d2sqr = w2e * d2sqr;
	IT aexbey    = aex * bey;
	IT bexaey    = bex * aey;
	IT ab        = aexbey - bexaey;
	IT bexcey    = bex * cey;
	IT cexbey    = cex * bey;
	IT bc        = bexcey - cexbey;
	IT cexdey    = cex * dey;
	IT dexcey    = dex * cey;
	IT cd        = cexdey - dexcey;
	IT dexaey    = dex * aey;
	IT aexdey    = aex * dey;
	IT da        = dexaey - aexdey;
	IT aexcey    = aex * cey;
	IT cexaey    = cex * aey;
	IT ac        = aexcey - cexaey;
	IT bexdey    = bex * dey;
	IT dexbey    = dex * bey;
	IT bd        = bexdey - dexbey;
	IT abc1      = aez * bc;
	IT abc2      = bez * ac;
	IT abc3      = cez * ab;
	IT abc4      = abc1 + abc3;
	IT abc       = abc4 - abc2;
	IT bcd1      = bez * cd;
	IT bcd2      = cez * bd;
	IT bcd3      = dez * bc;
	IT bcd4      = bcd1 + bcd3;
	IT bcd       = bcd4 - bcd2;
	IT cda1      = cez * da;
	IT cda2      = dez * ac;
	IT cda3      = aez * cd;
	IT cda4      = cda1 + cda3;
	IT cda       = cda4 + cda2;
	IT dab1      = dez * ab;
	IT dab2      = aez * bd;
	IT dab3      = bez * da;
	IT dab4      = dab1 + dab3;
	IT dab       = dab4 + dab2;
	IT al1       = aex * aex;
	IT al2       = aey * aey;
	IT al3       = aez * aez;
	IT al4       = al1 + al2;
	IT alift     = al4 + al3;
	IT walift    = alift - w1e_d1sqr;
	IT bl1       = bex * bex;
	IT bl2       = bey * bey;
	IT bl3       = bez * bez;
	IT bl4       = bl1 + bl2;
	IT blift     = bl4 + bl3;
	IT wblift    = blift - w2e_d2sqr;
	IT cl1       = cex * cex;
	IT cl2       = cey * cey;
	IT cl3       = cez * cez;
	IT cl4       = cl1 + cl2;
	IT clift     = cl4 + cl3;
	IT wclift    = clift - wce;
	IT dl1       = dex * dex;
	IT dl2       = dey * dey;
	IT dl3       = dez * dez;
	IT dl4       = dl1 + dl2;
	IT dlift     = dl4 + dl3;
	IT wdlift    = dlift - wde;
	IT ds1       = wdlift * abc;
	IT ds2       = wclift * dab;
	IT dl        = ds2 - ds1;
	IT dll       = dl * d1;
	IT dlll      = dll * d2;
	IT dr1       = wblift * cda;
	IT dr12      = dr1 * d1;
	IT dr2       = walift * bcd;
	IT dr22      = dr2 * d2;
	IT dr        = dr22 - dr12;
	IT det       = dlll + dr;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2, ET pcx, ET pcy,
                               ET pcz, ET pdx, ET pdy, ET pdz, ET pex, ET pey,
                               ET pez, ET w1, ET w2, ET wc, ET wd, ET we)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	ET pexd      = pex * d1;
	ET peyd      = pey * d1;
	ET pezd      = pez * d1;
	ET aex       = l1x - pexd;
	ET aey       = l1y - peyd;
	ET aez       = l1z - pezd;
	ET pexd2     = pex * d2;
	ET peyd2     = pey * d2;
	ET pezd2     = pez * d2;
	ET bex       = l2x - pexd2;
	ET bey       = l2y - peyd2;
	ET bez       = l2z - pezd2;
	ET cex       = pcx - pex;
	ET cey       = pcy - pey;
	ET cez       = pcz - pez;
	ET dex       = pdx - pex;
	ET dey       = pdy - pey;
	ET dez       = pdz - pez;
	ET w1e       = w1 - we;
	ET w2e       = w2 - we;
	ET wce       = wc - we;
	ET wde       = wd - we;
	ET d1sqr     = d1 * d1;
	ET d2sqr     = d2 * d2;
	ET w1e_d1sqr = w1e * d1sqr;
	ET w2e_d2sqr = w2e * d2sqr;
	ET aexbey    = aex * bey;
	ET bexaey    = bex * aey;
	ET ab        = aexbey - bexaey;
	ET bexcey    = bex * cey;
	ET cexbey    = cex * bey;
	ET bc        = bexcey - cexbey;
	ET cexdey    = cex * dey;
	ET dexcey    = dex * cey;
	ET cd        = cexdey - dexcey;
	ET dexaey    = dex * aey;
	ET aexdey    = aex * dey;
	ET da        = dexaey - aexdey;
	ET aexcey    = aex * cey;
	ET cexaey    = cex * aey;
	ET ac        = aexcey - cexaey;
	ET bexdey    = bex * dey;
	ET dexbey    = dex * bey;
	ET bd        = bexdey - dexbey;
	ET abc1      = aez * bc;
	ET abc2      = bez * ac;
	ET abc3      = cez * ab;
	ET abc4      = abc1 + abc3;
	ET abc       = abc4 - abc2;
	ET bcd1      = bez * cd;
	ET bcd2      = cez * bd;
	ET bcd3      = dez * bc;
	ET bcd4      = bcd1 + bcd3;
	ET bcd       = bcd4 - bcd2;
	ET cda1      = cez * da;
	ET cda2      = dez * ac;
	ET cda3      = aez * cd;
	ET cda4      = cda1 + cda3;
	ET cda       = cda4 + cda2;
	ET dab1      = dez * ab;
	ET dab2      = aez * bd;
	ET dab3      = bez * da;
	ET dab4      = dab1 + dab3;
	ET dab       = dab4 + dab2;
	ET al1       = aex * aex;
	ET al2       = aey * aey;
	ET al3       = aez * aez;
	ET al4       = al1 + al2;
	ET alift     = al4 + al3;
	ET walift    = alift - w1e_d1sqr;
	ET bl1       = bex * bex;
	ET bl2       = bey * bey;
	ET bl3       = bez * bez;
	ET bl4       = bl1 + bl2;
	ET blift     = bl4 + bl3;
	ET wblift    = blift - w2e_d2sqr;
	ET cl1       = cex * cex;
	ET cl2       = cey * cey;
	ET cl3       = cez * cez;
	ET cl4       = cl1 + cl2;
	ET clift     = cl4 + cl3;
	ET wclift    = clift - wce;
	ET dl1       = dex * dex;
	ET dl2       = dey * dey;
	ET dl3       = dez * dez;
	ET dl4       = dl1 + dl2;
	ET dlift     = dl4 + dl3;
	ET wdlift    = dlift - wde;
	ET ds1       = wdlift * abc;
	ET ds2       = wclift * dab;
	ET dl        = ds2 - ds1;
	ET dll       = dl * d1;
	ET dlll      = dll * d2;
	ET dr1       = wblift * cda;
	ET dr12      = dr1 * d1;
	ET dr2       = walift * bcd;
	ET dr22      = dr2 * d2;
	ET dr        = dr22 - dr12;
	ET det       = dlll + dr;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2, double pcx,
                                   double pcy, double pcz, double pdx,
                                   double pdy, double pdz, double pex,
                                   double pey, double pez, double w1, double w2,
                                   double wc, double wd, double we)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16], *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16],
	                  *l1z = l1z_p, d1_p[16], *d1 = d1_p, l2x_p[16], *l2x = l2x_p,
	                  l2y_p[16], *l2y = l2y_p, l2z_p[16], *l2z = l2z_p, d2_p[16],
	                  *d2 = d2_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16, l2x_len = 16,
	    l2y_len = 16, l2z_len = 16, d2_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double pexd2_p[16], *pexd2 = pexd2_p;
		int    pexd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pex, &pexd2, 16);
		double peyd2_p[16], *peyd2 = peyd2_p;
		int    peyd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pey, &peyd2, 16);
		double pezd2_p[16], *pezd2 = pezd2_p;
		int    pezd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pez, &pezd2, 16);
		double bex_p[16], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pexd2_len, pexd2, &bex, 16);
		double bey_p[16], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, peyd2_len, peyd2, &bey, 16);
		double bez_p[16], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, pezd2_len, pezd2, &bez, 16);
		double cex[2];
		o.Two_Diff(pcx, pex, cex);
		double cey[2];
		o.Two_Diff(pcy, pey, cey);
		double cez[2];
		o.Two_Diff(pcz, pez, cez);
		double dex[2];
		o.Two_Diff(pdx, pex, dex);
		double dey[2];
		o.Two_Diff(pdy, pey, dey);
		double dez[2];
		o.Two_Diff(pdz, pez, dez);
		double w1e[2];
		o.Two_Diff(w1, we, w1e);
		double w2e[2];
		o.Two_Diff(w2, we, w2e);
		double wce[2];
		o.Two_Diff(wc, we, wce);
		double wde[2];
		o.Two_Diff(wd, we, wde);
		double d1sqr_p[16], *d1sqr = d1sqr_p;
		int    d1sqr_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, d1_len, d1, &d1sqr, 16);
		double d2sqr_p[16], *d2sqr = d2sqr_p;
		int    d2sqr_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, d2_len, d2, &d2sqr, 16);
		double w1e_d1sqr_p[16], *w1e_d1sqr = w1e_d1sqr_p;
		int    w1e_d1sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w1e, d1sqr_len, d1sqr, &w1e_d1sqr, 16);
		double w2e_d2sqr_p[16], *w2e_d2sqr = w2e_d2sqr_p;
		int    w2e_d2sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w2e, d2sqr_len, d2sqr, &w2e_d2sqr, 16);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey_p[16], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, 2, cey, &bexcey, 16);
		double cexbey_p[16], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(2, cex, bey_len, bey, &cexbey, 16);
		double bc_p[16], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 16);
		double cexdey[8];
		int    cexdey_len = o.Gen_Product(2, cex, 2, dey, cexdey);
		double dexcey[8];
		int    dexcey_len = o.Gen_Product(2, dex, 2, cey, dexcey);
		double cd[16];
		int    cd_len = o.Gen_Diff(cexdey_len, cexdey, dexcey_len, dexcey, cd);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(2, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey_p[16], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, 2, dey, &bexdey, 16);
		double dexbey_p[16], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, bey_len, bey, &dexbey, 16);
		double bd_p[16], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 16);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int abc3_len = o.Gen_Product_With_PreAlloc(2, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int bcd2_len = o.Gen_Product_With_PreAlloc(2, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int cda1_len = o.Gen_Product_With_PreAlloc(2, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double walift_p[16], *walift = walift_p;
		int walift_len = o.Gen_Diff_With_PreAlloc(alift_len, alift, w1e_d1sqr_len,
		                                          w1e_d1sqr, &walift, 16);
		double bl1_p[16], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 16);
		double bl2_p[16], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 16);
		double bl3_p[16], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 16);
		double bl4_p[16], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 16);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double wblift_p[16], *wblift = wblift_p;
		int wblift_len = o.Gen_Diff_With_PreAlloc(blift_len, blift, w2e_d2sqr_len,
		                                          w2e_d2sqr, &wblift, 16);
		double cl1[8];
		int    cl1_len = o.Gen_Product(2, cex, 2, cex, cl1);
		double cl2[8];
		int    cl2_len = o.Gen_Product(2, cey, 2, cey, cl2);
		double cl3[8];
		int    cl3_len = o.Gen_Product(2, cez, 2, cez, cl3);
		double cl4[16];
		int    cl4_len = o.Gen_Sum(cl1_len, cl1, cl2_len, cl2, cl4);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double wclift_p[16], *wclift = wclift_p;
		int    wclift_len =
		  o.Gen_Diff_With_PreAlloc(clift_len, clift, 2, wce, &wclift, 16);
		double dl1[8];
		int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
		double dl2[8];
		int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
		double dl3[8];
		int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
		double dl4[16];
		int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double wdlift_p[16], *wdlift = wdlift_p;
		int    wdlift_len =
		  o.Gen_Diff_With_PreAlloc(dlift_len, dlift, 2, wde, &wdlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(wdlift_len, wdlift, abc_len, abc, &ds1, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(wclift_len, wclift, dab_len, dab, &ds2, 16);
		double dl_p[16], *dl = dl_p;
		int dl_len = o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1_len, ds1, &dl, 16);
		double dll_p[16], *dll = dll_p;
		int dll_len = o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dll, 16);
		double dlll_p[16], *dlll = dlll_p;
		int    dlll_len =
		  o.Gen_Product_With_PreAlloc(dll_len, dll, d2_len, d2, &dlll, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(wblift_len, wblift, cda_len, cda, &dr1, 16);
		double dr12_p[16], *dr12 = dr12_p;
		int    dr12_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr12, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(walift_len, walift, bcd_len, bcd, &dr2, 16);
		double dr22_p[16], *dr22 = dr22_p;
		int    dr22_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr22, 16);
		double dr_p[16], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr22_len, dr22, dr12_len, dr12, &dr, 16);
		double det_p[16], *det = det_p;
		int det_len = o.Gen_Sum_With_PreAlloc(dlll_len, dlll, dr_len, dr, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr22_p != dr22)
			FreeDoubles(dr22);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr12_p != dr12)
			FreeDoubles(dr12);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dlll_p != dlll)
			FreeDoubles(dlll);
		if (dll_p != dll)
			FreeDoubles(dll);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (wdlift_p != wdlift)
			FreeDoubles(wdlift);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (wclift_p != wclift)
			FreeDoubles(wclift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (wblift_p != wblift)
			FreeDoubles(wblift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (walift_p != walift)
			FreeDoubles(walift);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (w2e_d2sqr_p != w2e_d2sqr)
			FreeDoubles(w2e_d2sqr);
		if (w1e_d1sqr_p != w1e_d1sqr)
			FreeDoubles(w1e_d1sqr);
		if (d2sqr_p != d2sqr)
			FreeDoubles(d2sqr);
		if (d1sqr_p != d1sqr)
			FreeDoubles(d1sqr);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inPowerSphere_IIEEE_exact<IT, ET>(
		  p1, p2, pcx, pcy, pcz, pdx, pdy, pdz, pex, pey, pez, w1, w2, wc, wd, we);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2, double pcx,
                         double pcy, double pcz, double pdx, double pdy,
                         double pdz, double pex, double pey, double pez,
                         double w1, double w2, double wc, double wd, double we)
{
	Sign ret;
	ret = inPowerSphere_IIEEE_interval<IT, ET>(
	  p1, p2, pcx, pcy, pcz, pdx, pdy, pdz, pex, pey, pez, w1, w2, wc, wd, we);
	if (is_sign_reliable(ret))
		return ret;
	return inPowerSphere_IIEEE_expansion<IT, ET>(
	  p1, p2, pcx, pcy, pcz, pdx, pdy, pdz, pex, pey, pez, w1, w2, wc, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIEEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &pc,
                         const GenericPoint3T<IT, ET> &pd,
                         const GenericPoint3T<IT, ET> &pe, double w1, double w2,
                         double wc, double wd, double we)
{
	return inPowerSphere_IIEEE<IT, ET>(p1, p2, pc.x(), pc.y(), pc.z(), pd.x(),
	                                   pd.y(), pd.z(), pe.x(), pe.y(), pe.z(), w1,
	                                   w2, wc, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2,
                                  const GenericPoint3T<IT, ET> &p3, IT pdx,
                                  IT pdy, IT pdz, IT pex, IT pey, IT pez, IT w1,
                                  IT w2, IT w3, IT wd, IT we)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd      = pex * d1;
	IT peyd      = pey * d1;
	IT pezd      = pez * d1;
	IT aex       = l1x - pexd;
	IT aey       = l1y - peyd;
	IT aez       = l1z - pezd;
	IT pexd2     = pex * d2;
	IT peyd2     = pey * d2;
	IT pezd2     = pez * d2;
	IT bex       = l2x - pexd2;
	IT bey       = l2y - peyd2;
	IT bez       = l2z - pezd2;
	IT pexd3     = pex * d3;
	IT peyd3     = pey * d3;
	IT pezd3     = pez * d3;
	IT cex       = l3x - pexd3;
	IT cey       = l3y - peyd3;
	IT cez       = l3z - pezd3;
	IT dex       = pdx - pex;
	IT dey       = pdy - pey;
	IT dez       = pdz - pez;
	IT w1e       = w1 - we;
	IT w2e       = w2 - we;
	IT w3e       = w3 - we;
	IT wde       = wd - we;
	IT d1sqr     = d1 * d1;
	IT d2sqr     = d2 * d2;
	IT d3sqr     = d3 * d3;
	IT w1e_d1sqr = w1e * d1sqr;
	IT w2e_d2sqr = w2e * d2sqr;
	IT w3e_d3sqr = w3e * d3sqr;
	IT aexbey    = aex * bey;
	IT bexaey    = bex * aey;
	IT ab        = aexbey - bexaey;
	IT bexcey    = bex * cey;
	IT cexbey    = cex * bey;
	IT bc        = bexcey - cexbey;
	IT cexdey    = cex * dey;
	IT dexcey    = dex * cey;
	IT cd        = cexdey - dexcey;
	IT dexaey    = dex * aey;
	IT aexdey    = aex * dey;
	IT da        = dexaey - aexdey;
	IT aexcey    = aex * cey;
	IT cexaey    = cex * aey;
	IT ac        = aexcey - cexaey;
	IT bexdey    = bex * dey;
	IT dexbey    = dex * bey;
	IT bd        = bexdey - dexbey;
	IT abc1      = aez * bc;
	IT abc2      = bez * ac;
	IT abc3      = cez * ab;
	IT abc4      = abc1 + abc3;
	IT abc       = abc4 - abc2;
	IT bcd1      = bez * cd;
	IT bcd2      = cez * bd;
	IT bcd3      = dez * bc;
	IT bcd4      = bcd1 + bcd3;
	IT bcd       = bcd4 - bcd2;
	IT cda1      = cez * da;
	IT cda2      = dez * ac;
	IT cda3      = aez * cd;
	IT cda4      = cda1 + cda3;
	IT cda       = cda4 + cda2;
	IT dab1      = dez * ab;
	IT dab2      = aez * bd;
	IT dab3      = bez * da;
	IT dab4      = dab1 + dab3;
	IT dab       = dab4 + dab2;
	IT al1       = aex * aex;
	IT al2       = aey * aey;
	IT al3       = aez * aez;
	IT al4       = al1 + al2;
	IT alift     = al4 + al3;
	IT walift    = alift - w1e_d1sqr;
	IT bl1       = bex * bex;
	IT bl2       = bey * bey;
	IT bl3       = bez * bez;
	IT bl4       = bl1 + bl2;
	IT blift     = bl4 + bl3;
	IT wblift    = blift - w2e_d2sqr;
	IT cl1       = cex * cex;
	IT cl2       = cey * cey;
	IT cl3       = cez * cez;
	IT cl4       = cl1 + cl2;
	IT clift     = cl4 + cl3;
	IT wclift    = clift - w3e_d3sqr;
	IT dl1       = dex * dex;
	IT dl2       = dey * dey;
	IT dl3       = dez * dez;
	IT dl4       = dl1 + dl2;
	IT dlift     = dl4 + dl3;
	IT wdlift    = dlift - wde;
	IT ds1       = wdlift * abc;
	IT ds1n      = ds1 * d3;
	IT ds2       = wclift * dab;
	IT dl        = ds2 - ds1n;
	IT dlm       = dl * d1;
	IT dln       = dlm * d2;
	IT dr1       = wblift * cda;
	IT dr1n      = dr1 * d1;
	IT dr2       = walift * bcd;
	IT dr2n      = dr2 * d2;
	IT dr        = dr2n - dr1n;
	IT drn       = dr * d3;
	IT det       = dln + drn;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3, ET pdx, ET pdy,
                               ET pdz, ET pex, ET pey, ET pez, ET w1, ET w2,
                               ET w3, ET wd, ET we)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	ET pexd      = pex * d1;
	ET peyd      = pey * d1;
	ET pezd      = pez * d1;
	ET aex       = l1x - pexd;
	ET aey       = l1y - peyd;
	ET aez       = l1z - pezd;
	ET pexd2     = pex * d2;
	ET peyd2     = pey * d2;
	ET pezd2     = pez * d2;
	ET bex       = l2x - pexd2;
	ET bey       = l2y - peyd2;
	ET bez       = l2z - pezd2;
	ET pexd3     = pex * d3;
	ET peyd3     = pey * d3;
	ET pezd3     = pez * d3;
	ET cex       = l3x - pexd3;
	ET cey       = l3y - peyd3;
	ET cez       = l3z - pezd3;
	ET dex       = pdx - pex;
	ET dey       = pdy - pey;
	ET dez       = pdz - pez;
	ET w1e       = w1 - we;
	ET w2e       = w2 - we;
	ET w3e       = w3 - we;
	ET wde       = wd - we;
	ET d1sqr     = d1 * d1;
	ET d2sqr     = d2 * d2;
	ET d3sqr     = d3 * d3;
	ET w1e_d1sqr = w1e * d1sqr;
	ET w2e_d2sqr = w2e * d2sqr;
	ET w3e_d3sqr = w3e * d3sqr;
	ET aexbey    = aex * bey;
	ET bexaey    = bex * aey;
	ET ab        = aexbey - bexaey;
	ET bexcey    = bex * cey;
	ET cexbey    = cex * bey;
	ET bc        = bexcey - cexbey;
	ET cexdey    = cex * dey;
	ET dexcey    = dex * cey;
	ET cd        = cexdey - dexcey;
	ET dexaey    = dex * aey;
	ET aexdey    = aex * dey;
	ET da        = dexaey - aexdey;
	ET aexcey    = aex * cey;
	ET cexaey    = cex * aey;
	ET ac        = aexcey - cexaey;
	ET bexdey    = bex * dey;
	ET dexbey    = dex * bey;
	ET bd        = bexdey - dexbey;
	ET abc1      = aez * bc;
	ET abc2      = bez * ac;
	ET abc3      = cez * ab;
	ET abc4      = abc1 + abc3;
	ET abc       = abc4 - abc2;
	ET bcd1      = bez * cd;
	ET bcd2      = cez * bd;
	ET bcd3      = dez * bc;
	ET bcd4      = bcd1 + bcd3;
	ET bcd       = bcd4 - bcd2;
	ET cda1      = cez * da;
	ET cda2      = dez * ac;
	ET cda3      = aez * cd;
	ET cda4      = cda1 + cda3;
	ET cda       = cda4 + cda2;
	ET dab1      = dez * ab;
	ET dab2      = aez * bd;
	ET dab3      = bez * da;
	ET dab4      = dab1 + dab3;
	ET dab       = dab4 + dab2;
	ET al1       = aex * aex;
	ET al2       = aey * aey;
	ET al3       = aez * aez;
	ET al4       = al1 + al2;
	ET alift     = al4 + al3;
	ET walift    = alift - w1e_d1sqr;
	ET bl1       = bex * bex;
	ET bl2       = bey * bey;
	ET bl3       = bez * bez;
	ET bl4       = bl1 + bl2;
	ET blift     = bl4 + bl3;
	ET wblift    = blift - w2e_d2sqr;
	ET cl1       = cex * cex;
	ET cl2       = cey * cey;
	ET cl3       = cez * cez;
	ET cl4       = cl1 + cl2;
	ET clift     = cl4 + cl3;
	ET wclift    = clift - w3e_d3sqr;
	ET dl1       = dex * dex;
	ET dl2       = dey * dey;
	ET dl3       = dez * dez;
	ET dl4       = dl1 + dl2;
	ET dlift     = dl4 + dl3;
	ET wdlift    = dlift - wde;
	ET ds1       = wdlift * abc;
	ET ds1n      = ds1 * d3;
	ET ds2       = wclift * dab;
	ET dl        = ds2 - ds1n;
	ET dlm       = dl * d1;
	ET dln       = dlm * d2;
	ET dr1       = wblift * cda;
	ET dr1n      = dr1 * d1;
	ET dr2       = walift * bcd;
	ET dr2n      = dr2 * d2;
	ET dr        = dr2n - dr1n;
	ET drn       = dr * d3;
	ET det       = dln + drn;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2,
                                   const GenericPoint3T<IT, ET> &p3, double pdx,
                                   double pdy, double pdz, double pex,
                                   double pey, double pez, double w1, double w2,
                                   double w3, double wd, double we)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[16], *l1x = l1x_p, l1y_p[16], *l1y = l1y_p, l1z_p[16],
	                  *l1z = l1z_p, d1_p[16], *d1 = d1_p, l2x_p[16], *l2x = l2x_p,
	                  l2y_p[16], *l2y = l2y_p, l2z_p[16], *l2z = l2z_p, d2_p[16],
	                  *d2 = d2_p, l3x_p[16], *l3x = l3x_p, l3y_p[16],
	                  *l3y = l3y_p, l3z_p[16], *l3z = l3z_p, d3_p[16], *d3 = d3_p;
	int l1x_len = 16, l1y_len = 16, l1z_len = 16, d1_len = 16, l2x_len = 16,
	    l2y_len = 16, l2z_len = 16, d2_len = 16, l3x_len = 16, l3y_len = 16,
	    l3z_len = 16, d3_len = 16;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[16], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 16);
		double peyd_p[16], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 16);
		double pezd_p[16], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 16);
		double aex_p[16], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 16);
		double aey_p[16], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 16);
		double aez_p[16], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 16);
		double pexd2_p[16], *pexd2 = pexd2_p;
		int    pexd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pex, &pexd2, 16);
		double peyd2_p[16], *peyd2 = peyd2_p;
		int    peyd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pey, &peyd2, 16);
		double pezd2_p[16], *pezd2 = pezd2_p;
		int    pezd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pez, &pezd2, 16);
		double bex_p[16], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pexd2_len, pexd2, &bex, 16);
		double bey_p[16], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, peyd2_len, peyd2, &bey, 16);
		double bez_p[16], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, pezd2_len, pezd2, &bez, 16);
		double pexd3_p[16], *pexd3 = pexd3_p;
		int    pexd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pex, &pexd3, 16);
		double peyd3_p[16], *peyd3 = peyd3_p;
		int    peyd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pey, &peyd3, 16);
		double pezd3_p[16], *pezd3 = pezd3_p;
		int    pezd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pez, &pezd3, 16);
		double cex_p[16], *cex = cex_p;
		int    cex_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, pexd3_len, pexd3, &cex, 16);
		double cey_p[16], *cey = cey_p;
		int    cey_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, peyd3_len, peyd3, &cey, 16);
		double cez_p[16], *cez = cez_p;
		int    cez_len =
		  o.Gen_Diff_With_PreAlloc(l3z_len, l3z, pezd3_len, pezd3, &cez, 16);
		double dex[2];
		o.Two_Diff(pdx, pex, dex);
		double dey[2];
		o.Two_Diff(pdy, pey, dey);
		double dez[2];
		o.Two_Diff(pdz, pez, dez);
		double w1e[2];
		o.Two_Diff(w1, we, w1e);
		double w2e[2];
		o.Two_Diff(w2, we, w2e);
		double w3e[2];
		o.Two_Diff(w3, we, w3e);
		double wde[2];
		o.Two_Diff(wd, we, wde);
		double d1sqr_p[16], *d1sqr = d1sqr_p;
		int    d1sqr_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, d1_len, d1, &d1sqr, 16);
		double d2sqr_p[16], *d2sqr = d2sqr_p;
		int    d2sqr_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, d2_len, d2, &d2sqr, 16);
		double d3sqr_p[16], *d3sqr = d3sqr_p;
		int    d3sqr_len =
		  o.Gen_Product_With_PreAlloc(d3_len, d3, d3_len, d3, &d3sqr, 16);
		double w1e_d1sqr_p[16], *w1e_d1sqr = w1e_d1sqr_p;
		int    w1e_d1sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w1e, d1sqr_len, d1sqr, &w1e_d1sqr, 16);
		double w2e_d2sqr_p[16], *w2e_d2sqr = w2e_d2sqr_p;
		int    w2e_d2sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w2e, d2sqr_len, d2sqr, &w2e_d2sqr, 16);
		double w3e_d3sqr_p[16], *w3e_d3sqr = w3e_d3sqr_p;
		int    w3e_d3sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w3e, d3sqr_len, d3sqr, &w3e_d3sqr, 16);
		double aexbey_p[16], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 16);
		double bexaey_p[16], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 16);
		double ab_p[16], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 16);
		double bexcey_p[16], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, cey_len, cey, &bexcey, 16);
		double cexbey_p[16], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, bey_len, bey, &cexbey, 16);
		double bc_p[16], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 16);
		double cexdey_p[16], *cexdey = cexdey_p;
		int    cexdey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, 2, dey, &cexdey, 16);
		double dexcey_p[16], *dexcey = dexcey_p;
		int    dexcey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, cey_len, cey, &dexcey, 16);
		double cd_p[16], *cd = cd_p;
		int    cd_len =
		  o.Gen_Diff_With_PreAlloc(cexdey_len, cexdey, dexcey_len, dexcey, &cd, 16);
		double dexaey_p[16], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, aey_len, aey, &dexaey, 16);
		double aexdey_p[16], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, 2, dey, &aexdey, 16);
		double da_p[16], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 16);
		double aexcey_p[16], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, cey_len, cey, &aexcey, 16);
		double cexaey_p[16], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, aey_len, aey, &cexaey, 16);
		double ac_p[16], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 16);
		double bexdey_p[16], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, 2, dey, &bexdey, 16);
		double dexbey_p[16], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(2, dex, bey_len, bey, &dexbey, 16);
		double bd_p[16], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 16);
		double abc1_p[16], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 16);
		double abc2_p[16], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 16);
		double abc3_p[16], *abc3 = abc3_p;
		int    abc3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, ab_len, ab, &abc3, 16);
		double abc4_p[16], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 16);
		double abc_p[16], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 16);
		double bcd1_p[16], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 16);
		double bcd2_p[16], *bcd2 = bcd2_p;
		int    bcd2_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, bd_len, bd, &bcd2, 16);
		double bcd3_p[16], *bcd3 = bcd3_p;
		int bcd3_len = o.Gen_Product_With_PreAlloc(2, dez, bc_len, bc, &bcd3, 16);
		double bcd4_p[16], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 16);
		double bcd_p[16], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 16);
		double cda1_p[16], *cda1 = cda1_p;
		int    cda1_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, da_len, da, &cda1, 16);
		double cda2_p[16], *cda2 = cda2_p;
		int cda2_len = o.Gen_Product_With_PreAlloc(2, dez, ac_len, ac, &cda2, 16);
		double cda3_p[16], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 16);
		double cda4_p[16], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 16);
		double cda_p[16], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 16);
		double dab1_p[16], *dab1 = dab1_p;
		int dab1_len = o.Gen_Product_With_PreAlloc(2, dez, ab_len, ab, &dab1, 16);
		double dab2_p[16], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 16);
		double dab3_p[16], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 16);
		double dab4_p[16], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 16);
		double dab_p[16], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 16);
		double al1_p[16], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 16);
		double al2_p[16], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 16);
		double al3_p[16], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 16);
		double al4_p[16], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 16);
		double alift_p[16], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 16);
		double walift_p[16], *walift = walift_p;
		int walift_len = o.Gen_Diff_With_PreAlloc(alift_len, alift, w1e_d1sqr_len,
		                                          w1e_d1sqr, &walift, 16);
		double bl1_p[16], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 16);
		double bl2_p[16], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 16);
		double bl3_p[16], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 16);
		double bl4_p[16], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 16);
		double blift_p[16], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 16);
		double wblift_p[16], *wblift = wblift_p;
		int wblift_len = o.Gen_Diff_With_PreAlloc(blift_len, blift, w2e_d2sqr_len,
		                                          w2e_d2sqr, &wblift, 16);
		double cl1_p[16], *cl1 = cl1_p;
		int    cl1_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, cex_len, cex, &cl1, 16);
		double cl2_p[16], *cl2 = cl2_p;
		int    cl2_len =
		  o.Gen_Product_With_PreAlloc(cey_len, cey, cey_len, cey, &cl2, 16);
		double cl3_p[16], *cl3 = cl3_p;
		int    cl3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, cez_len, cez, &cl3, 16);
		double cl4_p[16], *cl4 = cl4_p;
		int cl4_len = o.Gen_Sum_With_PreAlloc(cl1_len, cl1, cl2_len, cl2, &cl4, 16);
		double clift_p[16], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 16);
		double wclift_p[16], *wclift = wclift_p;
		int wclift_len = o.Gen_Diff_With_PreAlloc(clift_len, clift, w3e_d3sqr_len,
		                                          w3e_d3sqr, &wclift, 16);
		double dl1[8];
		int    dl1_len = o.Gen_Product(2, dex, 2, dex, dl1);
		double dl2[8];
		int    dl2_len = o.Gen_Product(2, dey, 2, dey, dl2);
		double dl3[8];
		int    dl3_len = o.Gen_Product(2, dez, 2, dez, dl3);
		double dl4[16];
		int    dl4_len = o.Gen_Sum(dl1_len, dl1, dl2_len, dl2, dl4);
		double dlift_p[16], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 16);
		double wdlift_p[16], *wdlift = wdlift_p;
		int    wdlift_len =
		  o.Gen_Diff_With_PreAlloc(dlift_len, dlift, 2, wde, &wdlift, 16);
		double ds1_p[16], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(wdlift_len, wdlift, abc_len, abc, &ds1, 16);
		double ds1n_p[16], *ds1n = ds1n_p;
		int    ds1n_len =
		  o.Gen_Product_With_PreAlloc(ds1_len, ds1, d3_len, d3, &ds1n, 16);
		double ds2_p[16], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(wclift_len, wclift, dab_len, dab, &ds2, 16);
		double dl_p[16], *dl = dl_p;
		int    dl_len =
		  o.Gen_Diff_With_PreAlloc(ds2_len, ds2, ds1n_len, ds1n, &dl, 16);
		double dlm_p[16], *dlm = dlm_p;
		int dlm_len = o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dlm, 16);
		double dln_p[16], *dln = dln_p;
		int    dln_len =
		  o.Gen_Product_With_PreAlloc(dlm_len, dlm, d2_len, d2, &dln, 16);
		double dr1_p[16], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(wblift_len, wblift, cda_len, cda, &dr1, 16);
		double dr1n_p[16], *dr1n = dr1n_p;
		int    dr1n_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr1n, 16);
		double dr2_p[16], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(walift_len, walift, bcd_len, bcd, &dr2, 16);
		double dr2n_p[16], *dr2n = dr2n_p;
		int    dr2n_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr2n, 16);
		double dr_p[16], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr2n_len, dr2n, dr1n_len, dr1n, &dr, 16);
		double drn_p[16], *drn = drn_p;
		int drn_len = o.Gen_Product_With_PreAlloc(dr_len, dr, d3_len, d3, &drn, 16);
		double det_p[16], *det = det_p;
		int det_len = o.Gen_Sum_With_PreAlloc(dln_len, dln, drn_len, drn, &det, 16);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (drn_p != drn)
			FreeDoubles(drn);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr2n_p != dr2n)
			FreeDoubles(dr2n);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr1n_p != dr1n)
			FreeDoubles(dr1n);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dln_p != dln)
			FreeDoubles(dln);
		if (dlm_p != dlm)
			FreeDoubles(dlm);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1n_p != ds1n)
			FreeDoubles(ds1n);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (wdlift_p != wdlift)
			FreeDoubles(wdlift);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (wclift_p != wclift)
			FreeDoubles(wclift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cl4_p != cl4)
			FreeDoubles(cl4);
		if (cl3_p != cl3)
			FreeDoubles(cl3);
		if (cl2_p != cl2)
			FreeDoubles(cl2);
		if (cl1_p != cl1)
			FreeDoubles(cl1);
		if (wblift_p != wblift)
			FreeDoubles(wblift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (walift_p != walift)
			FreeDoubles(walift);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (dexcey_p != dexcey)
			FreeDoubles(dexcey);
		if (cexdey_p != cexdey)
			FreeDoubles(cexdey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (w3e_d3sqr_p != w3e_d3sqr)
			FreeDoubles(w3e_d3sqr);
		if (w2e_d2sqr_p != w2e_d2sqr)
			FreeDoubles(w2e_d2sqr);
		if (w1e_d1sqr_p != w1e_d1sqr)
			FreeDoubles(w1e_d1sqr);
		if (d3sqr_p != d3sqr)
			FreeDoubles(d3sqr);
		if (d2sqr_p != d2sqr)
			FreeDoubles(d2sqr);
		if (d1sqr_p != d1sqr)
			FreeDoubles(d1sqr);
		if (cez_p != cez)
			FreeDoubles(cez);
		if (cey_p != cey)
			FreeDoubles(cey);
		if (cex_p != cex)
			FreeDoubles(cex);
		if (pezd3_p != pezd3)
			FreeDoubles(pezd3);
		if (peyd3_p != peyd3)
			FreeDoubles(peyd3);
		if (pexd3_p != pexd3)
			FreeDoubles(pexd3);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inPowerSphere_IIIEE_exact<IT, ET>(p1, p2, p3, pdx, pdy, pdz, pex,
		                                         pey, pez, w1, w2, w3, wd, we);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3, double pdx,
                         double pdy, double pdz, double pex, double pey,
                         double pez, double w1, double w2, double w3, double wd,
                         double we)
{
	Sign ret;
	ret = inPowerSphere_IIIEE_interval<IT, ET>(p1, p2, p3, pdx, pdy, pdz, pex,
	                                           pey, pez, w1, w2, w3, wd, we);
	if (is_sign_reliable(ret))
		return ret;
	return inPowerSphere_IIIEE_expansion<IT, ET>(p1, p2, p3, pdx, pdy, pdz, pex,
	                                             pey, pez, w1, w2, w3, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIEE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &pd,
                         const GenericPoint3T<IT, ET> &pe, double w1, double w2,
                         double w3, double wd, double we)
{
	return inPowerSphere_IIIEE<IT, ET>(p1, p2, p3, pd.x(), pd.y(), pd.z(), pe.x(),
	                                   pe.y(), pe.z(), w1, w2, w3, wd, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2,
                                  const GenericPoint3T<IT, ET> &p3,
                                  const GenericPoint3T<IT, ET> &p4, IT pex,
                                  IT pey, IT pez, IT w1, IT w2, IT w3, IT w4,
                                  IT we)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3) ||
	    !p4.getIntervalLambda(l4x, l4y, l4z, d4))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd      = pex * d1;
	IT peyd      = pey * d1;
	IT pezd      = pez * d1;
	IT aex       = l1x - pexd;
	IT aey       = l1y - peyd;
	IT aez       = l1z - pezd;
	IT pexd2     = pex * d2;
	IT peyd2     = pey * d2;
	IT pezd2     = pez * d2;
	IT bex       = l2x - pexd2;
	IT bey       = l2y - peyd2;
	IT bez       = l2z - pezd2;
	IT pexd3     = pex * d3;
	IT peyd3     = pey * d3;
	IT pezd3     = pez * d3;
	IT cex       = l3x - pexd3;
	IT cey       = l3y - peyd3;
	IT cez       = l3z - pezd3;
	IT pexd4     = pex * d4;
	IT peyd4     = pey * d4;
	IT pezd4     = pez * d4;
	IT dex       = l4x - pexd4;
	IT dey       = l4y - peyd4;
	IT dez       = l4z - pezd4;
	IT w1e       = w1 - we;
	IT w2e       = w2 - we;
	IT w3e       = w3 - we;
	IT w4e       = w4 - we;
	IT d1sqr     = d1 * d1;
	IT d2sqr     = d2 * d2;
	IT d3sqr     = d3 * d3;
	IT d4sqr     = d4 * d4;
	IT w1e_d1sqr = w1e * d1sqr;
	IT w2e_d2sqr = w2e * d2sqr;
	IT w3e_d3sqr = w3e * d3sqr;
	IT w4e_d4sqr = w4e * d4sqr;
	IT aexbey    = aex * bey;
	IT bexaey    = bex * aey;
	IT ab        = aexbey - bexaey;
	IT bexcey    = bex * cey;
	IT cexbey    = cex * bey;
	IT bc        = bexcey - cexbey;
	IT cexdey    = cex * dey;
	IT dexcey    = dex * cey;
	IT cd        = cexdey - dexcey;
	IT dexaey    = dex * aey;
	IT aexdey    = aex * dey;
	IT da        = dexaey - aexdey;
	IT aexcey    = aex * cey;
	IT cexaey    = cex * aey;
	IT ac        = aexcey - cexaey;
	IT bexdey    = bex * dey;
	IT dexbey    = dex * bey;
	IT bd        = bexdey - dexbey;
	IT abc1      = aez * bc;
	IT abc2      = bez * ac;
	IT abc3      = cez * ab;
	IT abc4      = abc1 + abc3;
	IT abc       = abc4 - abc2;
	IT bcd1      = bez * cd;
	IT bcd2      = cez * bd;
	IT bcd3      = dez * bc;
	IT bcd4      = bcd1 + bcd3;
	IT bcd       = bcd4 - bcd2;
	IT cda1      = cez * da;
	IT cda2      = dez * ac;
	IT cda3      = aez * cd;
	IT cda4      = cda1 + cda3;
	IT cda       = cda4 + cda2;
	IT dab1      = dez * ab;
	IT dab2      = aez * bd;
	IT dab3      = bez * da;
	IT dab4      = dab1 + dab3;
	IT dab       = dab4 + dab2;
	IT al1       = aex * aex;
	IT al2       = aey * aey;
	IT al3       = aez * aez;
	IT al4       = al1 + al2;
	IT alift     = al4 + al3;
	IT walift    = alift - w1e_d1sqr;
	IT bl1       = bex * bex;
	IT bl2       = bey * bey;
	IT bl3       = bez * bez;
	IT bl4       = bl1 + bl2;
	IT blift     = bl4 + bl3;
	IT wblift    = blift - w2e_d2sqr;
	IT cl1       = cex * cex;
	IT cl2       = cey * cey;
	IT cl3       = cez * cez;
	IT cl4       = cl1 + cl2;
	IT clift     = cl4 + cl3;
	IT wclift    = clift - w3e_d3sqr;
	IT dl1       = dex * dex;
	IT dl2       = dey * dey;
	IT dl3       = dez * dez;
	IT dl4       = dl1 + dl2;
	IT dlift     = dl4 + dl3;
	IT wdlift    = dlift - w4e_d4sqr;
	IT ds1       = wdlift * abc;
	IT ds12      = ds1 * d3;
	IT ds2       = wclift * dab;
	IT ds22      = ds2 * d4;
	IT dl        = ds22 - ds12;
	IT dlx1      = dl * d1;
	IT dlx2      = dlx1 * d2;
	IT dr1       = wblift * cda;
	IT dr12      = dr1 * d1;
	IT dr2       = walift * bcd;
	IT dr22      = dr2 * d2;
	IT dr        = dr22 - dr12;
	IT drx1      = dr * d3;
	IT drx2      = drx1 * d4;
	IT det       = dlx2 + drx2;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3,
                               const GenericPoint3T<IT, ET> &p4, ET pex, ET pey,
                               ET pez, ET w1, ET w2, ET w3, ET w4, ET we)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	p4.getExactLambda(l4x, l4y, l4z, d4);
	ET pexd      = pex * d1;
	ET peyd      = pey * d1;
	ET pezd      = pez * d1;
	ET aex       = l1x - pexd;
	ET aey       = l1y - peyd;
	ET aez       = l1z - pezd;
	ET pexd2     = pex * d2;
	ET peyd2     = pey * d2;
	ET pezd2     = pez * d2;
	ET bex       = l2x - pexd2;
	ET bey       = l2y - peyd2;
	ET bez       = l2z - pezd2;
	ET pexd3     = pex * d3;
	ET peyd3     = pey * d3;
	ET pezd3     = pez * d3;
	ET cex       = l3x - pexd3;
	ET cey       = l3y - peyd3;
	ET cez       = l3z - pezd3;
	ET pexd4     = pex * d4;
	ET peyd4     = pey * d4;
	ET pezd4     = pez * d4;
	ET dex       = l4x - pexd4;
	ET dey       = l4y - peyd4;
	ET dez       = l4z - pezd4;
	ET w1e       = w1 - we;
	ET w2e       = w2 - we;
	ET w3e       = w3 - we;
	ET w4e       = w4 - we;
	ET d1sqr     = d1 * d1;
	ET d2sqr     = d2 * d2;
	ET d3sqr     = d3 * d3;
	ET d4sqr     = d4 * d4;
	ET w1e_d1sqr = w1e * d1sqr;
	ET w2e_d2sqr = w2e * d2sqr;
	ET w3e_d3sqr = w3e * d3sqr;
	ET w4e_d4sqr = w4e * d4sqr;
	ET aexbey    = aex * bey;
	ET bexaey    = bex * aey;
	ET ab        = aexbey - bexaey;
	ET bexcey    = bex * cey;
	ET cexbey    = cex * bey;
	ET bc        = bexcey - cexbey;
	ET cexdey    = cex * dey;
	ET dexcey    = dex * cey;
	ET cd        = cexdey - dexcey;
	ET dexaey    = dex * aey;
	ET aexdey    = aex * dey;
	ET da        = dexaey - aexdey;
	ET aexcey    = aex * cey;
	ET cexaey    = cex * aey;
	ET ac        = aexcey - cexaey;
	ET bexdey    = bex * dey;
	ET dexbey    = dex * bey;
	ET bd        = bexdey - dexbey;
	ET abc1      = aez * bc;
	ET abc2      = bez * ac;
	ET abc3      = cez * ab;
	ET abc4      = abc1 + abc3;
	ET abc       = abc4 - abc2;
	ET bcd1      = bez * cd;
	ET bcd2      = cez * bd;
	ET bcd3      = dez * bc;
	ET bcd4      = bcd1 + bcd3;
	ET bcd       = bcd4 - bcd2;
	ET cda1      = cez * da;
	ET cda2      = dez * ac;
	ET cda3      = aez * cd;
	ET cda4      = cda1 + cda3;
	ET cda       = cda4 + cda2;
	ET dab1      = dez * ab;
	ET dab2      = aez * bd;
	ET dab3      = bez * da;
	ET dab4      = dab1 + dab3;
	ET dab       = dab4 + dab2;
	ET al1       = aex * aex;
	ET al2       = aey * aey;
	ET al3       = aez * aez;
	ET al4       = al1 + al2;
	ET alift     = al4 + al3;
	ET walift    = alift - w1e_d1sqr;
	ET bl1       = bex * bex;
	ET bl2       = bey * bey;
	ET bl3       = bez * bez;
	ET bl4       = bl1 + bl2;
	ET blift     = bl4 + bl3;
	ET wblift    = blift - w2e_d2sqr;
	ET cl1       = cex * cex;
	ET cl2       = cey * cey;
	ET cl3       = cez * cez;
	ET cl4       = cl1 + cl2;
	ET clift     = cl4 + cl3;
	ET wclift    = clift - w3e_d3sqr;
	ET dl1       = dex * dex;
	ET dl2       = dey * dey;
	ET dl3       = dez * dez;
	ET dl4       = dl1 + dl2;
	ET dlift     = dl4 + dl3;
	ET wdlift    = dlift - w4e_d4sqr;
	ET ds1       = wdlift * abc;
	ET ds12      = ds1 * d3;
	ET ds2       = wclift * dab;
	ET ds22      = ds2 * d4;
	ET dl        = ds22 - ds12;
	ET dlx1      = dl * d1;
	ET dlx2      = dlx1 * d2;
	ET dr1       = wblift * cda;
	ET dr12      = dr1 * d1;
	ET dr2       = walift * bcd;
	ET dr22      = dr2 * d2;
	ET dr        = dr22 - dr12;
	ET drx1      = dr * d3;
	ET drx2      = drx1 * d4;
	ET det       = dlx2 + drx2;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2,
                                   const GenericPoint3T<IT, ET> &p3,
                                   const GenericPoint3T<IT, ET> &p4, double pex,
                                   double pey, double pez, double w1, double w2,
                                   double w3, double w4, double we)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[8], *l1x = l1x_p, l1y_p[8], *l1y = l1y_p, l1z_p[8], *l1z = l1z_p,
	                 d1_p[8], *d1 = d1_p, l2x_p[8], *l2x = l2x_p, l2y_p[8],
	                 *l2y = l2y_p, l2z_p[8], *l2z = l2z_p, d2_p[8], *d2 = d2_p,
	                 l3x_p[8], *l3x = l3x_p, l3y_p[8], *l3y = l3y_p, l3z_p[8],
	                 *l3z = l3z_p, d3_p[8], *d3 = d3_p, l4x_p[8], *l4x = l4x_p,
	                 l4y_p[8], *l4y = l4y_p, l4z_p[8], *l4z = l4z_p, d4_p[8],
	                 *d4 = d4_p;
	int l1x_len = 8, l1y_len = 8, l1z_len = 8, d1_len = 8, l2x_len = 8,
	    l2y_len = 8, l2z_len = 8, d2_len = 8, l3x_len = 8, l3y_len = 8,
	    l3z_len = 8, d3_len = 8, l4x_len = 8, l4y_len = 8, l4z_len = 8,
	    d4_len = 8;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	p4.getExpansionLambda(&l4x, l4x_len, &l4y, l4y_len, &l4z, l4z_len, &d4,
	                      d4_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0) &&
	    (d4[d4_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[8], *pexd = pexd_p;
		int    pexd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pex, &pexd, 8);
		double peyd_p[8], *peyd = peyd_p;
		int    peyd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pey, &peyd, 8);
		double pezd_p[8], *pezd = pezd_p;
		int    pezd_len = o.Gen_Scale_With_PreAlloc(d1_len, d1, pez, &pezd, 8);
		double aex_p[8], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(l1x_len, l1x, pexd_len, pexd, &aex, 8);
		double aey_p[8], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(l1y_len, l1y, peyd_len, peyd, &aey, 8);
		double aez_p[8], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(l1z_len, l1z, pezd_len, pezd, &aez, 8);
		double pexd2_p[8], *pexd2 = pexd2_p;
		int    pexd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pex, &pexd2, 8);
		double peyd2_p[8], *peyd2 = peyd2_p;
		int    peyd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pey, &peyd2, 8);
		double pezd2_p[8], *pezd2 = pezd2_p;
		int    pezd2_len = o.Gen_Scale_With_PreAlloc(d2_len, d2, pez, &pezd2, 8);
		double bex_p[8], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(l2x_len, l2x, pexd2_len, pexd2, &bex, 8);
		double bey_p[8], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(l2y_len, l2y, peyd2_len, peyd2, &bey, 8);
		double bez_p[8], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(l2z_len, l2z, pezd2_len, pezd2, &bez, 8);
		double pexd3_p[8], *pexd3 = pexd3_p;
		int    pexd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pex, &pexd3, 8);
		double peyd3_p[8], *peyd3 = peyd3_p;
		int    peyd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pey, &peyd3, 8);
		double pezd3_p[8], *pezd3 = pezd3_p;
		int    pezd3_len = o.Gen_Scale_With_PreAlloc(d3_len, d3, pez, &pezd3, 8);
		double cex_p[8], *cex = cex_p;
		int    cex_len =
		  o.Gen_Diff_With_PreAlloc(l3x_len, l3x, pexd3_len, pexd3, &cex, 8);
		double cey_p[8], *cey = cey_p;
		int    cey_len =
		  o.Gen_Diff_With_PreAlloc(l3y_len, l3y, peyd3_len, peyd3, &cey, 8);
		double cez_p[8], *cez = cez_p;
		int    cez_len =
		  o.Gen_Diff_With_PreAlloc(l3z_len, l3z, pezd3_len, pezd3, &cez, 8);
		double pexd4_p[8], *pexd4 = pexd4_p;
		int    pexd4_len = o.Gen_Scale_With_PreAlloc(d4_len, d4, pex, &pexd4, 8);
		double peyd4_p[8], *peyd4 = peyd4_p;
		int    peyd4_len = o.Gen_Scale_With_PreAlloc(d4_len, d4, pey, &peyd4, 8);
		double pezd4_p[8], *pezd4 = pezd4_p;
		int    pezd4_len = o.Gen_Scale_With_PreAlloc(d4_len, d4, pez, &pezd4, 8);
		double dex_p[8], *dex = dex_p;
		int    dex_len =
		  o.Gen_Diff_With_PreAlloc(l4x_len, l4x, pexd4_len, pexd4, &dex, 8);
		double dey_p[8], *dey = dey_p;
		int    dey_len =
		  o.Gen_Diff_With_PreAlloc(l4y_len, l4y, peyd4_len, peyd4, &dey, 8);
		double dez_p[8], *dez = dez_p;
		int    dez_len =
		  o.Gen_Diff_With_PreAlloc(l4z_len, l4z, pezd4_len, pezd4, &dez, 8);
		double w1e[2];
		o.Two_Diff(w1, we, w1e);
		double w2e[2];
		o.Two_Diff(w2, we, w2e);
		double w3e[2];
		o.Two_Diff(w3, we, w3e);
		double w4e[2];
		o.Two_Diff(w4, we, w4e);
		double d1sqr_p[8], *d1sqr = d1sqr_p;
		int    d1sqr_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, d1_len, d1, &d1sqr, 8);
		double d2sqr_p[8], *d2sqr = d2sqr_p;
		int    d2sqr_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, d2_len, d2, &d2sqr, 8);
		double d3sqr_p[8], *d3sqr = d3sqr_p;
		int    d3sqr_len =
		  o.Gen_Product_With_PreAlloc(d3_len, d3, d3_len, d3, &d3sqr, 8);
		double d4sqr_p[8], *d4sqr = d4sqr_p;
		int    d4sqr_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, d4_len, d4, &d4sqr, 8);
		double w1e_d1sqr_p[8], *w1e_d1sqr = w1e_d1sqr_p;
		int    w1e_d1sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w1e, d1sqr_len, d1sqr, &w1e_d1sqr, 8);
		double w2e_d2sqr_p[8], *w2e_d2sqr = w2e_d2sqr_p;
		int    w2e_d2sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w2e, d2sqr_len, d2sqr, &w2e_d2sqr, 8);
		double w3e_d3sqr_p[8], *w3e_d3sqr = w3e_d3sqr_p;
		int    w3e_d3sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w3e, d3sqr_len, d3sqr, &w3e_d3sqr, 8);
		double w4e_d4sqr_p[8], *w4e_d4sqr = w4e_d4sqr_p;
		int    w4e_d4sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w4e, d4sqr_len, d4sqr, &w4e_d4sqr, 8);
		double aexbey_p[8], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 8);
		double bexaey_p[8], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 8);
		double ab_p[8], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 8);
		double bexcey_p[8], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, cey_len, cey, &bexcey, 8);
		double cexbey_p[8], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, bey_len, bey, &cexbey, 8);
		double bc_p[8], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 8);
		double cexdey_p[8], *cexdey = cexdey_p;
		int    cexdey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, dey_len, dey, &cexdey, 8);
		double dexcey_p[8], *dexcey = dexcey_p;
		int    dexcey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, cey_len, cey, &dexcey, 8);
		double cd_p[8], *cd = cd_p;
		int    cd_len =
		  o.Gen_Diff_With_PreAlloc(cexdey_len, cexdey, dexcey_len, dexcey, &cd, 8);
		double dexaey_p[8], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, aey_len, aey, &dexaey, 8);
		double aexdey_p[8], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, dey_len, dey, &aexdey, 8);
		double da_p[8], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 8);
		double aexcey_p[8], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, cey_len, cey, &aexcey, 8);
		double cexaey_p[8], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, aey_len, aey, &cexaey, 8);
		double ac_p[8], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 8);
		double bexdey_p[8], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, dey_len, dey, &bexdey, 8);
		double dexbey_p[8], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, bey_len, bey, &dexbey, 8);
		double bd_p[8], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 8);
		double abc1_p[8], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 8);
		double abc2_p[8], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 8);
		double abc3_p[8], *abc3 = abc3_p;
		int    abc3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, ab_len, ab, &abc3, 8);
		double abc4_p[8], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 8);
		double abc_p[8], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 8);
		double bcd1_p[8], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 8);
		double bcd2_p[8], *bcd2 = bcd2_p;
		int    bcd2_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, bd_len, bd, &bcd2, 8);
		double bcd3_p[8], *bcd3 = bcd3_p;
		int    bcd3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, bc_len, bc, &bcd3, 8);
		double bcd4_p[8], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 8);
		double bcd_p[8], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 8);
		double cda1_p[8], *cda1 = cda1_p;
		int    cda1_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, da_len, da, &cda1, 8);
		double cda2_p[8], *cda2 = cda2_p;
		int    cda2_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ac_len, ac, &cda2, 8);
		double cda3_p[8], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 8);
		double cda4_p[8], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 8);
		double cda_p[8], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 8);
		double dab1_p[8], *dab1 = dab1_p;
		int    dab1_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ab_len, ab, &dab1, 8);
		double dab2_p[8], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 8);
		double dab3_p[8], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 8);
		double dab4_p[8], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 8);
		double dab_p[8], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 8);
		double al1_p[8], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 8);
		double al2_p[8], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 8);
		double al3_p[8], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 8);
		double al4_p[8], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 8);
		double alift_p[8], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 8);
		double walift_p[8], *walift = walift_p;
		int walift_len = o.Gen_Diff_With_PreAlloc(alift_len, alift, w1e_d1sqr_len,
		                                          w1e_d1sqr, &walift, 8);
		double bl1_p[8], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 8);
		double bl2_p[8], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 8);
		double bl3_p[8], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 8);
		double bl4_p[8], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 8);
		double blift_p[8], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 8);
		double wblift_p[8], *wblift = wblift_p;
		int wblift_len = o.Gen_Diff_With_PreAlloc(blift_len, blift, w2e_d2sqr_len,
		                                          w2e_d2sqr, &wblift, 8);
		double cl1_p[8], *cl1 = cl1_p;
		int    cl1_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, cex_len, cex, &cl1, 8);
		double cl2_p[8], *cl2 = cl2_p;
		int    cl2_len =
		  o.Gen_Product_With_PreAlloc(cey_len, cey, cey_len, cey, &cl2, 8);
		double cl3_p[8], *cl3 = cl3_p;
		int    cl3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, cez_len, cez, &cl3, 8);
		double cl4_p[8], *cl4 = cl4_p;
		int cl4_len = o.Gen_Sum_With_PreAlloc(cl1_len, cl1, cl2_len, cl2, &cl4, 8);
		double clift_p[8], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 8);
		double wclift_p[8], *wclift = wclift_p;
		int wclift_len = o.Gen_Diff_With_PreAlloc(clift_len, clift, w3e_d3sqr_len,
		                                          w3e_d3sqr, &wclift, 8);
		double dl1_p[8], *dl1 = dl1_p;
		int    dl1_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, dex_len, dex, &dl1, 8);
		double dl2_p[8], *dl2 = dl2_p;
		int    dl2_len =
		  o.Gen_Product_With_PreAlloc(dey_len, dey, dey_len, dey, &dl2, 8);
		double dl3_p[8], *dl3 = dl3_p;
		int    dl3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, dez_len, dez, &dl3, 8);
		double dl4_p[8], *dl4 = dl4_p;
		int dl4_len = o.Gen_Sum_With_PreAlloc(dl1_len, dl1, dl2_len, dl2, &dl4, 8);
		double dlift_p[8], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 8);
		double wdlift_p[8], *wdlift = wdlift_p;
		int wdlift_len = o.Gen_Diff_With_PreAlloc(dlift_len, dlift, w4e_d4sqr_len,
		                                          w4e_d4sqr, &wdlift, 8);
		double ds1_p[8], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(wdlift_len, wdlift, abc_len, abc, &ds1, 8);
		double ds12_p[8], *ds12 = ds12_p;
		int    ds12_len =
		  o.Gen_Product_With_PreAlloc(ds1_len, ds1, d3_len, d3, &ds12, 8);
		double ds2_p[8], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(wclift_len, wclift, dab_len, dab, &ds2, 8);
		double ds22_p[8], *ds22 = ds22_p;
		int    ds22_len =
		  o.Gen_Product_With_PreAlloc(ds2_len, ds2, d4_len, d4, &ds22, 8);
		double dl_p[8], *dl = dl_p;
		int    dl_len =
		  o.Gen_Diff_With_PreAlloc(ds22_len, ds22, ds12_len, ds12, &dl, 8);
		double dlx1_p[8], *dlx1 = dlx1_p;
		int    dlx1_len =
		  o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dlx1, 8);
		double dlx2_p[8], *dlx2 = dlx2_p;
		int    dlx2_len =
		  o.Gen_Product_With_PreAlloc(dlx1_len, dlx1, d2_len, d2, &dlx2, 8);
		double dr1_p[8], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(wblift_len, wblift, cda_len, cda, &dr1, 8);
		double dr12_p[8], *dr12 = dr12_p;
		int    dr12_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr12, 8);
		double dr2_p[8], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(walift_len, walift, bcd_len, bcd, &dr2, 8);
		double dr22_p[8], *dr22 = dr22_p;
		int    dr22_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr22, 8);
		double dr_p[8], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr22_len, dr22, dr12_len, dr12, &dr, 8);
		double drx1_p[8], *drx1 = drx1_p;
		int    drx1_len =
		  o.Gen_Product_With_PreAlloc(dr_len, dr, d3_len, d3, &drx1, 8);
		double drx2_p[8], *drx2 = drx2_p;
		int    drx2_len =
		  o.Gen_Product_With_PreAlloc(drx1_len, drx1, d4_len, d4, &drx2, 8);
		double det_p[8], *det = det_p;
		int    det_len =
		  o.Gen_Sum_With_PreAlloc(dlx2_len, dlx2, drx2_len, drx2, &det, 8);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (drx2_p != drx2)
			FreeDoubles(drx2);
		if (drx1_p != drx1)
			FreeDoubles(drx1);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr22_p != dr22)
			FreeDoubles(dr22);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr12_p != dr12)
			FreeDoubles(dr12);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dlx2_p != dlx2)
			FreeDoubles(dlx2);
		if (dlx1_p != dlx1)
			FreeDoubles(dlx1);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds22_p != ds22)
			FreeDoubles(ds22);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds12_p != ds12)
			FreeDoubles(ds12);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (wdlift_p != wdlift)
			FreeDoubles(wdlift);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (dl4_p != dl4)
			FreeDoubles(dl4);
		if (dl3_p != dl3)
			FreeDoubles(dl3);
		if (dl2_p != dl2)
			FreeDoubles(dl2);
		if (dl1_p != dl1)
			FreeDoubles(dl1);
		if (wclift_p != wclift)
			FreeDoubles(wclift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cl4_p != cl4)
			FreeDoubles(cl4);
		if (cl3_p != cl3)
			FreeDoubles(cl3);
		if (cl2_p != cl2)
			FreeDoubles(cl2);
		if (cl1_p != cl1)
			FreeDoubles(cl1);
		if (wblift_p != wblift)
			FreeDoubles(wblift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (walift_p != walift)
			FreeDoubles(walift);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (dexcey_p != dexcey)
			FreeDoubles(dexcey);
		if (cexdey_p != cexdey)
			FreeDoubles(cexdey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (w4e_d4sqr_p != w4e_d4sqr)
			FreeDoubles(w4e_d4sqr);
		if (w3e_d3sqr_p != w3e_d3sqr)
			FreeDoubles(w3e_d3sqr);
		if (w2e_d2sqr_p != w2e_d2sqr)
			FreeDoubles(w2e_d2sqr);
		if (w1e_d1sqr_p != w1e_d1sqr)
			FreeDoubles(w1e_d1sqr);
		if (d4sqr_p != d4sqr)
			FreeDoubles(d4sqr);
		if (d3sqr_p != d3sqr)
			FreeDoubles(d3sqr);
		if (d2sqr_p != d2sqr)
			FreeDoubles(d2sqr);
		if (d1sqr_p != d1sqr)
			FreeDoubles(d1sqr);
		if (dez_p != dez)
			FreeDoubles(dez);
		if (dey_p != dey)
			FreeDoubles(dey);
		if (dex_p != dex)
			FreeDoubles(dex);
		if (pezd4_p != pezd4)
			FreeDoubles(pezd4);
		if (peyd4_p != peyd4)
			FreeDoubles(peyd4);
		if (pexd4_p != pexd4)
			FreeDoubles(pexd4);
		if (cez_p != cez)
			FreeDoubles(cez);
		if (cey_p != cey)
			FreeDoubles(cey);
		if (cex_p != cex)
			FreeDoubles(cex);
		if (pezd3_p != pezd3)
			FreeDoubles(pezd3);
		if (peyd3_p != peyd3)
			FreeDoubles(peyd3);
		if (pexd3_p != pexd3)
			FreeDoubles(pexd3);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
		if (l4x_p != l4x)
			FreeDoubles(l4x);
		if (l4y_p != l4y)
			FreeDoubles(l4y);
		if (l4z_p != l4z)
			FreeDoubles(l4z);
		if (d4_p != d4)
			FreeDoubles(d4);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inPowerSphere_IIIIE_exact<IT, ET>(p1, p2, p3, p4, pex, pey, pez, w1,
		                                         w2, w3, w4, we);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4, double pex,
                         double pey, double pez, double w1, double w2,
                         double w3, double w4, double we)
{
	Sign ret;
	ret = inPowerSphere_IIIIE_interval<IT, ET>(p1, p2, p3, p4, pex, pey, pez, w1,
	                                           w2, w3, w4, we);
	if (is_sign_reliable(ret))
		return ret;
	return inPowerSphere_IIIIE_expansion<IT, ET>(p1, p2, p3, p4, pex, pey, pez,
	                                             w1, w2, w3, w4, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIIE(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4,
                         const GenericPoint3T<IT, ET> &pe, double w1, double w2,
                         double w3, double w4, double we)
{
	return inPowerSphere_IIIIE<IT, ET>(p1, p2, p3, p4, pe.x(), pe.y(), pe.z(), w1,
	                                   w2, w3, w4, we);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIII_interval(const GenericPoint3T<IT, ET> &p1,
                                  const GenericPoint3T<IT, ET> &p2,
                                  const GenericPoint3T<IT, ET> &p3,
                                  const GenericPoint3T<IT, ET> &p4,
                                  const GenericPoint3T<IT, ET> &p5, IT w1,
                                  IT w2, IT w3, IT w4, IT w5)
{
	IT l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4,
	  l5x, l5y, l5z, d5;
	if (!p1.getIntervalLambda(l1x, l1y, l1z, d1) ||
	    !p2.getIntervalLambda(l2x, l2y, l2z, d2) ||
	    !p3.getIntervalLambda(l3x, l3y, l3z, d3) ||
	    !p4.getIntervalLambda(l4x, l4y, l4z, d4) ||
	    !p5.getIntervalLambda(l5x, l5y, l5z, d5))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT pexd            = l5x * d1;
	IT peyd            = l5y * d1;
	IT pezd            = l5z * d1;
	IT ll1x            = l1x * d5;
	IT ll1y            = l1y * d5;
	IT ll1z            = l1z * d5;
	IT aex             = ll1x - pexd;
	IT aey             = ll1y - peyd;
	IT aez             = ll1z - pezd;
	IT pexd2           = l5x * d2;
	IT peyd2           = l5y * d2;
	IT pezd2           = l5z * d2;
	IT ll2x            = l2x * d5;
	IT ll2y            = l2y * d5;
	IT ll2z            = l2z * d5;
	IT bex             = ll2x - pexd2;
	IT bey             = ll2y - peyd2;
	IT bez             = ll2z - pezd2;
	IT pexd3           = l5x * d3;
	IT peyd3           = l5y * d3;
	IT pezd3           = l5z * d3;
	IT ll3x            = l3x * d5;
	IT ll3y            = l3y * d5;
	IT ll3z            = l3z * d5;
	IT cex             = ll3x - pexd3;
	IT cey             = ll3y - peyd3;
	IT cez             = ll3z - pezd3;
	IT pexd4           = l5x * d4;
	IT peyd4           = l5y * d4;
	IT pezd4           = l5z * d4;
	IT ll4x            = l4x * d5;
	IT ll4y            = l4y * d5;
	IT ll4z            = l4z * d5;
	IT dex             = ll4x - pexd4;
	IT dey             = ll4y - peyd4;
	IT dez             = ll4z - pezd4;
	IT w15             = w1 - w5;
	IT w25             = w2 - w5;
	IT w35             = w3 - w5;
	IT w45             = w4 - w5;
	IT d1sqr           = d1 * d1;
	IT d2sqr           = d2 * d2;
	IT d3sqr           = d3 * d3;
	IT d4sqr           = d4 * d4;
	IT d5sqr           = d5 * d5;
	IT w15_d1sqr       = w15 * d1sqr;
	IT w25_d2sqr       = w25 * d2sqr;
	IT w35_d3sqr       = w35 * d3sqr;
	IT w45_d4sqr       = w45 * d4sqr;
	IT w15_d1sqr_d5sqr = w15_d1sqr * d5sqr;
	IT w25_d2sqr_d5sqr = w25_d2sqr * d5sqr;
	IT w35_d3sqr_d5sqr = w35_d3sqr * d5sqr;
	IT w45_d4sqr_d5sqr = w45_d4sqr * d5sqr;
	IT aexbey          = aex * bey;
	IT bexaey          = bex * aey;
	IT ab              = aexbey - bexaey;
	IT bexcey          = bex * cey;
	IT cexbey          = cex * bey;
	IT bc              = bexcey - cexbey;
	IT cexdey          = cex * dey;
	IT dexcey          = dex * cey;
	IT cd              = cexdey - dexcey;
	IT dexaey          = dex * aey;
	IT aexdey          = aex * dey;
	IT da              = dexaey - aexdey;
	IT aexcey          = aex * cey;
	IT cexaey          = cex * aey;
	IT ac              = aexcey - cexaey;
	IT bexdey          = bex * dey;
	IT dexbey          = dex * bey;
	IT bd              = bexdey - dexbey;
	IT abc1            = aez * bc;
	IT abc2            = bez * ac;
	IT abc3            = cez * ab;
	IT abc4            = abc1 + abc3;
	IT abc             = abc4 - abc2;
	IT bcd1            = bez * cd;
	IT bcd2            = cez * bd;
	IT bcd3            = dez * bc;
	IT bcd4            = bcd1 + bcd3;
	IT bcd             = bcd4 - bcd2;
	IT cda1            = cez * da;
	IT cda2            = dez * ac;
	IT cda3            = aez * cd;
	IT cda4            = cda1 + cda3;
	IT cda             = cda4 + cda2;
	IT dab1            = dez * ab;
	IT dab2            = aez * bd;
	IT dab3            = bez * da;
	IT dab4            = dab1 + dab3;
	IT dab             = dab4 + dab2;
	IT al1             = aex * aex;
	IT al2             = aey * aey;
	IT al3             = aez * aez;
	IT al4             = al1 + al2;
	IT alift           = al4 + al3;
	IT walift          = alift - w15_d1sqr_d5sqr;
	IT bl1             = bex * bex;
	IT bl2             = bey * bey;
	IT bl3             = bez * bez;
	IT bl4             = bl1 + bl2;
	IT blift           = bl4 + bl3;
	IT wblift          = blift - w25_d2sqr_d5sqr;
	IT cl1             = cex * cex;
	IT cl2             = cey * cey;
	IT cl3             = cez * cez;
	IT cl4             = cl1 + cl2;
	IT clift           = cl4 + cl3;
	IT wclift          = clift - w35_d3sqr_d5sqr;
	IT dl1             = dex * dex;
	IT dl2             = dey * dey;
	IT dl3             = dez * dez;
	IT dl4             = dl1 + dl2;
	IT dlift           = dl4 + dl3;
	IT wdlift          = dlift - w45_d4sqr_d5sqr;
	IT ds1             = wdlift * abc;
	IT ds1n            = ds1 * d3;
	IT ds2             = wclift * dab;
	IT ds2n            = ds2 * d4;
	IT dl              = ds2n - ds1n;
	IT dla             = dl * d1;
	IT dlb             = dla * d2;
	IT dr1             = wblift * cda;
	IT dr1n            = dr1 * d1;
	IT dr2             = walift * bcd;
	IT dr2n            = dr2 * d2;
	IT dr              = dr2n - dr1n;
	IT dra             = dr * d3;
	IT drb             = dra * d4;
	IT det             = dlb + drb;
	if (!det.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIII_exact(const GenericPoint3T<IT, ET> &p1,
                               const GenericPoint3T<IT, ET> &p2,
                               const GenericPoint3T<IT, ET> &p3,
                               const GenericPoint3T<IT, ET> &p4,
                               const GenericPoint3T<IT, ET> &p5, ET w1, ET w2,
                               ET w3, ET w4, ET w5)
{
	ET l1x, l1y, l1z, d1, l2x, l2y, l2z, d2, l3x, l3y, l3z, d3, l4x, l4y, l4z, d4,
	  l5x, l5y, l5z, d5;
	p1.getExactLambda(l1x, l1y, l1z, d1);
	p2.getExactLambda(l2x, l2y, l2z, d2);
	p3.getExactLambda(l3x, l3y, l3z, d3);
	p4.getExactLambda(l4x, l4y, l4z, d4);
	p5.getExactLambda(l5x, l5y, l5z, d5);
	ET pexd            = l5x * d1;
	ET peyd            = l5y * d1;
	ET pezd            = l5z * d1;
	ET ll1x            = l1x * d5;
	ET ll1y            = l1y * d5;
	ET ll1z            = l1z * d5;
	ET aex             = ll1x - pexd;
	ET aey             = ll1y - peyd;
	ET aez             = ll1z - pezd;
	ET pexd2           = l5x * d2;
	ET peyd2           = l5y * d2;
	ET pezd2           = l5z * d2;
	ET ll2x            = l2x * d5;
	ET ll2y            = l2y * d5;
	ET ll2z            = l2z * d5;
	ET bex             = ll2x - pexd2;
	ET bey             = ll2y - peyd2;
	ET bez             = ll2z - pezd2;
	ET pexd3           = l5x * d3;
	ET peyd3           = l5y * d3;
	ET pezd3           = l5z * d3;
	ET ll3x            = l3x * d5;
	ET ll3y            = l3y * d5;
	ET ll3z            = l3z * d5;
	ET cex             = ll3x - pexd3;
	ET cey             = ll3y - peyd3;
	ET cez             = ll3z - pezd3;
	ET pexd4           = l5x * d4;
	ET peyd4           = l5y * d4;
	ET pezd4           = l5z * d4;
	ET ll4x            = l4x * d5;
	ET ll4y            = l4y * d5;
	ET ll4z            = l4z * d5;
	ET dex             = ll4x - pexd4;
	ET dey             = ll4y - peyd4;
	ET dez             = ll4z - pezd4;
	ET w15             = w1 - w5;
	ET w25             = w2 - w5;
	ET w35             = w3 - w5;
	ET w45             = w4 - w5;
	ET d1sqr           = d1 * d1;
	ET d2sqr           = d2 * d2;
	ET d3sqr           = d3 * d3;
	ET d4sqr           = d4 * d4;
	ET d5sqr           = d5 * d5;
	ET w15_d1sqr       = w15 * d1sqr;
	ET w25_d2sqr       = w25 * d2sqr;
	ET w35_d3sqr       = w35 * d3sqr;
	ET w45_d4sqr       = w45 * d4sqr;
	ET w15_d1sqr_d5sqr = w15_d1sqr * d5sqr;
	ET w25_d2sqr_d5sqr = w25_d2sqr * d5sqr;
	ET w35_d3sqr_d5sqr = w35_d3sqr * d5sqr;
	ET w45_d4sqr_d5sqr = w45_d4sqr * d5sqr;
	ET aexbey          = aex * bey;
	ET bexaey          = bex * aey;
	ET ab              = aexbey - bexaey;
	ET bexcey          = bex * cey;
	ET cexbey          = cex * bey;
	ET bc              = bexcey - cexbey;
	ET cexdey          = cex * dey;
	ET dexcey          = dex * cey;
	ET cd              = cexdey - dexcey;
	ET dexaey          = dex * aey;
	ET aexdey          = aex * dey;
	ET da              = dexaey - aexdey;
	ET aexcey          = aex * cey;
	ET cexaey          = cex * aey;
	ET ac              = aexcey - cexaey;
	ET bexdey          = bex * dey;
	ET dexbey          = dex * bey;
	ET bd              = bexdey - dexbey;
	ET abc1            = aez * bc;
	ET abc2            = bez * ac;
	ET abc3            = cez * ab;
	ET abc4            = abc1 + abc3;
	ET abc             = abc4 - abc2;
	ET bcd1            = bez * cd;
	ET bcd2            = cez * bd;
	ET bcd3            = dez * bc;
	ET bcd4            = bcd1 + bcd3;
	ET bcd             = bcd4 - bcd2;
	ET cda1            = cez * da;
	ET cda2            = dez * ac;
	ET cda3            = aez * cd;
	ET cda4            = cda1 + cda3;
	ET cda             = cda4 + cda2;
	ET dab1            = dez * ab;
	ET dab2            = aez * bd;
	ET dab3            = bez * da;
	ET dab4            = dab1 + dab3;
	ET dab             = dab4 + dab2;
	ET al1             = aex * aex;
	ET al2             = aey * aey;
	ET al3             = aez * aez;
	ET al4             = al1 + al2;
	ET alift           = al4 + al3;
	ET walift          = alift - w15_d1sqr_d5sqr;
	ET bl1             = bex * bex;
	ET bl2             = bey * bey;
	ET bl3             = bez * bez;
	ET bl4             = bl1 + bl2;
	ET blift           = bl4 + bl3;
	ET wblift          = blift - w25_d2sqr_d5sqr;
	ET cl1             = cex * cex;
	ET cl2             = cey * cey;
	ET cl3             = cez * cez;
	ET cl4             = cl1 + cl2;
	ET clift           = cl4 + cl3;
	ET wclift          = clift - w35_d3sqr_d5sqr;
	ET dl1             = dex * dex;
	ET dl2             = dey * dey;
	ET dl3             = dez * dez;
	ET dl4             = dl1 + dl2;
	ET dlift           = dl4 + dl3;
	ET wdlift          = dlift - w45_d4sqr_d5sqr;
	ET ds1             = wdlift * abc;
	ET ds1n            = ds1 * d3;
	ET ds2             = wclift * dab;
	ET ds2n            = ds2 * d4;
	ET dl              = ds2n - ds1n;
	ET dla             = dl * d1;
	ET dlb             = dla * d2;
	ET dr1             = wblift * cda;
	ET dr1n            = dr1 * d1;
	ET dr2             = walift * bcd;
	ET dr2n            = dr2 * d2;
	ET dr              = dr2n - dr1n;
	ET dra             = dr * d3;
	ET drb             = dra * d4;
	ET det             = dlb + drb;
	return OMC::sign(det);
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIII_expansion(const GenericPoint3T<IT, ET> &p1,
                                   const GenericPoint3T<IT, ET> &p2,
                                   const GenericPoint3T<IT, ET> &p3,
                                   const GenericPoint3T<IT, ET> &p4,
                                   const GenericPoint3T<IT, ET> &p5, double w1,
                                   double w2, double w3, double w4, double w5)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double l1x_p[8],
	  *l1x = l1x_p, l1y_p[8], *l1y = l1y_p, l1z_p[8], *l1z = l1z_p, d1_p[8],
	  *d1 = d1_p, l2x_p[8], *l2x = l2x_p, l2y_p[8], *l2y = l2y_p, l2z_p[8],
	  *l2z = l2z_p, d2_p[8], *d2 = d2_p, l3x_p[8], *l3x = l3x_p, l3y_p[8],
	  *l3y = l3y_p, l3z_p[8], *l3z = l3z_p, d3_p[8], *d3 = d3_p, l4x_p[8],
	  *l4x = l4x_p, l4y_p[8], *l4y = l4y_p, l4z_p[8], *l4z = l4z_p, d4_p[8],
	  *d4 = d4_p, l5x_p[8], *l5x = l5x_p, l5y_p[8], *l5y = l5y_p, l5z_p[8],
	  *l5z = l5z_p, d5_p[8], *d5 = d5_p;
	int l1x_len = 8, l1y_len = 8, l1z_len = 8, d1_len = 8, l2x_len = 8,
	    l2y_len = 8, l2z_len = 8, d2_len = 8, l3x_len = 8, l3y_len = 8,
	    l3z_len = 8, d3_len = 8, l4x_len = 8, l4y_len = 8, l4z_len = 8,
	    d4_len = 8, l5x_len = 8, l5y_len = 8, l5z_len = 8, d5_len = 8;
	p1.getExpansionLambda(&l1x, l1x_len, &l1y, l1y_len, &l1z, l1z_len, &d1,
	                      d1_len);
	p2.getExpansionLambda(&l2x, l2x_len, &l2y, l2y_len, &l2z, l2z_len, &d2,
	                      d2_len);
	p3.getExpansionLambda(&l3x, l3x_len, &l3y, l3y_len, &l3z, l3z_len, &d3,
	                      d3_len);
	p4.getExpansionLambda(&l4x, l4x_len, &l4y, l4y_len, &l4z, l4z_len, &d4,
	                      d4_len);
	p5.getExpansionLambda(&l5x, l5x_len, &l5y, l5y_len, &l5z, l5z_len, &d5,
	                      d5_len);
	if ((d1[d1_len - 1] != 0) && (d2[d2_len - 1] != 0) && (d3[d3_len - 1] != 0) &&
	    (d4[d4_len - 1] != 0) && (d5[d5_len - 1] != 0))
	{
		expansionObject o;
		double          pexd_p[8], *pexd = pexd_p;
		int             pexd_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d1_len, d1, &pexd, 8);
		double peyd_p[8], *peyd = peyd_p;
		int    peyd_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d1_len, d1, &peyd, 8);
		double pezd_p[8], *pezd = pezd_p;
		int    pezd_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d1_len, d1, &pezd, 8);
		double ll1x_p[8], *ll1x = ll1x_p;
		int    ll1x_len =
		  o.Gen_Product_With_PreAlloc(l1x_len, l1x, d5_len, d5, &ll1x, 8);
		double ll1y_p[8], *ll1y = ll1y_p;
		int    ll1y_len =
		  o.Gen_Product_With_PreAlloc(l1y_len, l1y, d5_len, d5, &ll1y, 8);
		double ll1z_p[8], *ll1z = ll1z_p;
		int    ll1z_len =
		  o.Gen_Product_With_PreAlloc(l1z_len, l1z, d5_len, d5, &ll1z, 8);
		double aex_p[8], *aex = aex_p;
		int    aex_len =
		  o.Gen_Diff_With_PreAlloc(ll1x_len, ll1x, pexd_len, pexd, &aex, 8);
		double aey_p[8], *aey = aey_p;
		int    aey_len =
		  o.Gen_Diff_With_PreAlloc(ll1y_len, ll1y, peyd_len, peyd, &aey, 8);
		double aez_p[8], *aez = aez_p;
		int    aez_len =
		  o.Gen_Diff_With_PreAlloc(ll1z_len, ll1z, pezd_len, pezd, &aez, 8);
		double pexd2_p[8], *pexd2 = pexd2_p;
		int    pexd2_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d2_len, d2, &pexd2, 8);
		double peyd2_p[8], *peyd2 = peyd2_p;
		int    peyd2_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d2_len, d2, &peyd2, 8);
		double pezd2_p[8], *pezd2 = pezd2_p;
		int    pezd2_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d2_len, d2, &pezd2, 8);
		double ll2x_p[8], *ll2x = ll2x_p;
		int    ll2x_len =
		  o.Gen_Product_With_PreAlloc(l2x_len, l2x, d5_len, d5, &ll2x, 8);
		double ll2y_p[8], *ll2y = ll2y_p;
		int    ll2y_len =
		  o.Gen_Product_With_PreAlloc(l2y_len, l2y, d5_len, d5, &ll2y, 8);
		double ll2z_p[8], *ll2z = ll2z_p;
		int    ll2z_len =
		  o.Gen_Product_With_PreAlloc(l2z_len, l2z, d5_len, d5, &ll2z, 8);
		double bex_p[8], *bex = bex_p;
		int    bex_len =
		  o.Gen_Diff_With_PreAlloc(ll2x_len, ll2x, pexd2_len, pexd2, &bex, 8);
		double bey_p[8], *bey = bey_p;
		int    bey_len =
		  o.Gen_Diff_With_PreAlloc(ll2y_len, ll2y, peyd2_len, peyd2, &bey, 8);
		double bez_p[8], *bez = bez_p;
		int    bez_len =
		  o.Gen_Diff_With_PreAlloc(ll2z_len, ll2z, pezd2_len, pezd2, &bez, 8);
		double pexd3_p[8], *pexd3 = pexd3_p;
		int    pexd3_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d3_len, d3, &pexd3, 8);
		double peyd3_p[8], *peyd3 = peyd3_p;
		int    peyd3_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d3_len, d3, &peyd3, 8);
		double pezd3_p[8], *pezd3 = pezd3_p;
		int    pezd3_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d3_len, d3, &pezd3, 8);
		double ll3x_p[8], *ll3x = ll3x_p;
		int    ll3x_len =
		  o.Gen_Product_With_PreAlloc(l3x_len, l3x, d5_len, d5, &ll3x, 8);
		double ll3y_p[8], *ll3y = ll3y_p;
		int    ll3y_len =
		  o.Gen_Product_With_PreAlloc(l3y_len, l3y, d5_len, d5, &ll3y, 8);
		double ll3z_p[8], *ll3z = ll3z_p;
		int    ll3z_len =
		  o.Gen_Product_With_PreAlloc(l3z_len, l3z, d5_len, d5, &ll3z, 8);
		double cex_p[8], *cex = cex_p;
		int    cex_len =
		  o.Gen_Diff_With_PreAlloc(ll3x_len, ll3x, pexd3_len, pexd3, &cex, 8);
		double cey_p[8], *cey = cey_p;
		int    cey_len =
		  o.Gen_Diff_With_PreAlloc(ll3y_len, ll3y, peyd3_len, peyd3, &cey, 8);
		double cez_p[8], *cez = cez_p;
		int    cez_len =
		  o.Gen_Diff_With_PreAlloc(ll3z_len, ll3z, pezd3_len, pezd3, &cez, 8);
		double pexd4_p[8], *pexd4 = pexd4_p;
		int    pexd4_len =
		  o.Gen_Product_With_PreAlloc(l5x_len, l5x, d4_len, d4, &pexd4, 8);
		double peyd4_p[8], *peyd4 = peyd4_p;
		int    peyd4_len =
		  o.Gen_Product_With_PreAlloc(l5y_len, l5y, d4_len, d4, &peyd4, 8);
		double pezd4_p[8], *pezd4 = pezd4_p;
		int    pezd4_len =
		  o.Gen_Product_With_PreAlloc(l5z_len, l5z, d4_len, d4, &pezd4, 8);
		double ll4x_p[8], *ll4x = ll4x_p;
		int    ll4x_len =
		  o.Gen_Product_With_PreAlloc(l4x_len, l4x, d5_len, d5, &ll4x, 8);
		double ll4y_p[8], *ll4y = ll4y_p;
		int    ll4y_len =
		  o.Gen_Product_With_PreAlloc(l4y_len, l4y, d5_len, d5, &ll4y, 8);
		double ll4z_p[8], *ll4z = ll4z_p;
		int    ll4z_len =
		  o.Gen_Product_With_PreAlloc(l4z_len, l4z, d5_len, d5, &ll4z, 8);
		double dex_p[8], *dex = dex_p;
		int    dex_len =
		  o.Gen_Diff_With_PreAlloc(ll4x_len, ll4x, pexd4_len, pexd4, &dex, 8);
		double dey_p[8], *dey = dey_p;
		int    dey_len =
		  o.Gen_Diff_With_PreAlloc(ll4y_len, ll4y, peyd4_len, peyd4, &dey, 8);
		double dez_p[8], *dez = dez_p;
		int    dez_len =
		  o.Gen_Diff_With_PreAlloc(ll4z_len, ll4z, pezd4_len, pezd4, &dez, 8);
		double w15[2];
		o.Two_Diff(w1, w5, w15);
		double w25[2];
		o.Two_Diff(w2, w5, w25);
		double w35[2];
		o.Two_Diff(w3, w5, w35);
		double w45[2];
		o.Two_Diff(w4, w5, w45);
		double d1sqr_p[8], *d1sqr = d1sqr_p;
		int    d1sqr_len =
		  o.Gen_Product_With_PreAlloc(d1_len, d1, d1_len, d1, &d1sqr, 8);
		double d2sqr_p[8], *d2sqr = d2sqr_p;
		int    d2sqr_len =
		  o.Gen_Product_With_PreAlloc(d2_len, d2, d2_len, d2, &d2sqr, 8);
		double d3sqr_p[8], *d3sqr = d3sqr_p;
		int    d3sqr_len =
		  o.Gen_Product_With_PreAlloc(d3_len, d3, d3_len, d3, &d3sqr, 8);
		double d4sqr_p[8], *d4sqr = d4sqr_p;
		int    d4sqr_len =
		  o.Gen_Product_With_PreAlloc(d4_len, d4, d4_len, d4, &d4sqr, 8);
		double d5sqr_p[8], *d5sqr = d5sqr_p;
		int    d5sqr_len =
		  o.Gen_Product_With_PreAlloc(d5_len, d5, d5_len, d5, &d5sqr, 8);
		double w15_d1sqr_p[8], *w15_d1sqr = w15_d1sqr_p;
		int    w15_d1sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w15, d1sqr_len, d1sqr, &w15_d1sqr, 8);
		double w25_d2sqr_p[8], *w25_d2sqr = w25_d2sqr_p;
		int    w25_d2sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w25, d2sqr_len, d2sqr, &w25_d2sqr, 8);
		double w35_d3sqr_p[8], *w35_d3sqr = w35_d3sqr_p;
		int    w35_d3sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w35, d3sqr_len, d3sqr, &w35_d3sqr, 8);
		double w45_d4sqr_p[8], *w45_d4sqr = w45_d4sqr_p;
		int    w45_d4sqr_len =
		  o.Gen_Product_With_PreAlloc(2, w45, d4sqr_len, d4sqr, &w45_d4sqr, 8);
		double w15_d1sqr_d5sqr_p[8], *w15_d1sqr_d5sqr = w15_d1sqr_d5sqr_p;
		int    w15_d1sqr_d5sqr_len = o.Gen_Product_With_PreAlloc(
      w15_d1sqr_len, w15_d1sqr, d5sqr_len, d5sqr, &w15_d1sqr_d5sqr, 8);
		double w25_d2sqr_d5sqr_p[8], *w25_d2sqr_d5sqr = w25_d2sqr_d5sqr_p;
		int    w25_d2sqr_d5sqr_len = o.Gen_Product_With_PreAlloc(
      w25_d2sqr_len, w25_d2sqr, d5sqr_len, d5sqr, &w25_d2sqr_d5sqr, 8);
		double w35_d3sqr_d5sqr_p[8], *w35_d3sqr_d5sqr = w35_d3sqr_d5sqr_p;
		int    w35_d3sqr_d5sqr_len = o.Gen_Product_With_PreAlloc(
      w35_d3sqr_len, w35_d3sqr, d5sqr_len, d5sqr, &w35_d3sqr_d5sqr, 8);
		double w45_d4sqr_d5sqr_p[8], *w45_d4sqr_d5sqr = w45_d4sqr_d5sqr_p;
		int    w45_d4sqr_d5sqr_len = o.Gen_Product_With_PreAlloc(
      w45_d4sqr_len, w45_d4sqr, d5sqr_len, d5sqr, &w45_d4sqr_d5sqr, 8);
		double aexbey_p[8], *aexbey = aexbey_p;
		int    aexbey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, bey_len, bey, &aexbey, 8);
		double bexaey_p[8], *bexaey = bexaey_p;
		int    bexaey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, aey_len, aey, &bexaey, 8);
		double ab_p[8], *ab = ab_p;
		int    ab_len =
		  o.Gen_Diff_With_PreAlloc(aexbey_len, aexbey, bexaey_len, bexaey, &ab, 8);
		double bexcey_p[8], *bexcey = bexcey_p;
		int    bexcey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, cey_len, cey, &bexcey, 8);
		double cexbey_p[8], *cexbey = cexbey_p;
		int    cexbey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, bey_len, bey, &cexbey, 8);
		double bc_p[8], *bc = bc_p;
		int    bc_len =
		  o.Gen_Diff_With_PreAlloc(bexcey_len, bexcey, cexbey_len, cexbey, &bc, 8);
		double cexdey_p[8], *cexdey = cexdey_p;
		int    cexdey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, dey_len, dey, &cexdey, 8);
		double dexcey_p[8], *dexcey = dexcey_p;
		int    dexcey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, cey_len, cey, &dexcey, 8);
		double cd_p[8], *cd = cd_p;
		int    cd_len =
		  o.Gen_Diff_With_PreAlloc(cexdey_len, cexdey, dexcey_len, dexcey, &cd, 8);
		double dexaey_p[8], *dexaey = dexaey_p;
		int    dexaey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, aey_len, aey, &dexaey, 8);
		double aexdey_p[8], *aexdey = aexdey_p;
		int    aexdey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, dey_len, dey, &aexdey, 8);
		double da_p[8], *da = da_p;
		int    da_len =
		  o.Gen_Diff_With_PreAlloc(dexaey_len, dexaey, aexdey_len, aexdey, &da, 8);
		double aexcey_p[8], *aexcey = aexcey_p;
		int    aexcey_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, cey_len, cey, &aexcey, 8);
		double cexaey_p[8], *cexaey = cexaey_p;
		int    cexaey_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, aey_len, aey, &cexaey, 8);
		double ac_p[8], *ac = ac_p;
		int    ac_len =
		  o.Gen_Diff_With_PreAlloc(aexcey_len, aexcey, cexaey_len, cexaey, &ac, 8);
		double bexdey_p[8], *bexdey = bexdey_p;
		int    bexdey_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, dey_len, dey, &bexdey, 8);
		double dexbey_p[8], *dexbey = dexbey_p;
		int    dexbey_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, bey_len, bey, &dexbey, 8);
		double bd_p[8], *bd = bd_p;
		int    bd_len =
		  o.Gen_Diff_With_PreAlloc(bexdey_len, bexdey, dexbey_len, dexbey, &bd, 8);
		double abc1_p[8], *abc1 = abc1_p;
		int    abc1_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bc_len, bc, &abc1, 8);
		double abc2_p[8], *abc2 = abc2_p;
		int    abc2_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, ac_len, ac, &abc2, 8);
		double abc3_p[8], *abc3 = abc3_p;
		int    abc3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, ab_len, ab, &abc3, 8);
		double abc4_p[8], *abc4 = abc4_p;
		int    abc4_len =
		  o.Gen_Sum_With_PreAlloc(abc1_len, abc1, abc3_len, abc3, &abc4, 8);
		double abc_p[8], *abc = abc_p;
		int    abc_len =
		  o.Gen_Diff_With_PreAlloc(abc4_len, abc4, abc2_len, abc2, &abc, 8);
		double bcd1_p[8], *bcd1 = bcd1_p;
		int    bcd1_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, cd_len, cd, &bcd1, 8);
		double bcd2_p[8], *bcd2 = bcd2_p;
		int    bcd2_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, bd_len, bd, &bcd2, 8);
		double bcd3_p[8], *bcd3 = bcd3_p;
		int    bcd3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, bc_len, bc, &bcd3, 8);
		double bcd4_p[8], *bcd4 = bcd4_p;
		int    bcd4_len =
		  o.Gen_Sum_With_PreAlloc(bcd1_len, bcd1, bcd3_len, bcd3, &bcd4, 8);
		double bcd_p[8], *bcd = bcd_p;
		int    bcd_len =
		  o.Gen_Diff_With_PreAlloc(bcd4_len, bcd4, bcd2_len, bcd2, &bcd, 8);
		double cda1_p[8], *cda1 = cda1_p;
		int    cda1_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, da_len, da, &cda1, 8);
		double cda2_p[8], *cda2 = cda2_p;
		int    cda2_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ac_len, ac, &cda2, 8);
		double cda3_p[8], *cda3 = cda3_p;
		int    cda3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, cd_len, cd, &cda3, 8);
		double cda4_p[8], *cda4 = cda4_p;
		int    cda4_len =
		  o.Gen_Sum_With_PreAlloc(cda1_len, cda1, cda3_len, cda3, &cda4, 8);
		double cda_p[8], *cda = cda_p;
		int    cda_len =
		  o.Gen_Sum_With_PreAlloc(cda4_len, cda4, cda2_len, cda2, &cda, 8);
		double dab1_p[8], *dab1 = dab1_p;
		int    dab1_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, ab_len, ab, &dab1, 8);
		double dab2_p[8], *dab2 = dab2_p;
		int    dab2_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, bd_len, bd, &dab2, 8);
		double dab3_p[8], *dab3 = dab3_p;
		int    dab3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, da_len, da, &dab3, 8);
		double dab4_p[8], *dab4 = dab4_p;
		int    dab4_len =
		  o.Gen_Sum_With_PreAlloc(dab1_len, dab1, dab3_len, dab3, &dab4, 8);
		double dab_p[8], *dab = dab_p;
		int    dab_len =
		  o.Gen_Sum_With_PreAlloc(dab4_len, dab4, dab2_len, dab2, &dab, 8);
		double al1_p[8], *al1 = al1_p;
		int    al1_len =
		  o.Gen_Product_With_PreAlloc(aex_len, aex, aex_len, aex, &al1, 8);
		double al2_p[8], *al2 = al2_p;
		int    al2_len =
		  o.Gen_Product_With_PreAlloc(aey_len, aey, aey_len, aey, &al2, 8);
		double al3_p[8], *al3 = al3_p;
		int    al3_len =
		  o.Gen_Product_With_PreAlloc(aez_len, aez, aez_len, aez, &al3, 8);
		double al4_p[8], *al4 = al4_p;
		int al4_len = o.Gen_Sum_With_PreAlloc(al1_len, al1, al2_len, al2, &al4, 8);
		double alift_p[8], *alift = alift_p;
		int    alift_len =
		  o.Gen_Sum_With_PreAlloc(al4_len, al4, al3_len, al3, &alift, 8);
		double walift_p[8], *walift = walift_p;
		int    walift_len = o.Gen_Diff_With_PreAlloc(
      alift_len, alift, w15_d1sqr_d5sqr_len, w15_d1sqr_d5sqr, &walift, 8);
		double bl1_p[8], *bl1 = bl1_p;
		int    bl1_len =
		  o.Gen_Product_With_PreAlloc(bex_len, bex, bex_len, bex, &bl1, 8);
		double bl2_p[8], *bl2 = bl2_p;
		int    bl2_len =
		  o.Gen_Product_With_PreAlloc(bey_len, bey, bey_len, bey, &bl2, 8);
		double bl3_p[8], *bl3 = bl3_p;
		int    bl3_len =
		  o.Gen_Product_With_PreAlloc(bez_len, bez, bez_len, bez, &bl3, 8);
		double bl4_p[8], *bl4 = bl4_p;
		int bl4_len = o.Gen_Sum_With_PreAlloc(bl1_len, bl1, bl2_len, bl2, &bl4, 8);
		double blift_p[8], *blift = blift_p;
		int    blift_len =
		  o.Gen_Sum_With_PreAlloc(bl4_len, bl4, bl3_len, bl3, &blift, 8);
		double wblift_p[8], *wblift = wblift_p;
		int    wblift_len = o.Gen_Diff_With_PreAlloc(
      blift_len, blift, w25_d2sqr_d5sqr_len, w25_d2sqr_d5sqr, &wblift, 8);
		double cl1_p[8], *cl1 = cl1_p;
		int    cl1_len =
		  o.Gen_Product_With_PreAlloc(cex_len, cex, cex_len, cex, &cl1, 8);
		double cl2_p[8], *cl2 = cl2_p;
		int    cl2_len =
		  o.Gen_Product_With_PreAlloc(cey_len, cey, cey_len, cey, &cl2, 8);
		double cl3_p[8], *cl3 = cl3_p;
		int    cl3_len =
		  o.Gen_Product_With_PreAlloc(cez_len, cez, cez_len, cez, &cl3, 8);
		double cl4_p[8], *cl4 = cl4_p;
		int cl4_len = o.Gen_Sum_With_PreAlloc(cl1_len, cl1, cl2_len, cl2, &cl4, 8);
		double clift_p[8], *clift = clift_p;
		int    clift_len =
		  o.Gen_Sum_With_PreAlloc(cl4_len, cl4, cl3_len, cl3, &clift, 8);
		double wclift_p[8], *wclift = wclift_p;
		int    wclift_len = o.Gen_Diff_With_PreAlloc(
      clift_len, clift, w35_d3sqr_d5sqr_len, w35_d3sqr_d5sqr, &wclift, 8);
		double dl1_p[8], *dl1 = dl1_p;
		int    dl1_len =
		  o.Gen_Product_With_PreAlloc(dex_len, dex, dex_len, dex, &dl1, 8);
		double dl2_p[8], *dl2 = dl2_p;
		int    dl2_len =
		  o.Gen_Product_With_PreAlloc(dey_len, dey, dey_len, dey, &dl2, 8);
		double dl3_p[8], *dl3 = dl3_p;
		int    dl3_len =
		  o.Gen_Product_With_PreAlloc(dez_len, dez, dez_len, dez, &dl3, 8);
		double dl4_p[8], *dl4 = dl4_p;
		int dl4_len = o.Gen_Sum_With_PreAlloc(dl1_len, dl1, dl2_len, dl2, &dl4, 8);
		double dlift_p[8], *dlift = dlift_p;
		int    dlift_len =
		  o.Gen_Sum_With_PreAlloc(dl4_len, dl4, dl3_len, dl3, &dlift, 8);
		double wdlift_p[8], *wdlift = wdlift_p;
		int    wdlift_len = o.Gen_Diff_With_PreAlloc(
      dlift_len, dlift, w45_d4sqr_d5sqr_len, w45_d4sqr_d5sqr, &wdlift, 8);
		double ds1_p[8], *ds1 = ds1_p;
		int    ds1_len =
		  o.Gen_Product_With_PreAlloc(wdlift_len, wdlift, abc_len, abc, &ds1, 8);
		double ds1n_p[8], *ds1n = ds1n_p;
		int    ds1n_len =
		  o.Gen_Product_With_PreAlloc(ds1_len, ds1, d3_len, d3, &ds1n, 8);
		double ds2_p[8], *ds2 = ds2_p;
		int    ds2_len =
		  o.Gen_Product_With_PreAlloc(wclift_len, wclift, dab_len, dab, &ds2, 8);
		double ds2n_p[8], *ds2n = ds2n_p;
		int    ds2n_len =
		  o.Gen_Product_With_PreAlloc(ds2_len, ds2, d4_len, d4, &ds2n, 8);
		double dl_p[8], *dl = dl_p;
		int    dl_len =
		  o.Gen_Diff_With_PreAlloc(ds2n_len, ds2n, ds1n_len, ds1n, &dl, 8);
		double dla_p[8], *dla = dla_p;
		int dla_len = o.Gen_Product_With_PreAlloc(dl_len, dl, d1_len, d1, &dla, 8);
		double dlb_p[8], *dlb = dlb_p;
		int    dlb_len =
		  o.Gen_Product_With_PreAlloc(dla_len, dla, d2_len, d2, &dlb, 8);
		double dr1_p[8], *dr1 = dr1_p;
		int    dr1_len =
		  o.Gen_Product_With_PreAlloc(wblift_len, wblift, cda_len, cda, &dr1, 8);
		double dr1n_p[8], *dr1n = dr1n_p;
		int    dr1n_len =
		  o.Gen_Product_With_PreAlloc(dr1_len, dr1, d1_len, d1, &dr1n, 8);
		double dr2_p[8], *dr2 = dr2_p;
		int    dr2_len =
		  o.Gen_Product_With_PreAlloc(walift_len, walift, bcd_len, bcd, &dr2, 8);
		double dr2n_p[8], *dr2n = dr2n_p;
		int    dr2n_len =
		  o.Gen_Product_With_PreAlloc(dr2_len, dr2, d2_len, d2, &dr2n, 8);
		double dr_p[8], *dr = dr_p;
		int    dr_len =
		  o.Gen_Diff_With_PreAlloc(dr2n_len, dr2n, dr1n_len, dr1n, &dr, 8);
		double dra_p[8], *dra = dra_p;
		int dra_len = o.Gen_Product_With_PreAlloc(dr_len, dr, d3_len, d3, &dra, 8);
		double drb_p[8], *drb = drb_p;
		int    drb_len =
		  o.Gen_Product_With_PreAlloc(dra_len, dra, d4_len, d4, &drb, 8);
		double det_p[8], *det = det_p;
		int det_len = o.Gen_Sum_With_PreAlloc(dlb_len, dlb, drb_len, drb, &det, 8);

		return_value = det[det_len - 1];
		if (det_p != det)
			FreeDoubles(det);
		if (drb_p != drb)
			FreeDoubles(drb);
		if (dra_p != dra)
			FreeDoubles(dra);
		if (dr_p != dr)
			FreeDoubles(dr);
		if (dr2n_p != dr2n)
			FreeDoubles(dr2n);
		if (dr2_p != dr2)
			FreeDoubles(dr2);
		if (dr1n_p != dr1n)
			FreeDoubles(dr1n);
		if (dr1_p != dr1)
			FreeDoubles(dr1);
		if (dlb_p != dlb)
			FreeDoubles(dlb);
		if (dla_p != dla)
			FreeDoubles(dla);
		if (dl_p != dl)
			FreeDoubles(dl);
		if (ds2n_p != ds2n)
			FreeDoubles(ds2n);
		if (ds2_p != ds2)
			FreeDoubles(ds2);
		if (ds1n_p != ds1n)
			FreeDoubles(ds1n);
		if (ds1_p != ds1)
			FreeDoubles(ds1);
		if (wdlift_p != wdlift)
			FreeDoubles(wdlift);
		if (dlift_p != dlift)
			FreeDoubles(dlift);
		if (dl4_p != dl4)
			FreeDoubles(dl4);
		if (dl3_p != dl3)
			FreeDoubles(dl3);
		if (dl2_p != dl2)
			FreeDoubles(dl2);
		if (dl1_p != dl1)
			FreeDoubles(dl1);
		if (wclift_p != wclift)
			FreeDoubles(wclift);
		if (clift_p != clift)
			FreeDoubles(clift);
		if (cl4_p != cl4)
			FreeDoubles(cl4);
		if (cl3_p != cl3)
			FreeDoubles(cl3);
		if (cl2_p != cl2)
			FreeDoubles(cl2);
		if (cl1_p != cl1)
			FreeDoubles(cl1);
		if (wblift_p != wblift)
			FreeDoubles(wblift);
		if (blift_p != blift)
			FreeDoubles(blift);
		if (bl4_p != bl4)
			FreeDoubles(bl4);
		if (bl3_p != bl3)
			FreeDoubles(bl3);
		if (bl2_p != bl2)
			FreeDoubles(bl2);
		if (bl1_p != bl1)
			FreeDoubles(bl1);
		if (walift_p != walift)
			FreeDoubles(walift);
		if (alift_p != alift)
			FreeDoubles(alift);
		if (al4_p != al4)
			FreeDoubles(al4);
		if (al3_p != al3)
			FreeDoubles(al3);
		if (al2_p != al2)
			FreeDoubles(al2);
		if (al1_p != al1)
			FreeDoubles(al1);
		if (dab_p != dab)
			FreeDoubles(dab);
		if (dab4_p != dab4)
			FreeDoubles(dab4);
		if (dab3_p != dab3)
			FreeDoubles(dab3);
		if (dab2_p != dab2)
			FreeDoubles(dab2);
		if (dab1_p != dab1)
			FreeDoubles(dab1);
		if (cda_p != cda)
			FreeDoubles(cda);
		if (cda4_p != cda4)
			FreeDoubles(cda4);
		if (cda3_p != cda3)
			FreeDoubles(cda3);
		if (cda2_p != cda2)
			FreeDoubles(cda2);
		if (cda1_p != cda1)
			FreeDoubles(cda1);
		if (bcd_p != bcd)
			FreeDoubles(bcd);
		if (bcd4_p != bcd4)
			FreeDoubles(bcd4);
		if (bcd3_p != bcd3)
			FreeDoubles(bcd3);
		if (bcd2_p != bcd2)
			FreeDoubles(bcd2);
		if (bcd1_p != bcd1)
			FreeDoubles(bcd1);
		if (abc_p != abc)
			FreeDoubles(abc);
		if (abc4_p != abc4)
			FreeDoubles(abc4);
		if (abc3_p != abc3)
			FreeDoubles(abc3);
		if (abc2_p != abc2)
			FreeDoubles(abc2);
		if (abc1_p != abc1)
			FreeDoubles(abc1);
		if (bd_p != bd)
			FreeDoubles(bd);
		if (dexbey_p != dexbey)
			FreeDoubles(dexbey);
		if (bexdey_p != bexdey)
			FreeDoubles(bexdey);
		if (ac_p != ac)
			FreeDoubles(ac);
		if (cexaey_p != cexaey)
			FreeDoubles(cexaey);
		if (aexcey_p != aexcey)
			FreeDoubles(aexcey);
		if (da_p != da)
			FreeDoubles(da);
		if (aexdey_p != aexdey)
			FreeDoubles(aexdey);
		if (dexaey_p != dexaey)
			FreeDoubles(dexaey);
		if (cd_p != cd)
			FreeDoubles(cd);
		if (dexcey_p != dexcey)
			FreeDoubles(dexcey);
		if (cexdey_p != cexdey)
			FreeDoubles(cexdey);
		if (bc_p != bc)
			FreeDoubles(bc);
		if (cexbey_p != cexbey)
			FreeDoubles(cexbey);
		if (bexcey_p != bexcey)
			FreeDoubles(bexcey);
		if (ab_p != ab)
			FreeDoubles(ab);
		if (bexaey_p != bexaey)
			FreeDoubles(bexaey);
		if (aexbey_p != aexbey)
			FreeDoubles(aexbey);
		if (w45_d4sqr_d5sqr_p != w45_d4sqr_d5sqr)
			FreeDoubles(w45_d4sqr_d5sqr);
		if (w35_d3sqr_d5sqr_p != w35_d3sqr_d5sqr)
			FreeDoubles(w35_d3sqr_d5sqr);
		if (w25_d2sqr_d5sqr_p != w25_d2sqr_d5sqr)
			FreeDoubles(w25_d2sqr_d5sqr);
		if (w15_d1sqr_d5sqr_p != w15_d1sqr_d5sqr)
			FreeDoubles(w15_d1sqr_d5sqr);
		if (w45_d4sqr_p != w45_d4sqr)
			FreeDoubles(w45_d4sqr);
		if (w35_d3sqr_p != w35_d3sqr)
			FreeDoubles(w35_d3sqr);
		if (w25_d2sqr_p != w25_d2sqr)
			FreeDoubles(w25_d2sqr);
		if (w15_d1sqr_p != w15_d1sqr)
			FreeDoubles(w15_d1sqr);
		if (d5sqr_p != d5sqr)
			FreeDoubles(d5sqr);
		if (d4sqr_p != d4sqr)
			FreeDoubles(d4sqr);
		if (d3sqr_p != d3sqr)
			FreeDoubles(d3sqr);
		if (d2sqr_p != d2sqr)
			FreeDoubles(d2sqr);
		if (d1sqr_p != d1sqr)
			FreeDoubles(d1sqr);
		if (dez_p != dez)
			FreeDoubles(dez);
		if (dey_p != dey)
			FreeDoubles(dey);
		if (dex_p != dex)
			FreeDoubles(dex);
		if (ll4z_p != ll4z)
			FreeDoubles(ll4z);
		if (ll4y_p != ll4y)
			FreeDoubles(ll4y);
		if (ll4x_p != ll4x)
			FreeDoubles(ll4x);
		if (pezd4_p != pezd4)
			FreeDoubles(pezd4);
		if (peyd4_p != peyd4)
			FreeDoubles(peyd4);
		if (pexd4_p != pexd4)
			FreeDoubles(pexd4);
		if (cez_p != cez)
			FreeDoubles(cez);
		if (cey_p != cey)
			FreeDoubles(cey);
		if (cex_p != cex)
			FreeDoubles(cex);
		if (ll3z_p != ll3z)
			FreeDoubles(ll3z);
		if (ll3y_p != ll3y)
			FreeDoubles(ll3y);
		if (ll3x_p != ll3x)
			FreeDoubles(ll3x);
		if (pezd3_p != pezd3)
			FreeDoubles(pezd3);
		if (peyd3_p != peyd3)
			FreeDoubles(peyd3);
		if (pexd3_p != pexd3)
			FreeDoubles(pexd3);
		if (bez_p != bez)
			FreeDoubles(bez);
		if (bey_p != bey)
			FreeDoubles(bey);
		if (bex_p != bex)
			FreeDoubles(bex);
		if (ll2z_p != ll2z)
			FreeDoubles(ll2z);
		if (ll2y_p != ll2y)
			FreeDoubles(ll2y);
		if (ll2x_p != ll2x)
			FreeDoubles(ll2x);
		if (pezd2_p != pezd2)
			FreeDoubles(pezd2);
		if (peyd2_p != peyd2)
			FreeDoubles(peyd2);
		if (pexd2_p != pexd2)
			FreeDoubles(pexd2);
		if (aez_p != aez)
			FreeDoubles(aez);
		if (aey_p != aey)
			FreeDoubles(aey);
		if (aex_p != aex)
			FreeDoubles(aex);
		if (ll1z_p != ll1z)
			FreeDoubles(ll1z);
		if (ll1y_p != ll1y)
			FreeDoubles(ll1y);
		if (ll1x_p != ll1x)
			FreeDoubles(ll1x);
		if (pezd_p != pezd)
			FreeDoubles(pezd);
		if (peyd_p != peyd)
			FreeDoubles(peyd);
		if (pexd_p != pexd)
			FreeDoubles(pexd);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (l1x_p != l1x)
			FreeDoubles(l1x);
		if (l1y_p != l1y)
			FreeDoubles(l1y);
		if (l1z_p != l1z)
			FreeDoubles(l1z);
		if (d1_p != d1)
			FreeDoubles(d1);
		if (l2x_p != l2x)
			FreeDoubles(l2x);
		if (l2y_p != l2y)
			FreeDoubles(l2y);
		if (l2z_p != l2z)
			FreeDoubles(l2z);
		if (d2_p != d2)
			FreeDoubles(d2);
		if (l3x_p != l3x)
			FreeDoubles(l3x);
		if (l3y_p != l3y)
			FreeDoubles(l3y);
		if (l3z_p != l3z)
			FreeDoubles(l3z);
		if (d3_p != d3)
			FreeDoubles(d3);
		if (l4x_p != l4x)
			FreeDoubles(l4x);
		if (l4y_p != l4y)
			FreeDoubles(l4y);
		if (l4z_p != l4z)
			FreeDoubles(l4z);
		if (d4_p != d4)
			FreeDoubles(d4);
		if (l5x_p != l5x)
			FreeDoubles(l5x);
		if (l5y_p != l5y)
			FreeDoubles(l5y);
		if (l5z_p != l5z)
			FreeDoubles(l5z);
		if (d5_p != d5)
			FreeDoubles(d5);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inPowerSphere_IIIII_exact<IT, ET>(p1, p2, p3, p4, p5, w1, w2, w3, w4,
		                                         w5);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inPowerSphere_IIIII(const GenericPoint3T<IT, ET> &p1,
                         const GenericPoint3T<IT, ET> &p2,
                         const GenericPoint3T<IT, ET> &p3,
                         const GenericPoint3T<IT, ET> &p4,
                         const GenericPoint3T<IT, ET> &p5, double w1, double w2,
                         double w3, double w4, double w5)
{
	Sign ret;
	ret = inPowerSphere_IIIII_interval<IT, ET>(p1, p2, p3, p4, p5, w1, w2, w3, w4,
	                                           w5);
	if (is_sign_reliable(ret))
		return ret;
	return inPowerSphere_IIIII_expansion<IT, ET>(p1, p2, p3, p4, p5, w1, w2, w3,
	                                             w4, w5);
}

template <typename IT>
Sign inSegmentDiametricalSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby,
                                         IT pbz, IT pcx, IT pcy, IT pcz)
{
	typename IT::Protector P;

	IT abx   = pbx - pax;
	IT aby   = pby - pay;
	IT abz   = pbz - paz;
	IT abx2  = abx * abx;
	IT aby2  = aby * aby;
	IT abz2  = abz * abz;
	IT t0    = abx2 + aby2;
	IT absqr = t0 + abz2;
	IT acx   = pcx - pax;
	IT acy   = pcy - pay;
	IT acz   = pcz - paz;
	IT acx2  = acx * acx;
	IT acy2  = acy * acy;
	IT acz2  = acz * acz;
	IT t1    = acx2 + acy2;
	IT acsqr = t1 + acz2;
	IT bcx   = pcx - pbx;
	IT bcy   = pcy - pby;
	IT bcz   = pcz - pbz;
	IT bcx2  = bcx * bcx;
	IT bcy2  = bcy * bcy;
	IT bcz2  = bcz * bcz;
	IT t2    = bcx2 + bcy2;
	IT bcsqr = t2 + bcz2;
	IT ac_bc = acsqr + bcsqr;
	IT d     = absqr - ac_bc;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign inSegmentDiametricalSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby,
                                      ET pbz, ET pcx, ET pcy, ET pcz)
{
	ET abx   = pbx - pax;
	ET aby   = pby - pay;
	ET abz   = pbz - paz;
	ET abx2  = abx * abx;
	ET aby2  = aby * aby;
	ET abz2  = abz * abz;
	ET t0    = abx2 + aby2;
	ET absqr = t0 + abz2;
	ET acx   = pcx - pax;
	ET acy   = pcy - pay;
	ET acz   = pcz - paz;
	ET acx2  = acx * acx;
	ET acy2  = acy * acy;
	ET acz2  = acz * acz;
	ET t1    = acx2 + acy2;
	ET acsqr = t1 + acz2;
	ET bcx   = pcx - pbx;
	ET bcy   = pcy - pby;
	ET bcz   = pcz - pbz;
	ET bcx2  = bcx * bcx;
	ET bcy2  = bcy * bcy;
	ET bcz2  = bcz * bcz;
	ET t2    = bcx2 + bcy2;
	ET bcsqr = t2 + bcz2;
	ET ac_bc = acsqr + bcsqr;
	ET d     = absqr - ac_bc;
	return OMC::sign(d);
}

Sign inSegmentDiametricalSphere_expansion(double pax, double pay, double paz,
                                          double pbx, double pby, double pbz,
                                          double pcx, double pcy, double pcz)
{
	expansionObject o;
	double          abx[2];
	o.Two_Diff(pbx, pax, abx);
	double aby[2];
	o.Two_Diff(pby, pay, aby);
	double abz[2];
	o.Two_Diff(pbz, paz, abz);
	double abx2[8];
	int    abx2_len = o.Gen_Product(2, abx, 2, abx, abx2);
	double aby2[8];
	int    aby2_len = o.Gen_Product(2, aby, 2, aby, aby2);
	double abz2[8];
	int    abz2_len = o.Gen_Product(2, abz, 2, abz, abz2);
	double t0[16];
	int    t0_len = o.Gen_Sum(abx2_len, abx2, aby2_len, aby2, t0);
	double absqr[24];
	int    absqr_len = o.Gen_Sum(t0_len, t0, abz2_len, abz2, absqr);
	double acx[2];
	o.Two_Diff(pcx, pax, acx);
	double acy[2];
	o.Two_Diff(pcy, pay, acy);
	double acz[2];
	o.Two_Diff(pcz, paz, acz);
	double acx2[8];
	int    acx2_len = o.Gen_Product(2, acx, 2, acx, acx2);
	double acy2[8];
	int    acy2_len = o.Gen_Product(2, acy, 2, acy, acy2);
	double acz2[8];
	int    acz2_len = o.Gen_Product(2, acz, 2, acz, acz2);
	double t1[16];
	int    t1_len = o.Gen_Sum(acx2_len, acx2, acy2_len, acy2, t1);
	double acsqr[24];
	int    acsqr_len = o.Gen_Sum(t1_len, t1, acz2_len, acz2, acsqr);
	double bcx[2];
	o.Two_Diff(pcx, pbx, bcx);
	double bcy[2];
	o.Two_Diff(pcy, pby, bcy);
	double bcz[2];
	o.Two_Diff(pcz, pbz, bcz);
	double bcx2[8];
	int    bcx2_len = o.Gen_Product(2, bcx, 2, bcx, bcx2);
	double bcy2[8];
	int    bcy2_len = o.Gen_Product(2, bcy, 2, bcy, bcy2);
	double bcz2[8];
	int    bcz2_len = o.Gen_Product(2, bcz, 2, bcz, bcz2);
	double t2[16];
	int    t2_len = o.Gen_Sum(bcx2_len, bcx2, bcy2_len, bcy2, t2);
	double bcsqr[24];
	int    bcsqr_len = o.Gen_Sum(t2_len, t2, bcz2_len, bcz2, bcsqr);
	double ac_bc[48];
	int    ac_bc_len = o.Gen_Sum(acsqr_len, acsqr, bcsqr_len, bcsqr, ac_bc);
	double d[72];
	int    d_len = o.Gen_Diff(absqr_len, absqr, ac_bc_len, ac_bc, d);

	double return_value = d[d_len - 1];

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere(double pax, double pay, double paz, double pbx,
                                double pby, double pbz, double pcx, double pcy,
                                double pcz)
{
	Sign ret;
	ret = inSegmentDiametricalSphere_interval<IT>(pax, pay, paz, pbx, pby, pbz,
	                                              pcx, pcy, pcz);
	if (is_sign_reliable(ret))
		return ret;
	return inSegmentDiametricalSphere_expansion(pax, pay, paz, pbx, pby, pbz, pcx,
	                                            pcy, pcz);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere(const GenericPoint3T<IT, ET> &pa,
                                const GenericPoint3T<IT, ET> &pb,
                                const GenericPoint3T<IT, ET> &pc)
{
	return inSegmentDiametricalSphere<IT, ET>(
	  pa.x(), pa.y(), pa.z(), pb.x(), pb.y(), pb.z(), pc.x(), pc.y(), pc.z());
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI_interval(const GenericPoint3T<IT, ET> &pc,
                                             IT pax, IT pay, IT paz, IT pbx,
                                             IT pby, IT pbz)
{
	IT lcx, lcy, lcz, dc;
	if (!pc.getIntervalLambda(lcx, lcy, lcz, dc))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT abx      = pbx - pax;
	IT aby      = pby - pay;
	IT abz      = pbz - paz;
	IT abx2     = abx * abx;
	IT aby2     = aby * aby;
	IT abz2     = abz * abz;
	IT t0       = abx2 + aby2;
	IT absqr    = t0 + abz2;
	IT dc2      = dc * dc;
	IT dc2absqr = dc2 * absqr;
	IT dcpax    = dc * pax;
	IT dcpay    = dc * pay;
	IT dcpaz    = dc * paz;
	IT acx      = lcx - dcpax;
	IT acy      = lcy - dcpay;
	IT acz      = lcz - dcpaz;
	IT acx2     = acx * acx;
	IT acy2     = acy * acy;
	IT acz2     = acz * acz;
	IT t1       = acx2 + acy2;
	IT acsqr    = t1 + acz2;
	IT dcpbx    = dc * pbx;
	IT dcpby    = dc * pby;
	IT dcpbz    = dc * pbz;
	IT bcx      = lcx - dcpbx;
	IT bcy      = lcy - dcpby;
	IT bcz      = lcz - dcpbz;
	IT bcx2     = bcx * bcx;
	IT bcy2     = bcy * bcy;
	IT bcz2     = bcz * bcz;
	IT t2       = bcx2 + bcy2;
	IT bcsqr    = t2 + bcz2;
	IT ac_bc    = acsqr + bcsqr;
	IT d        = dc2absqr - ac_bc;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI_exact(const GenericPoint3T<IT, ET> &pc,
                                          ET pax, ET pay, ET paz, ET pbx,
                                          ET pby, ET pbz)
{
	ET lcx, lcy, lcz, dc;
	pc.getExactLambda(lcx, lcy, lcz, dc);
	ET abx      = pbx - pax;
	ET aby      = pby - pay;
	ET abz      = pbz - paz;
	ET abx2     = abx * abx;
	ET aby2     = aby * aby;
	ET abz2     = abz * abz;
	ET t0       = abx2 + aby2;
	ET absqr    = t0 + abz2;
	ET dc2      = dc * dc;
	ET dc2absqr = dc2 * absqr;
	ET dcpax    = dc * pax;
	ET dcpay    = dc * pay;
	ET dcpaz    = dc * paz;
	ET acx      = lcx - dcpax;
	ET acy      = lcy - dcpay;
	ET acz      = lcz - dcpaz;
	ET acx2     = acx * acx;
	ET acy2     = acy * acy;
	ET acz2     = acz * acz;
	ET t1       = acx2 + acy2;
	ET acsqr    = t1 + acz2;
	ET dcpbx    = dc * pbx;
	ET dcpby    = dc * pby;
	ET dcpbz    = dc * pbz;
	ET bcx      = lcx - dcpbx;
	ET bcy      = lcy - dcpby;
	ET bcz      = lcz - dcpbz;
	ET bcx2     = bcx * bcx;
	ET bcy2     = bcy * bcy;
	ET bcz2     = bcz * bcz;
	ET t2       = bcx2 + bcy2;
	ET bcsqr    = t2 + bcz2;
	ET ac_bc    = acsqr + bcsqr;
	ET d        = dc2absqr - ac_bc;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI_expansion(const GenericPoint3T<IT, ET> &pc,
                                              double pax, double pay,
                                              double paz, double pbx,
                                              double pby, double pbz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lcx_p[32], *lcx = lcx_p, lcy_p[32], *lcy = lcy_p, lcz_p[32],
	                  *lcz = lcz_p, dc_p[32], *dc = dc_p;
	int lcx_len = 32, lcy_len = 32, lcz_len = 32, dc_len = 32;
	pc.getExpansionLambda(&lcx, lcx_len, &lcy, lcy_len, &lcz, lcz_len, &dc,
	                      dc_len);
	if ((dc[dc_len - 1] != 0))
	{
		expansionObject o;
		double          abx[2];
		o.Two_Diff(pbx, pax, abx);
		double aby[2];
		o.Two_Diff(pby, pay, aby);
		double abz[2];
		o.Two_Diff(pbz, paz, abz);
		double abx2[8];
		int    abx2_len = o.Gen_Product(2, abx, 2, abx, abx2);
		double aby2[8];
		int    aby2_len = o.Gen_Product(2, aby, 2, aby, aby2);
		double abz2[8];
		int    abz2_len = o.Gen_Product(2, abz, 2, abz, abz2);
		double t0[16];
		int    t0_len = o.Gen_Sum(abx2_len, abx2, aby2_len, aby2, t0);
		double absqr[24];
		int    absqr_len = o.Gen_Sum(t0_len, t0, abz2_len, abz2, absqr);
		double dc2_p[32], *dc2 = dc2_p;
		int dc2_len = o.Gen_Product_With_PreAlloc(dc_len, dc, dc_len, dc, &dc2, 32);
		double dc2absqr_p[32], *dc2absqr = dc2absqr_p;
		int    dc2absqr_len = o.Gen_Product_With_PreAlloc(dc2_len, dc2, absqr_len,
		                                                  absqr, &dc2absqr, 32);
		double dcpax_p[32], *dcpax = dcpax_p;
		int    dcpax_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pax, &dcpax, 32);
		double dcpay_p[32], *dcpay = dcpay_p;
		int    dcpay_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pay, &dcpay, 32);
		double dcpaz_p[32], *dcpaz = dcpaz_p;
		int    dcpaz_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, paz, &dcpaz, 32);
		double acx_p[32], *acx = acx_p;
		int    acx_len =
		  o.Gen_Diff_With_PreAlloc(lcx_len, lcx, dcpax_len, dcpax, &acx, 32);
		double acy_p[32], *acy = acy_p;
		int    acy_len =
		  o.Gen_Diff_With_PreAlloc(lcy_len, lcy, dcpay_len, dcpay, &acy, 32);
		double acz_p[32], *acz = acz_p;
		int    acz_len =
		  o.Gen_Diff_With_PreAlloc(lcz_len, lcz, dcpaz_len, dcpaz, &acz, 32);
		double acx2_p[32], *acx2 = acx2_p;
		int    acx2_len =
		  o.Gen_Product_With_PreAlloc(acx_len, acx, acx_len, acx, &acx2, 32);
		double acy2_p[32], *acy2 = acy2_p;
		int    acy2_len =
		  o.Gen_Product_With_PreAlloc(acy_len, acy, acy_len, acy, &acy2, 32);
		double acz2_p[32], *acz2 = acz2_p;
		int    acz2_len =
		  o.Gen_Product_With_PreAlloc(acz_len, acz, acz_len, acz, &acz2, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Sum_With_PreAlloc(acx2_len, acx2, acy2_len, acy2, &t1, 32);
		double acsqr_p[32], *acsqr = acsqr_p;
		int    acsqr_len =
		  o.Gen_Sum_With_PreAlloc(t1_len, t1, acz2_len, acz2, &acsqr, 32);
		double dcpbx_p[32], *dcpbx = dcpbx_p;
		int    dcpbx_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pbx, &dcpbx, 32);
		double dcpby_p[32], *dcpby = dcpby_p;
		int    dcpby_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pby, &dcpby, 32);
		double dcpbz_p[32], *dcpbz = dcpbz_p;
		int    dcpbz_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pbz, &dcpbz, 32);
		double bcx_p[32], *bcx = bcx_p;
		int    bcx_len =
		  o.Gen_Diff_With_PreAlloc(lcx_len, lcx, dcpbx_len, dcpbx, &bcx, 32);
		double bcy_p[32], *bcy = bcy_p;
		int    bcy_len =
		  o.Gen_Diff_With_PreAlloc(lcy_len, lcy, dcpby_len, dcpby, &bcy, 32);
		double bcz_p[32], *bcz = bcz_p;
		int    bcz_len =
		  o.Gen_Diff_With_PreAlloc(lcz_len, lcz, dcpbz_len, dcpbz, &bcz, 32);
		double bcx2_p[32], *bcx2 = bcx2_p;
		int    bcx2_len =
		  o.Gen_Product_With_PreAlloc(bcx_len, bcx, bcx_len, bcx, &bcx2, 32);
		double bcy2_p[32], *bcy2 = bcy2_p;
		int    bcy2_len =
		  o.Gen_Product_With_PreAlloc(bcy_len, bcy, bcy_len, bcy, &bcy2, 32);
		double bcz2_p[32], *bcz2 = bcz2_p;
		int    bcz2_len =
		  o.Gen_Product_With_PreAlloc(bcz_len, bcz, bcz_len, bcz, &bcz2, 32);
		double t2_p[32], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Sum_With_PreAlloc(bcx2_len, bcx2, bcy2_len, bcy2, &t2, 32);
		double bcsqr_p[32], *bcsqr = bcsqr_p;
		int    bcsqr_len =
		  o.Gen_Sum_With_PreAlloc(t2_len, t2, bcz2_len, bcz2, &bcsqr, 32);
		double ac_bc_p[32], *ac_bc = ac_bc_p;
		int    ac_bc_len =
		  o.Gen_Sum_With_PreAlloc(acsqr_len, acsqr, bcsqr_len, bcsqr, &ac_bc, 32);
		double d_p[32], *d = d_p;
		int    d_len = o.Gen_Diff_With_PreAlloc(dc2absqr_len, dc2absqr, ac_bc_len,
		                                        ac_bc, &d, 32);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (ac_bc_p != ac_bc)
			FreeDoubles(ac_bc);
		if (bcsqr_p != bcsqr)
			FreeDoubles(bcsqr);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (bcz2_p != bcz2)
			FreeDoubles(bcz2);
		if (bcy2_p != bcy2)
			FreeDoubles(bcy2);
		if (bcx2_p != bcx2)
			FreeDoubles(bcx2);
		if (bcz_p != bcz)
			FreeDoubles(bcz);
		if (bcy_p != bcy)
			FreeDoubles(bcy);
		if (bcx_p != bcx)
			FreeDoubles(bcx);
		if (dcpbz_p != dcpbz)
			FreeDoubles(dcpbz);
		if (dcpby_p != dcpby)
			FreeDoubles(dcpby);
		if (dcpbx_p != dcpbx)
			FreeDoubles(dcpbx);
		if (acsqr_p != acsqr)
			FreeDoubles(acsqr);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (acz2_p != acz2)
			FreeDoubles(acz2);
		if (acy2_p != acy2)
			FreeDoubles(acy2);
		if (acx2_p != acx2)
			FreeDoubles(acx2);
		if (acz_p != acz)
			FreeDoubles(acz);
		if (acy_p != acy)
			FreeDoubles(acy);
		if (acx_p != acx)
			FreeDoubles(acx);
		if (dcpaz_p != dcpaz)
			FreeDoubles(dcpaz);
		if (dcpay_p != dcpay)
			FreeDoubles(dcpay);
		if (dcpax_p != dcpax)
			FreeDoubles(dcpax);
		if (dc2absqr_p != dc2absqr)
			FreeDoubles(dc2absqr);
		if (dc2_p != dc2)
			FreeDoubles(dc2);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lcx_p != lcx)
			FreeDoubles(lcx);
		if (lcy_p != lcy)
			FreeDoubles(lcy);
		if (lcz_p != lcz)
			FreeDoubles(lcz);
		if (dc_p != dc)
			FreeDoubles(dc);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSegmentDiametricalSphere_EEI_exact<IT, ET>(pc, pax, pay, paz, pbx,
		                                                    pby, pbz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI(const GenericPoint3T<IT, ET> &pc,
                                    double pax, double pay, double paz,
                                    double pbx, double pby, double pbz)
{
	Sign ret;
	ret = inSegmentDiametricalSphere_EEI_interval<IT, ET>(pc, pax, pay, paz, pbx,
	                                                      pby, pbz);
	if (is_sign_reliable(ret))
		return ret;
	return inSegmentDiametricalSphere_EEI_expansion<IT, ET>(pc, pax, pay, paz,
	                                                        pbx, pby, pbz);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_EEI(const GenericPoint3T<IT, ET> &pc,
                                    const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb)
{
	return inSegmentDiametricalSphere_EEI<IT, ET>(pc, pa.x(), pa.y(), pa.z(),
	                                              pb.x(), pb.y(), pb.z());
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE_interval(const GenericPoint3T<IT, ET> &pa,
                                             IT pbx, IT pby, IT pbz, IT pcx,
                                             IT pcy, IT pcz)
{
	IT lax, lay, laz, da;
	if (!pa.getIntervalLambda(lax, lay, laz, da))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dapbx    = da * pbx;
	IT dapby    = da * pby;
	IT dapbz    = da * pbz;
	IT abx      = dapbx - lax;
	IT aby      = dapby - lay;
	IT abz      = dapbz - laz;
	IT abx2     = abx * abx;
	IT aby2     = aby * aby;
	IT abz2     = abz * abz;
	IT t0       = abx2 + aby2;
	IT absqr    = t0 + abz2;
	IT dapcx    = da * pcx;
	IT dapcy    = da * pcy;
	IT dapcz    = da * pcz;
	IT acx      = dapcx - lax;
	IT acy      = dapcy - lay;
	IT acz      = dapcz - laz;
	IT acx2     = acx * acx;
	IT acy2     = acy * acy;
	IT acz2     = acz * acz;
	IT t1       = acx2 + acy2;
	IT acsqr    = t1 + acz2;
	IT bcx      = pcx - pbx;
	IT bcy      = pcy - pby;
	IT bcz      = pcz - pbz;
	IT bcx2     = bcx * bcx;
	IT bcy2     = bcy * bcy;
	IT bcz2     = bcz * bcz;
	IT t2       = bcx2 + bcy2;
	IT bcsqr    = t2 + bcz2;
	IT da2      = da * da;
	IT da2bcsqr = da2 * bcsqr;
	IT ac_bc    = acsqr + da2bcsqr;
	IT d        = absqr - ac_bc;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE_exact(const GenericPoint3T<IT, ET> &pa,
                                          ET pbx, ET pby, ET pbz, ET pcx,
                                          ET pcy, ET pcz)
{
	ET lax, lay, laz, da;
	pa.getExactLambda(lax, lay, laz, da);
	ET dapbx    = da * pbx;
	ET dapby    = da * pby;
	ET dapbz    = da * pbz;
	ET abx      = dapbx - lax;
	ET aby      = dapby - lay;
	ET abz      = dapbz - laz;
	ET abx2     = abx * abx;
	ET aby2     = aby * aby;
	ET abz2     = abz * abz;
	ET t0       = abx2 + aby2;
	ET absqr    = t0 + abz2;
	ET dapcx    = da * pcx;
	ET dapcy    = da * pcy;
	ET dapcz    = da * pcz;
	ET acx      = dapcx - lax;
	ET acy      = dapcy - lay;
	ET acz      = dapcz - laz;
	ET acx2     = acx * acx;
	ET acy2     = acy * acy;
	ET acz2     = acz * acz;
	ET t1       = acx2 + acy2;
	ET acsqr    = t1 + acz2;
	ET bcx      = pcx - pbx;
	ET bcy      = pcy - pby;
	ET bcz      = pcz - pbz;
	ET bcx2     = bcx * bcx;
	ET bcy2     = bcy * bcy;
	ET bcz2     = bcz * bcz;
	ET t2       = bcx2 + bcy2;
	ET bcsqr    = t2 + bcz2;
	ET da2      = da * da;
	ET da2bcsqr = da2 * bcsqr;
	ET ac_bc    = acsqr + da2bcsqr;
	ET d        = absqr - ac_bc;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE_expansion(const GenericPoint3T<IT, ET> &pa,
                                              double pbx, double pby,
                                              double pbz, double pcx,
                                              double pcy, double pcz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lax_p[32], *lax = lax_p, lay_p[32], *lay = lay_p, laz_p[32],
	                  *laz = laz_p, da_p[32], *da = da_p;
	int lax_len = 32, lay_len = 32, laz_len = 32, da_len = 32;
	pa.getExpansionLambda(&lax, lax_len, &lay, lay_len, &laz, laz_len, &da,
	                      da_len);
	if ((da[da_len - 1] != 0))
	{
		expansionObject o;
		double          dapbx_p[32], *dapbx = dapbx_p;
		int    dapbx_len = o.Gen_Scale_With_PreAlloc(da_len, da, pbx, &dapbx, 32);
		double dapby_p[32], *dapby = dapby_p;
		int    dapby_len = o.Gen_Scale_With_PreAlloc(da_len, da, pby, &dapby, 32);
		double dapbz_p[32], *dapbz = dapbz_p;
		int    dapbz_len = o.Gen_Scale_With_PreAlloc(da_len, da, pbz, &dapbz, 32);
		double abx_p[32], *abx = abx_p;
		int    abx_len =
		  o.Gen_Diff_With_PreAlloc(dapbx_len, dapbx, lax_len, lax, &abx, 32);
		double aby_p[32], *aby = aby_p;
		int    aby_len =
		  o.Gen_Diff_With_PreAlloc(dapby_len, dapby, lay_len, lay, &aby, 32);
		double abz_p[32], *abz = abz_p;
		int    abz_len =
		  o.Gen_Diff_With_PreAlloc(dapbz_len, dapbz, laz_len, laz, &abz, 32);
		double abx2_p[32], *abx2 = abx2_p;
		int    abx2_len =
		  o.Gen_Product_With_PreAlloc(abx_len, abx, abx_len, abx, &abx2, 32);
		double aby2_p[32], *aby2 = aby2_p;
		int    aby2_len =
		  o.Gen_Product_With_PreAlloc(aby_len, aby, aby_len, aby, &aby2, 32);
		double abz2_p[32], *abz2 = abz2_p;
		int    abz2_len =
		  o.Gen_Product_With_PreAlloc(abz_len, abz, abz_len, abz, &abz2, 32);
		double t0_p[32], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Sum_With_PreAlloc(abx2_len, abx2, aby2_len, aby2, &t0, 32);
		double absqr_p[32], *absqr = absqr_p;
		int    absqr_len =
		  o.Gen_Sum_With_PreAlloc(t0_len, t0, abz2_len, abz2, &absqr, 32);
		double dapcx_p[32], *dapcx = dapcx_p;
		int    dapcx_len = o.Gen_Scale_With_PreAlloc(da_len, da, pcx, &dapcx, 32);
		double dapcy_p[32], *dapcy = dapcy_p;
		int    dapcy_len = o.Gen_Scale_With_PreAlloc(da_len, da, pcy, &dapcy, 32);
		double dapcz_p[32], *dapcz = dapcz_p;
		int    dapcz_len = o.Gen_Scale_With_PreAlloc(da_len, da, pcz, &dapcz, 32);
		double acx_p[32], *acx = acx_p;
		int    acx_len =
		  o.Gen_Diff_With_PreAlloc(dapcx_len, dapcx, lax_len, lax, &acx, 32);
		double acy_p[32], *acy = acy_p;
		int    acy_len =
		  o.Gen_Diff_With_PreAlloc(dapcy_len, dapcy, lay_len, lay, &acy, 32);
		double acz_p[32], *acz = acz_p;
		int    acz_len =
		  o.Gen_Diff_With_PreAlloc(dapcz_len, dapcz, laz_len, laz, &acz, 32);
		double acx2_p[32], *acx2 = acx2_p;
		int    acx2_len =
		  o.Gen_Product_With_PreAlloc(acx_len, acx, acx_len, acx, &acx2, 32);
		double acy2_p[32], *acy2 = acy2_p;
		int    acy2_len =
		  o.Gen_Product_With_PreAlloc(acy_len, acy, acy_len, acy, &acy2, 32);
		double acz2_p[32], *acz2 = acz2_p;
		int    acz2_len =
		  o.Gen_Product_With_PreAlloc(acz_len, acz, acz_len, acz, &acz2, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Sum_With_PreAlloc(acx2_len, acx2, acy2_len, acy2, &t1, 32);
		double acsqr_p[32], *acsqr = acsqr_p;
		int    acsqr_len =
		  o.Gen_Sum_With_PreAlloc(t1_len, t1, acz2_len, acz2, &acsqr, 32);
		double bcx[2];
		o.Two_Diff(pcx, pbx, bcx);
		double bcy[2];
		o.Two_Diff(pcy, pby, bcy);
		double bcz[2];
		o.Two_Diff(pcz, pbz, bcz);
		double bcx2[8];
		int    bcx2_len = o.Gen_Product(2, bcx, 2, bcx, bcx2);
		double bcy2[8];
		int    bcy2_len = o.Gen_Product(2, bcy, 2, bcy, bcy2);
		double bcz2[8];
		int    bcz2_len = o.Gen_Product(2, bcz, 2, bcz, bcz2);
		double t2[16];
		int    t2_len = o.Gen_Sum(bcx2_len, bcx2, bcy2_len, bcy2, t2);
		double bcsqr[24];
		int    bcsqr_len = o.Gen_Sum(t2_len, t2, bcz2_len, bcz2, bcsqr);
		double da2_p[32], *da2 = da2_p;
		int da2_len = o.Gen_Product_With_PreAlloc(da_len, da, da_len, da, &da2, 32);
		double da2bcsqr_p[32], *da2bcsqr = da2bcsqr_p;
		int    da2bcsqr_len = o.Gen_Product_With_PreAlloc(da2_len, da2, bcsqr_len,
		                                                  bcsqr, &da2bcsqr, 32);
		double ac_bc_p[32], *ac_bc = ac_bc_p;
		int    ac_bc_len = o.Gen_Sum_With_PreAlloc(acsqr_len, acsqr, da2bcsqr_len,
		                                           da2bcsqr, &ac_bc, 32);
		double d_p[32], *d = d_p;
		int    d_len =
		  o.Gen_Diff_With_PreAlloc(absqr_len, absqr, ac_bc_len, ac_bc, &d, 32);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (ac_bc_p != ac_bc)
			FreeDoubles(ac_bc);
		if (da2bcsqr_p != da2bcsqr)
			FreeDoubles(da2bcsqr);
		if (da2_p != da2)
			FreeDoubles(da2);
		if (acsqr_p != acsqr)
			FreeDoubles(acsqr);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (acz2_p != acz2)
			FreeDoubles(acz2);
		if (acy2_p != acy2)
			FreeDoubles(acy2);
		if (acx2_p != acx2)
			FreeDoubles(acx2);
		if (acz_p != acz)
			FreeDoubles(acz);
		if (acy_p != acy)
			FreeDoubles(acy);
		if (acx_p != acx)
			FreeDoubles(acx);
		if (dapcz_p != dapcz)
			FreeDoubles(dapcz);
		if (dapcy_p != dapcy)
			FreeDoubles(dapcy);
		if (dapcx_p != dapcx)
			FreeDoubles(dapcx);
		if (absqr_p != absqr)
			FreeDoubles(absqr);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (abz2_p != abz2)
			FreeDoubles(abz2);
		if (aby2_p != aby2)
			FreeDoubles(aby2);
		if (abx2_p != abx2)
			FreeDoubles(abx2);
		if (abz_p != abz)
			FreeDoubles(abz);
		if (aby_p != aby)
			FreeDoubles(aby);
		if (abx_p != abx)
			FreeDoubles(abx);
		if (dapbz_p != dapbz)
			FreeDoubles(dapbz);
		if (dapby_p != dapby)
			FreeDoubles(dapby);
		if (dapbx_p != dapbx)
			FreeDoubles(dapbx);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lax_p != lax)
			FreeDoubles(lax);
		if (lay_p != lay)
			FreeDoubles(lay);
		if (laz_p != laz)
			FreeDoubles(laz);
		if (da_p != da)
			FreeDoubles(da);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSegmentDiametricalSphere_IEE_exact<IT, ET>(pa, pbx, pby, pbz, pcx,
		                                                    pcy, pcz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE(const GenericPoint3T<IT, ET> &pa,
                                    double pbx, double pby, double pbz,
                                    double pcx, double pcy, double pcz)
{
	Sign ret;
	ret = inSegmentDiametricalSphere_IEE_interval<IT, ET>(pa, pbx, pby, pbz, pcx,
	                                                      pcy, pcz);
	if (is_sign_reliable(ret))
		return ret;
	return inSegmentDiametricalSphere_IEE_expansion<IT, ET>(pa, pbx, pby, pbz,
	                                                        pcx, pcy, pcz);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEE(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    const GenericPoint3T<IT, ET> &pc)
{
	return inSegmentDiametricalSphere_IEE<IT, ET>(pa, pb.x(), pb.y(), pb.z(),
	                                              pc.x(), pc.y(), pc.z());
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI_interval(const GenericPoint3T<IT, ET> &pa,
                                             const GenericPoint3T<IT, ET> &pc,
                                             IT pbx, IT pby, IT pbz)
{
	IT lax, lay, laz, da, lcx, lcy, lcz, dc;
	if (!pa.getIntervalLambda(lax, lay, laz, da) ||
	    !pc.getIntervalLambda(lcx, lcy, lcz, dc))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dapbx    = da * pbx;
	IT dapby    = da * pby;
	IT dapbz    = da * pbz;
	IT abx      = dapbx - lax;
	IT aby      = dapby - lay;
	IT abz      = dapbz - laz;
	IT abx2     = abx * abx;
	IT aby2     = aby * aby;
	IT abz2     = abz * abz;
	IT t0       = abx2 + aby2;
	IT absqr    = t0 + abz2;
	IT dc2      = dc * dc;
	IT dc2absqr = dc2 * absqr;
	IT dalcx    = da * lcx;
	IT dalcy    = da * lcy;
	IT dalcz    = da * lcz;
	IT dclax    = dc * lax;
	IT dclay    = dc * lay;
	IT dclaz    = dc * laz;
	IT acx      = dalcx - dclax;
	IT acy      = dalcy - dclay;
	IT acz      = dalcz - dclaz;
	IT acx2     = acx * acx;
	IT acy2     = acy * acy;
	IT acz2     = acz * acz;
	IT t1       = acx2 + acy2;
	IT acsqr    = t1 + acz2;
	IT dcpbx    = dc * pbx;
	IT dcpby    = dc * pby;
	IT dcpbz    = dc * pbz;
	IT bcx      = lcx - dcpbx;
	IT bcy      = lcy - dcpby;
	IT bcz      = lcz - dcpbz;
	IT bcx2     = bcx * bcx;
	IT bcy2     = bcy * bcy;
	IT bcz2     = bcz * bcz;
	IT t2       = bcx2 + bcy2;
	IT bcsqr    = t2 + bcz2;
	IT da2      = da * da;
	IT da2bcsqr = da2 * bcsqr;
	IT ac_bc    = acsqr + da2bcsqr;
	IT d        = dc2absqr - ac_bc;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI_exact(const GenericPoint3T<IT, ET> &pa,
                                          const GenericPoint3T<IT, ET> &pc,
                                          ET pbx, ET pby, ET pbz)
{
	ET lax, lay, laz, da, lcx, lcy, lcz, dc;
	pa.getExactLambda(lax, lay, laz, da);
	pc.getExactLambda(lcx, lcy, lcz, dc);
	ET dapbx    = da * pbx;
	ET dapby    = da * pby;
	ET dapbz    = da * pbz;
	ET abx      = dapbx - lax;
	ET aby      = dapby - lay;
	ET abz      = dapbz - laz;
	ET abx2     = abx * abx;
	ET aby2     = aby * aby;
	ET abz2     = abz * abz;
	ET t0       = abx2 + aby2;
	ET absqr    = t0 + abz2;
	ET dc2      = dc * dc;
	ET dc2absqr = dc2 * absqr;
	ET dalcx    = da * lcx;
	ET dalcy    = da * lcy;
	ET dalcz    = da * lcz;
	ET dclax    = dc * lax;
	ET dclay    = dc * lay;
	ET dclaz    = dc * laz;
	ET acx      = dalcx - dclax;
	ET acy      = dalcy - dclay;
	ET acz      = dalcz - dclaz;
	ET acx2     = acx * acx;
	ET acy2     = acy * acy;
	ET acz2     = acz * acz;
	ET t1       = acx2 + acy2;
	ET acsqr    = t1 + acz2;
	ET dcpbx    = dc * pbx;
	ET dcpby    = dc * pby;
	ET dcpbz    = dc * pbz;
	ET bcx      = lcx - dcpbx;
	ET bcy      = lcy - dcpby;
	ET bcz      = lcz - dcpbz;
	ET bcx2     = bcx * bcx;
	ET bcy2     = bcy * bcy;
	ET bcz2     = bcz * bcz;
	ET t2       = bcx2 + bcy2;
	ET bcsqr    = t2 + bcz2;
	ET da2      = da * da;
	ET da2bcsqr = da2 * bcsqr;
	ET ac_bc    = acsqr + da2bcsqr;
	ET d        = dc2absqr - ac_bc;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI_expansion(const GenericPoint3T<IT, ET> &pa,
                                              const GenericPoint3T<IT, ET> &pc,
                                              double pbx, double pby,
                                              double pbz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lax_p[32], *lax = lax_p, lay_p[32], *lay = lay_p, laz_p[32],
	                  *laz = laz_p, da_p[32], *da = da_p, lcx_p[32], *lcx = lcx_p,
	                  lcy_p[32], *lcy = lcy_p, lcz_p[32], *lcz = lcz_p, dc_p[32],
	                  *dc = dc_p;
	int lax_len = 32, lay_len = 32, laz_len = 32, da_len = 32, lcx_len = 32,
	    lcy_len = 32, lcz_len = 32, dc_len = 32;
	pa.getExpansionLambda(&lax, lax_len, &lay, lay_len, &laz, laz_len, &da,
	                      da_len);
	pc.getExpansionLambda(&lcx, lcx_len, &lcy, lcy_len, &lcz, lcz_len, &dc,
	                      dc_len);
	if ((da[da_len - 1] != 0) && (dc[dc_len - 1] != 0))
	{
		expansionObject o;
		double          dapbx_p[32], *dapbx = dapbx_p;
		int    dapbx_len = o.Gen_Scale_With_PreAlloc(da_len, da, pbx, &dapbx, 32);
		double dapby_p[32], *dapby = dapby_p;
		int    dapby_len = o.Gen_Scale_With_PreAlloc(da_len, da, pby, &dapby, 32);
		double dapbz_p[32], *dapbz = dapbz_p;
		int    dapbz_len = o.Gen_Scale_With_PreAlloc(da_len, da, pbz, &dapbz, 32);
		double abx_p[32], *abx = abx_p;
		int    abx_len =
		  o.Gen_Diff_With_PreAlloc(dapbx_len, dapbx, lax_len, lax, &abx, 32);
		double aby_p[32], *aby = aby_p;
		int    aby_len =
		  o.Gen_Diff_With_PreAlloc(dapby_len, dapby, lay_len, lay, &aby, 32);
		double abz_p[32], *abz = abz_p;
		int    abz_len =
		  o.Gen_Diff_With_PreAlloc(dapbz_len, dapbz, laz_len, laz, &abz, 32);
		double abx2_p[32], *abx2 = abx2_p;
		int    abx2_len =
		  o.Gen_Product_With_PreAlloc(abx_len, abx, abx_len, abx, &abx2, 32);
		double aby2_p[32], *aby2 = aby2_p;
		int    aby2_len =
		  o.Gen_Product_With_PreAlloc(aby_len, aby, aby_len, aby, &aby2, 32);
		double abz2_p[32], *abz2 = abz2_p;
		int    abz2_len =
		  o.Gen_Product_With_PreAlloc(abz_len, abz, abz_len, abz, &abz2, 32);
		double t0_p[32], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Sum_With_PreAlloc(abx2_len, abx2, aby2_len, aby2, &t0, 32);
		double absqr_p[32], *absqr = absqr_p;
		int    absqr_len =
		  o.Gen_Sum_With_PreAlloc(t0_len, t0, abz2_len, abz2, &absqr, 32);
		double dc2_p[32], *dc2 = dc2_p;
		int dc2_len = o.Gen_Product_With_PreAlloc(dc_len, dc, dc_len, dc, &dc2, 32);
		double dc2absqr_p[32], *dc2absqr = dc2absqr_p;
		int    dc2absqr_len = o.Gen_Product_With_PreAlloc(dc2_len, dc2, absqr_len,
		                                                  absqr, &dc2absqr, 32);
		double dalcx_p[32], *dalcx = dalcx_p;
		int    dalcx_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lcx_len, lcx, &dalcx, 32);
		double dalcy_p[32], *dalcy = dalcy_p;
		int    dalcy_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lcy_len, lcy, &dalcy, 32);
		double dalcz_p[32], *dalcz = dalcz_p;
		int    dalcz_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lcz_len, lcz, &dalcz, 32);
		double dclax_p[32], *dclax = dclax_p;
		int    dclax_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lax_len, lax, &dclax, 32);
		double dclay_p[32], *dclay = dclay_p;
		int    dclay_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lay_len, lay, &dclay, 32);
		double dclaz_p[32], *dclaz = dclaz_p;
		int    dclaz_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, laz_len, laz, &dclaz, 32);
		double acx_p[32], *acx = acx_p;
		int    acx_len =
		  o.Gen_Diff_With_PreAlloc(dalcx_len, dalcx, dclax_len, dclax, &acx, 32);
		double acy_p[32], *acy = acy_p;
		int    acy_len =
		  o.Gen_Diff_With_PreAlloc(dalcy_len, dalcy, dclay_len, dclay, &acy, 32);
		double acz_p[32], *acz = acz_p;
		int    acz_len =
		  o.Gen_Diff_With_PreAlloc(dalcz_len, dalcz, dclaz_len, dclaz, &acz, 32);
		double acx2_p[32], *acx2 = acx2_p;
		int    acx2_len =
		  o.Gen_Product_With_PreAlloc(acx_len, acx, acx_len, acx, &acx2, 32);
		double acy2_p[32], *acy2 = acy2_p;
		int    acy2_len =
		  o.Gen_Product_With_PreAlloc(acy_len, acy, acy_len, acy, &acy2, 32);
		double acz2_p[32], *acz2 = acz2_p;
		int    acz2_len =
		  o.Gen_Product_With_PreAlloc(acz_len, acz, acz_len, acz, &acz2, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Sum_With_PreAlloc(acx2_len, acx2, acy2_len, acy2, &t1, 32);
		double acsqr_p[32], *acsqr = acsqr_p;
		int    acsqr_len =
		  o.Gen_Sum_With_PreAlloc(t1_len, t1, acz2_len, acz2, &acsqr, 32);
		double dcpbx_p[32], *dcpbx = dcpbx_p;
		int    dcpbx_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pbx, &dcpbx, 32);
		double dcpby_p[32], *dcpby = dcpby_p;
		int    dcpby_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pby, &dcpby, 32);
		double dcpbz_p[32], *dcpbz = dcpbz_p;
		int    dcpbz_len = o.Gen_Scale_With_PreAlloc(dc_len, dc, pbz, &dcpbz, 32);
		double bcx_p[32], *bcx = bcx_p;
		int    bcx_len =
		  o.Gen_Diff_With_PreAlloc(lcx_len, lcx, dcpbx_len, dcpbx, &bcx, 32);
		double bcy_p[32], *bcy = bcy_p;
		int    bcy_len =
		  o.Gen_Diff_With_PreAlloc(lcy_len, lcy, dcpby_len, dcpby, &bcy, 32);
		double bcz_p[32], *bcz = bcz_p;
		int    bcz_len =
		  o.Gen_Diff_With_PreAlloc(lcz_len, lcz, dcpbz_len, dcpbz, &bcz, 32);
		double bcx2_p[32], *bcx2 = bcx2_p;
		int    bcx2_len =
		  o.Gen_Product_With_PreAlloc(bcx_len, bcx, bcx_len, bcx, &bcx2, 32);
		double bcy2_p[32], *bcy2 = bcy2_p;
		int    bcy2_len =
		  o.Gen_Product_With_PreAlloc(bcy_len, bcy, bcy_len, bcy, &bcy2, 32);
		double bcz2_p[32], *bcz2 = bcz2_p;
		int    bcz2_len =
		  o.Gen_Product_With_PreAlloc(bcz_len, bcz, bcz_len, bcz, &bcz2, 32);
		double t2_p[32], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Sum_With_PreAlloc(bcx2_len, bcx2, bcy2_len, bcy2, &t2, 32);
		double bcsqr_p[32], *bcsqr = bcsqr_p;
		int    bcsqr_len =
		  o.Gen_Sum_With_PreAlloc(t2_len, t2, bcz2_len, bcz2, &bcsqr, 32);
		double da2_p[32], *da2 = da2_p;
		int da2_len = o.Gen_Product_With_PreAlloc(da_len, da, da_len, da, &da2, 32);
		double da2bcsqr_p[32], *da2bcsqr = da2bcsqr_p;
		int    da2bcsqr_len = o.Gen_Product_With_PreAlloc(da2_len, da2, bcsqr_len,
		                                                  bcsqr, &da2bcsqr, 32);
		double ac_bc_p[32], *ac_bc = ac_bc_p;
		int    ac_bc_len = o.Gen_Sum_With_PreAlloc(acsqr_len, acsqr, da2bcsqr_len,
		                                           da2bcsqr, &ac_bc, 32);
		double d_p[32], *d = d_p;
		int    d_len = o.Gen_Diff_With_PreAlloc(dc2absqr_len, dc2absqr, ac_bc_len,
		                                        ac_bc, &d, 32);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (ac_bc_p != ac_bc)
			FreeDoubles(ac_bc);
		if (da2bcsqr_p != da2bcsqr)
			FreeDoubles(da2bcsqr);
		if (da2_p != da2)
			FreeDoubles(da2);
		if (bcsqr_p != bcsqr)
			FreeDoubles(bcsqr);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (bcz2_p != bcz2)
			FreeDoubles(bcz2);
		if (bcy2_p != bcy2)
			FreeDoubles(bcy2);
		if (bcx2_p != bcx2)
			FreeDoubles(bcx2);
		if (bcz_p != bcz)
			FreeDoubles(bcz);
		if (bcy_p != bcy)
			FreeDoubles(bcy);
		if (bcx_p != bcx)
			FreeDoubles(bcx);
		if (dcpbz_p != dcpbz)
			FreeDoubles(dcpbz);
		if (dcpby_p != dcpby)
			FreeDoubles(dcpby);
		if (dcpbx_p != dcpbx)
			FreeDoubles(dcpbx);
		if (acsqr_p != acsqr)
			FreeDoubles(acsqr);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (acz2_p != acz2)
			FreeDoubles(acz2);
		if (acy2_p != acy2)
			FreeDoubles(acy2);
		if (acx2_p != acx2)
			FreeDoubles(acx2);
		if (acz_p != acz)
			FreeDoubles(acz);
		if (acy_p != acy)
			FreeDoubles(acy);
		if (acx_p != acx)
			FreeDoubles(acx);
		if (dclaz_p != dclaz)
			FreeDoubles(dclaz);
		if (dclay_p != dclay)
			FreeDoubles(dclay);
		if (dclax_p != dclax)
			FreeDoubles(dclax);
		if (dalcz_p != dalcz)
			FreeDoubles(dalcz);
		if (dalcy_p != dalcy)
			FreeDoubles(dalcy);
		if (dalcx_p != dalcx)
			FreeDoubles(dalcx);
		if (dc2absqr_p != dc2absqr)
			FreeDoubles(dc2absqr);
		if (dc2_p != dc2)
			FreeDoubles(dc2);
		if (absqr_p != absqr)
			FreeDoubles(absqr);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (abz2_p != abz2)
			FreeDoubles(abz2);
		if (aby2_p != aby2)
			FreeDoubles(aby2);
		if (abx2_p != abx2)
			FreeDoubles(abx2);
		if (abz_p != abz)
			FreeDoubles(abz);
		if (aby_p != aby)
			FreeDoubles(aby);
		if (abx_p != abx)
			FreeDoubles(abx);
		if (dapbz_p != dapbz)
			FreeDoubles(dapbz);
		if (dapby_p != dapby)
			FreeDoubles(dapby);
		if (dapbx_p != dapbx)
			FreeDoubles(dapbx);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lax_p != lax)
			FreeDoubles(lax);
		if (lay_p != lay)
			FreeDoubles(lay);
		if (laz_p != laz)
			FreeDoubles(laz);
		if (da_p != da)
			FreeDoubles(da);
		if (lcx_p != lcx)
			FreeDoubles(lcx);
		if (lcy_p != lcy)
			FreeDoubles(lcy);
		if (lcz_p != lcz)
			FreeDoubles(lcz);
		if (dc_p != dc)
			FreeDoubles(dc);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSegmentDiametricalSphere_IEI_exact<IT, ET>(pa, pc, pbx, pby, pbz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pc,
                                    double pbx, double pby, double pbz)
{
	Sign ret;
	ret = inSegmentDiametricalSphere_IEI_interval<IT, ET>(pa, pc, pbx, pby, pbz);
	if (is_sign_reliable(ret))
		return ret;
	return inSegmentDiametricalSphere_IEI_expansion<IT, ET>(pa, pc, pbx, pby,
	                                                        pbz);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IEI(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pc,
                                    const GenericPoint3T<IT, ET> &pb)
{
	return inSegmentDiametricalSphere_IEI<IT, ET>(pa, pc, pb.x(), pb.y(), pb.z());
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE_interval(const GenericPoint3T<IT, ET> &pa,
                                             const GenericPoint3T<IT, ET> &pb,
                                             IT pcx, IT pcy, IT pcz)
{
	IT lax, lay, laz, da, lbx, lby, lbz, db;
	if (!pa.getIntervalLambda(lax, lay, laz, da) ||
	    !pb.getIntervalLambda(lbx, lby, lbz, db))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dalbx    = da * lbx;
	IT dalby    = da * lby;
	IT dalbz    = da * lbz;
	IT dblax    = db * lax;
	IT dblay    = db * lay;
	IT dblaz    = db * laz;
	IT abx      = dalbx - dblax;
	IT aby      = dalby - dblay;
	IT abz      = dalbz - dblaz;
	IT abx2     = abx * abx;
	IT aby2     = aby * aby;
	IT abz2     = abz * abz;
	IT t0       = abx2 + aby2;
	IT absqr    = t0 + abz2;
	IT dapcx    = da * pcx;
	IT dapcy    = da * pcy;
	IT dapcz    = da * pcz;
	IT acx      = dapcx - lax;
	IT acy      = dapcy - lay;
	IT acz      = dapcz - laz;
	IT acx2     = acx * acx;
	IT acy2     = acy * acy;
	IT acz2     = acz * acz;
	IT t1       = acx2 + acy2;
	IT acsqr    = t1 + acz2;
	IT db2      = db * db;
	IT db2acsqr = db2 * acsqr;
	IT dbpcx    = db * pcx;
	IT dbpcy    = db * pcy;
	IT dbpcz    = db * pcz;
	IT bcx      = dbpcx - lbx;
	IT bcy      = dbpcy - lby;
	IT bcz      = dbpcz - lbz;
	IT bcx2     = bcx * bcx;
	IT bcy2     = bcy * bcy;
	IT bcz2     = bcz * bcz;
	IT t2       = bcx2 + bcy2;
	IT bcsqr    = t2 + bcz2;
	IT da2      = da * da;
	IT da2bcsqr = da2 * bcsqr;
	IT ac_bc    = db2acsqr + da2bcsqr;
	IT d        = absqr - ac_bc;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE_exact(const GenericPoint3T<IT, ET> &pa,
                                          const GenericPoint3T<IT, ET> &pb,
                                          ET pcx, ET pcy, ET pcz)
{
	ET lax, lay, laz, da, lbx, lby, lbz, db;
	pa.getExactLambda(lax, lay, laz, da);
	pb.getExactLambda(lbx, lby, lbz, db);
	ET dalbx    = da * lbx;
	ET dalby    = da * lby;
	ET dalbz    = da * lbz;
	ET dblax    = db * lax;
	ET dblay    = db * lay;
	ET dblaz    = db * laz;
	ET abx      = dalbx - dblax;
	ET aby      = dalby - dblay;
	ET abz      = dalbz - dblaz;
	ET abx2     = abx * abx;
	ET aby2     = aby * aby;
	ET abz2     = abz * abz;
	ET t0       = abx2 + aby2;
	ET absqr    = t0 + abz2;
	ET dapcx    = da * pcx;
	ET dapcy    = da * pcy;
	ET dapcz    = da * pcz;
	ET acx      = dapcx - lax;
	ET acy      = dapcy - lay;
	ET acz      = dapcz - laz;
	ET acx2     = acx * acx;
	ET acy2     = acy * acy;
	ET acz2     = acz * acz;
	ET t1       = acx2 + acy2;
	ET acsqr    = t1 + acz2;
	ET db2      = db * db;
	ET db2acsqr = db2 * acsqr;
	ET dbpcx    = db * pcx;
	ET dbpcy    = db * pcy;
	ET dbpcz    = db * pcz;
	ET bcx      = dbpcx - lbx;
	ET bcy      = dbpcy - lby;
	ET bcz      = dbpcz - lbz;
	ET bcx2     = bcx * bcx;
	ET bcy2     = bcy * bcy;
	ET bcz2     = bcz * bcz;
	ET t2       = bcx2 + bcy2;
	ET bcsqr    = t2 + bcz2;
	ET da2      = da * da;
	ET da2bcsqr = da2 * bcsqr;
	ET ac_bc    = db2acsqr + da2bcsqr;
	ET d        = absqr - ac_bc;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE_expansion(const GenericPoint3T<IT, ET> &pa,
                                              const GenericPoint3T<IT, ET> &pb,
                                              double pcx, double pcy,
                                              double pcz)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lax_p[32], *lax = lax_p, lay_p[32], *lay = lay_p, laz_p[32],
	                  *laz = laz_p, da_p[32], *da = da_p, lbx_p[32], *lbx = lbx_p,
	                  lby_p[32], *lby = lby_p, lbz_p[32], *lbz = lbz_p, db_p[32],
	                  *db = db_p;
	int lax_len = 32, lay_len = 32, laz_len = 32, da_len = 32, lbx_len = 32,
	    lby_len = 32, lbz_len = 32, db_len = 32;
	pa.getExpansionLambda(&lax, lax_len, &lay, lay_len, &laz, laz_len, &da,
	                      da_len);
	pb.getExpansionLambda(&lbx, lbx_len, &lby, lby_len, &lbz, lbz_len, &db,
	                      db_len);
	if ((da[da_len - 1] != 0) && (db[db_len - 1] != 0))
	{
		expansionObject o;
		double          dalbx_p[32], *dalbx = dalbx_p;
		int             dalbx_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lbx_len, lbx, &dalbx, 32);
		double dalby_p[32], *dalby = dalby_p;
		int    dalby_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lby_len, lby, &dalby, 32);
		double dalbz_p[32], *dalbz = dalbz_p;
		int    dalbz_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lbz_len, lbz, &dalbz, 32);
		double dblax_p[32], *dblax = dblax_p;
		int    dblax_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lax_len, lax, &dblax, 32);
		double dblay_p[32], *dblay = dblay_p;
		int    dblay_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lay_len, lay, &dblay, 32);
		double dblaz_p[32], *dblaz = dblaz_p;
		int    dblaz_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, laz_len, laz, &dblaz, 32);
		double abx_p[32], *abx = abx_p;
		int    abx_len =
		  o.Gen_Diff_With_PreAlloc(dalbx_len, dalbx, dblax_len, dblax, &abx, 32);
		double aby_p[32], *aby = aby_p;
		int    aby_len =
		  o.Gen_Diff_With_PreAlloc(dalby_len, dalby, dblay_len, dblay, &aby, 32);
		double abz_p[32], *abz = abz_p;
		int    abz_len =
		  o.Gen_Diff_With_PreAlloc(dalbz_len, dalbz, dblaz_len, dblaz, &abz, 32);
		double abx2_p[32], *abx2 = abx2_p;
		int    abx2_len =
		  o.Gen_Product_With_PreAlloc(abx_len, abx, abx_len, abx, &abx2, 32);
		double aby2_p[32], *aby2 = aby2_p;
		int    aby2_len =
		  o.Gen_Product_With_PreAlloc(aby_len, aby, aby_len, aby, &aby2, 32);
		double abz2_p[32], *abz2 = abz2_p;
		int    abz2_len =
		  o.Gen_Product_With_PreAlloc(abz_len, abz, abz_len, abz, &abz2, 32);
		double t0_p[32], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Sum_With_PreAlloc(abx2_len, abx2, aby2_len, aby2, &t0, 32);
		double absqr_p[32], *absqr = absqr_p;
		int    absqr_len =
		  o.Gen_Sum_With_PreAlloc(t0_len, t0, abz2_len, abz2, &absqr, 32);
		double dapcx_p[32], *dapcx = dapcx_p;
		int    dapcx_len = o.Gen_Scale_With_PreAlloc(da_len, da, pcx, &dapcx, 32);
		double dapcy_p[32], *dapcy = dapcy_p;
		int    dapcy_len = o.Gen_Scale_With_PreAlloc(da_len, da, pcy, &dapcy, 32);
		double dapcz_p[32], *dapcz = dapcz_p;
		int    dapcz_len = o.Gen_Scale_With_PreAlloc(da_len, da, pcz, &dapcz, 32);
		double acx_p[32], *acx = acx_p;
		int    acx_len =
		  o.Gen_Diff_With_PreAlloc(dapcx_len, dapcx, lax_len, lax, &acx, 32);
		double acy_p[32], *acy = acy_p;
		int    acy_len =
		  o.Gen_Diff_With_PreAlloc(dapcy_len, dapcy, lay_len, lay, &acy, 32);
		double acz_p[32], *acz = acz_p;
		int    acz_len =
		  o.Gen_Diff_With_PreAlloc(dapcz_len, dapcz, laz_len, laz, &acz, 32);
		double acx2_p[32], *acx2 = acx2_p;
		int    acx2_len =
		  o.Gen_Product_With_PreAlloc(acx_len, acx, acx_len, acx, &acx2, 32);
		double acy2_p[32], *acy2 = acy2_p;
		int    acy2_len =
		  o.Gen_Product_With_PreAlloc(acy_len, acy, acy_len, acy, &acy2, 32);
		double acz2_p[32], *acz2 = acz2_p;
		int    acz2_len =
		  o.Gen_Product_With_PreAlloc(acz_len, acz, acz_len, acz, &acz2, 32);
		double t1_p[32], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Sum_With_PreAlloc(acx2_len, acx2, acy2_len, acy2, &t1, 32);
		double acsqr_p[32], *acsqr = acsqr_p;
		int    acsqr_len =
		  o.Gen_Sum_With_PreAlloc(t1_len, t1, acz2_len, acz2, &acsqr, 32);
		double db2_p[32], *db2 = db2_p;
		int db2_len = o.Gen_Product_With_PreAlloc(db_len, db, db_len, db, &db2, 32);
		double db2acsqr_p[32], *db2acsqr = db2acsqr_p;
		int    db2acsqr_len = o.Gen_Product_With_PreAlloc(db2_len, db2, acsqr_len,
		                                                  acsqr, &db2acsqr, 32);
		double dbpcx_p[32], *dbpcx = dbpcx_p;
		int    dbpcx_len = o.Gen_Scale_With_PreAlloc(db_len, db, pcx, &dbpcx, 32);
		double dbpcy_p[32], *dbpcy = dbpcy_p;
		int    dbpcy_len = o.Gen_Scale_With_PreAlloc(db_len, db, pcy, &dbpcy, 32);
		double dbpcz_p[32], *dbpcz = dbpcz_p;
		int    dbpcz_len = o.Gen_Scale_With_PreAlloc(db_len, db, pcz, &dbpcz, 32);
		double bcx_p[32], *bcx = bcx_p;
		int    bcx_len =
		  o.Gen_Diff_With_PreAlloc(dbpcx_len, dbpcx, lbx_len, lbx, &bcx, 32);
		double bcy_p[32], *bcy = bcy_p;
		int    bcy_len =
		  o.Gen_Diff_With_PreAlloc(dbpcy_len, dbpcy, lby_len, lby, &bcy, 32);
		double bcz_p[32], *bcz = bcz_p;
		int    bcz_len =
		  o.Gen_Diff_With_PreAlloc(dbpcz_len, dbpcz, lbz_len, lbz, &bcz, 32);
		double bcx2_p[32], *bcx2 = bcx2_p;
		int    bcx2_len =
		  o.Gen_Product_With_PreAlloc(bcx_len, bcx, bcx_len, bcx, &bcx2, 32);
		double bcy2_p[32], *bcy2 = bcy2_p;
		int    bcy2_len =
		  o.Gen_Product_With_PreAlloc(bcy_len, bcy, bcy_len, bcy, &bcy2, 32);
		double bcz2_p[32], *bcz2 = bcz2_p;
		int    bcz2_len =
		  o.Gen_Product_With_PreAlloc(bcz_len, bcz, bcz_len, bcz, &bcz2, 32);
		double t2_p[32], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Sum_With_PreAlloc(bcx2_len, bcx2, bcy2_len, bcy2, &t2, 32);
		double bcsqr_p[32], *bcsqr = bcsqr_p;
		int    bcsqr_len =
		  o.Gen_Sum_With_PreAlloc(t2_len, t2, bcz2_len, bcz2, &bcsqr, 32);
		double da2_p[32], *da2 = da2_p;
		int da2_len = o.Gen_Product_With_PreAlloc(da_len, da, da_len, da, &da2, 32);
		double da2bcsqr_p[32], *da2bcsqr = da2bcsqr_p;
		int    da2bcsqr_len = o.Gen_Product_With_PreAlloc(da2_len, da2, bcsqr_len,
		                                                  bcsqr, &da2bcsqr, 32);
		double ac_bc_p[32], *ac_bc = ac_bc_p;
		int    ac_bc_len = o.Gen_Sum_With_PreAlloc(db2acsqr_len, db2acsqr,
		                                           da2bcsqr_len, da2bcsqr, &ac_bc, 32);
		double d_p[32], *d = d_p;
		int    d_len =
		  o.Gen_Diff_With_PreAlloc(absqr_len, absqr, ac_bc_len, ac_bc, &d, 32);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (ac_bc_p != ac_bc)
			FreeDoubles(ac_bc);
		if (da2bcsqr_p != da2bcsqr)
			FreeDoubles(da2bcsqr);
		if (da2_p != da2)
			FreeDoubles(da2);
		if (bcsqr_p != bcsqr)
			FreeDoubles(bcsqr);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (bcz2_p != bcz2)
			FreeDoubles(bcz2);
		if (bcy2_p != bcy2)
			FreeDoubles(bcy2);
		if (bcx2_p != bcx2)
			FreeDoubles(bcx2);
		if (bcz_p != bcz)
			FreeDoubles(bcz);
		if (bcy_p != bcy)
			FreeDoubles(bcy);
		if (bcx_p != bcx)
			FreeDoubles(bcx);
		if (dbpcz_p != dbpcz)
			FreeDoubles(dbpcz);
		if (dbpcy_p != dbpcy)
			FreeDoubles(dbpcy);
		if (dbpcx_p != dbpcx)
			FreeDoubles(dbpcx);
		if (db2acsqr_p != db2acsqr)
			FreeDoubles(db2acsqr);
		if (db2_p != db2)
			FreeDoubles(db2);
		if (acsqr_p != acsqr)
			FreeDoubles(acsqr);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (acz2_p != acz2)
			FreeDoubles(acz2);
		if (acy2_p != acy2)
			FreeDoubles(acy2);
		if (acx2_p != acx2)
			FreeDoubles(acx2);
		if (acz_p != acz)
			FreeDoubles(acz);
		if (acy_p != acy)
			FreeDoubles(acy);
		if (acx_p != acx)
			FreeDoubles(acx);
		if (dapcz_p != dapcz)
			FreeDoubles(dapcz);
		if (dapcy_p != dapcy)
			FreeDoubles(dapcy);
		if (dapcx_p != dapcx)
			FreeDoubles(dapcx);
		if (absqr_p != absqr)
			FreeDoubles(absqr);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (abz2_p != abz2)
			FreeDoubles(abz2);
		if (aby2_p != aby2)
			FreeDoubles(aby2);
		if (abx2_p != abx2)
			FreeDoubles(abx2);
		if (abz_p != abz)
			FreeDoubles(abz);
		if (aby_p != aby)
			FreeDoubles(aby);
		if (abx_p != abx)
			FreeDoubles(abx);
		if (dblaz_p != dblaz)
			FreeDoubles(dblaz);
		if (dblay_p != dblay)
			FreeDoubles(dblay);
		if (dblax_p != dblax)
			FreeDoubles(dblax);
		if (dalbz_p != dalbz)
			FreeDoubles(dalbz);
		if (dalby_p != dalby)
			FreeDoubles(dalby);
		if (dalbx_p != dalbx)
			FreeDoubles(dalbx);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lax_p != lax)
			FreeDoubles(lax);
		if (lay_p != lay)
			FreeDoubles(lay);
		if (laz_p != laz)
			FreeDoubles(laz);
		if (da_p != da)
			FreeDoubles(da);
		if (lbx_p != lbx)
			FreeDoubles(lbx);
		if (lby_p != lby)
			FreeDoubles(lby);
		if (lbz_p != lbz)
			FreeDoubles(lbz);
		if (db_p != db)
			FreeDoubles(db);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSegmentDiametricalSphere_IIE_exact<IT, ET>(pa, pb, pcx, pcy, pcz);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    double pcx, double pcy, double pcz)
{
	Sign ret;
	ret = inSegmentDiametricalSphere_IIE_interval<IT, ET>(pa, pb, pcx, pcy, pcz);
	if (is_sign_reliable(ret))
		return ret;
	return inSegmentDiametricalSphere_IIE_expansion<IT, ET>(pa, pb, pcx, pcy,
	                                                        pcz);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_IIE(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    const GenericPoint3T<IT, ET> &pc)
{
	return inSegmentDiametricalSphere_IIE<IT, ET>(pa, pb, pc.x(), pc.y(), pc.z());
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III_interval(const GenericPoint3T<IT, ET> &pa,
                                             const GenericPoint3T<IT, ET> &pb,
                                             const GenericPoint3T<IT, ET> &pc)
{
	IT lax, lay, laz, da, lbx, lby, lbz, db, lcx, lcy, lcz, dc;
	if (!pa.getIntervalLambda(lax, lay, laz, da) ||
	    !pb.getIntervalLambda(lbx, lby, lbz, db) ||
	    !pc.getIntervalLambda(lcx, lcy, lcz, dc))
		return Sign::UNCERTAIN;

	typename IT::Protector P;

	IT dalbx    = da * lbx;
	IT dalby    = da * lby;
	IT dalbz    = da * lbz;
	IT dblax    = db * lax;
	IT dblay    = db * lay;
	IT dblaz    = db * laz;
	IT abx      = dalbx - dblax;
	IT aby      = dalby - dblay;
	IT abz      = dalbz - dblaz;
	IT abx2     = abx * abx;
	IT aby2     = aby * aby;
	IT abz2     = abz * abz;
	IT t0       = abx2 + aby2;
	IT absqr    = t0 + abz2;
	IT dc2      = dc * dc;
	IT dc2absqr = dc2 * absqr;
	IT dalcx    = da * lcx;
	IT dalcy    = da * lcy;
	IT dalcz    = da * lcz;
	IT dclax    = dc * lax;
	IT dclay    = dc * lay;
	IT dclaz    = dc * laz;
	IT acx      = dalcx - dclax;
	IT acy      = dalcy - dclay;
	IT acz      = dalcz - dclaz;
	IT acx2     = acx * acx;
	IT acy2     = acy * acy;
	IT acz2     = acz * acz;
	IT t1       = acx2 + acy2;
	IT acsqr    = t1 + acz2;
	IT db2      = db * db;
	IT db2acsqr = db2 * acsqr;
	IT dclbx    = dc * lbx;
	IT dclby    = dc * lby;
	IT dclbz    = dc * lbz;
	IT dblcx    = db * lcx;
	IT dblcy    = db * lcy;
	IT dblcz    = db * lcz;
	IT bcx      = dblcx - dclbx;
	IT bcy      = dblcy - dclby;
	IT bcz      = dblcz - dclbz;
	IT bcx2     = bcx * bcx;
	IT bcy2     = bcy * bcy;
	IT bcz2     = bcz * bcz;
	IT t2       = bcx2 + bcy2;
	IT bcsqr    = t2 + bcz2;
	IT da2      = da * da;
	IT da2bcsqr = da2 * bcsqr;
	IT ac_bc    = db2acsqr + da2bcsqr;
	IT d        = dc2absqr - ac_bc;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III_exact(const GenericPoint3T<IT, ET> &pa,
                                          const GenericPoint3T<IT, ET> &pb,
                                          const GenericPoint3T<IT, ET> &pc)
{
	ET lax, lay, laz, da, lbx, lby, lbz, db, lcx, lcy, lcz, dc;
	pa.getExactLambda(lax, lay, laz, da);
	pb.getExactLambda(lbx, lby, lbz, db);
	pc.getExactLambda(lcx, lcy, lcz, dc);
	ET dalbx    = da * lbx;
	ET dalby    = da * lby;
	ET dalbz    = da * lbz;
	ET dblax    = db * lax;
	ET dblay    = db * lay;
	ET dblaz    = db * laz;
	ET abx      = dalbx - dblax;
	ET aby      = dalby - dblay;
	ET abz      = dalbz - dblaz;
	ET abx2     = abx * abx;
	ET aby2     = aby * aby;
	ET abz2     = abz * abz;
	ET t0       = abx2 + aby2;
	ET absqr    = t0 + abz2;
	ET dc2      = dc * dc;
	ET dc2absqr = dc2 * absqr;
	ET dalcx    = da * lcx;
	ET dalcy    = da * lcy;
	ET dalcz    = da * lcz;
	ET dclax    = dc * lax;
	ET dclay    = dc * lay;
	ET dclaz    = dc * laz;
	ET acx      = dalcx - dclax;
	ET acy      = dalcy - dclay;
	ET acz      = dalcz - dclaz;
	ET acx2     = acx * acx;
	ET acy2     = acy * acy;
	ET acz2     = acz * acz;
	ET t1       = acx2 + acy2;
	ET acsqr    = t1 + acz2;
	ET db2      = db * db;
	ET db2acsqr = db2 * acsqr;
	ET dclbx    = dc * lbx;
	ET dclby    = dc * lby;
	ET dclbz    = dc * lbz;
	ET dblcx    = db * lcx;
	ET dblcy    = db * lcy;
	ET dblcz    = db * lcz;
	ET bcx      = dblcx - dclbx;
	ET bcy      = dblcy - dclby;
	ET bcz      = dblcz - dclbz;
	ET bcx2     = bcx * bcx;
	ET bcy2     = bcy * bcy;
	ET bcz2     = bcz * bcz;
	ET t2       = bcx2 + bcy2;
	ET bcsqr    = t2 + bcz2;
	ET da2      = da * da;
	ET da2bcsqr = da2 * bcsqr;
	ET ac_bc    = db2acsqr + da2bcsqr;
	ET d        = dc2absqr - ac_bc;
	return OMC::sign(d);
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III_expansion(const GenericPoint3T<IT, ET> &pa,
                                              const GenericPoint3T<IT, ET> &pb,
                                              const GenericPoint3T<IT, ET> &pc)
{
	double return_value = NAN;
#ifdef CHECK_FOR_XYZERFLOWS
	feclearexcept(FE_ALL_EXCEPT);
#endif
	double lax_p[16], *lax = lax_p, lay_p[16], *lay = lay_p, laz_p[16],
	                  *laz = laz_p, da_p[16], *da = da_p, lbx_p[16], *lbx = lbx_p,
	                  lby_p[16], *lby = lby_p, lbz_p[16], *lbz = lbz_p, db_p[16],
	                  *db = db_p, lcx_p[16], *lcx = lcx_p, lcy_p[16],
	                  *lcy = lcy_p, lcz_p[16], *lcz = lcz_p, dc_p[16], *dc = dc_p;
	int lax_len = 16, lay_len = 16, laz_len = 16, da_len = 16, lbx_len = 16,
	    lby_len = 16, lbz_len = 16, db_len = 16, lcx_len = 16, lcy_len = 16,
	    lcz_len = 16, dc_len = 16;
	pa.getExpansionLambda(&lax, lax_len, &lay, lay_len, &laz, laz_len, &da,
	                      da_len);
	pb.getExpansionLambda(&lbx, lbx_len, &lby, lby_len, &lbz, lbz_len, &db,
	                      db_len);
	pc.getExpansionLambda(&lcx, lcx_len, &lcy, lcy_len, &lcz, lcz_len, &dc,
	                      dc_len);
	if ((da[da_len - 1] != 0) && (db[db_len - 1] != 0) && (dc[dc_len - 1] != 0))
	{
		expansionObject o;
		double          dalbx_p[16], *dalbx = dalbx_p;
		int             dalbx_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lbx_len, lbx, &dalbx, 16);
		double dalby_p[16], *dalby = dalby_p;
		int    dalby_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lby_len, lby, &dalby, 16);
		double dalbz_p[16], *dalbz = dalbz_p;
		int    dalbz_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lbz_len, lbz, &dalbz, 16);
		double dblax_p[16], *dblax = dblax_p;
		int    dblax_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lax_len, lax, &dblax, 16);
		double dblay_p[16], *dblay = dblay_p;
		int    dblay_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lay_len, lay, &dblay, 16);
		double dblaz_p[16], *dblaz = dblaz_p;
		int    dblaz_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, laz_len, laz, &dblaz, 16);
		double abx_p[16], *abx = abx_p;
		int    abx_len =
		  o.Gen_Diff_With_PreAlloc(dalbx_len, dalbx, dblax_len, dblax, &abx, 16);
		double aby_p[16], *aby = aby_p;
		int    aby_len =
		  o.Gen_Diff_With_PreAlloc(dalby_len, dalby, dblay_len, dblay, &aby, 16);
		double abz_p[16], *abz = abz_p;
		int    abz_len =
		  o.Gen_Diff_With_PreAlloc(dalbz_len, dalbz, dblaz_len, dblaz, &abz, 16);
		double abx2_p[16], *abx2 = abx2_p;
		int    abx2_len =
		  o.Gen_Product_With_PreAlloc(abx_len, abx, abx_len, abx, &abx2, 16);
		double aby2_p[16], *aby2 = aby2_p;
		int    aby2_len =
		  o.Gen_Product_With_PreAlloc(aby_len, aby, aby_len, aby, &aby2, 16);
		double abz2_p[16], *abz2 = abz2_p;
		int    abz2_len =
		  o.Gen_Product_With_PreAlloc(abz_len, abz, abz_len, abz, &abz2, 16);
		double t0_p[16], *t0 = t0_p;
		int    t0_len =
		  o.Gen_Sum_With_PreAlloc(abx2_len, abx2, aby2_len, aby2, &t0, 16);
		double absqr_p[16], *absqr = absqr_p;
		int    absqr_len =
		  o.Gen_Sum_With_PreAlloc(t0_len, t0, abz2_len, abz2, &absqr, 16);
		double dc2_p[16], *dc2 = dc2_p;
		int dc2_len = o.Gen_Product_With_PreAlloc(dc_len, dc, dc_len, dc, &dc2, 16);
		double dc2absqr_p[16], *dc2absqr = dc2absqr_p;
		int    dc2absqr_len = o.Gen_Product_With_PreAlloc(dc2_len, dc2, absqr_len,
		                                                  absqr, &dc2absqr, 16);
		double dalcx_p[16], *dalcx = dalcx_p;
		int    dalcx_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lcx_len, lcx, &dalcx, 16);
		double dalcy_p[16], *dalcy = dalcy_p;
		int    dalcy_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lcy_len, lcy, &dalcy, 16);
		double dalcz_p[16], *dalcz = dalcz_p;
		int    dalcz_len =
		  o.Gen_Product_With_PreAlloc(da_len, da, lcz_len, lcz, &dalcz, 16);
		double dclax_p[16], *dclax = dclax_p;
		int    dclax_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lax_len, lax, &dclax, 16);
		double dclay_p[16], *dclay = dclay_p;
		int    dclay_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lay_len, lay, &dclay, 16);
		double dclaz_p[16], *dclaz = dclaz_p;
		int    dclaz_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, laz_len, laz, &dclaz, 16);
		double acx_p[16], *acx = acx_p;
		int    acx_len =
		  o.Gen_Diff_With_PreAlloc(dalcx_len, dalcx, dclax_len, dclax, &acx, 16);
		double acy_p[16], *acy = acy_p;
		int    acy_len =
		  o.Gen_Diff_With_PreAlloc(dalcy_len, dalcy, dclay_len, dclay, &acy, 16);
		double acz_p[16], *acz = acz_p;
		int    acz_len =
		  o.Gen_Diff_With_PreAlloc(dalcz_len, dalcz, dclaz_len, dclaz, &acz, 16);
		double acx2_p[16], *acx2 = acx2_p;
		int    acx2_len =
		  o.Gen_Product_With_PreAlloc(acx_len, acx, acx_len, acx, &acx2, 16);
		double acy2_p[16], *acy2 = acy2_p;
		int    acy2_len =
		  o.Gen_Product_With_PreAlloc(acy_len, acy, acy_len, acy, &acy2, 16);
		double acz2_p[16], *acz2 = acz2_p;
		int    acz2_len =
		  o.Gen_Product_With_PreAlloc(acz_len, acz, acz_len, acz, &acz2, 16);
		double t1_p[16], *t1 = t1_p;
		int    t1_len =
		  o.Gen_Sum_With_PreAlloc(acx2_len, acx2, acy2_len, acy2, &t1, 16);
		double acsqr_p[16], *acsqr = acsqr_p;
		int    acsqr_len =
		  o.Gen_Sum_With_PreAlloc(t1_len, t1, acz2_len, acz2, &acsqr, 16);
		double db2_p[16], *db2 = db2_p;
		int db2_len = o.Gen_Product_With_PreAlloc(db_len, db, db_len, db, &db2, 16);
		double db2acsqr_p[16], *db2acsqr = db2acsqr_p;
		int    db2acsqr_len = o.Gen_Product_With_PreAlloc(db2_len, db2, acsqr_len,
		                                                  acsqr, &db2acsqr, 16);
		double dclbx_p[16], *dclbx = dclbx_p;
		int    dclbx_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lbx_len, lbx, &dclbx, 16);
		double dclby_p[16], *dclby = dclby_p;
		int    dclby_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lby_len, lby, &dclby, 16);
		double dclbz_p[16], *dclbz = dclbz_p;
		int    dclbz_len =
		  o.Gen_Product_With_PreAlloc(dc_len, dc, lbz_len, lbz, &dclbz, 16);
		double dblcx_p[16], *dblcx = dblcx_p;
		int    dblcx_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lcx_len, lcx, &dblcx, 16);
		double dblcy_p[16], *dblcy = dblcy_p;
		int    dblcy_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lcy_len, lcy, &dblcy, 16);
		double dblcz_p[16], *dblcz = dblcz_p;
		int    dblcz_len =
		  o.Gen_Product_With_PreAlloc(db_len, db, lcz_len, lcz, &dblcz, 16);
		double bcx_p[16], *bcx = bcx_p;
		int    bcx_len =
		  o.Gen_Diff_With_PreAlloc(dblcx_len, dblcx, dclbx_len, dclbx, &bcx, 16);
		double bcy_p[16], *bcy = bcy_p;
		int    bcy_len =
		  o.Gen_Diff_With_PreAlloc(dblcy_len, dblcy, dclby_len, dclby, &bcy, 16);
		double bcz_p[16], *bcz = bcz_p;
		int    bcz_len =
		  o.Gen_Diff_With_PreAlloc(dblcz_len, dblcz, dclbz_len, dclbz, &bcz, 16);
		double bcx2_p[16], *bcx2 = bcx2_p;
		int    bcx2_len =
		  o.Gen_Product_With_PreAlloc(bcx_len, bcx, bcx_len, bcx, &bcx2, 16);
		double bcy2_p[16], *bcy2 = bcy2_p;
		int    bcy2_len =
		  o.Gen_Product_With_PreAlloc(bcy_len, bcy, bcy_len, bcy, &bcy2, 16);
		double bcz2_p[16], *bcz2 = bcz2_p;
		int    bcz2_len =
		  o.Gen_Product_With_PreAlloc(bcz_len, bcz, bcz_len, bcz, &bcz2, 16);
		double t2_p[16], *t2 = t2_p;
		int    t2_len =
		  o.Gen_Sum_With_PreAlloc(bcx2_len, bcx2, bcy2_len, bcy2, &t2, 16);
		double bcsqr_p[16], *bcsqr = bcsqr_p;
		int    bcsqr_len =
		  o.Gen_Sum_With_PreAlloc(t2_len, t2, bcz2_len, bcz2, &bcsqr, 16);
		double da2_p[16], *da2 = da2_p;
		int da2_len = o.Gen_Product_With_PreAlloc(da_len, da, da_len, da, &da2, 16);
		double da2bcsqr_p[16], *da2bcsqr = da2bcsqr_p;
		int    da2bcsqr_len = o.Gen_Product_With_PreAlloc(da2_len, da2, bcsqr_len,
		                                                  bcsqr, &da2bcsqr, 16);
		double ac_bc_p[16], *ac_bc = ac_bc_p;
		int    ac_bc_len = o.Gen_Sum_With_PreAlloc(db2acsqr_len, db2acsqr,
		                                           da2bcsqr_len, da2bcsqr, &ac_bc, 16);
		double d_p[16], *d = d_p;
		int    d_len = o.Gen_Diff_With_PreAlloc(dc2absqr_len, dc2absqr, ac_bc_len,
		                                        ac_bc, &d, 16);

		return_value = d[d_len - 1];
		if (d_p != d)
			FreeDoubles(d);
		if (ac_bc_p != ac_bc)
			FreeDoubles(ac_bc);
		if (da2bcsqr_p != da2bcsqr)
			FreeDoubles(da2bcsqr);
		if (da2_p != da2)
			FreeDoubles(da2);
		if (bcsqr_p != bcsqr)
			FreeDoubles(bcsqr);
		if (t2_p != t2)
			FreeDoubles(t2);
		if (bcz2_p != bcz2)
			FreeDoubles(bcz2);
		if (bcy2_p != bcy2)
			FreeDoubles(bcy2);
		if (bcx2_p != bcx2)
			FreeDoubles(bcx2);
		if (bcz_p != bcz)
			FreeDoubles(bcz);
		if (bcy_p != bcy)
			FreeDoubles(bcy);
		if (bcx_p != bcx)
			FreeDoubles(bcx);
		if (dblcz_p != dblcz)
			FreeDoubles(dblcz);
		if (dblcy_p != dblcy)
			FreeDoubles(dblcy);
		if (dblcx_p != dblcx)
			FreeDoubles(dblcx);
		if (dclbz_p != dclbz)
			FreeDoubles(dclbz);
		if (dclby_p != dclby)
			FreeDoubles(dclby);
		if (dclbx_p != dclbx)
			FreeDoubles(dclbx);
		if (db2acsqr_p != db2acsqr)
			FreeDoubles(db2acsqr);
		if (db2_p != db2)
			FreeDoubles(db2);
		if (acsqr_p != acsqr)
			FreeDoubles(acsqr);
		if (t1_p != t1)
			FreeDoubles(t1);
		if (acz2_p != acz2)
			FreeDoubles(acz2);
		if (acy2_p != acy2)
			FreeDoubles(acy2);
		if (acx2_p != acx2)
			FreeDoubles(acx2);
		if (acz_p != acz)
			FreeDoubles(acz);
		if (acy_p != acy)
			FreeDoubles(acy);
		if (acx_p != acx)
			FreeDoubles(acx);
		if (dclaz_p != dclaz)
			FreeDoubles(dclaz);
		if (dclay_p != dclay)
			FreeDoubles(dclay);
		if (dclax_p != dclax)
			FreeDoubles(dclax);
		if (dalcz_p != dalcz)
			FreeDoubles(dalcz);
		if (dalcy_p != dalcy)
			FreeDoubles(dalcy);
		if (dalcx_p != dalcx)
			FreeDoubles(dalcx);
		if (dc2absqr_p != dc2absqr)
			FreeDoubles(dc2absqr);
		if (dc2_p != dc2)
			FreeDoubles(dc2);
		if (absqr_p != absqr)
			FreeDoubles(absqr);
		if (t0_p != t0)
			FreeDoubles(t0);
		if (abz2_p != abz2)
			FreeDoubles(abz2);
		if (aby2_p != aby2)
			FreeDoubles(aby2);
		if (abx2_p != abx2)
			FreeDoubles(abx2);
		if (abz_p != abz)
			FreeDoubles(abz);
		if (aby_p != aby)
			FreeDoubles(aby);
		if (abx_p != abx)
			FreeDoubles(abx);
		if (dblaz_p != dblaz)
			FreeDoubles(dblaz);
		if (dblay_p != dblay)
			FreeDoubles(dblay);
		if (dblax_p != dblax)
			FreeDoubles(dblax);
		if (dalbz_p != dalbz)
			FreeDoubles(dalbz);
		if (dalby_p != dalby)
			FreeDoubles(dalby);
		if (dalbx_p != dalbx)
			FreeDoubles(dalbx);
	}

	if (!GenericPoint3T<IT, ET>::global_cached_values_enabled())
	{
		if (lax_p != lax)
			FreeDoubles(lax);
		if (lay_p != lay)
			FreeDoubles(lay);
		if (laz_p != laz)
			FreeDoubles(laz);
		if (da_p != da)
			FreeDoubles(da);
		if (lbx_p != lbx)
			FreeDoubles(lbx);
		if (lby_p != lby)
			FreeDoubles(lby);
		if (lbz_p != lbz)
			FreeDoubles(lbz);
		if (db_p != db)
			FreeDoubles(db);
		if (lcx_p != lcx)
			FreeDoubles(lcx);
		if (lcy_p != lcy)
			FreeDoubles(lcy);
		if (lcz_p != lcz)
			FreeDoubles(lcz);
		if (dc_p != dc)
			FreeDoubles(dc);
	}

#ifdef CHECK_FOR_XYZERFLOWS
	if (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW))
		return inSegmentDiametricalSphere_III_exact<IT, ET>(pa, pb, pc);
#endif

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign inSegmentDiametricalSphere_III(const GenericPoint3T<IT, ET> &pa,
                                    const GenericPoint3T<IT, ET> &pb,
                                    const GenericPoint3T<IT, ET> &pc)
{
	Sign ret;
	ret = inSegmentDiametricalSphere_III_interval<IT, ET>(pa, pb, pc);
	if (is_sign_reliable(ret))
		return ret;
	return inSegmentDiametricalSphere_III_expansion<IT, ET>(pa, pb, pc);
}

template <typename IT>
Sign largerTriangleCircumSphere_interval(IT pax, IT pay, IT paz, IT pbx, IT pby,
                                         IT pbz, IT pcx, IT pcy, IT pcz, IT pdx,
                                         IT pdy, IT pdz)
{
	typename IT::Protector P;

	IT acx   = pcx - pax;
	IT acy   = pcy - pay;
	IT acz   = pcz - paz;
	IT acx2  = acx * acx;
	IT acy2  = acy * acy;
	IT acz2  = acz * acz;
	IT t0    = acx2 + acy2;
	IT acsqr = t0 + acz2;
	IT bcx   = pcx - pbx;
	IT bcy   = pcy - pby;
	IT bcz   = pcz - pbz;
	IT bcx2  = bcx * bcx;
	IT bcy2  = bcy * bcy;
	IT bcz2  = bcz * bcz;
	IT t1    = bcx2 + bcy2;
	IT bcsqr = t1 + bcz2;
	IT adx   = pdx - pax;
	IT ady   = pdy - pay;
	IT adz   = pdz - paz;
	IT adx2  = adx * adx;
	IT ady2  = ady * ady;
	IT adz2  = adz * adz;
	IT t2    = adx2 + ady2;
	IT adsqr = t2 + adz2;
	IT bdx   = pdx - pbx;
	IT bdy   = pdy - pby;
	IT bdz   = pdz - pbz;
	IT bdx2  = bdx * bdx;
	IT bdy2  = bdy * bdy;
	IT bdz2  = bdz * bdz;
	IT t3    = bdx2 + bdy2;
	IT bdsqr = t3 + bdz2;
	IT dotcx = acx * bcx;
	IT dotcy = acy * bcy;
	IT dotcz = acz * bcz;
	IT t4    = dotcx + dotcy;
	IT dotc  = t4 + dotcz;
	IT dotc2 = dotc * dotc;
	IT dotdx = adx * bdx;
	IT dotdy = ady * bdy;
	IT dotdz = adz * bdz;
	IT t5    = dotdx + dotdy;
	IT dotd  = t5 + dotdz;
	IT dotd2 = dotd * dotd;
	IT t6    = acsqr * bcsqr;
	IT beta  = t6 * dotd2;
	IT t7    = adsqr * bdsqr;
	IT alpha = t7 * dotc2;
	IT d     = beta - alpha;
	if (!d.is_sign_reliable())
		return Sign::UNCERTAIN;
	return OMC::sign(d);
}

template <typename ET>
Sign largerTriangleCircumSphere_exact(ET pax, ET pay, ET paz, ET pbx, ET pby,
                                      ET pbz, ET pcx, ET pcy, ET pcz, ET pdx,
                                      ET pdy, ET pdz)
{
	ET acx   = pcx - pax;
	ET acy   = pcy - pay;
	ET acz   = pcz - paz;
	ET acx2  = acx * acx;
	ET acy2  = acy * acy;
	ET acz2  = acz * acz;
	ET t0    = acx2 + acy2;
	ET acsqr = t0 + acz2;
	ET bcx   = pcx - pbx;
	ET bcy   = pcy - pby;
	ET bcz   = pcz - pbz;
	ET bcx2  = bcx * bcx;
	ET bcy2  = bcy * bcy;
	ET bcz2  = bcz * bcz;
	ET t1    = bcx2 + bcy2;
	ET bcsqr = t1 + bcz2;
	ET adx   = pdx - pax;
	ET ady   = pdy - pay;
	ET adz   = pdz - paz;
	ET adx2  = adx * adx;
	ET ady2  = ady * ady;
	ET adz2  = adz * adz;
	ET t2    = adx2 + ady2;
	ET adsqr = t2 + adz2;
	ET bdx   = pdx - pbx;
	ET bdy   = pdy - pby;
	ET bdz   = pdz - pbz;
	ET bdx2  = bdx * bdx;
	ET bdy2  = bdy * bdy;
	ET bdz2  = bdz * bdz;
	ET t3    = bdx2 + bdy2;
	ET bdsqr = t3 + bdz2;
	ET dotcx = acx * bcx;
	ET dotcy = acy * bcy;
	ET dotcz = acz * bcz;
	ET t4    = dotcx + dotcy;
	ET dotc  = t4 + dotcz;
	ET dotc2 = dotc * dotc;
	ET dotdx = adx * bdx;
	ET dotdy = ady * bdy;
	ET dotdz = adz * bdz;
	ET t5    = dotdx + dotdy;
	ET dotd  = t5 + dotdz;
	ET dotd2 = dotd * dotd;
	ET t6    = acsqr * bcsqr;
	ET beta  = t6 * dotd2;
	ET t7    = adsqr * bdsqr;
	ET alpha = t7 * dotc2;
	ET d     = beta - alpha;
	return OMC::sign(d);
}

Sign largerTriangleCircumSphere_expansion(double pax, double pay, double paz,
                                          double pbx, double pby, double pbz,
                                          double pcx, double pcy, double pcz,
                                          double pdx, double pdy, double pdz)
{
	expansionObject o;
	double          acx[2];
	o.Two_Diff(pcx, pax, acx);
	double acy[2];
	o.Two_Diff(pcy, pay, acy);
	double acz[2];
	o.Two_Diff(pcz, paz, acz);
	double acx2[8];
	int    acx2_len = o.Gen_Product(2, acx, 2, acx, acx2);
	double acy2[8];
	int    acy2_len = o.Gen_Product(2, acy, 2, acy, acy2);
	double acz2[8];
	int    acz2_len = o.Gen_Product(2, acz, 2, acz, acz2);
	double t0[16];
	int    t0_len = o.Gen_Sum(acx2_len, acx2, acy2_len, acy2, t0);
	double acsqr[24];
	int    acsqr_len = o.Gen_Sum(t0_len, t0, acz2_len, acz2, acsqr);
	double bcx[2];
	o.Two_Diff(pcx, pbx, bcx);
	double bcy[2];
	o.Two_Diff(pcy, pby, bcy);
	double bcz[2];
	o.Two_Diff(pcz, pbz, bcz);
	double bcx2[8];
	int    bcx2_len = o.Gen_Product(2, bcx, 2, bcx, bcx2);
	double bcy2[8];
	int    bcy2_len = o.Gen_Product(2, bcy, 2, bcy, bcy2);
	double bcz2[8];
	int    bcz2_len = o.Gen_Product(2, bcz, 2, bcz, bcz2);
	double t1[16];
	int    t1_len = o.Gen_Sum(bcx2_len, bcx2, bcy2_len, bcy2, t1);
	double bcsqr[24];
	int    bcsqr_len = o.Gen_Sum(t1_len, t1, bcz2_len, bcz2, bcsqr);
	double adx[2];
	o.Two_Diff(pdx, pax, adx);
	double ady[2];
	o.Two_Diff(pdy, pay, ady);
	double adz[2];
	o.Two_Diff(pdz, paz, adz);
	double adx2[8];
	int    adx2_len = o.Gen_Product(2, adx, 2, adx, adx2);
	double ady2[8];
	int    ady2_len = o.Gen_Product(2, ady, 2, ady, ady2);
	double adz2[8];
	int    adz2_len = o.Gen_Product(2, adz, 2, adz, adz2);
	double t2[16];
	int    t2_len = o.Gen_Sum(adx2_len, adx2, ady2_len, ady2, t2);
	double adsqr[24];
	int    adsqr_len = o.Gen_Sum(t2_len, t2, adz2_len, adz2, adsqr);
	double bdx[2];
	o.Two_Diff(pdx, pbx, bdx);
	double bdy[2];
	o.Two_Diff(pdy, pby, bdy);
	double bdz[2];
	o.Two_Diff(pdz, pbz, bdz);
	double bdx2[8];
	int    bdx2_len = o.Gen_Product(2, bdx, 2, bdx, bdx2);
	double bdy2[8];
	int    bdy2_len = o.Gen_Product(2, bdy, 2, bdy, bdy2);
	double bdz2[8];
	int    bdz2_len = o.Gen_Product(2, bdz, 2, bdz, bdz2);
	double t3[16];
	int    t3_len = o.Gen_Sum(bdx2_len, bdx2, bdy2_len, bdy2, t3);
	double bdsqr[24];
	int    bdsqr_len = o.Gen_Sum(t3_len, t3, bdz2_len, bdz2, bdsqr);
	double dotcx[8];
	int    dotcx_len = o.Gen_Product(2, acx, 2, bcx, dotcx);
	double dotcy[8];
	int    dotcy_len = o.Gen_Product(2, acy, 2, bcy, dotcy);
	double dotcz[8];
	int    dotcz_len = o.Gen_Product(2, acz, 2, bcz, dotcz);
	double t4[16];
	int    t4_len = o.Gen_Sum(dotcx_len, dotcx, dotcy_len, dotcy, t4);
	double dotc[24];
	int    dotc_len = o.Gen_Sum(t4_len, t4, dotcz_len, dotcz, dotc);
	double dotc2_p[128], *dotc2 = dotc2_p;
	int    dotc2_len =
	  o.Gen_Product_With_PreAlloc(dotc_len, dotc, dotc_len, dotc, &dotc2, 128);
	double dotdx[8];
	int    dotdx_len = o.Gen_Product(2, adx, 2, bdx, dotdx);
	double dotdy[8];
	int    dotdy_len = o.Gen_Product(2, ady, 2, bdy, dotdy);
	double dotdz[8];
	int    dotdz_len = o.Gen_Product(2, adz, 2, bdz, dotdz);
	double t5[16];
	int    t5_len = o.Gen_Sum(dotdx_len, dotdx, dotdy_len, dotdy, t5);
	double dotd[24];
	int    dotd_len = o.Gen_Sum(t5_len, t5, dotdz_len, dotdz, dotd);
	double dotd2_p[128], *dotd2 = dotd2_p;
	int    dotd2_len =
	  o.Gen_Product_With_PreAlloc(dotd_len, dotd, dotd_len, dotd, &dotd2, 128);
	double t6_p[128], *t6 = t6_p;
	int    t6_len =
	  o.Gen_Product_With_PreAlloc(acsqr_len, acsqr, bcsqr_len, bcsqr, &t6, 128);
	double beta_p[128], *beta = beta_p;
	int    beta_len =
	  o.Gen_Product_With_PreAlloc(t6_len, t6, dotd2_len, dotd2, &beta, 128);
	double t7_p[128], *t7 = t7_p;
	int    t7_len =
	  o.Gen_Product_With_PreAlloc(adsqr_len, adsqr, bdsqr_len, bdsqr, &t7, 128);
	double alpha_p[128], *alpha = alpha_p;
	int    alpha_len =
	  o.Gen_Product_With_PreAlloc(t7_len, t7, dotc2_len, dotc2, &alpha, 128);
	double d_p[128], *d = d_p;
	int    d_len =
	  o.Gen_Diff_With_PreAlloc(beta_len, beta, alpha_len, alpha, &d, 128);

	double return_value = d[d_len - 1];
	if (d_p != d)
		FreeDoubles(d);
	if (alpha_p != alpha)
		FreeDoubles(alpha);
	if (t7_p != t7)
		FreeDoubles(t7);
	if (beta_p != beta)
		FreeDoubles(beta);
	if (t6_p != t6)
		FreeDoubles(t6);
	if (dotd2_p != dotd2)
		FreeDoubles(dotd2);
	if (dotc2_p != dotc2)
		FreeDoubles(dotc2);

	if (return_value > 0)
		return Sign::POSITIVE;
	if (return_value < 0)
		return Sign::NEGATIVE;
	if (return_value == 0)
		return Sign::ZERO;
	OMC_EXIT("Should not happen.");
}

template <typename IT, typename ET>
Sign largerTriangleCircumSphere(double pax, double pay, double paz, double pbx,
                                double pby, double pbz, double pcx, double pcy,
                                double pcz, double pdx, double pdy, double pdz)
{
	Sign ret;
	ret = largerTriangleCircumSphere_interval<IT>(pax, pay, paz, pbx, pby, pbz,
	                                              pcx, pcy, pcz, pdx, pdy, pdz);
	if (is_sign_reliable(ret))
		return ret;
	return largerTriangleCircumSphere_expansion(pax, pay, paz, pbx, pby, pbz, pcx,
	                                            pcy, pcz, pdx, pdy, pdz);
}

template <typename IT, typename ET>
Sign largerTriangleCircumSphere(const GenericPoint3T<IT, ET> &pa,
                                const GenericPoint3T<IT, ET> &pb,
                                const GenericPoint3T<IT, ET> &pc,
                                const GenericPoint3T<IT, ET> &pd)
{
	return largerTriangleCircumSphere<IT, ET>(pa.x(), pa.y(), pa.z(), pb.x(),
	                                          pb.y(), pb.z(), pc.x(), pc.y(),
	                                          pc.z(), pd.x(), pd.y(), pd.z());
}

} // namespace OMC