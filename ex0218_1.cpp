#include <stdio.h>
#define DEBUG

const int MAX_COLL_KOMNT = 30;
const int MAX_COLL_MEST = 15;

struct Otel
{
    int collKomnt, numKomnt[MAX_COLL_KOMNT], collMest[MAX_COLL_KOMNT];
    char dlyKogoKomnt[MAX_COLL_KOMNT];
};

struct Gryppa
{
    int numGr, coll;
};

void inzDannix(Otel &otel, FILE *fIn0)
{
    int i;

    fscanf(fIn0, "%d", &otel.collKomnt);

    for(i = 0; i < otel.collKomnt; i++)
    {
        fscanf(fIn0, "%d %d", &otel.numKomnt[i], &otel.collMest[i]);
        otel.dlyKogoKomnt[i] = 'n';
    }

    return;
}

int raspPoKomnatam(Gryppa gryppa, Otel &otel, char pol)
{
    int i, minCollMest, kom = -1;

    minCollMest = MAX_COLL_MEST +1;

    for(i = 0; i < otel.collKomnt; i++)
    {
        if(((otel.dlyKogoKomnt[i] == pol)||(otel.dlyKogoKomnt[i] == 'n'))&&(otel.collMest[i] >= gryppa.coll)&&(minCollMest > otel.collMest[i]))
        {
            minCollMest = otel.collMest[i];
            kom = i;
        }
    }

    if(kom == -1)
    {
        return -1;
    }
    else
    {
        otel.collMest[kom] -= gryppa.coll;
        otel.dlyKogoKomnt[kom] = pol;
        return kom;
    }
}

#ifdef DEBUG
void vizProgrammi(Otel otel, Otel constM)
{
    int i, j;

    printf("\n");

    for(i = 0; i < otel.collKomnt; i++)
    {
        printf("%2d.%c ",i + 1, otel.dlyKogoKomnt[i]);

        for(j = 0; j < constM.collMest[i] - otel.collMest[i]; j++)
        {
            printf("*");
        }
        for(j = constM.collMest[i] - otel.collMest[i]; j < constM.collMest[i]; j++)
        {
            printf(".");
        }

        printf("\n");
    }

    printf("----------------\n");

    return;
}
#endif

int main()
{
    Otel otel;
    Gryppa gryppa;

    char pol[2] = {'M', 'F'};
    int i, temp;

    FILE *fIn0,
         *fIn1,
         *fOut;

    fIn0 = fopen("ex0218_1.in0", "r");
    fIn1 = fopen("ex0218_1.in1", "r");
    fOut = fopen("ex0218_1.out", "w");

    inzDannix(otel, fIn0);

    fclose(fIn0);

#ifdef DEBUG
    Otel constM;

    constM = otel;

    printf("Nachalo programmi");

    vizProgrammi(otel, constM);
#endif

    while(fscanf(fIn1, "%d ", &gryppa.numGr) == 1)
    {
#ifdef DEBUG
    printf("Gryp %d  ", gryppa.numGr);
#endif
        for(i = 0; i < 2; i++)
        {
            fscanf(fIn1, "%d ", &gryppa.coll);

            if(gryppa.coll != 0)
            {
                temp = raspPoKomnatam(gryppa, otel, pol[i]);

                if(temp != -1)
                {
                    fprintf(fOut,"%d %c %d %d\n", gryppa.numGr, pol[i], temp + 1, gryppa.coll);
#ifdef DEBUG
    printf("%c-%d  ", pol[i], gryppa.coll);
#endif
                }
                else
                {
                    fprintf(fOut,"%d %c no places\n", gryppa.numGr, pol[i]);
                }
            }
        }
#ifdef DEBUG
    vizProgrammi(otel, constM);
#endif
    }

    fclose(fIn1);
    fclose(fOut);

    return 0;
}
