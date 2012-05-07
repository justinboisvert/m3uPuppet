/*
	M3uPuppet, an mp3 streaming server through HTTTP which can be accessed through the 
	.m3u file it serves.
*/

#include <iostream>
#include <string.h>
#include "m3up.h"
#include "mongoose.h"

//Callback function

static void *callbck (enum mg_event event, struct mg_connection *conn, const struct mg_request_info *request_info){
	if(event == MG_NEW_REQUEST){
		//if new request
		return 0;
	}
	else {
		return NULL;
	}
}

int main(int argc, char *argv[]){
	m3up *puppet = new m3up("m3upuppet.conf");
	std::string port = puppet->getPort();
	const char* options[] = {
		"listening_ports", port.c_str(),
		"document_root", puppet->getRoot().c_str(),
		NULL
	};
	static struct mg_context *context;
	context = mg_start(&callbck, NULL, options);
	std::cout << "m3upuppet server running at http://" << ip << ":" << port << " ..press enter to end process.\n";
	std::cout << "Document root: " << puppet->getRoot() << " Playlist file: " << puppet->getPlaylistName() << "\n";
	getchar();
	mg_stop(context);
}