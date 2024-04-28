#pragma once

#include "temp_struct.h"

// Читает CSV файл с данными об измерениях
extern PMeasurement load_measurements(char* filename);

// Очищает память использованую под данные об измерениях
extern void free_measurements(PMeasurement first);

// Выводит статистику по переданным измерениях
extern void print_statistics(PMeasurement first, unsigned int month);