#include <stdbool.h>
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

typedef struct {
        bool debug;
        double latitude;
        double longitude;
        double distance;
        char *url;
} configuration;

int read_configuration(char *ini_path, configuration *config);

#endif
