#include <array>

#include "Quaternion.hpp"

char str_buf[100];

const Quaternion Quaternion::un = q{1, 0, 0, 0};

Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion{q1.reel + q2.reel, q1.imi + q2.imi, q1.imj + q2.imj, q1.imk + q2.imk};
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion{q1.reel - q2.reel, q1.imi - q2.imi, q1.imj - q2.imj, q1.imk - q2.imk};
}

bool Quaternion::operator==(const Quaternion& q1) {
    return reel == q1.reel && imi == q1.imi &&
        imj == q1.imj && imk == q1.imk;
}

bool Quaternion::operator==(const std::array<double, 4>& a) {
    return reel == a[0] && imi == a[1] &&
        imj == a[0] && imk == a[3];
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion{
        q1.reel * q2.reel - q1.imi * q2.imi - q1.imj * q2.imj - q1.imk * q2.imk, 
        q1.reel * q2.imi + q1.imi * q2.reel + q1.imj * q2.imk - q1.imk * q2.imj, 
        q1.reel * q2.imj + q1.imj * q2.reel + q1.imk * q2.imj - q1.imi * q2.imk, 
        q1.reel * q2.imk + q1.imk * q2.reel + q1.imi * q2.imj - q1.imj * q2.imi
    };
}

Quaternion::operator const char* ()
{
    sprintf(str_buf, "%10.2f %10.2f %10.2f %10.2f", reel, imi, imj, imk);
    
    return str_buf;
}

Quaternion Quaternion::operator-() const
{
    return q{reel, -imi, -imj, -imk};
}
