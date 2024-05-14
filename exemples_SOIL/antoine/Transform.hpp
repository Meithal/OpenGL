#include <iostream>

struct Vector2;

struct Vector3 {
    float x, y, z;

    Vector3();
    Vector3(float _x, float _y, float _z = 0);

    Vector3 operator*(const float& s) const;
    friend Vector3 operator*(float s, const Vector3& v) {
        return v * s;
    }
    Vector3 operator/(const float& s) const;
    friend Vector3 operator/(float s, const Vector3& v) {
        return v / s;
    }
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator-() const;

    void operator*=(const float& s);
    void operator/=(const float& s);
    void operator+=(const Vector3& v);
    void operator-=(const Vector3& v);
    static float distance(const Vector3 &u, const Vector3 &v);
    float magnitude() const;
    Vector3 normalize() const;

    operator Vector2() const;

    static Vector3 cross(const Vector3& u, const Vector3& v);
    static float dot(const Vector3& u, const Vector3& v);
    static float angle(const Vector3& u, const Vector3& v);

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
    {
        os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
        return os;
    }
};

struct Vector2 {
    float x, y;

    Vector2();
    Vector2(float _x, float _y);

    Vector2 operator*(const float& s) const;
    friend Vector2 operator*(float s, const Vector2& v) {
        return v * s;
    }
    Vector2 operator/(const float& s) const;
    friend Vector2 operator/(float s, const Vector2& v) {
        return v / s;
    }
    Vector2 operator+(const Vector2& v) const;
    Vector2 operator-(const Vector2& v) const;
    Vector2 operator-() const;

    void operator*=(const float& s);
    void operator/=(const float& s);
    void operator+=(const Vector2& v);
    void operator-=(const Vector2& v);

    float magnitude() const;
    Vector2 normalize() const;

    operator Vector3() const;

    static float dot(const Vector2& u, const Vector2& v);
    static float angle(const Vector2& u, const Vector2& v);

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
    {
        os << '(' << v.x << ", " << v.y << ')';
        return os;
    }
};

typedef struct QuatA {
    float x, y, z, w;

    QuatA();
    QuatA(float _w, float _x, float _y, float _z);

    QuatA operator-() const;
    QuatA operator*(const QuatA& q) const;
    Vector3 operator*(const Vector3& v) const;

    void operator*=(const QuatA& q);

    float magnitude() const;
    QuatA normalize() const;
    Vector3 toEuler() const;
    void quaternionToMatrix(float* matrix);

    static QuatA euler(const Vector3& euler);
    static QuatA euler(float x, float y, float z);
    static QuatA matrixToQuaternion(const float* matrix);

    friend std::ostream& operator<<(std::ostream& os, const QuatA& v)
    {
        os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
        return os;
    }
} qa;

struct Transform {
    Vector3 position, scale{ 1, 1, 1 };
    QuatA rotation;

    Vector3 forward() const;
    Vector3 right() const;
    Vector3 up() const;
    Vector3 localToWorld(const Vector3& p) const;
    Vector3 worldToLocal(const Vector3& p) const;

};
