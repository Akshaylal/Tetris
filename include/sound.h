#ifndef SOUND_H
#define SOUND_H

#define BGM "SFX/Tetris.ogg"
#define SEL "SFX/select.ogg"
#define SPIN "SFX/block-rotate.ogg"
#define HDROP "SFX/force-hit.ogg"
#define MOVELR "SFX/whoosh.ogg"
#define CLEAR "SFX/line-remove.ogg"
#define GAME_OVER "SFX/gameover.ogg"


#include "settings.h"

class Sound{
	char command[100];
	bool bgm_enable, sfx_enable;
	bool bgm_playing;
	public:
		Sound();
		Sound(Settings&);
		~Sound();
		void refresh(Settings&);
		void bgm();
		void spin();
		void hdrop();
		void movelr();
		void clear();
		void gameover();
		void select();
		void stop_all();
		
};

#endif
