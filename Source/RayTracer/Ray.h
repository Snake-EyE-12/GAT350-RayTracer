#pragma once

#include <glm/glm.hpp>

struct ray_t
{
	glm::vec3 origin{ 0 };
	glm::vec3 direction{ 0 };
	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) :
		origin{ origin },
		direction{ direction }
	{};

	glm::vec3 At(float distance) const { return origin + (direction * distance); }
	glm::vec3 operator * (float d) const { return origin + (direction * d); }
};
struct raycastHit_t
{
	// distance along the ray direction, from the origin to the hit point
	float distance = 0;

	// world point of raycast hit
	glm::vec3 point{ 0 };
	// surface normal of raycast hit
	glm::vec3 normal{ 0 };

	// material attached to hit object
	class Material* material{ nullptr };
};