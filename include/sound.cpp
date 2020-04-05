#include <cstdlib>
#include <cstdio>

#include "sound.h"



Sound::Sound(){
	bgm_enable = true;
	sfx_enable = true;
	bgm_playing = false;
	bgm();
}

Sound::Sound(Settings &sett){
	bgm_enable = sett.sound_bgm;
	sfx_enable = sett.sound_sfx;
	bgm();
}

Sound::~Sound(){
	stop_all();
}

void Sound::refresh(Settings &sett){
	bgm_enable = sett.sound_bgm;
	sfx_enable = sett.sound_sfx;
	if(bgm_playing & !bgm_enable){
		stop_all();
	}
	if(!bgm_playing & bgm_enable){
		bgm();
	}
}

void Sound::bgm(){
	if(bgm_enable){
		sprintf(command , "canberra-gtk-play -f %s -l 10000 -V 10.0 &", BGM);
		system(command);
		bgm_playing = true;
	}
}

void Sound::spin(){
	if(sfx_enable){
		sprintf(command , "canberra-gtk-play -f %s -V -5.0 &", SPIN);
		system(command);
	}
}

void Sound::hdrop(){
	if(sfx_enable){
		sprintf(command , "canberra-gtk-play -f %s -V -5.0 &", HDROP);
		system(command);
	}
}

void Sound::movelr(){
	if(sfx_enable){
		sprintf(command , "canberra-gtk-play -f %s -V 0.0 &", MOVELR);
		system(command);
	}
}

void Sound::clear(){
	if(sfx_enable){
		sprintf(command , "canberra-gtk-play -f %s -V -5.0 &", CLEAR);
		system(command);
	}
}

void Sound::gameover(){
	stop_all();
	if(sfx_enable){
		system("killall canberra-gtk-play");
		sprintf(command , "canberra-gtk-play -f %s -V -5.0 &", GAME_OVER);
		system(command);
	}
}

void Sound::stop_all(){
	system("killall canberra-gtk-play");
	bgm_playing = false;
}