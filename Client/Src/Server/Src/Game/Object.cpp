#include "stdafx.h"
#include "Object.hpp"
#include "ScriptEngine.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		void Object::Register(ScriptEngine* engine)
		{
			engine->RegisterPODType(Vector3);
			engine->RegisterProperty(Vector3, "float x", x);
			engine->RegisterProperty(Vector3, "float y", y);
			engine->RegisterProperty(Vector3, "float z", z);

			engine->RegisterReferenceClass(Object);
			engine->RegisterMethod(Object, "const string& GetName()", GetName);
			engine->RegisterMethod(Object, "void SetName(const string &in)", SetName);
			engine->RegisterMethod(Object, "void SetPosition(const Vector3 &in)", SetPosition);
			engine->RegisterMethod(Object, "void SetRotation(const Vector3 &in)", SetRotation);
			engine->RegisterMethod(Object, "void SetHeader(float)", SetHeading);
			engine->RegisterMethod(Object, "Vector3 GetPosition()", GetPosition);
			engine->RegisterMethod(Object, "Vector3 GetRotation()", GetRotation);
			engine->RegisterMethod(Object, "float GetHeading()", GetHeading);

		}
		//--------------------------------------------------------------------------------
		Object::Object()
		{

		}
		//--------------------------------------------------------------------------------
		Object::~Object()
		{

		}
		//--------------------------------------------------------------------------------
		const std::string& Object::GetName()
		{
			return mName;
		}
		//--------------------------------------------------------------------------------
		Vector3 Object::GetPosition()
		{
			return mPosition;
		}
		//--------------------------------------------------------------------------------
		Vector3 Object::GetRotation()
		{
			return mRotation;
		}
		//--------------------------------------------------------------------------------
		float Object::GetHeading()
		{
			return mRotation.y;
		}
		//--------------------------------------------------------------------------------
		void Object::SetPosition(const Vector3& pos)
		{
			mPosition.x = pos.x;
			mPosition.y = pos.y;
			mPosition.z = pos.z;
		}
		//--------------------------------------------------------------------------------
		void Object::SetRotation(const Vector3& rot)
		{
			mRotation.x = rot.x;
			mRotation.y = rot.y;
			mRotation.z = rot.z;
		}
		//--------------------------------------------------------------------------------
		void Object::SetHeading(float heading)
		{
			mRotation.y = heading;
		}
		//--------------------------------------------------------------------------------
		void Object::SetName(const std::string& pName)
		{
			mName = pName;
		}
		//--------------------------------------------------------------------------------
	}
}