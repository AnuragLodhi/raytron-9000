#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
   public:
    sphere() {}
    sphere(point3 center, double radius) : center(center), radius(radius) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

   private:
    point3 center;
    double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);

    // Nearest root in range
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}