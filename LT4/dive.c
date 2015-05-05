#include <stdio.h>
#include <stdlib.h>

void OutputCalculations(double depth, double percentage_oxygen) {
   float ambient_pressure, partial_oxygen_pressure;
   char oxygen_pressure_group;

   ambient_pressure = depth / 33 + 1;
   printf("\nAmbient pressure                : %1.1lf\n", ambient_pressure);

   partial_oxygen_pressure = (percentage_oxygen / 100) * ambient_pressure;
   printf("O2 pressure                     : %4.2lf\n", partial_oxygen_pressure);

   oxygen_pressure_group = (partial_oxygen_pressure*10) + 'A';
   printf("O2 group                        : %c\n", oxygen_pressure_group);

   printf("\n\nExceeds maximal O2 pressure     : %s\n", partial_oxygen_pressure > 1.4 ? "true" : "false");
   printf("Exceeds contingency O2 pressure : %s\n",partial_oxygen_pressure > 1.6 ? "true" : "false");
}

int main(void) {
   float depth, percentage_oxygen;

   printf("Enter depth and percentage O2   : ");
   scanf("%f %f", &depth, &percentage_oxygen);

   OutputCalculations(depth, percentage_oxygen);

   return(EXIT_SUCCESS);
}
