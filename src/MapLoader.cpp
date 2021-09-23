#include "MapLoader.h"

MapLoader::MapLoader(int size) {
    tileSize = size;

    reservedLabels = { "layout" };
    baseAssetPath = "./assets/";
}

Map* MapLoader::Load(const char* file) {
    unordered_map<string, vector<string>> groups = LoadAndParseFileIntoGroups(file);
    vector<vector<string>> layout = ParseLayout(groups["layout"]);

    unordered_map<string, TileDefinition*> tileDefinitions;
    for (auto const& kvp : groups) {
        if (find(reservedLabels.begin(), reservedLabels.end(), kvp.first) == reservedLabels.end()) {
            TileDefinition* def = CreateTileDefinitionFromGroup(kvp.first, kvp.second);
            string defImage = def->GetImageFile();
            tileDefinitions.insert(pair<string, TileDefinition*>(def->GetSymbol(), def));
        }
    }

    Map* map = new Map(layout, tileDefinitions, tileSize);

    return map;
}

unordered_map<string, vector<string>> MapLoader::LoadAndParseFileIntoGroups(const char* file) {
    unordered_map<string, vector<string>> groups;
    string currLabel = "";

    try {
        ifstream mapStream(file, ios_base::in);
        string line;

        while (getline(mapStream, line)) {
            line.erase(remove_if(line.begin(), line.end(), 
               [](char c){ 
                  return std::isspace(static_cast<unsigned char>(c));
               }), line.end());

            if (line.find("{") != string::npos) {
                currLabel = line.substr(0, line.find('{'));
                groups.insert(pair<string, vector<string>>(currLabel, vector<string>()));
            } else if (line.find("}") != string::npos) {
                currLabel = "";
            } else if (!line.empty() && !currLabel.empty()) {
                groups[currLabel].push_back(line);
            }
        }

        mapStream.close();
    } catch (int e) {
        printf("Failed to load map");
    }

    return groups;
}

vector<vector<string>> MapLoader::ParseLayout(vector<string> layout) {
    vector<vector<string>> charLayout;

    for (auto const& row : layout) {
        vector<string> charRow;
        for (auto const& c : row) {
            string s(1, c);
            charRow.push_back(s);
        }

        charLayout.push_back(charRow);
    }

    return charLayout;
}

TileDefinition* MapLoader::CreateTileDefinitionFromGroup(string label, vector<string> definition) {
    unordered_map<string, string> elements;

    for (auto const& line : definition) {
        string token = line.substr(0, line.find('='));
        string predicate = line.substr(line.find('=') + 1);

        elements.insert(pair<string, string>(token, predicate));
    }

    string assetPath = baseAssetPath + elements["image"] + ".png";
    bool isPassable = Utils::StoB(elements["passable"]);

    return new TileDefinition(
        label,
        elements["symbol"],
        assetPath,
        isPassable,
        elements["attribute"]
    );
}