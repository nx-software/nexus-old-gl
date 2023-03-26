#ifndef SCRIPT_H
#define SCRIPT_H
class Script{
private:
	char** keyWords = {"load","set"};
public:
	Script(char* fileName, Nexus nx){
		FILE* fp = fopen(fileName, "r");
		fseek(fp, 0L, SEEK_END);
		size_t scriptL = ftell(fp);
		char scriptData[scriptL];
		std::vector<char> lines;
		char* c;
		int g = 0;
		for(int i = 0; i < strlen(scriptData); i++){
			 if(scriptData[i] != "\n")	
			 	c[g++] = scriptData[i];
			 else{
			 	lines.push_back(c);
			 	c = "";
			 	g = 0;
			 }
		}
		GameObject* model;
		for(int i = 0; i < lines.size(); i++){
			std::string s = lines[i];
			if(s.find("load") != std::string::npos){
				s.substr(0, s.find(" "));
				s.erase(0, s.find(" ") + " ".length());
				model = std::find_if(std::begin(nx.gameObjects), std::end(nx.gameObjects), [&] (gameObject const& g) { return g.Name == s.substr(0, " ");}

			}
		}
	}
}
#endif
