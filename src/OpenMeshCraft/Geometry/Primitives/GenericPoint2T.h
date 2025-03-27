#pragma once

#include "Primitive2.h"
#include "Vector2T.h"

#include "ImplicitPoints/GlobalCachedValues.h"
#include "OpenMeshCraft/NumberTypes/NumberUtils.h"

#include <cassert>

namespace OMC {

/***** Forward declarations ******/
template <typename IT, typename ET>
class ExplicitPoint2T;

template <typename IT, typename ET>
class ImplicitPoint2T_SSI;
/*** Forward declarations end ***/

/// @brief the generic point of 2D exact implicit and explicit points
template <typename IT, typename ET>
class GenericPoint2T : public Primitive2<double>
{
public: /* types *************************************************************/
  using NT   = double;
  using VecT = Vec2T<NT>;

  using EP     = ExplicitPoint2T<IT, ET>;
  using IP_SSI = ImplicitPoint2T_SSI<IT, ET>;

  enum class PointType : uint32_t
  {
    Explicit = 0,
    Implicit = 1,
    SSI      = 2
  };

public: /* members ************************************************************/
  /// Indicates the point type in derived classes.
  /// The only member variable in the base class.
  PointType m_point_type;

public: /* Constructor and Destructor ****************************************/
  GenericPoint2T(PointType pt)
    : m_point_type(pt)
  {
  }

  GenericPoint2T(const GenericPoint2T &gp)            = default;
  GenericPoint2T(GenericPoint2T &&gp)                 = default;
  GenericPoint2T &operator=(const GenericPoint2T &gp) = default;
  GenericPoint2T &operator=(GenericPoint2T &&gp)      = default;

protected:
  /// you can't delete a protected and nonvirtual derived class
  /// by delete the pointer to this base class.
  ~GenericPoint2T() = default;

public: /* functions about types **********************************************/
  /// @brief get the point type
  inline PointType point_type() const { return m_point_type; };

  bool is_explicit() const { return point_type() == PointType::Explicit; }
  bool is_implicit() const { return point_type() > PointType::Implicit; }
  bool is_SSI() const { return point_type() == PointType::SSI; }

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

  /// @brief Convert to SSI point, won't check type again.
  IP_SSI &SSI()
  {
    OMC_EXPENSIVE_ASSERT(is_SSI(), "point type mismatch.");
    return *static_cast<IP_SSI *>(this);
  }
  /// @brief Convert to SSI point, won't check type again.
  const IP_SSI &SSI() const
  {
    OMC_EXPENSIVE_ASSERT(is_SSI(), "point type mismatch.");
    return *static_cast<const IP_SSI *>(this);
  }

public: /* get lambda values from implicit points ****************************/
  /**
   * @brief Get the Lambda values represented by interval numbers.
   * @return true if the sign of d is reliable.
   */
  template <typename _IT = IT,
            typename     = std::enable_if_t<!std::is_void_v<_IT>>>
  bool getIntervalLambda(_IT &lx, _IT &ly, _IT &d) const
  {
    OMC_EXPENSIVE_ASSERT(point_type() != PointType::Explicit,
                         "no lambda for explicit point");
    /*if (point_type() == PointType::SSI)*/
    return SSI().getIntervalLambda(lx, ly, d);
  }

  /**
   * @brief Get the Lambda values represented by exact numbers.
   */
  template <typename _ET = ET,
            typename     = std::enable_if_t<!std::is_void_v<_ET>>>
  void getExactLambda(_ET &lx, _ET &ly, _ET &d) const
  {
    OMC_EXPENSIVE_ASSERT(point_type() != PointType::Explicit,
                         "no lambda for explicit point");
    /*if (point_type() == PointType::SSI)*/
    return SSI().getExactLambda(lx, ly, d);
  }

  /**
   * @brief Get the Lambda values represented by expansion numbers.
   */
  void getExpansionLambda(NT **lx, int &lx_len, NT **ly, int &ly_len, NT **d,
                          int &d_len) const
  {
    OMC_EXPENSIVE_ASSERT(point_type() != PointType::Explicit,
                         "no lambda for explicit point");
    /*if (point_type() == PointType::SSI)*/
    return SSI().getExpansionLambda(lx, lx_len, ly, ly_len, d, d_len);
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
      NT lx, ly, d;
      if constexpr (!std::is_void_v<IT>)
      {
        // calculate approximate lambda values by interval arithmetic
        IT ilx, ily, id;
        if (!aeap && getIntervalLambda(ilx, ily, id))
        {
          lx = ilx.sup() + ilx.inf();
          ly = ily.sup() + ily.inf();
          d  = id.sup() + id.inf();
          e  = EP(lx / d, ly / d);
          return;
        }
      }
      // calculate more accurate lambda values by exact arithmetic
      ET elx, ely, ed;
      getExactLambda(elx, ely, ed);
      lx = OMC::to_double(elx);
      ly = OMC::to_double(ely);
      d  = OMC::to_double(ed);
      e  = EP(lx / d, ly / d);
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
  void get_coordinates(NT &x, NT &y, bool aeap = false) const
  {
    EP e_;
    get_explicit(e_, aeap);
    x = e_.x();
    y = e_.y();
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

  /// @brief Get the value on dimension \p i. Assume this is explicit point.
  NT       &operator[](size_t i) { return EXP()[i]; }
  /// @brief Get the value on dimension \p i. Assume this is explicit point.
  const NT &operator[](size_t i) const { return EXP()[i]; }

  /// @brief Get the coordinate pointer.
  const NT *data() const { return EXP().data(); }

  /// @brief use point as vector
  VecT       &as_vec() { return EXP().as_vec(); }
  /// @brief use point as vector
  const VecT &as_vec() const { return EXP().as_vec(); }

  /// @brief convert point to vector
  VecT to_vec() const { return EXP().to_vec(); }

  /// @brief negative
  GenericPoint2T operator-() const { return GenericPoint2T(-as_vec()); }
  /// @brief calculate the vector from \p rhs to \p this.
  /// vec = this - rhs.
  VecT           operator-(const GenericPoint2T &rhs) const
  {
    return as_vec() - rhs.as_vec();
  }
  /// @brief new point = this point + another point
  GenericPoint2T operator+(const GenericPoint2T &rhs) const
  {
    return GenericPoint2T(as_vec() + rhs.as_vec());
  }
  /// @brief add this point with a vector
  GenericPoint2T operator+(const VecT &rhs) const
  {
    return GenericPoint2T(as_vec() + rhs);
  }
  /// @brief subtract this point with a vector
  GenericPoint2T operator-(const VecT &rhs) const
  {
    return GenericPoint2T(as_vec() - rhs);
  }
  /// @brief this point += another point
  GenericPoint2T &operator+=(const GenericPoint2T &rhs)
  {
    as_vec() += rhs.as_vec();
    return *this;
  }
  /// @brief add this point with a vector
  GenericPoint2T &operator+=(const VecT &rhs)
  {
    as_vec() += rhs;
    return *this;
  }
  /// @brief this point -= another point
  GenericPoint2T &operator-=(const GenericPoint2T &rhs)
  {
    as_vec() -= rhs.as_vec();
    return *this;
  }
  /// @brief subtract this point with a vector
  GenericPoint2T &operator-=(const VecT &rhs)
  {
    as_vec() -= rhs;
    return *this;
  }
  /// @brief multiply a scalar
  GenericPoint2T &operator*=(const NT &scale_factor)
  {
    as_vec() *= scale_factor;
    return *this;
  }
  /// @brief divide a scalar
  GenericPoint2T &operator/=(const NT &scale_factor)
  {
    as_vec() /= scale_factor;
    return *this;
  }

  /// @brief set this point with minimal values between this and another point
  void minimize(const GenericPoint2T &rhs) { as_vec().minimize(rhs.as_vec()); }
  /// @brief set this point with maximal values between this and another point
  void maximize(const GenericPoint2T &rhs) { as_vec().maximize(rhs.as_vec()); }

/// Compare \p this with \p rhs element-wisely.
#define ELEMENT_WISELY_COMPARE(op)                         \
  inline bool operator op(const GenericPoint2T &rhs) const \
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
  using GCV = GlobalCachedValues<OnePointCachedValues2<IT, ET>>;

  static void enable_global_cached_values() { gcv().enable(); }

  static void disable_global_cached_values() { gcv().disable(); }

  static void clear_global_cached_values() { gcv().clear_cached_values(); }

  static bool global_cached_values_enabled() { return gcv().is_enabled(); }

  static GCV &gcv() { return global_cached_values; }

  static GCV global_cached_values;
};

template <typename IT_, typename ET_>
typename GenericPoint2T<IT_, ET_>::GCV
  GenericPoint2T<IT_, ET_>::global_cached_values = {};

} // namespace OMC