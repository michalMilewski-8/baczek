#version 330 core

uniform mat4 vieww;
uniform mat4 vieww_i;
uniform mat4 proj;
uniform mat4 proj_i;

layout (location = 0) in vec3 aPos;

out vec3 nearPoint;
out vec3 farPoint;
out float near; //0.01
out float far; //100

// Grid position are in clipped space
vec3 gridPlane[6] = vec3[] (
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    vec4 unprojectedPoint =  view * projection * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
    near = 0.01;
    far = 100;
    vec3 p = aPos;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, vieww_i, proj_i).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, vieww_i, proj_i).xyz; // unprojecting on the far plane
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}