#include <array>
#include <cmath>
#include <cstring>
#include <cstdio>

#include "Quaternion.hpp"


char str_buf[STRLEN];

const Quaternion Quaternion::un = q{1, 0, 0, 0};

Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion{q1.reel + q2.reel, q1.imi + q2.imi, q1.imj + q2.imj, q1.imk + q2.imk};
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion{q1.reel - q2.reel, q1.imi - q2.imi, q1.imj - q2.imj, q1.imk - q2.imk};
}

bool Quaternion::operator==(const Quaternion& q1) const {
    return reel == q1.reel && imi == q1.imi &&
        imj == q1.imj && imk == q1.imk;
}

bool Quaternion::operator==(const std::array<double, 4>& a) const {
    return reel == a[0] && imi == a[1] &&
        imj == a[2] && imk == a[3];
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion{
        q1.reel * q2.reel - q1.imi * q2.imi - q1.imj * q2.imj - q1.imk * q2.imk, 
        q1.reel * q2.imi + q1.imi * q2.reel + q1.imj * q2.imk - q1.imk * q2.imj, 
        q1.reel * q2.imj - q1.imi * q2.imk + q1.imj * q2.reel + q1.imk * q2.imi, 
        q1.reel * q2.imk + q1.imi * q2.imj - q1.imj * q2.imi + q1.imk * q2.reel
    };
}

Quaternion::operator const char* () const     // representation dans puts, printf...
{
    sprintf(str_buf, "%10.2f %10.2f %10.2f %10.2f", reel, imi, imj, imk);
    
    return str_buf;
}

Quaternion Quaternion::operator-() const    // conjugue
{
    return q{reel, -imi, -imj, -imk};
}

double Quaternion::operator+() const    // magnitude
{
    return sqrt(this->scalaire());
}

bool Quaternion::operator==(double d) const {
    return +(*this) == d;
}

Quaternion operator*(const Quaternion& q1, const double d) {
    return Quaternion {
        q1.reel * d, 
        q1.imi * d, 
        q1.imj * d, 
        q1.imk * d
    };
}

/// Dot product entre deux quaternions
double operator%(const Quaternion& q1, const Quaternion& q2) {
    return 
        q1.reel * q2.reel+
        q1.imi * q2.imi+
        q1.imj * q2.imj+
        q1.imk * q2.imk
    ;
}

// a tester
Quaternion cross(const Quaternion& q1, const Quaternion& q2)
{
    return q{
        q1.imi * q2.imj - q1.imj * q2.imi,
        q1.imj * q2.imk - q1.imk * q2.imj,
        q1.imk * q2.reel - q1.reel * q2.imk,
        q1.reel * q2.imi - q1.imi * q2.reel
    };
}

// prend en compte la perte de precision des nombres
// flottants quand on teste leur egalité
bool eq(double a, double b)
{
    return fabs(a - b) < 1e-9; 
}

bool eq(Quaternion a, Quaternion b)
{
    return eq(+a,  +b); 
}

Quaternion operator/(const Quaternion& q1, double d) {
    return q{
        q1.reel / d,
        q1.imi / d,
        q1.imj / d,
        q1.imk / d
    };
}

// utile surtout avec q^-1
Quaternion operator/(double d, const Quaternion& q2) {
    double inverse = 1 / q2.scalaire();
    return q{
        q2.reel * inverse,
        - q2.imi * inverse,
        - q2.imj * inverse,
        - q2.imk * inverse
    } * d;
}

double Quaternion::scalaire() const
{
    return reel * reel + imi * imi + imj * imj + imk * imk;
}

Quaternion operator/(const Quaternion& q1, const Quaternion& q2) {
    return q1 * (1 / q2);
}

Quaternion Quaternion::unit() const
{
    return (*this) / +(*this);
}

Quaternion Quaternion::fromMatrix(MatriceRot m) 
{
    return q{m[0], m[4], m[8], m[12]};
}

MatriceRot::MatriceRot(const std::array<double, 4*4> && arr) : vec{}
{
    //puts("ici");
    //memcpy(&vec, arr.data(), sizeof vec);
    for (int i = 0; i < 4*4; i++)
    {
        vec[i] = arr[i];
    }
    //puts(*this);
}

MatriceRot::MatriceRot(const Quaternion & q) : M(std::array<double, 4*4>{
    {
        q.reel, -q.imi, -q.imj, -q.imk, 
        q.imi, q.reel, -q.imk, q.imj,
        q.imj, q.imk, q.reel, -q.imi,
        q.imk, -q.imj, q.imi, q.reel
    }
})
{
    ;
}

MatriceRot::MatriceRot(Quaternion && q) : M(std::array<double, 4*4>{{0}})
{
    ;
}

MatriceRot::MatriceRot() : M(q{})
{
    ;
}

bool MatriceRot::operator==(const Quaternion& q) const
{
    return true;
}

bool MatriceRot::operator==(const MatriceRot& m) const
{
    return memcmp(this->vec, m.vec, sizeof m.vec) == 0;
}

double MatriceRot::operator[](int idx) const{
    return vec[idx];
}

double& MatriceRot::operator[](int idx) {
    return vec[idx];
}

MatriceRot operator+(const MatriceRot& m1, const MatriceRot& m2) {
    return M{{
        m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3], 
        m1[4] + m2[4], m1[5] + m2[5], m1[6] + m2[6], m1[7] + m2[7], 
        m1[8] + m2[8], m1[9] + m2[9], m1[10] + m2[10], m1[11] + m2[11], 
        m1[12] + m2[12], m1[13] + m2[13], m1[14] + m2[14], m1[15] + m2[15], 
    }};

    /*for (int i = 0; i < 4*4; i++)
        m[i] = m1[i] + m2[i];
    
    return m;*/
}

MatriceRot operator-(const MatriceRot& m1, const MatriceRot& m2){
    return M{
        {
        m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3], 
        m1[4] - m2[4], m1[5] - m2[5], m1[6] - m2[6], m1[7] - m2[7], 
        m1[8] - m2[8], m1[9] - m2[9], m1[10] - m2[10], m1[11] - m2[11], 
        m1[12] - m2[12], m1[13] - m2[13], m1[14] - m2[14], m1[15] - m2[15], 
 
        }
    };

    /*for (int i = 0; i < 4*4; i++)
        m[i] = m1[i] - m2[i];
    
    return m;*/
}

MatriceRot::operator const char* ()     // representation dans puts, printf...
{
    snprintf(
        str_buf, STRLEN, "/--\n\
%10.2f %10.2f %10.2f %10.2f\n\
%10.2f %10.2f %10.2f %10.2f\n\
%10.2f %10.2f %10.2f %10.2f\n\
%10.2f %10.2f %10.2f %10.2f\n\
\\--\
", 
        vec[0], vec[1], vec[2], vec[3],
        vec[4], vec[5], vec[6], vec[7],
        vec[8], vec[9], vec[10], vec[11],
        vec[12], vec[13], vec[14], vec[15]
    );
    
    return str_buf;
}

const MatriceRot mr{{
    1, 0, 0, 0, 
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
}};

const MatriceRot mi{{
    0, -1, 0, 0, 
    1, 0, 0, 0,
    0, 0, 0, -1,
    0, 0, 1, 0
}};

const MatriceRot mj{{
    0, 0, -1, 0, 
    0, 0, 0, 1,
    1, 0, 0, 0,
    0, -1, 0, 0
}};

const MatriceRot mk{{
    0, 0, 0, -1, 
    0, 0, -1, 0,
    0, 1, 0, 0,
    1, 0, 0, 0
}};

MatriceRot MatriceRot::operator*(double v) const
{
    MatriceRot m = *this;
    for (int i = 0; i < 4*4; i++) 
        m[i] = v * vec[i];

    return m;
}

Vec3::operator const char * ()
{
    snprintf(
        str_buf, STRLEN, "v3: \
%10.2f %10.2f %10.2f\n", 
        i, j, k
    );
    
    return str_buf;
}

Vec3 Vec3::unit()
{
    double norm = sqrt(i*i + j*j + k*k);
    return Vec3{i / norm, j / norm, k / norm};
}

Vec3 operator+(const Vec3& q1, const Vec3& q2) {
    return Vec3{q1.i + q2.i, q1.j + q2.j, q1.k + q2.k};
}

Vec3 operator-(const Vec3& q1, const Vec3& q2) {
    return Vec3{q1.i - q2.i, q1.j - q2.j, q1.k - q2.k};
}

Vec3 operator*(const Vec3& q1, const double d) {
    return Vec3 {
            q1.i * d,
            q1.j * d,
            q1.k * d,
    };
}

v3 rot(v3 v, q qt)
{
    int angle = qt.reel;
    angle %= 360;
    double theta = angle * M_PI / 180.;
    theta /= 2.;
    v3 u{qt.imi, qt.imj, qt.imk};
    u = u.unit();
    //const q unit{qt.unit()};
    q qr {cos(theta), u.i * sin(theta), u.j * sin(theta), u.k * sin(theta)};

    q r = (qr * q{0, v.i, v.j, v.k}) * -qr;
    return {r.imi, r.imj, r.imk};
}

v3 rot(v3 v, q q1, q q2)
{
    return rot(rot(v, q1), q2);
}

v3 rot(v3 v, q q1, q q2, q q3)
{
    return rot(rot(rot(v, q1), q2), q3);
}
