#ifndef PERCOLATIONSTAT_H
#define PERCOLATIONSTAT_H


class percolationStat
{
    public:
        percolationStat(int t,int a);
        ~percolationStat();
        double stdDev();
        void init(int k);
        double mean();
        void display();


    protected:

    private:
        double dev;
        double avg;
        int trials;
        int n;
        int *arr;//it is for storing values after trials
};

#endif // STAT_H
