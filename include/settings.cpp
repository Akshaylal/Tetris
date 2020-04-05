#include <iostream>
#include <fstream>

#include "defval.h"
#include "settings.h"

using namespace std;

Settings::Settings(){
    ifstream s;
    s.open(F_SET, ios::binary);
    if(s){
        if(!s.read((char*)this, sizeof(Settings))){
            reset();
        }
    }else{
        reset();
    }
    s.close();
}

void Settings::change(int c){
    switch(c){
        case 1:sound_bgm = !sound_bgm;
        break;
        case 2:sound_sfx = !sound_sfx;
        break;
        case 3:bg = !bg;
        default:break;
    }
}

void Settings::show(){
    int opt, n = 4, i = 0;
    char ar[n][100];

    do{
        i = 0;
        sprintf(ar[i++], "\t\t|           %d. BGM           (%c)                 |\n", i, sound_bgm?'Y':'N');
        sprintf(ar[i++], "\t\t|           %d. SFX           (%c)                 |\n", i, sound_sfx?'Y':'N');
        sprintf(ar[i++], "\t\t|           %d. Background    (%c)                 |\n", i, bg?'.':' ');
        sprintf(ar[i++], "\t\t|           %d. Reset                             |\n", i);

        cout<<"\033c\n\n\n";
	    cout<<"\t\t+------------------------------------------------+\n";
    	cout<<"\t\t|                                                |\n";
	    cout<<"\t\t|                    SETTINGS                    |\n";
	    cout<<"\t\t|                                                |\n";
        cout<<"\t\t+------------------------------------------------+\n";
	    cout<<"\t\t|                                                |\n";
    	for(int i = 0; i < n; ++i){
            cout<<ar[i];
            cout<<"\t\t|                                                |\n";
        }
        cout<<"\t\t|           0. Back                              |\n";
        cout<<"\t\t|                                                |\n";
	    cout<<"\t\t+------------------------------------------------+\n";
    	cout<<"\t\t: ";
	    cin>>opt;
        if(opt == n){
            reset();
        }else{
            change(opt);
        }
    }while(opt);

    save();
}

void Settings::save(){
    ofstream s;
    s.open(F_SET, ios::binary);
    s.write((char*)this, sizeof(Settings));
    s.close();
}

void Settings::reset(){
    sound_bgm = true;
    sound_sfx = true;
    bg = false;
    save();
}