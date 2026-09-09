#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ESCORTS 100
#define MAX_PATH 100

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

    int alive;
} Escort;

typedef struct
{
    char type;
    double x;
    double y;

    double vMax;

    int alive;
} Battleship;


/* check whether an escort can hit the battleship */

int canAttack(Battleship b, Escort e)
{
    double dx;
    double dy;
    double distance;

    dx = b.x - e.x;
    dy = b.y - e.y;

    distance = sqrt(dx * dx + dy * dy);

    

    double angle = 45.0;
    double radians = angle * M_PI / 180.0;

    double range;

    range = (e.vMax * e.vMax * sin(2 * radians)) / 9.81;

    if (distance <= range)
    {
        return 1;
    }

    return 0;
}


/* create escort ships */

void createEscorts(Escort ships[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        ships[i].id = i + 1;

        ships[i].type[0] = 'E';
        ships[i].type[1] = 'A' + (rand() % 4);
        ships[i].type[2] = '\0';

        ships[i].x = ((double)rand() / RAND_MAX) * 100.0;
        ships[i].y = ((double)rand() / RAND_MAX) * 100.0;

        ships[i].vMin = 10.0;
        ships[i].vMax = 50.0;

        ships[i].angleMin = 10.0;
        ships[i].angleMax = 70.0;

        ships[i].alive = 1;



        if (ships[i].type[1] == 'A')
        {
            ships[i].impactPower = 0.08;
        }
        else if (ships[i].type[1] == 'B')
        {
            ships[i].impactPower = 0.10;
        }
        else if (ships[i].type[1] == 'C')
        {
            ships[i].impactPower = 0.12;
        }
        else
        {
            ships[i].impactPower = 0.15;
        }
    }
}


/* display escort ships */

void displayEscorts(Escort ships[], int n)
{
    int i;

    printf("\nESCORT SHIPS\n");
    printf("-------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("\nEscort %d\n", ships[i].id);
        printf("Type: %s\n", ships[i].type);

        printf("Position: (%.2f, %.2f)\n",
               ships[i].x,
               ships[i].y);

        printf("Impact Power: %.2f\n",
               ships[i].impactPower);
    }
}


/* Part 1-C Simulation A */

void simulationA(Battleship b, Escort ships[], int n)
{
    int i;

    double cumulativeImpact = 0.0;

    int destroyedShips = 0;

    int sinkingShip = -1;

    
    printf("PART 1-C - SIMULATION A\n");
  

    printf("\nBattleship position: (%.2f, %.2f)\n",
           b.x,
           b.y);


    

    for (i = 0; i < n; i++)
    {
        if (ships[i].alive == 0)
        {
            continue;
        }

        if (canAttack(b, ships[i]))
        {
            printf("\nBattleship attacked Escort %d\n",
                   ships[i].id);

            ships[i].alive = 0;

            destroyedShips++;
        }
    }


   

    for (i = 0; i < n; i++)
    {
        if (ships[i].alive == 0)
        {
            continue;
        }

        if (canAttack(b, ships[i]))
        {
            cumulativeImpact =
                cumulativeImpact + ships[i].impactPower;

            printf("\nEscort %d attacked Battleship\n",
                   ships[i].id);

            printf("Impact Power: %.2f\n",
                   ships[i].impactPower);

            printf("Cumulative Impact: %.2f\n",
                   cumulativeImpact);


            if (cumulativeImpact >= 1.0)
            {
                b.alive = 0;

                sinkingShip = ships[i].id;

                printf("\nBATTLESHIP IS SUNK!\n");
                printf("Escort %d destroyed the Battleship.\n",
                       sinkingShip);

                break;
            }
        }
    }



    printf("Escorts destroyed: %d\n",
           destroyedShips);

    printf("Cumulative impact on B: %.2f\n",
           cumulativeImpact);


    if (b.alive)
    {
        printf("Battleship was NOT sunk.\n");
    }
    else
    {
        printf("Battleship was sunk.\n");
    }
}


/* Part 1-C Simulation B */

void simulationB(Battleship b,
                 Escort ships[],
                 int n,
                 double pathX[],
                 double pathY[],
                 int k)
{
    int p;
    int i;

    double cumulativeImpact = 0.0;

    
    printf("PART 1-C - SIMULATION B\n");
   


    /*
       B moves through k path points.
    */

    for (p = 0; p < k; p++)
    {
        printf("\n-----------------------------\n");
        printf("Path Point %d\n", p + 1);
        printf("-----------------------------\n");

        b.x = pathX[p];
        b.y = pathY[p];

        printf("Battleship position: (%.2f, %.2f)\n",
               b.x,
               b.y);


        if (b.alive == 0)
        {
            break;
        }


        /*
           First B attacks an escort.
        */

        for (i = 0; i < n; i++)
        {
            if (ships[i].alive == 0)
            {
                continue;
            }

            if (canAttack(b, ships[i]))
            {
                ships[i].alive = 0;

                printf("B destroyed Escort %d\n",
                       ships[i].id);

                break;
            }
        }



        for (i = 0; i < n; i++)
        {
            if (ships[i].alive == 0)
            {
                continue;
            }

            if (canAttack(b, ships[i]))
            {
                cumulativeImpact =
                    cumulativeImpact +
                    ships[i].impactPower;

                printf("Escort %d attacked B\n",
                       ships[i].id);

                printf("Impact: %.2f\n",
                       ships[i].impactPower);

                printf("Cumulative impact: %.2f\n",
                       cumulativeImpact);


                if (cumulativeImpact >= 1.0)
                {
                    b.alive = 0;

                    printf("\nBATTLESHIP IS SUNK!\n");

                    printf("Battleship was destroyed at "
                           "path point %d.\n",
                           p + 1);

                    break;
                }
            }
        }


        if (b.alive == 0)
        {
            break;
        }
    }


 

    printf("PART 1-C FINAL RESULT\n");

    printf("Cumulative Impact: %.2f\n",
           cumulativeImpact);

    if (b.alive)
    {
        printf("Battleship was NOT sunk.\n");
    }
    else
    {
        printf("Battleship was sunk.\n");
    }
}



void saveResult(Battleship b,
                Escort ships[],
                int n,
                double cumulativeImpact)
{
    FILE *file;

    int i;

    file = fopen("part1C_results.txt", "w");

    if (file == NULL)
    {
        printf("Error opening result file.\n");
        return;
    }


    fprintf(file, "PART 1-C SIMULATION RESULTS\n");
    fprintf(file, "============================\n\n");


    fprintf(file,
            "Battleship Position: (%.2f, %.2f)\n",
            b.x,
            b.y);


    fprintf(file,
            "\nCumulative Impact on Battleship: %.2f\n",
            cumulativeImpact);


    if (b.alive)
    {
        fprintf(file,
                "Battleship was NOT sunk.\n");
    }
    else
    {
        fprintf(file,
                "Battleship was sunk.\n");
    }


    fprintf(file, "\nESCORT SHIPS\n");
    fprintf(file, "------------\n");


    for (i = 0; i < n; i++)
    {
        fprintf(file,
                "Escort %d | Type: %s | Impact: %.2f | ",
                ships[i].id,
                ships[i].type,
                ships[i].impactPower);

        if (ships[i].alive)
        {
            fprintf(file, "Alive\n");
        }
        else
        {
            fprintf(file, "Destroyed\n");
        }
    }


    fclose(file);

    printf("\nResults saved to part1C_results.txt\n");
}



int main()
{
    Battleship battleship;

    Escort ships[MAX_ESCORTS];

    double pathX[MAX_PATH];
    double pathY[MAX_PATH];

    int n;
    int k;

    int i;


    srand(time(NULL));

    printf("       PART 1-C SIMULATOR\n");
   


    printf("\nEnter number of escort ships: ");
    scanf("%d", &n);


    if (n < 1 || n > MAX_ESCORTS)
    {
        printf("Invalid number of escort ships.\n");
        return 1;
    }


    printf("\nEnter number of path points: ");
    scanf("%d", &k);


    if (k < 2 || k > MAX_PATH)
    {
        printf("Invalid number of path points.\n");
        return 1;
    }


    /*
       Battleship details
    */

    battleship.type = 'M';

    printf("\nEnter Battleship X position: ");
    scanf("%lf", &battleship.x);

    printf("Enter Battleship Y position: ");
    scanf("%lf", &battleship.y);

    printf("Enter Battleship maximum velocity: ");
    scanf("%lf", &battleship.vMax);

    battleship.alive = 1;



    createEscorts(ships, n);

    displayEscorts(ships, n);


    printf("\nPATH POINTS\n");

    for (i = 0; i < k; i++)
    {
        pathX[i] =
            ((double)rand() / RAND_MAX) * 100.0;

        pathY[i] =
            ((double)rand() / RAND_MAX) * 100.0;

        printf("Point %d: (%.2f, %.2f)\n",
               i + 1,
               pathX[i],
               pathY[i]);
    }


    simulationA(battleship, ships, n);

    createEscorts(ships, n);

    battleship.alive = 1;

    simulationB(battleship,
                ships,
                n,
                pathX,
                pathY,
                k);

    double finalImpact = 0.0;

    for (i = 0; i < n; i++)
    {

        if (ships[i].alive)
        {
            finalImpact =
                finalImpact + ships[i].impactPower;
        }
    }


    saveResult(battleship,
               ships,
               n,
               finalImpact);


    return 0;
}
