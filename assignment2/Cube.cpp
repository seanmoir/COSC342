/* $Rev: 250 $ */
#include "Cube.h"

#include "utility.h"

Cube::Cube() : Object() {

}

Cube::Cube(const Cube& cube) : Object(cube) {

}

Cube::~Cube() {

}

Cube& Cube::operator=(const Cube& cube) {
	if (this != &cube) {
		Object::operator=(cube);
	}
	return *this;
}

std::vector<RayIntersection> Cube::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	Ray inverseRay = transform.applyInverse(ray);

	// Z-axis
	double zO = inverseRay.point(2);
	double dz = inverseRay.direction(2);
	double t;

	t = (1 - zO) / dz;
	if (std::abs(dz) > epsilon && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(0) >= -1 && hit.point(0) <= 1 && hit.point(1) >= -1 && hit.point(1) <= 1) {

			hit.material = material;

			Vector normalHit(3);
			normalHit(0) = 1; normalHit(1) = 0; normalHit(2) = 0;
			hit.normal = normalHit;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			if (hit.normal.dot(ray.direction) > 0)
			{
					hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	t = (-1 - zO) / dz;
	if (std::abs(dz) > epsilon && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(0) >= -1 && hit.point(0) <= 1 && hit.point(1) >= -1 && hit.point(1) <= 1) {

			hit.material = material;

			Vector normalHit(3);
			normalHit(0) = 1; normalHit(1) = 0; normalHit(2) = 0;
			hit.normal = normalHit;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			if (hit.normal.dot(ray.direction) > 0)
			{
					hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	//  Y-axis
	double yO = inverseRay.point(1);
	double dy = inverseRay.direction(1);

	t = (-1 - yO) / dy;
	if (std::abs(dy) > epsilon  && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(0) >= -1 && hit.point(0) <= 1 && hit.point(2) >= -1 && hit.point(2) <= 1) {

			hit.material = material;

			Vector normalHit(3);
			normalHit(0) = 0; normalHit(1) = 1; normalHit(2) = 0;
			hit.normal = normalHit;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			if (hit.normal.dot(ray.direction) > 0)
			{
					hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	t = (1 - yO) / dy;
	if (std::abs(dy) > epsilon && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(0) >= -1 && hit.point(0) <= 1 && hit.point(2) >= -1 && hit.point(2) <= 1) {

			hit.material = material;

			Vector normalHit(3);
			normalHit(0) = 0; normalHit(1) = 1; normalHit(2) = 0;
			hit.normal = normalHit;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			if (hit.normal.dot(ray.direction) > 0)
			{
					hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	// X-axis
	double xO = inverseRay.point(0);
	double dx = inverseRay.direction(0);

	t = (1 - xO) / dx;
	if (std::abs(dx) > epsilon && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(1) >= -1 && hit.point(1) <= 1 && hit.point(2) >= -1 && hit.point(2) <= 1) {

			hit.material = material;

			Vector normalHit(3);
			normalHit(0) = 0; normalHit(1) = 0; normalHit(2) = 1;
			hit.normal = normalHit;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			if (hit.normal.dot(ray.direction) > 0)
			{
					hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}

	t = (-1 - xO) / dx;
	if (std::abs(dx) > epsilon  & t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(1) >= -1 && hit.point(1) <= 1 && hit.point(2) >= -1 && hit.point(2) <= 1) {

			hit.material = material;

			Vector normalHit(3);
			normalHit(0) = 0; normalHit(1) = 0; normalHit(2) = 1;
			hit.normal = normalHit;

			hit.point = transform.apply(hit.point);
			hit.normal = transform.apply(hit.normal);
			if (hit.normal.dot(ray.direction) > 0)
			{
					hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm();
			result.push_back(hit);
		}
	}
	return result;
}
