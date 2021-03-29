#pragma once

#include "Config.hpp"

class ApplicationConfig : public Config
{
public:
	struct
	{
		std::string executableFolderPath;
		std::string executableFile;
		std::string configFile;
		std::string logFile;
		std::string lookupURL;
		std::vector<std::string> modArchiveExtensions;
#pragma warning( push )
#pragma warning( disable : 26495 )
		bool createLogFile;
		bool showTooltips;
		bool showExtractTip;
#pragma warning( pop )
		std::string version;
	} application;

	struct
	{
		int maxFolderLength;
		int maxFullPathLength;
		int maxPathCount;
		int maxActive;
		std::string executableFile;
		std::vector<std::string> additionalExecutableFiles;
		std::string productName;
		std::string requiredVersion;
		std::string modsConfigFile;
		std::string installConfigFile;
		std::vector<std::string> additionalInstallConfigFiles;
		std::string pauseIndicator;
		std::string modPathSuffix;
		std::string baseMoviePath;
		std::vector<std::string> cutsceneFolders;
		std::string subtitleFolder;
		std::string squirrelFolder;
		std::string shaderFolder;
		std::string folderPath;
		std::string modsFolder;
		std::string archivesFolder;
		std::string modPathPrefix;
	} game;

	struct
	{
		bool isMaximized;
		std::string listColumnOrder;
		std::string position;
		std::string size;
	} window;

	ApplicationConfig()
	{
		wxString path, name, ext;
		wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(), &path, &name, &ext);

		if (ext != wxEmptyString)
			name += "." + ext;

		application.executableFolderPath = std::string(path);
		application.executableFile = std::string(name);

		application.configFile = "dmm.cfg";
		application.logFile = "dmm.log";
		application.lookupURL = "https://www.google.com/search?q=";
		application.modArchiveExtensions.assign({ "7z", "zip", "rar", "crf" });

		game.maxFolderLength = 30;
		game.maxFullPathLength = 255;
		game.maxPathCount = 63;
		game.maxActive = 0; // Computed while loading mods setup.
		game.additionalExecutableFiles.assign({ "shock2.exe", "ss2.exe", "thief.exe", "thief2.exe" });
		game.additionalInstallConfigFiles.assign({ "install.cfg", "darkinst.cfg" }); // install.cfg for SS2/Thief, darkinst.cfg for Thief2
		game.modsConfigFile = "cam_mod.ini";
		game.pauseIndicator = "*";
		game.cutsceneFolders.assign({ "cutscenes", "movies" }); // cutscenes for SS2, movies for Thief games
		game.subtitleFolder = "subtitles";
		game.squirrelFolder = "sq_scripts";
		game.shaderFolder = "shaders";

		configVariables();
	}

private:
	void configVariables() override
	{
		CVAR(application.createLogFile, true);
		CVAR(application.showTooltips, true);
		CVAR(application.showExtractTip, true);
		CVAR(application.version, "");

		CVAR(game.modPathSuffix, ".\\patch_ext");
		CVAR(game.modPathPrefix, "");
		CVAR(game.baseMoviePath, ".\\cutscenes+.\\Data\\cutscenes");
		CVAR(game.folderPath, "");
		CVAR(game.executableFile, "shock2.exe");
		CVAR(game.installConfigFile, "install.cfg");
		CVAR(game.modsFolder, "DMM");
		CVAR(game.archivesFolder, "DMMArchives");

		CVAR(window.isMaximized, false);
		CVAR(window.listColumnOrder, "");
		CVAR(window.position, "");
		CVAR(window.size, "");
	}
};