#ifndef HS_H
#define HS_H


class Player{
    char name[20]{};
    unsigned int score;

    public:
        Player();
        Player(char *, unsigned int);
        void print();
        unsigned int getscore();
};


class HS{
    Player p[MAX_HS];
    unsigned int low;
    int count;

    void insert(unsigned int);
    void init();

    public:
        HS();
        HS(unsigned int);
};

#endif