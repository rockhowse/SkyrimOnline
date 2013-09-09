namespace Game.API.Utilities
{
    public enum GameType
    {
        kSkyrim,
        kOblivion
    }

    public interface IModule
    {
        string Name { get; }

        GameType GameType { get; }
    }
}