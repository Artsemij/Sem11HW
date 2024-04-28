#include "temp_function.h"

#include <stdio.h>
#include <stdlib.h>

PMeasurement load_measurements(char* filename)
{
    FILE* file;

    if (fopen_s(&file, filename, "r") != 0)
    {
        printf("Error while opening input file\n");

        return NULL;
    }

    int row = 1;

    PMeasurement measurement_first = NULL;
    PMeasurement measurement_prev = NULL;

    while (1)
    {
        PMeasurement measurement_current = (PMeasurement)calloc(sizeof(Measurement), sizeof(char));

        if (measurement_current == NULL)
        {
            printf("Can't allocate memory for measurements\n");

            free_measurements(measurement_first);

            return NULL;
        }

        int result = fscanf_s(
            file,
            "%4u;%2u;%2u;%2u;%2u;%3i\n",
            &measurement_current->year,
            &measurement_current->month,
            &measurement_current->day,
            &measurement_current->hour,
            &measurement_current->minute,
            &measurement_current->temperature);

        if (result == EOF)
        {
            free(measurement_current);

            break;
        }

        if (result != 6)
        {
            free(measurement_current);

            printf("Found error in row %i\n", row);

            fscanf_s(file, "%*[^\n]\n");

            continue;
        }

        if (measurement_first == NULL)
        {
            measurement_first = measurement_current;
        }
        else
        {
            measurement_prev->next = measurement_current;
        }

        measurement_prev = measurement_current;

        row++;
    }

    fclose(file);

    return measurement_first;
}

void free_measurements(PMeasurement first)
{
    PMeasurement current = first;

    while (current != NULL)
    {
        PMeasurement next = current->next;

        free(current);

        current = next;
    }
}

void print_statistics(PMeasurement first, unsigned int month)
{
    PMeasurement current = first;

    double current_month_sum = 0;

    int current_month_count = 0,
        current_month_min = INT_MAX,
        current_month_max = INT_MIN;

    double year_sum = 0;

    int year_count = 0,
        year_min = INT_MAX,
        year_max = INT_MIN;

    printf("#\tYear\tMonth\tAvg\tMin\tMax\n");

    while (current != NULL)
    {
        current_month_sum += current->temperature;
        current_month_count++;

        year_sum += current->temperature;
        year_count++;

        if (current->temperature < year_min)
        {
            year_min = current->temperature;
        }

        if (current->temperature > year_max)
        {
            year_max = current->temperature;
        }

        if (current->temperature < current_month_min)
        {
            current_month_min = current->temperature;
        }

        if (current->temperature > current_month_max)
        {
            current_month_max = current->temperature;
        }

        if (current->next == NULL || current->month != current->next->month)
        {
            if (current->month == month || month == 0)
            {
                printf(
                    "%i\t%i\t%i\t%.2f\t%i\t%i\n",
                    current->month - 1,
                    current->year,
                    current->month,
                    current_month_count > 0 ? current_month_sum / current_month_count : 0.0,
                    current_month_min,
                    current_month_max);
            }

            current_month_sum = 0;
            current_month_count = 0;
            current_month_min = INT_MAX;
            current_month_max = INT_MIN;
        }

        current = current->next;
    }

    if (month == 0)
    {
        printf("Statistics for year: avg - %.2f; min - %i; max - %i\n",
            year_count > 0 ? year_sum / year_count : 0.0,
            year_min,
            year_max);
    }
}