#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "A5.hpp"
#include "Ray.hpp" 

#include "GeometryNode.hpp"
#include "PhongMaterial.hpp"

using namespace glm;
using namespace std;

#include <vector>

const bool REFLECTION_ON = true;
const bool GLOSSY_REFLECTION_ON = false;
const bool REFRACTION_ON = false;
const bool GLOSSY_REFRACTION_ON = false;
const bool SOFT_SHADOWS_ON = false;
const bool ANTI_ALIASING_ON = false;
const bool DEPTH_OF_FIELD_ON = false;


float random_num() {
	return (float) rand() / (RAND_MAX);
}

vec3 recurse(Ray &ray,
            SceneNode *root,
            const glm::vec3 & eye,
            const glm::vec3 & ambient,
            const std::list<Light *> & lights,
			const int count = 2,
			const int refractNum = 0
			) {
	Intersection intersection;
    vec3 color;

	if ( root->intersect( ray, 0, 999999, intersection ) ) {
		intersection.normal = normalize(intersection.normal);
		intersection.intersectionPoint += intersection.normal*0.001;
		PhongMaterial *material1 = static_cast<PhongMaterial *>(intersection.material);
		color += material1->diffuse()*ambient;

		for (Light * light : lights) {
			Ray shadow(intersection.intersectionPoint, light->position - intersection.intersectionPoint);
			Intersection shadowIntersection;
			
			if (!root->intersect(shadow,  0, 999999, shadowIntersection)) {

				//  soft shadows
				float softShadow = 1;
				if (SOFT_SHADOWS_ON) {
					int areaLights = 12; 
					int intersects = 0;
					for (int i = 0; i < areaLights-1; i++) {
						Intersection shadowIntersection;
						vec3 lightPosition = vec3(light->position.x + 35 * (random_num() - 0.5f),
												light->position.y + 35 * (random_num() - 0.5f),
												light->position.z + 35 * (random_num() - 0.5f));
						Ray shadowRay(intersection.intersectionPoint, lightPosition - intersection.intersectionPoint);
						intersects = root->intersect( shadowRay, 0, numeric_limits<float>::max(), shadowIntersection) ? intersects+1 : intersects;
					}
					softShadow = (areaLights - intersects) * 1.0f / areaLights;
				}
			
				vec3 dir = normalize(shadow.get_direction());
				vec3 norm = intersection.normal;
				double r = length(shadow.get_direction());
				vec3 kd = material1->diffuse();
				vec3 ks = material1->specular();
				double shine = material1->shininess();
				double tempDot = (double)dot(normalize(2*norm*dot(norm, dir) - dir), normalize(eye - intersection.intersectionPoint));
				double mag = length(shadow.get_direction());
				double attenuation = 1.0 / ( light->falloff[0] + light->falloff[1] * mag + light->falloff[2] * mag * mag );
				color += pow(glm::max(0.0, tempDot), shine)*attenuation*ks*light->colour * softShadow;
				color += dot(dir, norm)*attenuation*kd*light->colour * softShadow;
			}
		}

		PhongMaterial* material2 = dynamic_cast<PhongMaterial*>(intersection.material);

		if (material2 != nullptr && count > 0) {
			vec3 reflectColor = vec3(0.0f);
			vec3 refractColor;
			ray.direction = normalize(ray.get_direction());

			// specular reflection
			if (REFLECTION_ON) {
					vec3 reflection = ray.get_direction() - 2 * intersection.normal * dot(ray.get_direction(), intersection.normal);
					Ray reflectionRay(intersection.intersectionPoint, reflection);
					reflectColor = recurse(reflectionRay, root, eye, ambient, lights, count - 1);
			
				// glossy reflection
				if (GLOSSY_REFLECTION_ON) {
					reflection = normalize(reflection);
					srand(0);
					reflectColor = reflectColor / 12;
					for (int i = 0; i < 11; i++) {
						float u = -0.3f/2 + random_num() * 0.3f;
						float v = -0.3f/2 + random_num() * 0.3f;

						vec3 reflectionVector = reflection + u * cross(reflection, intersection.normal) + v * cross(cross(reflection, intersection.normal), reflection);
						reflectionVector = normalize(reflectionVector);
						Ray reflectionRay(intersection.intersectionPoint, reflectionVector);
						reflectColor += dot(reflectionVector, reflection) / 12 * recurse(reflectionRay, root, eye, ambient, lights, 0, refractNum);
					}
				}
			}

			// specular refraction
			if (REFRACTION_ON) {
				double r = material2->ratio();
				if (refractNum % 2 == 1) r = 1/r;
				float temp = (1-pow(r,2)*(1-pow((-dot(ray.get_direction(), intersection.normal)),2)));
				if (temp <= 0) { return color; }
				vec3 refractDirection = r * ray.get_direction() + (r * (-dot(ray.get_direction(), intersection.normal)) - sqrt(temp)) * intersection.normal;
				Ray refractionRay(intersection.intersectionPoint - 2 * intersection.normal * 0.001, refractDirection);
				refractColor = recurse(refractionRay, root, eye, ambient, lights, count - 1, refractNum + 1);
				
				// glossy refraction
				if (GLOSSY_REFRACTION_ON) {
					refractDirection = normalize(refractDirection);
					vec3 u_vec = cross(refractDirection, -intersection.normal);
					vec3 v_vec = cross(u_vec, refractDirection);
					refractColor = refractColor / 6;
					for (int i = 0; i < 5; i++) {
						float u = -0.15f + random_num() * 0.3f;
						float v = -0.15f + random_num() * 0.3f;
						vec3 refractionVector = refractDirection + u * u_vec + v * v_vec;
						refractionVector = normalize(refractionVector);
						Ray refractionVector_ray(intersection.intersectionPoint - 2 * intersection.normal * 0.001, refractionVector);
						refractColor += dot(refractionVector, refractDirection) / 6 * recurse(refractionVector_ray, root, eye, ambient, lights, count-1, refractNum);
					}
				}
			}
			color = (1-material2->reflectiveness()-material2->refractiveness()) * color + material2->reflectiveness() * reflectColor + material2->refractiveness() * refractColor;
		}
	}
	else {
        color = vec3(0.6, 0.85, 1.0);
	} 
	return color;
}

vec3 random_in_unit_disk() {
    return 2.0 * (vec3(random_num(), random_num(), 0)) - vec3(1, 1, 0);
}

void A5_Render(
		// What to render  
		SceneNode*root,

		// Image to write to, set to a given width and height  
		Image & image,

		// Viewing parameters  
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters  
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {
  	size_t h = image.height();
	size_t w = image.width();

	// find camera coordinate system
	vec3 wVec = normalize(view - eye);
	vec3 uVec = normalize(cross(wVec, up)); 
	vec3 vVec = cross(uVec, wVec); 

	// calculate d 
	float tangentOfAngle = glm::tan(glm::radians(fovy/2));
	float d = h / 2 / tangentOfAngle;

  // iterate over each pixel
  for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {
		
			// create ray
			const vec3 direction = wVec*d - vVec*(float)h / 2 - uVec*(float)w / 2 + (float)x*uVec + (float)(h - y)*vVec ;
			vec3 color;

			// depth of field
			if (DEPTH_OF_FIELD_ON) {
				for (int i = 0; i < 10; i++) {
					vec3 relative_move = vec3((random_num()-0.5f)*15, (random_num()-0.5f)*15, 0);
					vec3 eye_pos = eye + relative_move;
					vec3 focalDir = (direction * ((direction.z-700.0f) / direction.z)) - relative_move;
					Ray ray = Ray(eye_pos, focalDir);
					color += recurse( ray, root, eye_pos, ambient, lights) / 10;
				}
			}
			else {
				Ray ray = Ray(eye, direction);
				ray.direction = direction;

				// anti aliasing
				if (ANTI_ALIASING_ON) {
					for ( int i = 0; i < 4; ++i ) {
						ray.direction = direction + random_in_unit_disk() * ( uVec + vVec ) * 0.5;
						color += recurse(ray, root, eye, ambient, lights);
					}
					color = color / 4;
				}
				else {
					ray.direction = direction;
					color += recurse(ray, root, eye, ambient, lights);
				}
			}
			
			// Red:
			image(x, y, 0) = (double)color.r;
			// Green: 
			image(x, y, 1) = (double)color.g;
			// Blue: 
			image(x, y, 2) = (double)color.b;
		}
	}
	  
  	// printing
 	std::cout << "Calling A5_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light*light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;
}
