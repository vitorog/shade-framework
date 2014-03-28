#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Object::Object()
{

}

Object::Object(glm::vec3 position) :
    position_(position)
{
}
