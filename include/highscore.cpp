#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "defval.h"
#include "highscore.h"

using namespace std;

// Player

Player::Player(){
    score = 0;
    for(int i = 0; i < 20; ++i)
        name[i] = 0;
}

Player::Player(char* n, unsigned int sc){
    strcpy(name, n);
    score = sc;
}

void Player::print(){
    cout<<setw(20)<<left<<name<<" | "<<setw(14)<<right<<score;
}

unsigned int Player::getscore(){
    return score;
}

// HS

HS::HS(){
    ifstream f;
    f.open(F_HSC, ios::binary);
    if(f){
        if(f.read((char*)this, sizeof(HS))){
            // show HS
            cout<<"\033c\n\n";
            cout<<"\t\t+----------------------------------------------+"<<endl;
            cout<<"\t\t|                                              |"<<endl;
            cout<<"\t\t|                  HIGHSCORES                  |"<<endl;
            cout<<"\t\t|                                              |"<<endl;
            cout<<"\t\t+------+----------------------+----------------+"<<endl;
            cout<<"\t\t| Rank |       Player         |      Score     |"<<endl;
            cout<<"\t\t+------+----------------------+----------------+"<<endl;
            for(int i = 0; i < count; ++i){
                cout<<"\t\t| "<<setw(3)<<right<<i+1<<". | ";
                p[i].print();
                cout<<" |"<<endl;
            }
            cout<<"\t\t+------+----------------------+----------------+"<<endl;
        }else{
            // show no file
            cout<<"\033c\n\n\n\n\n\n\n\n\n";
            cout<<"\t\t   +------------------------------------+"<<endl;
            cout<<"\t\t   |                                    |"<<endl;
            cout<<"\t\t   |            No Highscores           |"<<endl;
            cout<<"\t\t   |                                    |"<<endl;
            cout<<"\t\t   +------------------------------------+"<<endl;
        }
    }else{
        // show no file
        cout<<"\033c\n\n\n\n\n\n\n\n\n";
        cout<<"\t\t   +------------------------------------+"<<endl;
        cout<<"\t\t   |                                    |"<<endl;
        cout<<"\t\t   |            No Highscores           |"<<endl;
        cout<<"\t\t   |                                    |"<<endl;
        cout<<"\t\t   +------------------------------------+"<<endl;
    }
    f.close();
}

HS::HS(unsigned int score){
    ifstream fin;
    ofstream fout;
    char name[20];
    fin.open(F_HSC, ios::binary);
    if(fin){
        if(!fin.read((char*)this, sizeof(HS))){
            init();
        }
    }else{
        init();
    }
    fin.close();
    if(low < score){
        insert(score);
        if(count < MAX_HS)
            count++;
        low = p[MAX_HS - 1].getscore();
    }
    fout.open(F_HSC, ios::binary);
    if(fout){
        fout.write((char*)this, sizeof(HS));
    }
    fout.close();
}

void HS::insert(unsigned int score){
    string s;
    char name[20];
    cout<<"\033c\n\n\n\n\n\n\n";
    cout<<"\t\t   +------------------------------------+"<<endl;
    cout<<"\t\t   |                                    |"<<endl;
    cout<<"\t\t   |            New Highscore           |"<<endl;
    cout<<"\t\t   |                                    |"<<endl;
    cout<<"\t\t   +------------------------------------+"<<endl;
    cout<<"\n\n";
    cout<<"\t\t\tName : ";
    getline(cin, s);
    strcpy(name, s.c_str());
    for(int i = count; i > -1; i--){
		if((score > p[i - 1].getscore()) && (i != 0)){
			if(i < MAX_HS){
                p[i] = p[i-1];
            }
		}else{
			p[i] = Player(name, score);
			break;
		}
	}
}

void HS::init(){
    count = 0;
    low = 0;
    for(int i = 0; i < MAX_HS; ++i)
        p[i] = Player();
}