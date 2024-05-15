#include <cassert>
#include <cstdio>
#include <cmath>

#include "Quaternion.hpp"
#include "Transform.hpp"

int main()
{
    auto q1 = q{1., 0., 0., 0.};
    auto q2 = q{0., 20., 0., 0.};
    auto q3 = q{1., 3., -4., 2.5};
    auto q4 = q{1./3, 3., -4., 2.5};

    assert((q1 + q2 == q{1., 20., 0., 0.}));
    assert((q1 - q2 == q{1., -20., 0., 0.}));
    //assert((q1 + q2 == std::array<double, 4>{{1., 20., 0., 0.}}));

    puts(q1);
    puts(q1 * q2);
    puts(q3 * q2);
    puts(q2 * q3);

    assert((q{1., 0., 0., 0.} * q2 == q2));
    assert((q::un * q1 == q1));
    assert((q::un * q2 == q2));
    assert((q::un * q3 == q3));
    assert((q::un * q::un == q::un));
    assert((q4 * q::un == q4));

    assert((-q{1., 3., -4., 2.5} == q{1., -3., 4., -2.5}));

    assert(-(-q3) == q3);

    assert(+q1 == 1);
    assert(+q2 == 20);
    assert((+q{3, 0, 0, 0} == 3));
    assert((+q{0, 3, 0, 0} == 3));
    assert((+q{0, 0, 3, 0} == 3));
    assert((+q{0, 0, 0, 3} == 3));
    assert((+q{3, 4, 0, 0} == 5));
    assert((+q{0, 4, 3, 0} == 5));
    assert((+q{0, 0, 3, 4} == 5));
    printf("%lf\n", +q3);

    puts("ici");
    printf("%lf\n", +q3 * +-q3);
    printf("%lf\n", +q3 * +q3);

    assert(+q3 * +-q3 == +q3 * +q3);    // q * _q == || q || ^ 2

    puts(q3 * 2);
    assert((q3 * 2 == q{2, 6, -8, 5})); // multiplication

    assert((+(q3 * 2) == +q3 * 2));    // |a| * ||q|| = || a * q ||

    auto q1a = qa{1., 0., 0., 0.};
    auto q2a = qa{0., 20., 0., 0.};
    auto q3a = qa{1., 3., -4., 2.5};
    auto q4a = qa{1./3, 3., -4., 2.5};
    //assert(q3a.do);

    printf(
        "prod %lf %lf %lf %lf %lf\n", 
        +(q3 * q4), +q3 * +q4, +(q3 % q4), q3a * q4a, q3a % q4a
    );

    assert(+q3 == +-q3);        // || q || = || _q ||
    assert((+(q3 * q4) == +q3 * +q4));
    puts("tests ok");

}
