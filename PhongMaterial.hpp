#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"

class PhongMaterial : public Material {
public:
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess);
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess,
   double reflect, double refract, double refract_ratio);
  virtual ~PhongMaterial();
  glm::vec3 diffuse();
  glm::vec3 specular();
  double shininess();
  double reflectiveness();
  double refractiveness();
  double ratio();

private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;
  double m_shininess;
  double m_reflectiveness;
  double m_refractiveness;
  double m_ratio;
};
