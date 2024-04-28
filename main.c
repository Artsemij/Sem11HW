#include "temp_function.h"

#include <string.h>
#include <stdio.h>

void print_help() {
    printf("Application arguments:\n"
        "-h: This help screen\n"
        "-f <filename.csv>: input csv file\n"
        "-m <month number (1 - 12)>: if this arg specified, statistics will be shown only for this month!\n");
}

int main(int argc, char** argv) 
{
    if (argc == 1)
    {
        print_help();

        return 0;
    }

    char* filename = NULL;
    int month = 0;

    for (int i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "-h") == 0) 
        {
            print_help();

            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) 
        {
            filename = argv[++i];
        }
        else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) 
        {
            if (sscanf_s(argv[++i], "%2i", &month) != 1)
            {
                if (month < 1 || month > 12)
                {
                    printf("Invalid month\n");

                    print_help();

                    return 0;
                }
            }
        }
        else 
        {
            printf("Invalid arg: %s\n", argv[i]);

            print_help();

            return 0;
        }
    }

    if (filename == NULL)
    {
        printf("Input file name is required!");

        print_help();

        return 0;
    }

    PMeasurement measurements = load_measurements(filename);

    print_statistics(measurements, month);

    free_measurements(measurements);

    return 0;
}