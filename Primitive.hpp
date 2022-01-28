#pragma once

#include <glm/glm.hpp>
#include "Ray.hpp"

class Primitive {
public:
  virtual ~Primitive();
  virtual bool intersect( Ray &ray, float closet, float fart, Intersection &intersection);
};

class Sphere : public Primitive {
  Primitive * primative;
public:
  Sphere();
  virtual ~Sphere();
  virtual bool intersect( Ray &ray, float closet, float fart, Intersection &intersection) override;
};

class Cube : public Primitive {
  Primitive * primative;
public:
  Cube();
  virtual ~Cube();
  virtual bool intersect( Ray &ray, float closet, float fart, Intersection &intersection) override;
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : position(pos), rad(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual bool intersect( Ray &ray, float closet, float fart, Intersection &intersection) override;

private:
  glm::vec3 position;
  double rad;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size);
  
  virtual ~NonhierBox();
  virtual bool intersect( Ray &ray, float closet, float fart, Intersection &intersection) override;
private:
  glm::vec3 vertices[8];
  glm::vec3 position;
  double m_size;
  Primitive * m_mesh;
};

class NonhierCone : public Primitive {
public:
  NonhierCone(const glm::vec3& pos, double size);

  virtual ~NonhierCone();
  virtual bool intersect( Ray &ray, float closet, float fart, Intersection &intersection) override;
private:
  glm::vec3 position;
  double m_size;
  glm::vec3 vertices[4];

  Primitive * m_mesh;
};
