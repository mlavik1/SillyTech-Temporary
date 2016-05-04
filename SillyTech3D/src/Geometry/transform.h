#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"


class Actor;

class Transform
{
	friend class EditorGUI; // A is a friend of B
public:
	Transform(Actor* arg_actor);
	~Transform();

private:
	glm::vec3 mPosition;
	glm::mat4 mRotation;
	glm::vec3 mScale;
	//glm::vec3 mGlobalPosition;
	//bool isDirty;
	Actor *mActor;
	glm::quat mRotationQuaternion;
	

public:
	glm::vec3 GetPosition();
	glm::vec3 GetGlobalPosition();
	void SetPosition(glm::vec3 arg_pos);
	void SetGlobalPosition(glm::vec3 arg_pos);
	void PrintPosition();
	//void SetDirty();
	void Rotate(float arg_angles, glm::vec3& rotation);
	void SetRotation(float arg_angles, glm::vec3& rotation);
	void RotateAbout(glm::vec3 rotation, glm::vec3 point);
	glm::vec3 Up();
	glm::vec3 Forward();
	glm::vec3 Right();
	glm::mat4 GetRotation();
	glm::mat4 GetGlobalRotation();
	void SetScale(glm::vec3 arg_scale);
	glm::vec3 GetScale();
	glm::vec3 GetGlobalScale();
	glm::mat4 GetModelMatrix();
	glm::mat4 GetGlobalModelMatrix();

	void Print();
};

#endif