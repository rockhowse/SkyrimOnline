#pragma once

namespace Skyrim
{
	namespace Game
	{
		class AssetManager
		{
		public:

			AssetManager();
			~AssetManager();
			void Add(TESObjectREFR* pAsset);
			void Remove(TESObjectREFR* pAsset);

		protected:

			void Write();

		private:

			std::list<uint32_t> mAssets;
		};
	}
}