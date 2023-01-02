#include <stdio.h>
#include <stdlib.h>
#include "configuration.h"


/*
 * Ask the user where he is
 * Ask the user how long his travel should be
 * Invoke overpass api to gather the surrounding region
 * Use (yet to be defined) algorithm to compute route
 * Export the result as .gpx file
 */
int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr, "%s", "Please supply path to settings.ini");
                exit(1);
        }

        configuration config;
        read_configuration(argv[1], &config);

        printf("Config loaded with: debug=%s lat=%e lon=%e dist=%e url=%s",
              config.debug?"yes":"no", config.latitude, config.longitude, config.distance,
              config.url);


        if (config.url) {
                free((void *) config.url);
        }
}
