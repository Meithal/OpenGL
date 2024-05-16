#include <cassert>
#include <cstdio>
#include <cmath>

#include "Quaternion.hpp"
#include "Transform.hpp"


static auto q1 = q{1., 0., 0., 0.};
static auto q2 = q{0., 20., 0., 0.};
static auto q3 = q{1., 3., -4., 2.5};
static auto q4 = q{1./3, 3., -4., 2.5};

void test_vec()
{

    assert((q1 + q2 == q{1., 20., 0., 0.}));
    assert((q1 - q2 == q{1., -20., 0., 0.}));
    //assert((q1 + q2 == std::array<double, 4>{{1., 20., 0., 0.}}));

    assert((q1 * q2) * q3 == q1 * (q2 * q3));   // associativité
    assert((q1 + q2) * q3 == (q1 * q3) + (q2 * q3));   // distributivité

    assert(!(q3 * q4 == q4 * q3));  // non commutativité

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

    assert(-(-q3) == q3);   // __q = q
    assert(-(1 / q3) == 1 / -q3);  // _(q−1) =(_q)−1
    assert(-(1 / q3) == q3 / q3.scalaire());  // _(q−1) = q / (|| q || ^ 2)
    assert(-(q3 + q4) == -q3 + -q4);    // _(q+q') = _q + _q'
    assert(eq(-(q3 * q4), -q4 * -q3));  // _(q*q') = _q' * _q

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
        "prod %.20lf %.20lf %lf %lf %lf\n", 
        +(q3 * q4), +q3 * +q4, +(q3 % q4), q3a * q4a, q3a % q4a
    );

    assert(+q3 == +-q3);        // || q || = || _q ||
    assert(eq(+(q3 * q4), +q3 * +q4));  // || qxq' || = || q |||| q' || \
        ^ on a des errers d'arrondi a l'epsilon ici, \
        donc on utilise eq() au lieu de ==
    printf(
        "prod %.20lf %.20lf %.20lf %.20lf\n", 
        +(1/q1), 1/+q1, +(1/q3), 1/+q3
    );
    assert(eq(+(1/q3), 1/+q3)); // || 1 / q || = 1 / || q ||
    puts(q1 * (1 / q1));
    puts(q2 * (1 / q2));
    puts(q3 * (1 / q3));
    puts(q4 * (1 / q4));
    assert(eq(+(q1 * (1 / q1)), +q::un)); // q x q' = (1, 0, 0, 0)
    assert(eq(+(q2 * (1 / q2)), +q::un)); // q x q' = (1, 0, 0, 0)
    assert(eq(+(q3 * (1 / q3)), +q::un)); // q x q' = (1, 0, 0, 0)
    assert(eq(+(q4 * (1 / q4)), +q::un)); // q x q' = (1, 0, 0, 0)

    assert(eq(1 / (q3 * q4), (1 / q4) * (1 / q3))); // (q × q′)−1 = q′−1 × q−1

    puts("tests vec ok");
}


void test_mat()
{
    //assert((M{q3} == M{{1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2}}));
//    puts(M{{1, 2,0,0,0,}});
//    puts(M{{0, 1, 2, 5, 6}});
//    puts(M{{1, 2, 0,0,1}} + M{{0, 1, 2,0,0}});
    assert((M{{1,2,0, 0 , 0}} + M{{0,1,2,0,0,0}} == M{{1,3,2,0,0}}));
    assert((M{{1,2,0,0,0}} - M{{0,1,2,0,0,0}} == M{{1,1,-2,0,0}}));

    assert((M{q3} == mr * q3.reel + mi * q3.imi + mj * q3.imj + mk * q3.imk));

    assert(Quaternion::fromMatrix(M{q3}) == q3);
    assert(Quaternion::fromMatrix(M{q1}) == q1);
    assert(Quaternion::fromMatrix(M{q2}) == q2);
    assert(Quaternion::fromMatrix(M{q4}) == q4);

    puts("tests mac ok");
}

int main()
{
    test_vec();
    test_mat();
}
