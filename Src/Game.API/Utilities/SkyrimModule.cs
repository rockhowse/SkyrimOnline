namespace Game.API.Utilities
{
    public class SkyrimModule : IModule
    {
        string IModule.Name
        {
            get { return "Skyrim"; }
        }

        GameType IModule.GameType
        {
            get { return GameType.kSkyrim; }
        }
    }
}