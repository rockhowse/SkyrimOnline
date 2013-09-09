namespace Game.API.Utilities
{
    public class OblivionModule : IModule
    {
        string IModule.Name
        {
            get { return "Oblivion"; }
        }

        GameType IModule.GameType
        {
            get { return GameType.kOblivion; }
        }
    }
}