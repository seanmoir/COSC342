#include "Plane.h"

#include "utility.h"

Plane::Plane() : Object() {

}

Plane::Plane(const Plane& plane) : Object(plane) {

}

Plane::~Plane() {

}

Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		Object::operator=(plane);
	}
	return *this;
}

std::vector<RayIntersection> Plane::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;
	Ray inverseRay = transform.applyInverse(ray);

	double z0 = inverseRay.point(2);
	double dz = inverseRay.direction(2);
	double t = -z0 / dz;

	if (std::abs(dz) > epsilon) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(1) <= 1 && hit.point(1) >= -1 && hit.point(0) <= 1 && hit.point(0) >= -1) {
			
			hit.material = material;
			
			Vector norm(3);
			norm(0) = 0; norm(1) = 0; norm(2) = 1;
			hit.normal = norm;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			hit.distance = (hit.point - ray.point).norm();

			result.push_back(hit);
		}
	}
	return result;
}