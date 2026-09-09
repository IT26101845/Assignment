#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SHIPS 100
#define MAX_PATH 50

#define GRAVITY 9.81

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

    double fireTime;

    int alive;

} EscortShip;


typedef struct
{
    char type;

    double x;
    double y;

    double vMax;

    double fireTime;

    int alive;

} Battleship;




double findRange(double v, double angle)
{
    double radians;

    radians = angle * M_PI / 180.0;

    return (v * v * sin(2 * radians)) / GRAVITY;
}




int canAttack(Battleship b, EscortShip e)
{
    double dx;
    double dy;
    double distance;

    double range1;
    double range2;

    dx = b.x - e.x;
    dy = b.y - e.y;

    distance = sqrt(dx * dx + dy * dy);

    range1 = findRange(e.vMin, e.angleMin);

    range2 = findRange(e.vMax, e.angleMax);

    if (distance <= range1 || distance <= range2)
    {
        return 1;
    }

    return 0;
}



int bCanAttack(Battleship b, EscortShip e)
{
    double dx;
    double dy;

    double distance;
    double range;

    dx = b.x - e.x;
    dy = b.y - e.y;

    distance = sqrt(dx * dx + dy * dy);

    range = findRange(b.vMax, 45.0);

    if (distance <= range)
    {
        return 1;
    }

    return 0;
}



void createEscorts(EscortShip ships[], int n, double bVmax)
{
    int i;
    int type;

    for (i = 0; i < n; i++)
    {
        ships[i].id = i + 1;

        type = rand() % 5;

        ships[i].type[0] = 'E';
        ships[i].type[1] = 'A' + type;
        ships[i].type[2] = '\0';


        ships[i].x =
            ((double)rand() / RAND_MAX) * 100.0;

        ships[i].y =
            ((double)rand() / RAND_MAX) * 100.0;



        if (type == 0)
        {
            

            ships[i].impactPower = 0.08;
            ships[i].angleMin = 20.0;
        }
        else if (type == 1)
        {
            

            ships[i].impactPower = 0.06;
            ships[i].angleMin = 30.0;
        }
        else if (type == 2)
        {
            

            ships[i].impactPower = 0.07;
            ships[i].angleMin = 25.0;
        }
        else if (type == 3)
        {
            

            ships[i].impactPower = 0.05;
            ships[i].angleMin = 50.0;
        }
        else
        {
            

            ships[i].impactPower = 0.04;
            ships[i].angleMin = 70.0;
        }


        ships[i].angleMax = 90.0;


        ships[i].vMin = 10.0;

        ships[i].vMax =
            bVmax * (1.0 + (double)rand() / RAND_MAX);


        if (type == 0)
        {
            ships[i].fireTime = 4.0;
        }
        else if (type == 1)
        {
            ships[i].fireTime = 5.0;
        }
        else if (type == 2)
        {
            ships[i].fireTime = 6.0;
        }
        else if (type == 3)
        {
            ships[i].fireTime = 7.0;
        }
        else
        {
            ships[i].fireTime = 8.0;
        }


        ships[i].alive = 1;
    }
}




void displayEscorts(EscortShip ships[], int n)
{
    int i;

    printf("\nESCORT SHIPS");
    printf("\n------------\n");

    for (i = 0; i < n; i++)
    {
        printf("\nEscort %d\n", ships[i].id);

        printf("Type: %s\n",
               ships[i].type);

        printf("Position: (%.2f, %.2f)\n",
               ships[i].x,
               ships[i].y);

        printf("Impact Power: %.2f\n",
               ships[i].impactPower);

        printf("Angle: %.2f - %.2f degrees\n",
               ships[i].angleMin,
               ships[i].angleMax);

        printf("Firing interval: %.2f seconds\n",
               ships[i].fireTime);
    }
}



int chooseTarget(Battleship b,
                 EscortShip ships[],
                 int n)
{
    int i;

    int target = -1;

    double smallestDistance = 999999.0;

    for (i = 0; i < n; i++)
    {
        double dx;
        double dy;
        double distance;

        if (ships[i].alive == 0)
        {
            continue;
        }

        if (bCanAttack(b, ships[i]) == 0)
        {
            continue;
        }

        dx = b.x - ships[i].x;
        dy = b.y - ships[i].y;

        distance =
            sqrt(dx * dx + dy * dy);


        if (distance < smallestDistance)
        {
            smallestDistance = distance;

            target = i;
        }
    }

    return target;
}



void runBattle(Battleship b,
               EscortShip ships[],
               int n,
               double pathX[],
               double pathY[],
               int k)
{
    int p;

    int round;

    int target;

    double currentTime = 0.0;

    double cumulativeImpact = 0.0;

    int maxRounds = 100;


    printf("\n====================================");
    printf("\nPART 2-B SIMULATION");
    printf("\n====================================\n");


    for (p = 0; p < k; p++)
    {
        

        b.x = pathX[p];
        b.y = pathY[p];


        printf("\n-----------------------------");
        printf("\nPath Point %d", p + 1);
        printf("\n-----------------------------\n");

        printf("Battleship position: (%.2f, %.2f)\n",
               b.x,
               b.y);


        if (b.alive == 0)
        {
            break;
        }


        currentTime =
            currentTime + b.fireTime;



        target =
            chooseTarget(b, ships, n);


        if (target != -1)
        {
            printf("B attacks Escort %d\n",
                   ships[target].id);

            printf("Attack order: Escort %d\n",
                   ships[target].id);


            ships[target].alive = 0;

            printf("Escort %d destroyed.\n",
                   ships[target].id);
        }
        else
        {
            printf("No escort in B attack range.\n");
        }


        for (round = 0;
             round < maxRounds;
             round++)
        {
            int i;

            int someoneFired = 0;


            currentTime =
                currentTime + 0.1;


            for (i = 0; i < n; i++)
            {
                double dx;
                double dy;

                double distance;

                double fireCheck;


                if (ships[i].alive == 0)
                {
                    continue;
                }


  

                if (canAttack(b, ships[i]) == 0)
                {
                    continue;
                }


                dx = b.x - ships[i].x;
                dy = b.y - ships[i].y;

                distance =
                    sqrt(dx * dx + dy * dy);


         

                fireCheck =
                    fmod(currentTime,
                         ships[i].fireTime);


                if (fireCheck < 0.11 ||
                    ships[i].fireTime - fireCheck < 0.11)
                {
                    printf("\nTime: %.2f seconds",
                           currentTime);

                    printf("\nEscort %d fires at B",
                           ships[i].id);

                    printf("\nDistance: %.2f",
                           distance);

                    printf("\nImpact: %.2f",
                           ships[i].impactPower);


     

                    cumulativeImpact =
                        cumulativeImpact +
                        ships[i].impactPower;


                    someoneFired = 1;


                    printf("\nCumulative impact on B: %.2f",
                           cumulativeImpact);



                    if (cumulativeImpact >= 1.0)
                    {
                        b.alive = 0;

                        printf("\n\nBATTLESHIP IS SUNK!\n");

                        printf("Escort %d destroyed B.\n",
                               ships[i].id);

                        break;
                    }
                }
            }


            if (b.alive == 0)
            {
                break;
            }


            if (someoneFired == 0)
            {
              
            }
        }


        if (b.alive == 0)
        {
            break;
        }
    }


    printf("\n\n====================================");
    printf("\nFINAL RESULT");
    printf("\n====================================\n");


    printf("Battle time: %.2f seconds\n",
           currentTime);

    printf("Cumulative impact on B: %.2f\n",
           cumulativeImpact);

    printf("Cumulative impact percentage: %.2f%%\n",
           cumulativeImpact * 100.0);


    if (b.alive == 1)
    {
        printf("Battleship survived.\n");
    }
    else
    {
        printf("Battleship was destroyed.\n");
    }
}



void saveResults(Battleship b,
                 EscortShip ships[],
                 int n,
                 double cumulativeImpact,
                 double totalTime)
{
    FILE *file;

    int i;


    file =
        fopen("part2B_results.txt", "w");


    if (file == NULL)
    {
        printf("Error opening result file.\n");

        return;
    }


    fprintf(file,
            "PART 2-B NAVAL BATTLE SIMULATION\n");

    fprintf(file,
            "=================================\n\n");


    fprintf(file,
            "Battleship type: %c\n",
            b.type);


    fprintf(file,
            "Battleship final position: "
            "(%.2f, %.2f)\n",
            b.x,
            b.y);


    fprintf(file,
            "Total simulation time: %.2f seconds\n",
            totalTime);


    fprintf(file,
            "Cumulative impact on B: %.4f\n",
            cumulativeImpact);


    fprintf(file,
            "Cumulative impact: %.2f%%\n",
            cumulativeImpact * 100.0);


    if (b.alive)
    {
        fprintf(file,
                "Battleship survived.\n");
    }
    else
    {
        fprintf(file,
                "Battleship was destroyed.\n");
    }


    fprintf(file,
            "\nESCORT SHIPS\n");

    fprintf(file,
            "------------\n");


    for (i = 0; i < n; i++)
    {
        fprintf(file,
                "Escort %d\n",
                ships[i].id);

        fprintf(file,
                "Type: %s\n",
                ships[i].type);

        fprintf(file,
                "Position: %.2f %.2f\n",
                ships[i].x,
                ships[i].y);

        fprintf(file,
                "Impact Power: %.2f\n",
                ships[i].impactPower);

        fprintf(file,
                "Firing Interval: %.2f seconds\n",
                ships[i].fireTime);

        if (ships[i].alive)
        {
            fprintf(file,
                    "Status: Alive\n\n");
        }
        else
        {
            fprintf(file,
                    "Status: Destroyed\n\n");
        }
    }


    fclose(file);


    printf("\nResults saved to part2B_results.txt\n");
}




int main()
{
    Battleship battleship;

    EscortShip ships[MAX_SHIPS];

    double pathX[MAX_PATH];
    double pathY[MAX_PATH];

    int n;
    int k;

    int i;

    double canvasSize;

    double cumulativeImpact = 0.0;

    double totalTime = 0.0;


    srand(time(NULL));


    printf("====================================\n");
    printf("       PART 2-B NAVAL SIMULATOR\n");
    printf("====================================\n");


   

    printf("\nEnter canvas size D: ");
    scanf("%lf", &canvasSize);


    

    printf("Enter number of escort ships: ");
    scanf("%d", &n);


    if (n < 1 || n > MAX_SHIPS)
    {
        printf("Invalid number of escort ships.\n");

        return 1;
    }


   

    printf("Enter number of path points: ");
    scanf("%d", &k);


    if (k < 1 || k > MAX_PATH)
    {
        printf("Invalid number of path points.\n");

        return 1;
    }


  

    printf("\nBattleship types:\n");

    printf("U - USS Iowa\n");
    printf("M - MS King George V\n");
    printf("R - Richelieu\n");
    printf("S - Sovetsky Soyuz-class\n");


    printf("\nEnter Battleship type: ");
    scanf(" %c", &battleship.type);


    printf("Enter Battleship X position: ");
    scanf("%lf", &battleship.x);


    printf("Enter Battleship Y position: ");
    scanf("%lf", &battleship.y);


    printf("Enter Battleship maximum shell velocity: ");
    scanf("%lf", &battleship.vMax);


    

    printf("Enter B firing interval in seconds: ");
    scanf("%lf", &battleship.fireTime);


    battleship.alive = 1;


    

    createEscorts(ships,
                  n,
                  battleship.vMax);


    displayEscorts(ships, n);


    

    printf("\nPATH POINTS\n");
    printf("-----------\n");


    for (i = 0; i < k; i++)
    {
        pathX[i] =
            ((double)rand() / RAND_MAX)
            * canvasSize;

        pathY[i] =
            ((double)rand() / RAND_MAX)
            * canvasSize;


        printf("Point %d: (%.2f, %.2f)\n",
               i + 1,
               pathX[i],
               pathY[i]);
    }


    

    runBattle(battleship,
              ships,
              n,
              pathX,
              pathY,
              k);


    

    for (i = 0; i < n; i++)
    {
        

        if (ships[i].alive)
        {
            cumulativeImpact =
                cumulativeImpact +
                ships[i].impactPower;
        }
    }


    totalTime = 0.0;


    saveResults(battleship,
                ships,
                n,
                cumulativeImpact,
                totalTime);


    return 0;
}
