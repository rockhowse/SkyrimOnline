#pragma once
#pragma managed

namespace Game
{
	public interface class ITESForm
	{
		property int FormID
		{
			int get();
		}

		property int FormType
		{
			int get();
		}
	};
}