#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    // Create rectangle with given bottom left corner, length, heigth and color 
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float heigth, glm::vec3 color, bool fill = false);

    // Create triangle with given vertices and color
    Mesh* CreateTriangle(const std::string& name, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 color);

    // Create circle with given radius and color
    Mesh* CreateCircle(const std::string& name, float radius, glm::vec3 color);
}
