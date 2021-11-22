#include "Block.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

glm::vec3 Block::TransformToDivisions(glm::vec3 pos) const
{
	return {  std::round((pos.x / (double)x_size + 0.5f) * (x_divisions - 1)),std::round((pos.y / (double)y_size + 0.5f) * (y_divisions - 1)),pos.z };
}

void Block::SetViewPos(glm::vec3 view_pos)
{
	this->view_pos = view_pos;
}

void Block::Update()
{
	need_update = true;
}

float Block::GetHeight(int x, int y)
{
	
	if (x >= 0 && x < x_divisions && y >= 0 && y < y_divisions)
		return data[y * x_divisions + x];
	else
		return -100.0f;
}

void Block::SetHeight(int x, int y, float val)
{
	if (x >= 0 && x < x_divisions && y >= 0 && y < y_divisions)
		data[y * x_divisions + x] = val;
}

void Block::DrawFrame(float T, glm::vec3 start_pos, glm::vec3 end_pos, glm::vec3 rotation_start, glm::vec3 rotation_end, bool aproximation_is_line)
{
	rotate = glm::mat4(0.0f);

	if (aproximation_is_line) {
		this->MoveObjectTo(start_pos + (end_pos - start_pos) * T);
		this->RotateObject(EulerToQuaternion(rotation_start + (rotation_end - rotation_start) * T));
	}
}

void Block::DrawFrame(float T, glm::vec3 start_pos, glm::vec3 end_pos, glm::quat rotation_start, glm::quat rotation_end, bool aproximation_is_line)
{
	rotate = glm::mat4(0.0f);

	if (aproximation_is_line) {
		this->MoveObjectTo(start_pos + (end_pos - start_pos) * T);
		this->RotateObject(rotation_start + (rotation_end - rotation_start) * T);
	}
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
	for (int i = 0; i < points.size(); i+=6) {
		quads.push_back(i/6);
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
		przekontna->AddPoint({ 0,0,0 });
		przekontna->AddPoint({ x_size,-y_size,z_size });
	}

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
	else {
		przekontna->DrawObject(model * mvp);
	}
	
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
