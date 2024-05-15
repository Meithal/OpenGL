#include <array>

/**
 *      | j
 *      | 
 *      |___ i
 *     /
 *    / k    main droite, ijk, pouce index, majeur - ou index, majeur pouce
**/

/** 
 * i^2 = j^2 = k^2 = (ijk = kk) = (kij = jj) = (jki = ii) = -1
 */

extern char str_buf[100];

typedef struct Quaternion {
    double reel;
    double imi;
    double imj;
    double imk;

    friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
    friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
    bool operator==(const Quaternion& q1);
    bool operator==(const std::array<double, 4>& q1);
    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
    operator const char* ();
    Quaternion operator-() const;    // conjugué
    static const Quaternion un;      // unitaire
    double operator+() const;    // norme
    bool operator==(double d);      // egalite scalaire
    friend Quaternion operator*(const Quaternion& q1, double d); // produit avec un scalaire
    friend double operator%(const Quaternion& q1, const Quaternion& q2); // produit scalaire
} q;

