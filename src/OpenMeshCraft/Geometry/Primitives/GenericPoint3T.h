#pragma once

#include "Primitive3.h"
#include "Vector3T.h"

#include "ImplicitPoints/GlobalCachedValues.h"
#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#include <cassert>

namespace OMC {

/***** Forward declarations ******/
template <typename IT, typename ET>
class ExplicitPoint3T;

template <typename IT, typename ET>
class ImplicitPoint3T_SSI;

template <typename IT, typename ET>
class ImplicitPoint3T_LNC;

template <typename IT, typename ET>
class ImplicitPoint3T_LPI;

template <typename IT, typename ET>
class ImplicitPoint3T_TPI;
/*** Forward declarations end ***/

/// @brief the generic point of 3D exact implicit and explicit points
template <typename IT, typename ET>
class GenericPoint3T : public Primitive3<double>
{
public: /* types *************************************************************/
  using NT   = double;
  using VecT = Vec3T<NT>;

  using EP     = ExplicitPoint3T<IT, ET>;
  using IP_SSI = ImplicitPoint3T_SSI<IT, ET>;
  using IP_LNC = ImplicitPoint3T_LNC<IT, ET>;
  using IP_LPI = ImplicitPoint3T_LPI<IT, ET>;
  using IP_TPI = ImplicitPoint3T_TPI<IT, ET>;

  enum class PointType : uint32_t
  {
    Explicit = 0,
    Implicit = 1,
    SSI      = 2,
    LNC      = 3,
    LPI      = 4,
    TPI      = 5,
  };

public: /* members ************************************************************/
  /// Indicates the point type in derived classes.
  /// The only member variable in the base class.
  PointType m_point_type;

public: /* Constructor and Destructor *****************************************/
  GenericPoint3T(PointType pt)
    : m_point_type(pt)
  {
  }

  GenericPoint3T(const GenericPoint3T &gp)            = default;
  GenericPoint3T(GenericPoint3T &&gp)                 = default;
  GenericPoint3T &operator=(const GenericPoint3T &gp) = default;
  GenericPoint3T &operator=(GenericPoint3T &&gp)      = default;

protected:
  /// you can't delete a protected and nonvirtual derived class
  /// by delete the pointer to this base class.
  ~GenericPoint3T() = default;

public: /* functions about types **********************************************/
  /// @brief get the point type
  inline PointType point_type() const { return m_point_type; }

  bool is_explicit() const { return point_type() == PointType::Explicit; }
  bool is_implicit() const { return point_type() > PointType::Implicit; }
  bool is_SSI() const { return point_type() == PointType::SSI; }
  bool is_LNC() const { return point_type() == PointType::LNC; }
  bool is_LPI() const { return point_type() == PointType::LPI; }
  bool is_TPI() const { return point_type() == PointType::TPI; }

  /// @brief Convert to explicit point, won't check type again.
  EP &EXP()
  {
    OMC_EXPENSIVE_ASSERT(is_explicit(), "point type mismatch.");
    return *static_cast<EP *>(this);
  }
  /// @brief Convert to explicit point, won't check type again.
  const EP &EXP() const
  {
    OMC_EXPENSIVE_ASSERT(is_explicit(), "point type mismatch.");
    return *static_cast<const EP *>(this);
  }

#define CONVERT_AS_FUNC(name)                                  \
  IP_##name &name()                                            \
  {                                                            \
    OMC_EXPENSIVE_ASSERT(is_##name(), "point type mismatch."); \
    return *static_cast<IP_##name *>(this);                    \
  }                                                            \
  const IP_##name &name() const                                \
  {                                                            \
    OMC_EXPENSIVE_ASSERT(is_##name(), "point type mismatch."); \
    return *static_cast<const IP_##name *>(this);              \
  }

  CONVERT_AS_FUNC(SSI);
  CONVERT_AS_FUNC(LNC);
  CONVERT_AS_FUNC(LPI);
  CONVERT_AS_FUNC(TPI);

#undef CONVERT_AS_FUNC

public: /* get lambda values from implicit points ****************************/
  /**
   * @brief Get the Lambda values represented by interval numbers.
   * @return true if the sign of d is reliable.
   */
  template <typename _IT = IT,
            typename     = std::enable_if_t<!std::is_void_v<_IT>>>
  bool getIntervalLambda(_IT &lx, _IT &ly, _IT &lz, _IT &d) const
  {
    OMC_EXPENSIVE_ASSERT(point_type() != PointType::Explicit,
                         "no lambda for explicit point");
    if (point_type() == PointType::SSI)
      return SSI().getIntervalLambda(lx, ly, lz, d);
    else if (point_type() == PointType::LNC)
      return LNC().getIntervalLambda(lx, ly, lz, d);
    else if (point_type() == PointType::LPI)
      return LPI().getIntervalLambda(lx, ly, lz, d);
    else // if (point_type() == PointType::TPI)
      return TPI().getIntervalLambda(lx, ly, lz, d);
  }

  /**
   * @brief Get the Lambda values represented by exact numbers.
   */
  template <typename _ET = ET,
            typename     = std::enable_if_t<!std::is_void_v<_ET>>>
  void getExactLambda(_ET &lx, _ET &ly, _ET &lz, _ET &d) const
  {
    OMC_EXPENSIVE_ASSERT(point_type() != PointType::Explicit,
                         "no lambda for explicit point");
    if (point_type() == PointType::SSI)
      SSI().getExactLambda(lx, ly, lz, d);
    else if (point_type() == PointType::LNC)
      LNC().getExactLambda(lx, ly, lz, d);
    else if (point_type() == PointType::LPI)
      LPI().getExactLambda(lx, ly, lz, d);
    else // if (point_type() == PointType::TPI)
      TPI().getExactLambda(lx, ly, lz, d);
  }

  /**
   * @brief Get the Lambda values represented by expansion numbers.
   */
  void getExpansionLambda(NT **lx, int &lx_len, NT **ly, int &ly_len, NT **lz,
                          int &lz_len, NT **d, int &d_len) const
  {
    OMC_EXPENSIVE_ASSERT(point_type() != PointType::Explicit,
                         "no lambda for explicit point");
    if (point_type() == PointType::SSI)
      SSI().getExpansionLambda(lx, lx_len, ly, ly_len, lz, lz_len, d, d_len);
    else if (point_type() == PointType::LNC)
      LNC().getExpansionLambda(lx, lx_len, ly, ly_len, lz, lz_len, d, d_len);
    else if (point_type() == PointType::LPI)
      LPI().getExpansionLambda(lx, lx_len, ly, ly_len, lz, lz_len, d, d_len);
    else // if (point_type() == PointType::TPI)
      TPI().getExpansionLambda(lx, lx_len, ly, ly_len, lz, lz_len, d, d_len);
  }

public: /* Convert to other point types ************************************/
  /**
   * @brief get the explicit reprensentation of the point.
   * @param e the explicit point to store the result.
   * @param aeap abbreviates "as exact as possible". If true, the exact
   * value is calculated and rounded to the nearest floating point number.
   */
  void get_explicit(EP &e, bool aeap = false) const
  {
    if (point_type() == PointType::Explicit)
      e = EXP();
    else
    {
      NT lx, ly, lz, d;
      if constexpr (!std::is_void_v<IT>)
      {
        // calculate approximate lambda values by interval arithmetic
        IT ilx, ily, ilz, id;
        if (!aeap && getIntervalLambda(ilx, ily, ilz, id))
        {
          lx = ilx.sup() + ilx.inf();
          ly = ily.sup() + ily.inf();
          lz = ilz.sup() + ilz.inf();
          d  = id.sup() + id.inf();
          e  = EP(lx / d, ly / d, lz / d);
          return;
        }
      }
      // calculate more accurate lambda values by exact arithmetic
      ET elx, ely, elz, ed;
      getExactLambda(elx, ely, elz, ed);
      lx = OMC::to_double(elx);
      ly = OMC::to_double(ely);
      lz = OMC::to_double(elz);
      d  = OMC::to_double(ed);
      e  = EP(lx / d, ly / d, lz / d);
    }
  }

  /**
   * @brief get the explicit reprensentation of the point.
   * @param aeap abbreviates "as exact as possible". If true, the exact
   * value is calculated and rounded to the nearest floating point number.
   * @return the explicit point.
   */
  EP to_explicit(bool aeap = false) const
  {
    EP e;
    get_explicit(e, aeap);
    return e;
  }

  /**
   * @brief Get approximate values on all dimensions of this generic point.
   * @param aeap abbreviates "as exact as possible". If true, the exact
   * value is calculated and rounded to the nearest floating point number.
   */
  void get_coordinates(NT &x, NT &y, NT &z, bool aeap = false) const
  {
    EP e_;
    get_explicit(e_, aeap);
    x = e_.x();
    y = e_.y();
    z = e_.z();
  }

public:
  /***********************************************************************
   * Below functions are wrappers of functions from explicit point.
   * NOT safe!! just for efficiency :(
   ***********************************************************************/

  /// @brief Access value on x. Assume this is explicit when call the func.
  NT       &x() { return EXP().x(); }
  /// @brief Access value on x. Assume this is explicit when call the func.
  const NT &x() const { return EXP().x(); }

  /// @brief Access value on y. Assume this is explicit when call the func.
  NT       &y() { return EXP().y(); }
  /// @brief Access value on y. Assume this is explicit when call the func.
  const NT &y() const { return EXP().y(); }

  /// @brief Access value on z. Assume this is explicit when call the func.
  NT       &z() { return EXP().z(); }
  /// @brief Access value on x. Assume this is explicit when call the func.
  const NT &z() const { return EXP().z(); }

  /// @brief Get the value on dimension \p i. Assume this is explicit point.
  NT       &operator[](size_t i) { return EXP()[i]; }
  /// @brief Get the value on dimension \p i. Assume this is explicit point.
  const NT &operator[](size_t i) const { return EXP()[i]; }

  /// @brief Get the coordinate pointer.
  const NT *data() const { return EXP().data(); }

  /// @brief use point as vector
  VecT &as_vec() { return EXP().as_vec(); }

  /// @brief use point as vector
  const VecT &as_vec() const { return EXP().as_vec(); }

  /// @brief convert point to vector
  VecT to_vec() const { return EXP().to_vec(); }

  /// @brief negative
  GenericPoint3T operator-() const { return GenericPoint3T(-as_vec()); }
  /// @brief calculate the vector from \p rhs to \p this.
  /// vec = this - rhs.
  VecT           operator-(const GenericPoint3T &rhs) const
  {
    return as_vec() - rhs.as_vec();
  }
  /// @brief new point = this point + another point
  GenericPoint3T operator+(const GenericPoint3T &rhs) const
  {
    return GenericPoint3T(as_vec() + rhs.as_vec());
  }
  /// @brief add this point with a vector
  GenericPoint3T operator+(const VecT &rhs) const
  {
    return GenericPoint3T(as_vec() + rhs);
  }
  /// @brief subtract this point with a vector
  GenericPoint3T operator-(const VecT &rhs) const
  {
    return GenericPoint3T(as_vec() - rhs);
  }
  /// @brief this point += another point
  GenericPoint3T &operator+=(const GenericPoint3T &rhs)
  {
    as_vec() += rhs.as_vec();
    return *this;
  }
  /// @brief add this point with a vector
  GenericPoint3T &operator+=(const VecT &rhs)
  {
    as_vec() += rhs;
    return *this;
  }
  /// @brief this point -= another point
  GenericPoint3T &operator-=(const GenericPoint3T &rhs)
  {
    as_vec() -= rhs.as_vec();
    return *this;
  }
  /// @brief subtract this point with a vector
  GenericPoint3T &operator-=(const VecT &rhs)
  {
    as_vec() -= rhs;
    return *this;
  }
  /// @brief multiply a scalar
  GenericPoint3T &operator*=(const NT &scale_factor)
  {
    as_vec() *= scale_factor;
    return *this;
  }
  /// @brief divide a scalar
  GenericPoint3T &operator/=(const NT &scale_factor)
  {
    as_vec() /= scale_factor;
    return *this;
  }

  /// @brief set this point with minimal values between this and another point
  void minimize(const GenericPoint3T &rhs) { as_vec().minimize(rhs.as_vec()); }
  /// @brief set this point with maximal values between this and another point
  void maximize(const GenericPoint3T &rhs) { as_vec().maximize(rhs.as_vec()); }

/// Compare \p this with \p rhs element-wisely.
#define ELEMENT_WISELY_COMPARE(op)                         \
  inline bool operator op(const GenericPoint3T &rhs) const \
  {                                                        \
    return as_vec() op rhs.as_vec();                       \
  }                                                        \
  inline bool operator op(const NT &rhs) const { return as_vec() op rhs; }

  ELEMENT_WISELY_COMPARE(==);
  ELEMENT_WISELY_COMPARE(!=);
  ELEMENT_WISELY_COMPARE(<);
  ELEMENT_WISELY_COMPARE(<=);
  ELEMENT_WISELY_COMPARE(>);
  ELEMENT_WISELY_COMPARE(>=);
#undef ELEMENT_WISELY_COMPARE

public: /* Global cache lambda values ****************************************/
  /// A class to store cached values for one point.
  using GCV = GlobalCachedValues<OnePointCachedValues3<IT, ET>>;

  static void enable_global_cached_values() { gcv().enable(); }

  static void disable_global_cached_values() { gcv().disable(); }

  static void clear_global_cached_values() { gcv().clear_cached_values(); }

  static bool global_cached_values_enabled() { return gcv().is_enabled(); }

  static GCV &gcv() { return global_cached_values; }

  static GCV global_cached_values;
};

template <typename IT_, typename ET_>
typename GenericPoint3T<IT_, ET_>::GCV
  GenericPoint3T<IT_, ET_>::global_cached_values = {};

} // namespace OMC