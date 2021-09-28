#ifndef SRC_STATS_H_
#define SRC_STATS_H_

class Stats {
    public:
        Stats();
        Stats(int hp, int hpMax, int str, int def, int agi, int spd, int mov);
        int hp, hpMax, str, def, agi, spd, mov;
};

#endif /* SRC_STATS_H_ */
