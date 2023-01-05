#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "configuration.h"
#include "ini.h"

/*
 * Matches key=value pairs of the ini file
 */
static int assign_values_to_struct(void *data,
                                   const char *section,
                                   const char *name,
                                   const char *value)
{
        configuration *config = (configuration *) data;

        #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
        if (MATCH("development", "debug")) {
                if (strcmp("yes", value) == 0) {
                        config->debug = true;
                } else if (strcmp("no", value) == 0) {
                        config->debug = false;
                } else {
                        fprintf(stderr, "%s", "Error reading config file - ");
                        fprintf(stderr, "%s", "debug key contains useless value");
                        return 0; // Unsuccessful parsing of .ini file
                }
        } else if (MATCH("location", "latitude")) {
                double lat_candidate = strtod(value, NULL);
                if (lat_candidate < -90.0 || lat_candidate > 90.0) {
                        fprintf(stderr, "%s", "Error reading config file - ");
                        fprintf(stderr, "%s", "latitude out of range");
                        return 0; // latitude out of range
                }
                config->latitude = lat_candidate;
        } else if (MATCH("location", "longitude")) {
                double lon_candidate = strtod(value, NULL);
                if (lon_candidate < -180.0 || lon_candidate > 180.0) {
                        fprintf(stderr, "%s", "Error reading config file - ");
                        fprintf(stderr, "%s", "longitude out of range");
                        return 0; // longitude out of range
                }
                config->longitude = lon_candidate;
        } else if (MATCH("route", "distance")) {
                // Distance should be max 100km
                double dist_candidate = strtod(value, NULL);
                if (dist_candidate < 0 || dist_candidate > 100) {
                        fprintf(stderr, "%s", "Error reading config file - ");
                        fprintf(stderr, "%s", "distance out of range");
                        return 0; // longitude out of range
                }
                config->distance = dist_candidate;
        } else if (MATCH("server", "url")) {
                char *url_candidate = strdup(value);
                if (strstr(value, "https") == NULL) {
                        fprintf(stderr, "%s", "Error reading config file - ");
                        fprintf(stderr, "%s", "url seems malformed, no https found");
                        return 0; // longitude out of range
                }
                config->url = url_candidate;
        } else {
                return 0; // Unsuccessful parsing of .ini file
        }
        #undef MATCH
        return 1; // All ok, key=value pair matched some setting
}

/*
 * High level procedure to expose the contents of the settings.ini config
 * file to the program loop. Call with full path of the ini file. If there was
 * an error in parsing the file, the returned struct will have NAN set for both
 * coordinate components
 */
int read_configuration(char *ini_path, configuration *config)
{
        // Add default values
        config->debug = true;
        config->latitude = 51.492546;
        config->longitude = 7.414952;
        // config.url missing, because length is variable

        if (ini_parse(ini_path, assign_values_to_struct, config) < 0) {
                fprintf(stderr, "%s", "Error reading config file - ");
                fprintf(stderr, "%s", "ini_parse did return an error code");
                config->latitude = NAN;
                config->longitude = NAN;
                return 0; // Unsuccessful parsing of .ini file
        }

        return 1; // All ok, configuration read completely
}
