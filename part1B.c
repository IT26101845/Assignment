#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct
{
    int id;
    char type[3];

    double x;
    double y;

    double vMin;
    double vMax;

    double angleMin;
    double angleMax;

    double impactPower;


} EscortShip;

typedef struct
{
    char type;

    double x;
    double y;

    double vMax;

} Battleship;

int main()
{
    printf("Part 1-B\n");
    printf("========\n");

    int k;

printf("Enter number of path points: ");
scanf("%d", &k);

if (k < 2)
{
    printf("Number of points should be at least 2.\n");
    return 1;
}


double pathX[k];
double pathY[k];

printf("\nBattleship path points:\n");

for (int i=0;i<k;i++)
{
    printf("Point %d:",i+1);
    scanf("%lf %lf",&pathX[i],&pathY[i]);
}

printf("\nPath points entered:\n");

    for (int i=0;i<k;i++)
    {
        printf("Point %d= (%.2f,%.2f)\n",i+1,pathX[i],pathY[i]);
    }

    int numberOfShips;

    printf("\nEnter number of escort ships: ");
    scanf("%d", &numberOfShips);

    EscortShip ships[numberOfShips];

    srand(time(NULL));

    for (int i=0;i<numberOfShips;i++)
    {
        ships[i].id=i+1;

        /* generate a simple ship type */
        ships[i].type[0] = 'E';
        ships[i].type[1] = 'A' + (rand() % 5);
        ships[i].type[2] = '\0';

        /* generate a random position */
        ships[i].x = (double)rand() / RAND_MAX * 100.0;
        ships[i].y = (double)rand() / RAND_MAX * 100.0;

        /* simple values for the ship */
        ships[i].vMin = 1.0;
        ships[i].vMax = 10.0;

        ships[i].angleMin = 10.0;
        ships[i].angleMax = 70.0;

        ships[i].impactPower = 0.04+((double)rand() / RAND_MAX) * 0.06;
    }


    printf("\nESCORT SHIPS\n");

    for (int i=0;i<numberOfShips;i++)
    {
        printf("\nEscort %d\n", ships[i].id);
        printf("Type: %s\n", ships[i].type);
        printf("Position: (%.2f, %.2f)\n",ships[i].x, ships[i].y);
        printf("Impact Power: %.2f\n",ships[i].impactPower);
        printf("Angle Range: %.2f degrees\n",ships[i].angleMax);
    }



    return 0;
}
