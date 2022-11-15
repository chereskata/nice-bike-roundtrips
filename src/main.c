#include <stdio.h>
#include <stdlib.h>

//#include "openbsd_source/"

/*
    - Ask the user where he is
    - Ask the user how long his travel should be
    - Invoke overpass api to gather the surrounding region
    - Use (yet to be defined) algorithm to compute route
    - Export the result as .gpx file
*/
int main(int argc, char **argv)
{
    printf("Hello, please enter your coordinates:\n");
    printf("example: lat: 51.25675 and lon: 6.113430\n");
    printf("lat: ");
    float latitude;
    scanf("%ff", &latitude);

    printf("lon: ");
    float longitude;
    scanf("%ff", &longitude);

    // Intput check
    if (latitude < -90.0 || latitude > 90.0)
    {
        printf("Please check your latitude\n");
        exit(1);
    }
    if (longitude < -180.0 || longitude > 180.0)
    {
        printf("Please check your longitude\n");
        exit(1);
    }
    printf("You entered lat: %ff and lon: %ff\n", latitude, longitude);


    printf("Please enter your desired roundtrip distance in kilometers\n");
    printf("example: 20.5km\n");
    printf("distance in km:");

    float distance;
    scanf("%ff", &distance);

    // Input check
    if (distance < 0.0 || distance > 50.0)
    {
        printf("Please check your distance\n");
        exit(1);
    }
}
