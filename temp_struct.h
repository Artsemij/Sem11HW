#pragma once

// Структура для хранения информации об измерениии температуры
typedef struct Measurement {
    // Год измерения
    unsigned int year;


    // Месяц измерения
    unsigned int month;

    
    // День измерения
    unsigned int day;

    
    // Час измерения
    unsigned int hour;

   
    // Минута измерения
    unsigned int minute;

    
    // Температура во время измерения
    int temperature;

    
    // Указатель на следующее измерение
    struct Measurement* next;
} Measurement, *PMeasurement;