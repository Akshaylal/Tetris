#ifndef SETTINGS_H
#define SETTINGS_H

class Settings{
    public:
       	bool sound_bgm, sound_sfx;
        bool bg;
        
        Settings();
        void change(int);
        void show();
        void menu();
        void save();
        void reset();
};

#endif