# SkyrimOnline

This mod is intended to sync the player and the world state accross multiple clients.

## Building

You will need **Visual Studio 2013** to build, the community edition is free.
You will also need to install the following :
* [Directx SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
* [Python 3.5](https://www.python.org/ftp/python/3.5.1/python-3.5.1.exe)

1. Now go to **Build/** and double click **MakeVS2013Projects.bat**, this will codegen the netcode and create the Visual Studio solution.
2. Go to *Build/projects* and open **SkyrimOnline.sln**
3. Choose the configuration *PriRel* or *PubRel* (PriDeg does *NOT* work)
4. Click Build.
5. Enjoy.

## Running

1. You will first need to copy the **Data** directory in your Skyrim installation folder.
2. Then you will need to copy **dinput8.dll**, **MyGUIEngine.dll** and **ScriptDragon.dll** which you can find in **Build/Bin** in your Skyrim installation folder.
3. We recommend creating a simlink to **SkyrimOnline.dll** in **Data/SKSE/plugins/**, you can always copy/paste the binary there every time.
4. In **Build/bin/server** you will find Game.exe (PubRel) or Game_r.exe (PriRel), launch one. 

Remember this is the experimental branch and as you can probably see there is no release or stable branch, so if it might not work or even build.

## Licence

See LICENCE
