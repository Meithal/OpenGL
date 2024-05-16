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
#define STRLEN 200

extern char str_buf[STRLEN];

struct MatriceRot;

typedef const struct Quaternion {
    const double reel;
    const double imi;
    const double imj;
    const double imk;

    friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
    friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
    bool operator==(const Quaternion& q1) const;
    bool operator==(const std::array<double, 4>& q1) const;
    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
    operator const char* () const;
    Quaternion operator-() const;    // conjugué
    static const Quaternion un;      // unitaire
    double operator+() const;    // norme
    bool operator==(double d) const;      // egalite scalaire
    friend Quaternion operator*(const Quaternion& q1, double d); // produit avec un scalaire
    friend double operator%(const Quaternion& q1, const Quaternion& q2); // produit scalaire
    friend Quaternion cross(const Quaternion& q1, const Quaternion& q2); // douteux
    friend Quaternion operator/(const Quaternion& q1, double d);
    friend Quaternion operator/(double d, const Quaternion& q2);
    double scalaire() const;
    friend Quaternion operator/(const Quaternion& q1, const Quaternion& q2);
    Quaternion unitaire();
    static Quaternion fromMatrix(MatriceRot);
} q;

// verifie l'egalité de deux doubles avant l'epsilon
bool eq(double a, double b);
bool eq(Quaternion a, Quaternion b);

typedef const struct MatriceRot {
    double vec[4*4];

    explicit MatriceRot();
    MatriceRot(const std::array<double, 4*4>&&);
    //MatriceRot(Quaternion) = delete;
    MatriceRot(Quaternion&&);   // M(q{...});
    MatriceRot(const Quaternion&);  // M(q1);

    bool operator==(const MatriceRot&) const;
    bool operator==(const Quaternion&) const;
    double operator[](int index) const;
    double &operator[](const int index);
    friend MatriceRot operator+(const MatriceRot&, const MatriceRot&);
    friend MatriceRot operator-(const MatriceRot&, const MatriceRot&);
    operator const char* ();
    MatriceRot operator*(double op) const;
} M;

extern const MatriceRot mr;
extern const MatriceRot mi;
extern const MatriceRot mj;
extern const MatriceRot mk;