
#include <stdio.h>
#include <math.h>

int main()
{
    char bType, eType;
    double bImpact, eImpact;
    double bGamma, eGamma;
    int attacks;
    int i;

    FILE *file;

    
    printf("PART 2-C SIMULATION\n");
   

    
    printf("Enter Battleship type: ");
    scanf(" %c", &bType);

    printf("Enter initial Battleship impact power: ");
    scanf("%lf", &bImpact);

    printf("Enter Battleship gamma value: ");
    scanf("%lf", &bGamma);

    /* Escort ship details */
    printf("\nEnter Escort ship type: ");
    scanf(" %c", &eType);

    printf("Enter initial Escort impact power: ");
    scanf("%lf", &eImpact);

    printf("Enter Escort gamma value: ");
    scanf("%lf", &eGamma);

    printf("\nEnter number of gun firings: ");
    scanf("%d", &attacks);

    
    file = fopen("part2C_results.txt", "w");

    if (file==NULL)
    {
        printf("Error creating result file.\n");
        return 1;
    }

    
    fprintf(file, "          PART 2-C SIMULATION\n");
    

    fprintf(file, "Battleship Type : %c\n", bType);
    fprintf(file, "Initial Impact Power : %.2f\n", bImpact);
    fprintf(file, "Gamma : %.4f\n\n", bGamma);

    fprintf(file, "Escort Ship Type : %c\n", eType);
    fprintf(file, "Initial Impact Power : %.2f\n", eImpact);
    fprintf(file, "Gamma : %.4f\n\n", eGamma);

    fprintf(file, "Number of Gun Firings : %d\n\n", attacks);

    printf("\n------------------------------------\n");
    printf("Impact Power Changes\n");
    printf("------------------------------------\n");

    fprintf(file, "Impact Power Changes\n");
    fprintf(file, "------------------------------------\n");

    
    for (i=1;i<=attacks;i++)
    {
        double bCurrent;
        double eCurrent;

        bCurrent = bImpact * exp(-bGamma * i);
        eCurrent = eImpact * exp(-eGamma * i);

        printf("\nFiring %d\n", i);
        printf("Battleship Impact Power = %.2f\n", bCurrent);
        printf("Escort Impact Power     = %.2f\n", eCurrent);

        fprintf(file, "\nFiring %d\n", i);
        fprintf(file, "Battleship Impact Power = %.2f\n", bCurrent);
        fprintf(file, "Escort Impact Power     = %.2f\n", eCurrent);
    }

    fprintf(file, "\n------------------------------------\n");
    fprintf(file, "Simulation completed.\n");

    fclose(file);

    printf("\n------------------------------------\n");
    printf("Simulation completed.\n");
    printf("Results saved to part2C_results.txt\n");

    return 0;
}
