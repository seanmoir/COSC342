#include "Tube.h"

#include "utility.h"


Tube::Tube(double ratio) : Object(), ratio_(ratio) {
}

Tube::Tube(const Tube& tube) : Object(tube), ratio_(tube.ratio_) {

}

Tube::~Tube() {

}

Tube& Tube::operator=(const Tube& tube) {
	if (this != &tube) {
		Object::operator=(tube);
		ratio_ = tube.ratio_;
	}
	return *this;
}

std::vector<RayIntersection> Tube::intersect(const Ray& ray) const {
	std::vector<RayIntersection> result;

	Ray inverseRay = transform.applyInverse(ray);

	// Intersection is of the form ad^2 + bd + c, where d = distance along the ray

	const Point &p = inverseRay.point;
	const Direction &d = inverseRay.direction;
	double a = (d(0) * d(0)) + (d(1) * d(1));
	double b = 2 * ((p(0) * d(0)) + (p(1) * d(1)));
	double c = (p(0) * p(0)) + (p(1) * p(1) - 1);

	RayIntersection hit;
	hit.material = material;
	double x0 = inverseRay.point(0);
	double y0 = inverseRay.point(1);
	double dx = inverseRay.direction(0);
	double dy = inverseRay.direction(1);

	double b2_4ac = b * b - 4 * a * c;
	double t;

	switch (sign(b2_4ac))
	{
	case -1:
		// No intersections
		break;
	case 0:
		// One intersection
		t = -b / (2 * a);
		if (t > 0)
		{
			hit.point = p + t * d;
			if (hit.point(2) <= 1 && hit.point(2) >= -1)
			{
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(1, 1, 0));
				if (hit.normal.dot(ray.direction) > 0)
				{
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
		break;
	case 1:
		// Two intersections
		t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		if (t > 0)
		{
			hit.point = p + t * d;
			if (hit.point(2) <= 1 && hit.point(2) >= -1)
			{
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(1, 1, 0));
				if (hit.normal.dot(ray.direction) > 0)
				{
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}

		t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (t > 0)
		{
			hit.point = p + t * d;
			if (hit.point(2) <= 1 && hit.point(2) >= -1)
			{
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(1, 1, 0));
				if (hit.normal.dot(ray.direction) > 0)
				{
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
		break;
	default:
		// Shouldn't be possible, but just in case
		std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
		exit(-1);
		break;
	}

	c = (p(0) * p(0)) + (p(1) * p(1) - ratio_);
	b2_4ac = b * b - 4 * a * c;
	switch (sign(b2_4ac))
	{
	case -1:
		// No intersections
		break;
	case 0:
		// One intersection
		t = -b / (2 * a);
		if (t > 0)
		{
			hit.point = p + t * d;
			if (hit.point(2) <= 1 && hit.point(2) >= -1)
			{
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(1, 1, 0));
				if (hit.normal.dot(ray.direction) > 0)
				{
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
		break;
	case 1:
		// Two intersections
		t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		if (t > 0)
		{
			hit.point = p + t * d;
			if (hit.point(2) <= 1 && hit.point(2) >= -1)
			{
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(1, 1, 0));
				if (hit.normal.dot(ray.direction) > 0)
				{
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}

		t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (t > 0)
		{
			hit.point = p + t * d;
			if (hit.point(2) <= 1 && hit.point(2) >= -1)
			{
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(1, 1, 0));
				if (hit.normal.dot(ray.direction) > 0)
				{
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
		break;
	default:
		// Shouldn't be possible, but just in case
		std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
		exit(-1);
		break;
	}


	double z0 = inverseRay.point(2);
	double dz = inverseRay.direction(2);
	double x2_y2;
	//FRONT ENDCAP
	t = (-1-z0) / dz;
 	x2_y2 = ((x0 + t * dx) * (x0 + t * dx)) + ((y0 + t * dy) * (y0 + t * dy));
	if (std::abs(dz) > epsilon && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(2) <= 1 && hit.point(2) >= -1 && x2_y2 <= 1 && x2_y2 >= ratio_ * ratio_) {
			
			hit.material = material;
			
			Vector norm(3);
			norm(0) = 0; norm(1) = 0; norm(2) = 1;
			hit.normal = norm;

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

	//BACK END CAP
	t = (1-z0) / dz;
	x2_y2 = ((x0 + t * dx) * (x0 + t * dx)) + ((y0 + t * dy) * (y0 + t * dy));
	if (std::abs(dz) > epsilon && t > 0) {
		RayIntersection hit;
		hit.point = inverseRay.point + t * inverseRay.direction;

		if (hit.point(2) <= 1 && hit.point(2) >= -1 && x2_y2 <= 1 && x2_y2 >= ratio_ * ratio_) {
			
			hit.material = material;
			
			Vector norm(3);
			norm(0) = 0; norm(1) = 0; norm(2) = 1;
			hit.normal = norm;

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
