#include "camera.h"
#include "../window/window.h"

#include <glm/ext.hpp>

Camera::Camera(vec3 position, float fov) : position(position), fov(fov), rotation(1.0f) {
    updateVectors();
}

void Camera::updateVectors() {
    front = vec3(rotation * vec4(0, 0, -1, 1));
    right = vec3(rotation * vec4(1, 0, 0, 1));
    up = vec3(rotation * vec4(0, 1, 0, 1));
}

void Camera::rotate(vec2 rot, float z) {
    rotation = glm::rotate(rotation, z, vec3(0,0,1));
    rotation = glm::rotate(rotation, rot.x, vec3(0,1,0));
    rotation = glm::rotate(rotation, rot.y, vec3(1,0,0));

    updateVectors();
}

vec3 Camera::getPosition() {
    return position*10.0f;
}

mat4 Camera::getProjection() {
    float aspect = (float)Window::width / (float)Window::height;
    return glm::perspective(fov, aspect, 0.1f, 100.0f);
}

mat4 Camera::getView() {
    return glm::lookAt(position, position+front, up);
}