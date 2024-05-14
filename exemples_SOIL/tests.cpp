#include <cassert>
#include <cstdio>

#include "Quaternion.hpp"

int main()
{
    auto q1 = q{1., 0., 0., 0.};
    auto q2 = q{0., 20., 0., 0.};
    auto q3 = q{1., 3., -4., 2.5};

    assert((q1 + q2 == q{1., 20., 0., 0.}));
    assert((q1 - q2 == q{1., -20., 0., 0.}));
    //assert((q1 + q2 == std::array{1., 2., 0., 0.}));

    puts(q1);
    puts(q1 * q2);

    assert((q{1., 0., 0., 0.} * q2 == q2));
    assert((q::un * q1 == q1));
    assert((q::un * q2 == q2));
    assert((q::un * q3 == q3));


    assert((-q{1., 3., -4., 2.5} == q{1., -3., 4., -2.5}));

    assert(-(-q3) == q3);
    puts("tests ok");

}
