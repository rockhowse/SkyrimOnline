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
			engine->RegisterReferenceClass(Object);
			engine->RegisterMethod(Object, "const string& GetName()", asMETHOD(Object, GetName));
			engine->RegisterMethod(Object, "void SetName(const string &in)", asMETHOD(Object, SetName));
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
		void Object::SetPosition(float x, float y, float z)
		{
			mPosition.x = x;
			mPosition.y = y;
			mPosition.z = z;
		}
		//--------------------------------------------------------------------------------
		void Object::SetRotation(float x, float y, float z)
		{
			mRotation.x = x;
			mRotation.y = y;
			mRotation.z = z;
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