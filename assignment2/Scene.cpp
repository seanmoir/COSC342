#include "Scene.h"

#include "Colour.h"
#include "ImageDisplay.h"
#include "utility.h"
#include "math.h"

// For demos

Scene::Scene() : backgroundColour(0, 0, 0), ambientLight(0, 0, 0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	ImageDisplay display("Render", renderWidth, renderHeight);

	const double w = double(renderWidth);
	const double h = double(renderHeight);

	for (unsigned int v = 0; v < renderHeight; ++v) {
		for (unsigned int u = 0; u < renderWidth; ++u) {
			double cu = -1 + (u + 0.5) * (2.0 / w);
			double cv = -h / w + (v + 0.5) * (2.0 / w);
			Ray ray = camera_->castRay(cu, cv);
			display.set(u, v, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}

	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;
	std::vector<RayIntersection> hits;

	for (const auto& obj : objects_) {
		for (const auto& hit : obj->intersect(ray)) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}
	return firstHit;
}

Colour Scene::computeColour(const Ray& ray, unsigned int rayDepth) const {
	RayIntersection hitPoint = intersect(ray);
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}

	Colour hitColour(0, 0, 0);

	// Code to do better lighting, shadows, and reflections goes here.
	for (const auto& light : lights_) {
		// Compute the influence of this light on the appearance of the hit object.
		if (light->getDistanceToLight(hitPoint.point) < 0) {
			// An ambient light, ignore shadows and add appropriate colour
			hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
		}
		else {
			// Not an ambient light

			// diffuse element of the ith light
			Colour id = light->getIlluminationAt(hitPoint.point);
			// diffuse colour of the object
			Colour kd = hitPoint.material.diffuseColour;
			// normal vector to the surface at the hit point
			Vector n = hitPoint.normal;
			// vector from the hit point towards the ith light source
			Vector l = -light->getLightDirection(hitPoint.point);
			// specular element of the ith light
			Colour is = light->getIlluminationAt(hitPoint.point);
			// specular colour of the object
			Colour ks = hitPoint.material.specularColour;
			// reflection of l
			Vector r = 2 * (n.dot(l)) * n - l;
			// vector from the hit point back along the view ray
			Vector v = -ray.direction;
			// specular exponent of the object's material
			double a = hitPoint.material.specularExponent;

			// unit vectors
			n = n / n.norm();
			l = l / l.norm();
			v = v / v.norm();
			r = r / r.norm();

			double diffuse = std::max<double>(0, n.dot(l));
			double specular = std::max<double>(0, r.dot(v));

			Ray shadowRay;
			shadowRay.direction = l;
			// shadow starting point
			shadowRay.point = hitPoint.point;
			RayIntersection shadow = intersect(shadowRay);
			if (shadow.distance - light->getDistanceToLight(hitPoint.point) > 0) {
				hitColour += id * (kd * diffuse) + is * (ks * pow(specular, a));
			}
		}
	}

	// Compute mirror reflections - only if surface hit is a mirror and we've not reached our rayDepth
	if (rayDepth > 0 && (hitPoint.material.mirrorColour.red > 0 ||
		hitPoint.material.mirrorColour.green > 0 ||
		hitPoint.material.mirrorColour.blue > 0)) {

		// Compute the reflected ray
		Ray reflectedRay;

		// Surface normal as a unit vector
		Normal n = hitPoint.normal;
		n = n / n.norm();

		// View direction as a unit vector
		Direction v = -ray.direction;
		v = v / v.norm();

		// Ray starts at the hit point
		reflectedRay.point = hitPoint.point;

		// And goes in the reflection of v about n
		reflectedRay.direction = 2 * (v.dot(n)) * n - v;

		// Hit colour is a mix of the current surface and reflected ray
		hitColour = (Colour(1, 1, 1) - hitPoint.material.mirrorColour) * hitColour +
			hitPoint.material.mirrorColour * computeColour(reflectedRay, rayDepth - 1);
	}

	hitColour.clip();
	return hitColour;
}

bool Scene::hasCamera() const {
	return bool(camera_);
}