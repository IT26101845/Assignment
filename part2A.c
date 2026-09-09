#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SHIPS 100
#define ATTACK_RANGE 50.0

/* Escort ship details */
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


/* Battleship details */
typedef struct
{
    char type;

    double x;
    double y;

    double vMax;

} Battleship;


/* Get the name of battleship */
void printBattleshipType(char type)
{
    if (type == 'U')
        printf("U - USS Iowa\n");
    else if (type == 'M')
        printf("M - MS King George V\n");
    else if (type == 'R')
        printf("R - Richelieu\n");
    else if (type == 'S')
        printf("S - Sovetsky Soyuz-class\n");
}


void setEscortDetails(EscortShip *ship, char type)
{
    ship->type[0]= 'E';
    ship->type[1]= type;
    ship->type[2]= '\0';

    if (type=='A')
    {
        ship->impactPower = 0.08;
        ship->angleMin = 20.0;
        ship->angleMax = 90.0;
        ship->vMin = 1.0;
        ship->vMax = 10.0;
    }
    else if (type=='B')
    {
        ship->impactPower = 0.06;
        ship->angleMin = 30.0;
        ship->angleMax = 90.0;
        ship->vMin = 1.0;
        ship->vMax = 10.0;
    }
    else if (type=='C')
    {
        ship->impactPower = 0.07;
        ship->angleMin = 25.0;
        ship->angleMax = 90.0;
        ship->vMin = 1.0;
        ship->vMax = 10.0;
    }
    else if (type=='D')
    {
        ship->impactPower = 0.05;
        ship->angleMin = 50.0;
        ship->angleMax = 90.0;
        ship->vMin = 1.0;
        ship->vMax = 10.0;
    }
    else
    {
        ship->impactPower=0.04;
        ship->angleMin=70.0;
        ship->angleMax=90.0;
        ship->vMin = 1.0;
        ship->vMax = 10.0;
    }
}



double calculateDistance(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt(dx*dx+dy*dy);
}



int findShipsInRange(Battleship battleship,EscortShip ships[],int numberOfShips,int inRange[])


{
    int count=0;

    for (int i =0;i<numberOfShips;i++)
    {
        double distance;

        distance = calculateDistance(battleship.x,battleship.y,ships[i].x,ships[i].y);

        if (distance<=ATTACK_RANGE)
        {
            inRange[count] = i;
            count++;
        }
    }

    return count;
}


void makeAttackOrder(Battleship battleship,EscortShip ships[],int numberOfShips,int attackOrder[],int *orderCount)
{
    int inRange[MAX_SHIPS];

    *orderCount = findShipsInRange(
        battleship,
        ships,
        numberOfShips,
        inRange
    );

    for (int i=0;i<*orderCount;i++)
    {
        attackOrder[i] =inRange[i];
    }


  
    for (int i=0;i<*orderCount-1;i++)
    {
        for (int j =i+1;j<*orderCount;j++)
        {
            double distance1;
            double distance2;

            distance1 = calculateDistance(
                battleship.x,
                battleship.y,
                ships[attackOrder[i]].x,
                ships[attackOrder[i]].y
            );

            distance2 = calculateDistance(
                battleship.x,
                battleship.y,
                ships[attackOrder[j]].x,
                ships[attackOrder[j]].y
            );

            if (distance2<distance1)
            {
                int temp;

                temp =attackOrder[i];
                attackOrder[i] =attackOrder[j];
                attackOrder[j] =temp;
            }
        }
    }
}



void printAttackOrder(Battleship battleship,
                      EscortShip ships[],
                      int attackOrder[],
                      int orderCount)
{
    printf("\nCUSTOM ATTACK ORDER\n");
    printf("-------------------\n");

    if (orderCount==0)
    {
        printf("No escort ships are in attack range.\n");
        return;
    }

    for (int i=0;i<orderCount;i++)
    {
        int index;
        double distance;

        index = attackOrder[i];

        distance = calculateDistance(battleship.x,battleship.y,ships[index].x,ships[index].y);

        printf("%d. Escort %d - Distance %.2f\n", i + 1,ships[index].id,distance);
    }
}


void saveAttackOrder(FILE *file,Battleship battleship,EscortShip ships[],int attackOrder[],int orderCount,int step)
{
    fprintf(file, "\nSimulation Step %d\n", step);
    fprintf(file, "Battleship Position: (%.2f, %.2f)\n",battleship.x,battleship.y);

    fprintf(file, "Attack Order:\n");

    if (orderCount == 0)
    {
        fprintf(file, "No escort ships in attack range.\n");
    }

    for (int i = 0; i < orderCount; i++)
    {
        int index;
        double distance;

        index = attackOrder[i];

        distance = calculateDistance(battleship.x,battleship.y,ships[index].x,ships[index].y);

        fprintf(file,"%d. Escort %d - Distance %.2f\n",i + 1,ships[index].id,distance);
    }
}


void simulation1A(Battleship battleship,EscortShip ships[],int numberOfShips,double firingTime,FILE *file)
{
    int attackOrder[MAX_SHIPS];
    int orderCount;

    printf("\n");
    printf("====================================\n");
    printf("SIMULATION 1 - PART 1-A STYLE\n");
    printf("====================================\n");

    makeAttackOrder(battleship,ships,numberOfShips,attackOrder,&orderCount);

    printAttackOrder(battleship,ships,attackOrder,orderCount);

    fprintf(file, "\n====================================\n");
    fprintf(file, "SIMULATION 1 - PART 1-A STYLE\n");
    fprintf(file, "====================================\n");

    fprintf(file,
            "Time between B firings = %.2f seconds\n",
            firingTime);

    saveAttackOrder(
        file,
        battleship,
        ships,
        attackOrder,
        orderCount,
        1
    );

    /*
       B destroys one E ship per firing.
       Time increases by T_B after each firing.
    */

    double currentTime = 0.0;

    for (int i = 0; i < orderCount; i++)
    {
        int shipIndex;

        shipIndex = attackOrder[i];

        currentTime = currentTime + firingTime;

        printf("Time %.2f : B attacks Escort %d\n",
               currentTime,
               ships[shipIndex].id);

        fprintf(file,
                "Time %.2f : B attacks Escort %d\n",
                currentTime,
                ships[shipIndex].id);
    }

    printf("Part 1-A style simulation completed.\n");
}


/* Part 1-B Simulation 1 */
void simulation1B(Battleship battleship,
                  EscortShip ships[],
                  int numberOfShips,
                  double firingTime,
                  int k,
                  FILE *file)
{
    double pathX[MAX_SHIPS];
    double pathY[MAX_SHIPS];

    int destroyed[MAX_SHIPS];

    printf("\n");
    printf("====================================\n");
    printf("SIMULATION 2 - PART 1-B STYLE\n");
    printf("====================================\n");

    fprintf(file, "\n====================================\n");
    fprintf(file, "SIMULATION 2 - PART 1-B STYLE\n");
    fprintf(file, "====================================\n");

    /* Generate path points */
    for (int i = 0; i < k; i++)
    {
        pathX[i] = (double)(rand() % 101);
        pathY[i] = (double)(rand() % 101);
    }

    for (int i = 0; i < numberOfShips; i++)
    {
        destroyed[i] = 0;
    }


    double currentTime = 0.0;

    for (int p = 0; p < k; p++)
    {
        int attackOrder[MAX_SHIPS];
        int orderCount;

        battleship.x = pathX[p];
        battleship.y = pathY[p];

        printf("\nBattleship at point %d\n", p + 1);
        printf("Position: (%.2f, %.2f)\n",
               battleship.x,
               battleship.y);

        fprintf(file, "\nPath Point %d\n", p + 1);
        fprintf(file, "Position: (%.2f, %.2f)\n",
                battleship.x,
                battleship.y);

        /*
           Create a temporary list using only
           ships which are not destroyed.
        */

        int activeShips[MAX_SHIPS];
        int activeCount = 0;

        for (int i = 0; i < numberOfShips; i++)
        {
            if (destroyed[i] == 0)
            {
                activeShips[activeCount] = i;
                activeCount++;
            }
        }

        /* Check active ships */
        for (int i = 0; i < activeCount; i++)
        {
            int index;
            double distance;

            index = activeShips[i];

            distance = calculateDistance(
                battleship.x,
                battleship.y,
                ships[index].x,
                ships[index].y
            );

            if (distance <= ATTACK_RANGE)
            {
                printf("Escort %d is in attack range.\n",
                       ships[index].id);

                fprintf(file,
                        "Escort %d is in attack range.\n",
                        ships[index].id);
            }
            else
            {
                printf("Escort %d is out of attack range.\n",
                       ships[index].id);

                fprintf(file,
                        "Escort %d is out of attack range.\n",
                        ships[index].id);
            }
        }


        /*
           Find attack order.
           The normal function uses all ships,
           so here we manually make an order using
           the active ships.
        */

        orderCount = 0;

        for (int i = 0; i < activeCount; i++)
        {
            int index;
            double distance;

            index = activeShips[i];

            distance = calculateDistance(
                battleship.x,
                battleship.y,
                ships[index].x,
                ships[index].y
            );

            if (distance <= ATTACK_RANGE)
            {
                attackOrder[orderCount] = index;
                orderCount++;
            }
        }


        /* Sort nearest first */
        for (int i = 0; i < orderCount - 1; i++)
        {
            for (int j = i + 1; j < orderCount; j++)
            {
                double d1;
                double d2;

                d1 = calculateDistance(
                    battleship.x,
                    battleship.y,
                    ships[attackOrder[i]].x,
                    ships[attackOrder[i]].y
                );

                d2 = calculateDistance(
                    battleship.x,
                    battleship.y,
                    ships[attackOrder[j]].x,
                    ships[attackOrder[j]].y
                );

                if (d2 < d1)
                {
                    int temp;

                    temp = attackOrder[i];
                    attackOrder[i] = attackOrder[j];
                    attackOrder[j] = temp;
                }
            }
        }


        printf("Attack order:\n");
        fprintf(file, "Attack order:\n");

        for (int i = 0; i < orderCount; i++)
        {
            int index;

            index = attackOrder[i];

            printf("%d. Escort %d\n",
                   i + 1,
                   ships[index].id);

            fprintf(file,
                    "%d. Escort %d\n",
                    i + 1,
                    ships[index].id);
        }


        /*
           B fires at each ship according to
           the selected attack order.
        */

        for (int i = 0; i < orderCount; i++)
        {
            int index;

            index = attackOrder[i];

            currentTime = currentTime + firingTime;

            destroyed[index] = 1;

            printf("Time %.2f : Escort %d destroyed.\n",
                   currentTime,
                   ships[index].id);

            fprintf(file,
                    "Time %.2f : Escort %d destroyed.\n",
                    currentTime,
                    ships[index].id);
        }
    }
}


/* Part 1-C style simulation */
void simulation1C(Battleship battleship,
                  EscortShip ships[],
                  int numberOfShips,
                  double firingTime,
                  FILE *file)
{
    int attackOrder[MAX_SHIPS];
    int orderCount;

    double battleDamage = 0.0;
    double currentTime = 0.0;

    printf("\n");
    printf("====================================\n");
    printf("SIMULATION 3 - PART 1-C STYLE\n");
    printf("====================================\n");

    fprintf(file, "\n====================================\n");
    fprintf(file, "SIMULATION 3 - PART 1-C STYLE\n");
    fprintf(file, "====================================\n");

    makeAttackOrder(
        battleship,
        ships,
        numberOfShips,
        attackOrder,
        &orderCount
    );

    printAttackOrder(
        battleship,
        ships,
        attackOrder,
        orderCount
    );

    fprintf(file,
            "Time between B firings = %.2f seconds\n",
            firingTime);

    fprintf(file, "Attack order:\n");

    for (int i = 0; i < orderCount; i++)
    {
        int index;

        index = attackOrder[i];

        fprintf(file,
                "%d. Escort %d\n",
                i + 1,
                ships[index].id);
    }


    /*
       Each E can attack B once.
       Impact power is cumulative.
    */

    for (int i = 0; i < orderCount; i++)
    {
        int index;

        index = attackOrder[i];

        currentTime = currentTime + firingTime;

        battleDamage =
            battleDamage + ships[index].impactPower;

        printf("Time %.2f : B destroys Escort %d\n",
               currentTime,
               ships[index].id);

        printf("Cumulative impact on B = %.2f%%\n",
               battleDamage * 100.0);

        fprintf(file,
                "Time %.2f : B destroys Escort %d\n",
                currentTime,
                ships[index].id);

        fprintf(file,
                "Cumulative impact on B = %.2f%%\n",
                battleDamage * 100.0);

        if (battleDamage >= 1.0)
        {
            printf("Battleship is sunk.\n");

            fprintf(file,
                    "Battleship is sunk.\n");

            break;
        }
    }

    if (battleDamage < 1.0)
    {
        printf("Battleship was not sunk.\n");

        fprintf(file,
                "Battleship was not sunk.\n");
    }
}


/* Main function */
int main()
{
    Battleship battleship;
    EscortShip ships[MAX_SHIPS];

    int numberOfShips;
    int pathPoints;

    double firingTime;

    FILE *file;

    srand(time(NULL));

    printf("============================================\n");
    printf("       PART 2-A NAVAL BATTLE SIMULATOR\n");
    printf("============================================\n");


    /* Get B firing time */
    printf("\nEnter time between B ship firings: ");
    scanf("%lf", &firingTime);

    if (firingTime <= 0)
    {
        printf("Invalid firing time.\n");
        return 1;
    }


    /* Get number of escort ships */
    printf("Enter number of escort ships: ");
    scanf("%d", &numberOfShips);

    if (numberOfShips <= 0 || numberOfShips > MAX_SHIPS)
    {
        printf("Invalid number of ships.\n");
        return 1;
    }


    /* Get B type */
    printf("\nBattleship Types:\n");
    printBattleshipType('U');
    printBattleshipType('M');
    printBattleshipType('R');
    printBattleshipType('S');

    printf("\nEnter Battleship type: ");
    scanf(" %c", &battleship.type);

    if (battleship.type != 'U' &&
        battleship.type != 'M' &&
        battleship.type != 'R' &&
        battleship.type != 'S')
    {
        printf("Invalid battleship type.\n");
        return 1;
    }


    /* Get B position */
    printf("Enter Battleship X position: ");
    scanf("%lf", &battleship.x);

    printf("Enter Battleship Y position: ");
    scanf("%lf", &battleship.y);


    /* Get B maximum velocity */
    printf("Enter Battleship maximum shell velocity: ");
    scanf("%lf", &battleship.vMax);


    printf("\nBattleship position: (%.2f, %.2f)\n",
           battleship.x,
           battleship.y);


    /* Generate escort ships */
    printf("\nGenerating Escort Ships...\n");

    for (int i = 0; i < numberOfShips; i++)
    {
        char randomType;

        ships[i].id = i + 1;

        randomType = 'A' + (rand() % 5);

        setEscortDetails(
            &ships[i],
            randomType
        );

        ships[i].x = (double)(rand() % 101);
        ships[i].y = (double)(rand() % 101);

        printf("Escort %d: Type E%c  Position (%.2f, %.2f)\n",
               ships[i].id,
               randomType,
               ships[i].x,
               ships[i].y);
    }


    
    printf("\nEnter number of path points for Part 1-B: ");
    scanf("%d", &pathPoints);

    if (pathPoints <= 0 || pathPoints > MAX_SHIPS)
    {
        printf("Invalid number of path points.\n");
        return 1;
    }

    file = fopen("part2A_results.txt", "w");

    if (file == NULL)
    {
        printf("Error opening result file.\n");
        return 1;
    }



    fprintf(file,"PART 2-A NAVAL BATTLE SIMULATOR\n\n");
    fprintf(file,"Battleship Type: %c\n",battleship.type);

    fprintf(file,"Battleship Position: (%.2f, %.2f)\n",battleship.x,battleship.y);

    fprintf(file,"Battleship Maximum Velocity: %.2f\n",battleship.vMax);

    fprintf(file,"Time Between B Firings: %.2f seconds\n",firingTime);

    fprintf(file,"Attack Range: %.2f\n",ATTACK_RANGE);


    fprintf(file, "\nESCORT SHIPS\n");
    fprintf(file, "============\n");

    for (int i = 0; i < numberOfShips; i++)
    {
        fprintf(file,
                "Escort %d\n",
                ships[i].id);

        fprintf(file,
                "Type: %s\n",
                ships[i].type);

        fprintf(file,
                "Position: (%.2f, %.2f)\n",
                ships[i].x,
                ships[i].y);

        fprintf(file,
                "Impact Power: %.2f\n",
                ships[i].impactPower);

        fprintf(file,
                "Angle Range: %.2f - %.2f degrees\n\n",
                ships[i].angleMin,
                ships[i].angleMax);
    }


    simulation1A(
        battleship,
        ships,
        numberOfShips,
        firingTime,
        file
    );


    simulation1B(
        battleship,
        ships,
        numberOfShips,
        firingTime,
        pathPoints,
        file
    );


    simulation1C(
        battleship,
        ships,
        numberOfShips,
        firingTime,
        file
    );


  
    fclose(file);

    printf("\n============================================\n");
    printf("Part 2-A simulation completed.\n");
    printf("Results saved to part2A_results.txt\n");
    printf("============================================\n");

    return 0;
}
