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

Battleship battleship;

battleship.type='s';
battleship.vMax=10.0;



int destroyed[numberOfShips];

for(int i=0;i<numberOfShips;i++)
{
	destroyed[i]=0;
}

int battleshipSunk=0;
int sinkingShip=-1;

printf("\nBATTLE SIMULATION\n");
printf("------------------\n");


for(int p=0;p<k;p++)
{
	battleship.x = pathX[p];
	battleship.y = pathY[p];

	printf("\nBattleship at point %d\n",p+1);
	printf("Position: (%.2f,%.2f)\n",battleship.x,battleship.y);


	char filename[100];
	
	sprintf(filename,"results/part1B_simulation1_step%d.txt",p+1);
	
	FILE *stepFile = fopen(filename, "w");
	
	
	if (stepFile == NULL)
	
	{
        printf("Error creating result file.\n");
        return 1;
	}


    

    fprintf(stepFile, "PART 1-B SIMULATION 1\n");
    fprintf(stepFile, "=====================\n\n");

    fprintf(stepFile, "Path Point %d\n", p+1);
    fprintf(stepFile, "Battleship Position: (%.2f, %.2f)\n\n",battleship.x, battleship.y);

/*attack code*/
	for(int i=0;i<numberOfShips;i++)
		{
			if(destroyed[i]==1)
			{
				continue;
			}


			double dx = ships[i].x-battleship.x;
			double dy = ships[i].y-battleship.y;

			double distance = sqrt(dx*dx+dy*dy);

			printf("Distance to Escort %d = %.2f\n",ships[i].id,distance);


			double attackRange = 50.0;

			if(distance<=attackRange)
			{
				printf("Escort %d is in attack range.\n",ships[i].id);
				printf("Battleship hit Escort %d.\n",ships[i].id);
				battleshipSunk=1;
				sinkingShip=ships[i].id;

				break;
			}
			else
			
			{
				printf("Escort %d is out of attack range.\n",ships[i].id);
			}
		}
	if (battleshipSunk == 1)
	{
		printf("\nBATTLESHIP IS SUNK!\n");
		printf("Escort ship %d sank the battleship.\n",sinkingShip);
		break;

	
	fclose(stepFile);
	}



FILE *file;

file = fopen("part1B_results.txt","w");

if(file==NULL)
{
	printf("Error opening results file.\n");
	return 1;
}

fprintf(file,"PART 1-B SIMULATION 1\n");
fprintf(file,"----------------------\n\n");

for (int p=0;p<k;p++)
{
	fprintf(file,"Path Point %d:(%.2f,%.2f)\n",p+1,pathX[p],pathY[p]);
}
fprintf(file,"\n");

if(battleshipSunk==1)
{
	fprintf(file,"Battleship was sunk.\n");
	fprintf(file,"Sinking Escort Ship: %d\n",sinkingShip);
}
else
{
	fprintf(file,"Battleship was not sunk.\n");
}

fclose(file);

printf("\nSimulation results saved to part1B_results.txt\n");

}





printf("\nSIMULATION 2\n");
printf("============\n");

double thetaMin;

printf("\nEnter thetaMin (0 < thetaMin < 30): ");
scanf("%lf", &thetaMin);

if (thetaMin <= 0 || thetaMin >= 30)
{
    printf("Invalid thetaMin.\n");
    return 1;
}

printf("\nVertical angle range: %.2f - 90.00 degrees\n", thetaMin);




for (int i = 0; i < numberOfShips; i++)
{
    destroyed[i] = 0;
}

battleshipSunk = 0;
sinkingShip = -1;




FILE *file2;

file2 = fopen("part1B_simulation2_results.txt", "w");

if (file2 == NULL)
{
    printf("Error opening simulation 2 results file.\n");
    return 1;
}

fprintf(file2, "PART 1-B SIMULATION 2\n");
fprintf(file2, "=====================\n\n");

fprintf(file2, "Theta minimum: %.2f degrees\n",thetaMin);
fprintf(file2, "Vertical angle range: %.2f - 90.00 degrees\n\n",thetaMin);


for (int p = 0; p < k; p++)
{
    battleship.x = pathX[p];
    battleship.y = pathY[p];

    printf("\nBattleship at point %d\n", p+1);
    printf("Position: (%.2f, %.2f)\n",
           battleship.x, battleship.y);

    fprintf(file2, "Battleship at point %d\n", p+1);
    fprintf(file2, "Position: (%.2f, %.2f)\n",battleship.x, battleship.y);


    for (int i=0; i<numberOfShips;i++)
    {
        if (destroyed[i] == 1)
        {
            continue;
        }

        double dx=ships[i].x - battleship.x;
        double dy=ships[i].y - battleship.y;

        double distance = sqrt(dx * dx + dy * dy);

        printf("Distance to Escort %d = %.2f\n",ships[i].id, distance);

        fprintf(file2, "Distance to Escort %d = %.2f\n",ships[i].id, distance);


        double attackRange = 50.0;


        if (distance<=attackRange)
        {
            printf("Escort %d is in attack range.\n",ships[i].id);

            fprintf(file2, "Escort %d is in attack range.\n",ships[i].id);

            double verticalAngle;

            verticalAngle =
                atan(battleship.vMax / distance) * 180.0 / M_PI;


            printf("Vertical angle to Escort %d = %.2f degrees\n",ships[i].id, verticalAngle);

            fprintf(file2,"Vertical angle to Escort %d = %.2f degrees\n",ships[i].id, verticalAngle);

            if (verticalAngle>= thetaMin &&verticalAngle <= 90.0)
            {
                printf("Escort %d can be attacked.\n",ships[i].id);

                fprintf(file2,"Escort %d can be attacked.\n",ships[i].id);


                battleshipSunk = 1;
                sinkingShip = ships[i].id;

                printf("Escort %d attacks the Battleship.\n",ships[i].id);

                fprintf(file2,"Escort %d attacks the Battleship.\n",ships[i].id);

                break;
            }
            else
            {
                printf("Escort %d cannot be attacked due to vertical angle.\n",ships[i].id);

                fprintf(file2,"Escort %d cannot be attacked due to vertical angle.\n",ships[i].id);
            }
        }
        else
        {
            printf("Escort %d is out of attack range.\n",ships[i].id);

            fprintf(file2,"Escort %d is out of attack range.\n",ships[i].id);
        }
    }


    

    if (battleshipSunk==1)
    {
        printf("\nBATTLESHIP IS SUNK!\n");
        printf("Escort ship %d sank the Battleship.\n",sinkingShip);

        fprintf(file2, "\nBATTLESHIP IS SUNK!\n");
        fprintf(file2,"Escort ship %d sank the Battleship.\n",sinkingShip);

        break;
    }
    else
    {
        printf("\nBattleship is not sunk.\n");

        fprintf(file2,"\nBattleship is not sunk.\n");
    }

    printf("\n-------------------------\n");

    fprintf(file2,"\n-------------------------\n\n");
}




fclose(file2);

printf("\nSimulation 2 results saved to ");
printf("part1B_simulation2_results.txt\n");





return 0;
}
