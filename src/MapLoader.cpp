#include "MapLoader.h"

const std::string hp = "hp";
const std::string hpMax = "hpMax";
const std::string str = "str";
const std::string def = "def";
const std::string agi = "agi";
const std::string spd = "spd";
const std::string mov = "mov";

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

// Parse a Stats object from provided attribute string. Formatted as [attr1, attr3, attr-2, etc]
Stats MapLoader::ParseStats(string attributes) {
    attributes.erase(remove(attributes.begin(), attributes.end(), '['), attributes.end());
    attributes.erase(remove(attributes.begin(), attributes.end(), ']'), attributes.end());

    string delimiter = ",";
    string token;
    size_t pos = 0;

    vector<string> attrs;
    while ((pos = attributes.find(delimiter)) != string::npos) {
        token = attributes.substr(0, pos);
        attrs.push_back(token);
        attributes.erase(0, pos + delimiter.length());
    }

    if (!attributes.empty()) {
        attrs.push_back(attributes);
    }

    Stats stats;
    smatch matches;
    regex pattern("([A-Za-z]+)(-?[0-9]+)");

    for (auto const& attr : attrs) {
        if (!regex_search(attr, matches, pattern)) {
            throw invalid_argument("attributes not properly formatted");
        }

        string attrType = matches.str(1);
        int attrVal = stoi(matches.str(2));

        if (attrType.compare(hp) == 0) {
            stats.hp = attrVal;
        } else if (attrType.compare(hpMax) == 0) {
            stats.hpMax = attrVal;
        } else if (attrType.compare(str) == 0) {
            stats.str = attrVal;
        } else if (attrType.compare(def) == 0) {
            stats.def = attrVal;
        } else if (attrType.compare(agi) == 0) {
            stats.agi = attrVal;
        } else if (attrType.compare(spd) == 0) {
            stats.spd = attrVal;
        } else if (attrType.compare(mov) == 0) {
            stats.mov = attrVal;
        }
    }

    return stats;
}

TileDefinition* MapLoader::CreateTileDefinitionFromGroup(string label, vector<string> definition) {
    unordered_map<string, string> elements;

    for (auto const& line : definition) {
        string token = line.substr(0, line.find('='));
        string predicate = line.substr(line.find('=') + 1);

        elements.insert(pair<string, string>(token, predicate));
    }

    Stats stats = ParseStats(elements["attributes"]);
    string assetPath = baseAssetPath + elements["image"] + ".png";
    bool isPassable = Utils::StoB(elements["passable"]);

    return new TileDefinition(
        label,
        elements["symbol"],
        assetPath,
        isPassable,
        stats
    );
}