#pragma once
#include "Object.h"
#include "Line.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

class Block :
	public Object
{
public:
	Block(float x_size_, float y_size_, float z_size_, int x_divisions_, int y_divisions_, Shader sh);

	void DrawObject(glm::mat4 mvp) override;
	void RotateObject(glm::quat q) override;

	static glm::quat EulerToQuaternion(glm::vec3 rot);
	static glm::vec3 QuaternionToEuler(glm::quat quat);

	int GetXDivisions() const { return x_divisions; }
	int GetYDivisions() const { return y_divisions; }
	float GetXSize() const { return x_size; }
	float GetYSize() const { return y_size; }

	glm::vec3 TransformToDivisions(glm::vec3 pos) const;

	void SetViewPos(glm::vec3 view_pos);
	void Update() override;

	glm::vec3 GetPoint();

	void SetSize(float size);
	void SetDenisity(float den);
	void SetAngularSpeed(float sp);

	void DrawFrame(glm::mat4 mvp);
	void CalculateFrame(float T);

	bool draw_cube = true;
	bool draw_diagonal = true;
	bool gravity = true;

private:
	void create_block_points();
	void update_object() override;
	void recalc_tensor(float size);
	void runge_kutta_next_step(float h, glm::vec3 w, glm::quat q, glm::vec3& w_next, glm::quat& q_next);
	void calculate_f(float h, glm::vec3 w, glm::quat q, glm::vec3& w_res, glm::quat& q_res);
	void calculate_mass();
	glm::quat quat_x_vec(glm::quat q, glm::vec3 v);

	int x_divisions;
	int y_divisions;

	float x_size;
	float y_size;
	float z_size;

	float denisity = 1;

	std::vector<std::vector<float>> height_map;
	std::vector<float>data = {};

	glm::vec3 view_pos;
	bool blocks_need_creation = true;
	float x_delta;
	float y_delta;

	std::shared_ptr<Line> przekontna;

	glm::quat rotation_;
	glm::vec3 angular_speed = {0,0,0};
	float mass = 1.0f;

	unsigned int texture;
	std::vector<float> points;
	std::vector<unsigned int> quads;





	glm::vec3 color;
	glm::mat3 tensor;
	glm::mat3 tensor_inv;
};

