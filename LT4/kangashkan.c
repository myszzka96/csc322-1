#include <stdio.h>
#include <stdlib.h>

int main() {
   double side_of_land, length_of_road, num_roos, road_surface, land_area, roo_density, expected_kills;

   printf("Enter side of square in km  : ");
   scanf("%lf", &side_of_land);
   printf("Enter roads length in km    : ");
   scanf("%lf", &length_of_road);
   printf("Enter number of 'roos       : ");
   scanf("%lf", &num_roos);

   road_surface = length_of_road * .01;
   land_area = side_of_land * side_of_land;
   roo_density = num_roos / land_area;

   expected_kills = roo_density * road_surface * 1.47;
   printf("Expected number of kills is : %1.1lf \n", expected_kills);

   return 0;
}
