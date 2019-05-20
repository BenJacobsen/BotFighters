class Bot{
friend class Grid;
public:
    Bot();
    int health();
    int points();
    coor coors();
private:
    int bot_health;
    int bot_points;
    coor bot_coors;
};

Bot::Bot (coor startCoors) {
    bot_health = 50;
    bot_points = 0;
    bot_coors = startCoors
}

int Bot::health() {
    return bot_health;
};

int Bot::points() {
    return bot_points;
};

coor Bot::coors() {
    return bot_coors;
}
