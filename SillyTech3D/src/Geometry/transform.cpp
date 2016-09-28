// ************************************************************
// *********************** Transformations ********************
//
// Litt rotete, det bør fiksast opp i
//
// Rotasjonsmatrisen er eit slags mellomlager. Rotasjonen ligg eigentleg lagra i mRotationQuaternion
// IKKJE FORSØK ?LAGRE ROTASJON DIREKTE I MATRISEN  - AntTweakBar bruker quaternion'en

#include "transform.h"
#include "debug.h"
#include "actor.h"

Transform::Transform(Actor* arg_actor)
{
	REPLICATION_CONSTRUCTOR()

	SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//isDirty = true;
	mActor = arg_actor;
	mRotation = glm::mat4(1.0f);
	mScale = glm::vec3(1.0f);
}

Transform::~Transform()
{

}


glm::vec3 Transform::GetPosition()
{
	return mPosition;
}

glm::vec3 Transform::GetGlobalPosition()
{
	/*if (isDirty)
	{
		if (mActor->GetParent())
			mGlobalPosition = mPosition + mActor->GetParent()->GetTransform().GetGlobalPosition();
		else
			mGlobalPosition = mPosition;

		isDirty = false;		
	}*/
	if (mActor->GetParent())
		return mPosition + mActor->GetParent()->GetTransform().GetGlobalPosition();
	else
		return mPosition;

	//return mGlobalPosition;
}


void Transform::SetPosition(glm::vec3 arg_pos)
{
	mPosition = arg_pos;
	//mActor->SetTransformDirty();
}

void Transform::SetGlobalPosition(glm::vec3 arg_pos)
{
	mPosition = arg_pos;
}

void Transform::PrintPosition()
{
	LOG_INFO() << "x: " << mPosition.x << " - y: " << mPosition.y << " - z: " << mPosition.z;
}

/*
void Transform::SetDirty()
{
	isDirty = true;
}*/


glm::vec3 Transform::Up()
{
	return glm::normalize(glm::vec3(GetRotation() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
}
glm::vec3 Transform::Forward()
{
	return glm::normalize(glm::vec3(GetRotation() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
}
glm::vec3 Transform::Right()
{
	return glm::normalize(glm::cross(Forward(), Up()));
}

void Transform::SetRotation(float arg_angles, glm::vec3& rotation)
{
	mRotationQuaternion = glm::normalize(glm::angleAxis(arg_angles, rotation));//gtx::quaternion::angleAxis(degrees(RotationAngle), RotationAxis);

	mRotation = glm::toMat4(mRotationQuaternion);
}

void Transform::Rotate(float arg_angles, glm::vec3& rotation)
{
	// rotation is local
	mRotationQuaternion =  glm::normalize(glm::angleAxis(arg_angles, rotation))*mRotationQuaternion ;//gtx::quaternion::angleAxis(degrees(RotationAngle), RotationAxis);
		
	mRotation = glm::toMat4(mRotationQuaternion);
}

void Transform::RotateAbout(glm::vec3 arg_angles, glm::vec3 point)
{
	// TODO
}

glm::mat4 Transform::GetRotation()
{
	return mRotation;
}

glm::mat4 Transform::GetGlobalRotation()
{
	if (mActor->GetParent())
	{
		glm::mat4 mv = mActor->GetParent()->GetTransform().GetModelMatrix() * GetModelMatrix();
		glm::mat3 O = glm::mat3(mv);
		O = O._inverse();
		glm::mat4 voff(O);
		voff[3][3] = 1;
		//return voff;
		return glm::toMat4(mActor->GetParent()->GetTransform().mRotationQuaternion* mRotationQuaternion);
	}
		
	else
		return mRotation;
}

void Transform::SetScale(glm::vec3 arg_scale)
{
	mScale = arg_scale;
}

glm::vec3 Transform::GetScale()
{
	return mScale;
}

glm::vec3 Transform::GetGlobalScale()
{
	if (mActor->GetParent())
		return mScale * mActor->GetParent()->GetTransform().GetGlobalScale();
	else
		return mScale;
}

void Transform::Print()
{
	LOG_INFO() << mPosition.x << ", " << mPosition.y << ", " << mPosition.z;
}

glm::mat4 Transform::GetModelMatrix()
{
	mRotation = glm::toMat4(mRotationQuaternion); 

	glm::mat4 transMat, scaleMat;
	transMat = glm::translate(glm::mat4(1.0f), GetPosition());
	scaleMat = glm::scale(glm::mat4(1.0f), GetScale());
	return transMat * GetRotation() * scaleMat;

}

glm::mat4 Transform::GetGlobalModelMatrix()
{
	if (mActor->GetParent())
		return mActor->GetParent()->GetTransform().GetGlobalModelMatrix() * GetModelMatrix();
	return GetModelMatrix();

}