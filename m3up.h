#ifndef M3UP_H
#define M3UP_H
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <dirent.h>
#include <libconfig.h++>
class m3up {
	private:
		int sound_cnt;
		std::string root;
		std::string port;
		std::string playlist_file;
		std::vector<char*> songs;
		std::string ip;
		bool endsWith(std::string ext, std::string filename);
	public:
		m3up(std::string conf);
		void getConfigInformation(std::string path);
		int getSoundCount();
		std::string getPort();
		std::string getPlaylistName();
		std::string getRoot();
		std::string getIP();

};
#endif