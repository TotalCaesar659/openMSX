#ifndef CSTD_HH
#define CSTD_HH

#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <string_view>
#include <utility>

namespace cstd {

// Inspired by this post:
//    http://tristanbrindle.com/posts/a-more-useful-compile-time-quicksort

// Constexpr reimplementations of standard algorithms or data-structures.
//
// Everything implemented in 'cstd' will very likely become part of standard
// C++ in the future. So then we can remove our (re)implementation and change
// the callers from 'cstd::xxx()' to 'std::xxx()'.

//
// Various constexpr reimplementation of STL algorithms.
//

template<typename Iter1, typename Iter2>
constexpr void iter_swap(Iter1 a, Iter2 b)
{
	auto temp = std::move(*a);
	*a = std::move(*b);
	*b = std::move(temp);
}

template<typename InputIt, typename UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p)
{
	for (/**/; first != last; ++first) {
		if (!p(*first)) {
			return first;
		}
	}
	return last;
}

template<typename ForwardIt, typename UnaryPredicate>
constexpr ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
	first = cstd::find_if_not(first, last, p);
	if (first == last) return first;

	for (ForwardIt i = first + 1; i != last; ++i) {
		if (p(*i)) {
			cstd::iter_swap(i, first);
			++first;
		}
	}
	return first;
}

// Textbook implementation of quick sort. Not optimized, but the intention is
// that it only gets executed during compile-time.
template<typename RAIt, typename Compare = std::less<>>
constexpr void sort(RAIt first, RAIt last, Compare cmp = Compare{})
{
	auto const N = last - first;
	if (N <= 1) return;
	auto const pivot = *(first + N / 2);
	auto const middle1 = cstd::partition(
	        first, last, [&](const auto& elem) { return cmp(elem, pivot); });
	auto const middle2 = cstd::partition(
	        middle1, last, [&](const auto& elem) { return !cmp(pivot, elem); });
	cstd::sort(first, middle1, cmp);
	cstd::sort(middle2, last, cmp);
}

template<typename RandomAccessRange, typename Compare = std::less<>>
constexpr void sort(RandomAccessRange&& range, Compare cmp = Compare{})
{
	cstd::sort(std::begin(range), std::end(range), cmp);
}

template<typename InputIt1, typename InputIt2>
constexpr bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2)
{
	for (/**/; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return (first1 == last1) && (first2 != last2);
}


// Reimplementation of various mathematical functions. You must specify an
// iteration count, this controls how accurate the result will be.
#if (defined(__GNUC__) && !defined(__clang__))

// Gcc has constexpr versions of most mathematical functions (this is a
// non-standard extension). Prefer those over our implementations.
template<int>      constexpr double sin  (double x) { return std::sin  (x); }
template<int>      constexpr double cos  (double x) { return std::cos  (x); }
template<int, int> constexpr double log  (double x) { return std::log  (x); }
template<int, int> constexpr double log2 (double x) { return    ::log  (x) / ::log(2); } // should be std::log2(x) but this doesn't seem to compile in g++-4.8/g++-4.9 (bug?)
template<int, int> constexpr double log10(double x) { return std::log10(x); }
template<int>      constexpr double exp  (double x) { return std::exp  (x); }
template<int>      constexpr double exp2 (double x) { return    ::exp2 (x); } // see log2, but apparently no need to use exp(log(2) * x) here?!
template<int, int> constexpr double pow(double x, double y) { return std::pow(x, y); }
inline constexpr double round(double x) { return ::round(x); } // should be std::round(), see above

#else

constexpr double upow(double x, unsigned u)
{
    double y = 1.0;
    while (u) {
        if (u & 1) y *= x;
        x *= x;
        u >>= 1;
    }
    return y;
}

constexpr double ipow(double x, int i)
{
	return (i >= 0) ? upow(x, i) : upow(x, -i);
}

template<int ITERATIONS>
constexpr double exp(double x)
{
    // Split x into integral and fractional part:
    //   exp(x) = exp(i + f) = exp(i) * exp(f)
    //   with: i an int     (undefined if out of range)
    //         -1 < f < 1
    int i = int(x);
    double f = x - i;

    // Approximate exp(f) with Taylor series.
    double y = 1.0;
    double t = f;
    double n = 1.0;
    for (int k = 2; k < (2 + ITERATIONS); ++k) {
        y += t / n;
        t *= f;
        n *= k;
    }

    // Approximate exp(i) by squaring.
    int p = (i >= 0) ? i : -i; // abs(i);
    double s = upow(M_E, p);

    // Combine the results.
    if (i >= 0) {
        return y * s;
    } else {
        return y / s;
    }
}

constexpr double simple_fmod(double x, double y)
{
    assert(y > 0.0);
    return x - int(x / y) * y;
}

template<int ITERATIONS>
constexpr double sin_iter(double x)
{
    double x2 = x * x;
    double y = 0.0;
    double t = x;
    double n = 1.0;
    for (int k = 1; k < (1 + 4 * ITERATIONS); /**/) {
        y += t / n;
        t *= x2;
        n *= ++k;
        n *= ++k;

        y -= t / n;
        t *= x2;
        n *= ++k;
        n *= ++k;
    }
    return y;
}

template<int ITERATIONS>
constexpr double cos_iter(double x)
{
    double x2 = x * x;
    double y = 1.0;
    double t = x2;
    double n = 2.0;
    for (int k = 2; k < (2 + 4 * ITERATIONS); /**/) {
        y -= t / n;
        t *= x2;
        n *= ++k;
        n *= ++k;

        y += t / n;
        t *= x2;
        n *= ++k;
        n *= ++k;
    }
    return y;
}

template<int ITERATIONS>
constexpr double sin(double x)
{
    double sign = 1.0;

    // reduce to [0, +inf)
    if (x < 0.0) {
        sign = -1.0;
        x = -x;
    }

    // reduce to [0, 2pi)
    x = simple_fmod(x, 2 * M_PI);

    // reduce to [0, pi]
    if (x > M_PI) {
        sign = -sign;
        x -= M_PI;
    }

    // reduce to [0, pi/2]
    if (x > M_PI/2) {
        x = M_PI - x;
    }

    // reduce to [0, pi/4]
    if (x > M_PI/4) {
        x = M_PI/2 - x;
        return sign * cos_iter<ITERATIONS>(x);
    } else {
        return sign * sin_iter<ITERATIONS>(x);
    }
}

template<int ITERATIONS>
constexpr double cos(double x)
{
    double sign = 1.0;

    // reduce to [0, +inf)
    if (x < 0.0) {
        x = -x;
    }

    // reduce to [0, 2pi)
    x = simple_fmod(x, 2 * M_PI);

    // reduce to [0, pi]
    if (x > M_PI) {
        x = 2.0 * M_PI - x;
    }

    // reduce to [0, pi/2]
    if (x > M_PI/2) {
        sign = -sign;
        x = M_PI - x;
    }

    // reduce to [0, pi/4]
    if (x > M_PI/4) {
        x = M_PI/2 - x;
        return sign * sin_iter<ITERATIONS>(x);
    } else {
        return sign * cos_iter<ITERATIONS>(x);
    }
}


// https://en.wikipedia.org/wiki/Natural_logarithm#High_precision
template<int E_ITERATIONS, int L_ITERATIONS>
constexpr double log(double x)
{
	int a = 0;
	while (x <= 0.25) {
		x *= M_E;
		++a;
	}
	double y = 0.0;
	for (int i = 0; i < L_ITERATIONS; ++i) {
		auto ey = cstd::exp<E_ITERATIONS>(y);
		y = y + 2.0 * (x - ey) / (x + ey);
	}
	return y - a;
}

template<int E_ITERATIONS, int L_ITERATIONS>
constexpr double log2(double x)
{
	return cstd::log<E_ITERATIONS, L_ITERATIONS>(x) / M_LN2;
}

template<int E_ITERATIONS, int L_ITERATIONS>
constexpr double log10(double x)
{
	return cstd::log<E_ITERATIONS, L_ITERATIONS>(x) / M_LN10;
}

template<int E_ITERATIONS, int L_ITERATIONS>
constexpr double pow(double x, double y)
{
	return cstd::exp<E_ITERATIONS>(cstd::log<E_ITERATIONS, L_ITERATIONS>(x) * y);
}

template<int ITERATIONS>
constexpr double exp2(double x)
{
	return cstd::exp<ITERATIONS>(M_LN2 * x);
}

constexpr double round(double x)
{
	return (x >= 0) ?  int( x + 0.5)
	                : -int(-x + 0.5);
}

#endif

} // namespace cstd

#endif
