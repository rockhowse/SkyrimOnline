#pragma once

namespace Skyrim
{
	namespace Game
	{
		class Object
		{
		public:

			Object();
			~Object();

			static void Register(class ScriptEngine* engine);

			Vector3 GetPosition();
			Vector3 GetRotation();
			float GetHeading();
			const std::string& GetName();

			void SetPosition(const Vector3& pos);
			void SetRotation(const Vector3& rot);
			void SetHeading(float heading);
			void SetName(const std::string& pName);

		private:

			std::string mName;
			Vector3 mPosition;
			Vector3 mRotation;
		};
	}
}