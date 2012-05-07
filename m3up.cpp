#include "m3up.h"

m3up::m3up(std::string conf){
	DIR *dir;
	struct dirent *ent;
	sound_cnt = 0;
	getConfigInformation(conf);
	//go through files in directory to check if mp3, flac, wav, ogg
	dir = opendir(root.c_str());
	if(dir != NULL){
		while((ent = readdir(dir)) != NULL){
			if(endsWith("mp3", ent->d_name) || endsWith("flac", ent->d_name) || endsWith("wav", ent->d_name) || endsWith("ogg", ent->d_name)){
				sound_cnt++;
				songs.push_back(ent->d_name);
			}
		}

		closedir(dir);
		std::cout << sound_cnt << "\n";
	}
	else {
		std::cout << "Error opening directory " << "'" << getRoot() << "'\n";
	}

	std::string real_path = root + "/" + playlist_file;
    //create m3u playlist
    FILE *f = fopen(real_path.c_str(),"w");
	fprintf(f, "#m3uPuppet generated playlist file\n");
	for(int i = 0; i < songs.size(); i++){
		fprintf(f, "http://%s:%s/%s\n", ip.c_str(), port.c_str(), songs[i]);
	}
	fclose(f);


}


void m3up::getConfigInformation(std::string path){
	libconfig::Config config;
	config.readFile(path.c_str());
	root = config.lookup("music_root").c_str();
	port = config.lookup("listen_to").c_str();
	playlist_file = config.lookup("playlist_name").c_str();
	ip = config.lookup("host").c_str();
	
}


std::string m3up::getRoot(){
	return root;
}

std::string m3up::getPort(){
	return port;
}

std::string m3up::getPlaylistName(){
	return playlist_file;
}

int m3up::getSoundCount(){
	return sound_cnt;
}

std::string m3up::getIP(){
	return ip;
}

bool m3up::endsWith(std::string ext, std::string filename){
	int n_last = filename.find_last_of(".");
	filename = filename.substr(n_last + 1, filename.size() -1);
	if(strcmp(ext.c_str(), filename.c_str()) == 0){
		return true;
	}
	else {
		return false;
	}
}