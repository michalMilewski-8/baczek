#include "Block.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

glm::vec3 Block::TransformToDivisions(glm::vec3 pos) const
{
	return { std::round((pos.x / (double)x_size + 0.5f) * (x_divisions - 1)),std::round((pos.y / (double)y_size + 0.5f) * (y_divisions - 1)),pos.z };
}

void Block::SetViewPos(glm::vec3 view_pos)
{
	this->view_pos = view_pos;
}

void Block::Update()
{
	need_update = true;
}

glm::vec3 Block::GetPoint()
{
	glm::mat4 model = translate * rotate * resize;
	glm::vec3 lp = przekontna->GetLastPoint();
	glm::vec4 lp4 = { lp.x,lp.y,lp.z,1 };
	return model * lp4;
}

void Block::SetSize(float size)
{
	x_size = size;
	y_size = size;
	z_size = size;
	blocks_need_creation = true;
	recalc_tensor(size);
	Update();
}

void Block::SetDenisity(float den)
{
	denisity = den;
	recalc_tensor(x_size);
}

void Block::SetAngularSpeed(float sp)
{
	angular_speed = { 0,sp,0 };
}

void Block::CalculateFrame(float T)
{
	runge_kutta_next_step(T, angular_speed, rotation_, angular_speed, rotation_);
}

void Block::DrawFrame(glm::mat4 mvp)
{
	this->RotateObject(rotation_);
	DrawObject(mvp);
}

void Block::create_block_points()
{

	// Point xyz // 0
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(1.0f);

	// Point xyz // 4
	points.push_back(0);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(1.0f);

	// Point xyz // 1
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(1.0f);

	// Point xyz // 1
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(1.0f);

	// Point xyz // 4
	points.push_back(0);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(1.0f);

	// Point xyz // 5
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(1.0f);

	// Point xyz // 1
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 5
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 6
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 1
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 6
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 2
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 0
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(-1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 3
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(-1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 4
	points.push_back(0);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(-1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);


	// Point xyz // 3
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(-1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 7
	points.push_back(0);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(-1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 4
	points.push_back(0);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(-1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);


	// Point xyz // 7
	points.push_back(0);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(-1.0f);

	// Point xyz // 3
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(-1.0f);

	// Point xyz // 6
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(-1.0f);

	// Point xyz // 6
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(-1.0f);

	// Point xyz // 3
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(-1.0f);

	// Point xyz // 2
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(0.0f);
	points.push_back(-1.0f);


	// Point xyz // 4
	points.push_back(0);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(1.0f);
	points.push_back(0.0f);

	// Point xyz // 7
	points.push_back(0);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(1.0f);
	points.push_back(0.0f);

	// Point xyz // 6
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(1.0f);
	points.push_back(0.0f);


	// Point xyz // 5
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(1.0f);
	points.push_back(0.0f);
	points.push_back(0.0f);

	// Point xyz // 4
	points.push_back(0);
	points.push_back(0);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(1.0f);
	points.push_back(0.0f);

	// Point xyz // 6
	points.push_back(x_size);
	points.push_back(0);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(1.0f);
	points.push_back(0.0f);


	// Point xyz // 0
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(-1.0f);
	points.push_back(0.0f);

	// Point xyz // 1
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(-1.0f);
	points.push_back(0.0f);

	// Point xyz // 3
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(-1.0f);
	points.push_back(0.0f);


	// Point xyz // 1
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(z_size);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(-1.0f);
	points.push_back(0.0f);

	// Point xyz // 2
	points.push_back(x_size);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(-1.0f);
	points.push_back(0.0f);

	// Point xyz // 3
	points.push_back(0);
	points.push_back(-y_size);
	points.push_back(0);
	// Normal xyz
	points.push_back(0.0f);
	points.push_back(-1.0f);
	points.push_back(0.0f);


	//// Point xyz // 7
	//points.push_back(0);
	//points.push_back(0);
	//points.push_back(0);
	//// Normal xyz
	//points.push_back(0.0f);
	//points.push_back(0.0f);
	//points.push_back(1.0f);

	//// Point xyz // 1
	//points.push_back(x_size);
	//points.push_back(-y_size);
	//points.push_back(z_size);
	//// Normal xyz
	//points.push_back(0.0f);
	//points.push_back(0.0f);
	//points.push_back(1.0f);



// Indexing triangles
	for (int i = 0; i < points.size(); i += 6) {
		quads.push_back(i / 6);
	}

	blocks_need_creation = false;
}

void Block::update_object()
{
	if (blocks_need_creation) {
		quads.clear();
		points.clear();

		create_block_points();

		shader.use();
		// 1. bind Vertex Array Object
		glBindVertexArray(VAO);
		// 2. copy our vertices array in a vertex buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_DYNAMIC_DRAW);
		// 3. copy our index array in a element buffer for OpenGL to use
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * quads.size(), quads.data(), GL_DYNAMIC_DRAW);
		// 4. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, description_number * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, description_number * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		int x_deltaPos = glGetUniformLocation(shader.ID, "x_delta");
		glUniform1f(x_deltaPos, x_delta);

		int y_deltaPos = glGetUniformLocation(shader.ID, "y_delta");
		glUniform1f(y_deltaPos, y_delta);

		int x_sizePos = glGetUniformLocation(shader.ID, "x_size");
		glUniform1f(x_sizePos, x_size);

		int y_sizePos = glGetUniformLocation(shader.ID, "y_size");
		glUniform1f(y_sizePos, y_size);

		int z_sizePos = glGetUniformLocation(shader.ID, "z_size");
		glUniform1f(z_sizePos, z_size);

		blocks_need_creation = false;
		przekontna->ClearPoints();
		przekontna->AddPoint({ 0,0,0 });
		przekontna->AddPoint({ x_size,-y_size,z_size });
		calculate_mass();
	}

}

void Block::recalc_tensor(float size)
{
	float pow5 = pow(size, 5);
	tensor = glm::mat3(1.0f);
	tensor[0][0] = 11.0f * pow5 / 12;
	tensor[1][1] = pow5 / 6;
	tensor[2][2] = 11.0f * pow5 / 12;

	tensor = tensor * denisity;

	tensor_inv = glm::inverse(tensor);
	calculate_mass();
}

void Block::runge_kutta_next_step(float h, glm::vec3 w, glm::quat q, glm::vec3& w_next, glm::quat& q_next)
{
	glm::vec3 w_k1; glm::quat q_k1;
	glm::vec3 w_k2; glm::quat q_k2;
	glm::vec3 w_k3; glm::quat q_k3;
	glm::vec3 w_k4; glm::quat q_k4;

	calculate_f(h / 2,
		w, q,
		w_k1, q_k1);

	calculate_f(h / 2,
		w + h * w_k1 / 2.0f, q + h * q_k1 / 2.0f,
		w_k2, q_k2);

	calculate_f(h / 2,
		w + h * w_k2 / 2.0f, q + h * q_k2 / 2.0f,
		w_k3, q_k3);

	calculate_f(h,
		w + h * w_k3, q + h * q_k3,
		w_k4, q_k4);

	h = h / 6.0f;
	w_next = w + h * (w_k1 + 2.0f * w_k2 + 2.0f * w_k3 + w_k4);
	q_next = glm::normalize(q + h * (q_k1 + 2.0f * q_k2 + 2.0f * q_k3 + q_k4));
}

void Block::calculate_f(float h, glm::vec3 w, glm::quat q, glm::vec3& w_res, glm::quat& q_res)
{
	//TODO calculate N
	glm::vec3 N = { 0,0,0 };



	if (gravity) {
		N.y = -mass * 9.8123f;
		N = glm::rotate(glm::inverse(glm::normalize(q)), N);
		N = glm::cross(glm::vec3(0, x_size * 1.73205080757f/2.0f, 0), N);
	}

	w_res = tensor_inv * (N + glm::cross(tensor * w, w));
	q_res = quat_x_vec(q, w) / 2.0f;
}

void Block::calculate_mass()
{
	mass = x_size * x_size * x_size * denisity;
	center_of_mass = glm::vec3(0.5, -0.5, 0.5) * x_size;

	gravity_vec->ClearPoints();
	gravity_vec->AddPoint(center_of_mass);
	gravity_vec->AddPoint(center_of_mass - glm::vec3(0, mass / 2.0f, 0));
	gravity_vec->AddPoint(center_of_mass - glm::vec3(-0.05f * mass, mass / 2.0f - 0.05f * mass, 0));
	gravity_vec->AddPoint(center_of_mass - glm::vec3(0, mass / 2.0f, 0));
	gravity_vec->AddPoint(center_of_mass - glm::vec3(0.05f * mass, mass / 2.0f - 0.05f * mass, 0));
	gravity_vec->AddPoint(center_of_mass - glm::vec3(0, mass / 2.0f, 0));
}

glm::quat Block::quat_x_vec(glm::quat q, glm::vec3 v)
{
	glm::mat3x4 m;

	m[0][0] = -q.x;
	m[1][0] = -q.y;
	m[2][0] = -q.z;

	m[0][1] = q.w;
	m[1][1] = -q.z;
	m[2][1] = q.y;

	m[0][2] = q.z;
	m[1][2] = q.w;
	m[2][2] = -q.x;

	m[0][3] = -q.y;
	m[1][3] = q.x;
	m[2][3] = q.w;

	glm::vec4 w = m * v;

	return glm::quat(w[0], w[1], w[2], w[3]);
}

Block::Block(float x_size_, float y_size_, float z_size_, int x_divisions_, int y_divisions_, Shader sh) :
	Object(sh, 6)
{
	x_size = x_size_;
	y_size = y_size_;
	z_size = z_size_;
	x_divisions = x_divisions_;
	y_divisions = y_divisions_;
	przekontna = std::make_shared<Line>(sh);
	przekontna->SetColor({ 1,0,0,1 });
	przekontna->SetLineWidth(5.0f);

	gravity_vec = std::make_shared<Line>(sh);
	gravity_vec->SetColor({ 0,0.8,1,1 });
	gravity_vec->SetLineWidth(3.0f);

	shader = Shader("shader_tex.vs", "shader_tex.fs");
	update_object();
	shader.use();
}

void Block::DrawObject(glm::mat4 mvp)
{
	if (need_update) {
		update_object();
		need_update = false;
	}

	Object::DrawObject(mvp);

	glm::mat4 model = translate * rotate * resize;
	glm::mat4 vp = mvp;
	if (draw_cube) {
		shader.use();
		glm::mat4 trmodel = glm::transpose(glm::inverse(model));
		int projectionLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(model));

		int trmodelLoc = glGetUniformLocation(shader.ID, "trmodel");
		glUniformMatrix4fv(trmodelLoc, 1, GL_FALSE, glm::value_ptr(trmodel));

		int mvLoc = glGetUniformLocation(shader.ID, "vp");
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(vp));

		int viewPos = glGetUniformLocation(shader.ID, "viewPos");
		glUniform3fv(viewPos, 1, &view_pos[0]);

		int colorPos = glGetUniformLocation(shader.ID, "color");


		color = { 0.7,0.7,0 };
		glUniform3fv(colorPos, 1, &color[0]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, quads.size(), GL_UNSIGNED_INT, 0);

		color = { 1,1,1 };
		glUniform3fv(colorPos, 1, &color[0]);
		glLineWidth(5.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, quads.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	if (draw_diagonal) {
		glDisable(GL_DEPTH_TEST);
		przekontna->DrawObject(mvp * model);
		glEnable(GL_DEPTH_TEST);
	}
	if (gravity) {
		glDisable(GL_DEPTH_TEST);
		gravity_vec->MoveObjectTo(glm::vec3(model * glm::vec4(center_of_mass, 0)) - center_of_mass);
		gravity_vec->DrawObject(mvp);
		glEnable(GL_DEPTH_TEST);
	}

}

void Block::RotateObject(glm::quat q)
{
	q = glm::normalize(q);
	rotation_ = q;
	glm::quat q1 = glm::normalize(RotationBetweenVectors(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	Object::RotateObject(q * q1);
}

glm::quat Block::EulerToQuaternion(glm::vec3 rot)
{
	//glm::vec3 Ox = { 1,0,0 };
	//glm::vec3 Oy = { 0,1,0 };
	//glm::vec3 Oz = { 0,0,1 };

	//rot = rot / (float)(180.0f * M_PI);

	//glm::quat quat = {0,0,0,1};
	//auto q = glm::angleAxis(rot.x, Oz);
	//Ox = q * Ox;
	//Oy = q * Oy;
	//Oz = q * Oz;
	//quat = q * quat;

	//q = glm::angleAxis(rot.y, Ox);
	//Ox = q * Ox;
	//Oy = q * Oy;
	//Oz = q * Oz;
	//quat = q * quat;

	//q = glm::angleAxis(rot.z, Oz);
	//Ox = q * Ox;
	//Oy = q * Oy;
	//Oz = q * Oz;
	//quat = q * quat;

	//return quat;

	rot = rot / (float)(180.0f * M_PI);
	// Abbreviations for the various angular functions
	double yaw = rot.x;
	double pitch = rot.y;
	double roll = rot.z;
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

glm::vec3 Block::QuaternionToEuler(glm::quat quat)
{
	return (glm::eulerAngles(quat) / (float)M_PI) * 180.0f;
}
