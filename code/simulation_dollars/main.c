#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

const int billDenominations[] = {1, 2, 5, 10, 20, 50, 100};
const int numBillDenominations = sizeof(billDenominations) / sizeof(billDenominations[0]);

const TimePeriod timePeriod = {50, 'a'};

double calculateExpectedDailyValue(void) {
    double sum = 0;
    for (int i = 0; i < numBillDenominations; i++) {
        sum += billDenominations[i];
    }
    return sum / numBillDenominations;
}

void printCurrencyFormatted(double value) {
    unsigned long long intPart = (unsigned long long)value;
    int decimalPart = (int)((value - intPart) * 100 + 0.5);

    if (intPart == 0) {
        printf("0");
    } else {
        char buffer[30];
        int count = 0;
        char *p = buffer + sizeof(buffer) - 1;
        *p = '\0';

        while (intPart > 0) {
            if (count == 3) {
                *--p = ',';
                count = 0;
            }
            *--p = '0' + (intPart % 10);
            intPart /= 10;
            count++;
        }
        printf("%s", p);
    }

    printf(".");
    if (decimalPart < 10) printf("0");
    printf("%d", decimalPart);
}

int convertTimePeriodToDays(int amount, char unit) {
    switch (unit) {
        case 'd': return amount;
        case 'm': return amount * 30;
        case 'a': return amount * 365;
        default: return -1;
    }
}

int validateTimePeriod(char* outUnit) {
    if (timePeriod.amount <= 0) {
        fprintf(stderr, "Error: The amount must be a positive integer.\n");
        return 1;
    }

    char unit = tolower(timePeriod.unit);
    if (unit != 'd' && unit != 'm' && unit != 'a') {
        fprintf(stderr, "Error: The unit must be 'd', 'm', or 'a'.\n");
        return 1;
    }

    *outUnit = unit;
    return 0;
}

int validateAndConvertToDays(int amount, char unit, int* outDays) {
    int days = convertTimePeriodToDays(amount, unit);
    if (days < 0) {
        fprintf(stderr, "Error converting the time unit to days.\n");
        return 1;
    }

    *outDays = days;
    return 0;
}

void printMessageWithCurrency(const char* message, double value) {
    printf("%s", message);
    printCurrencyFormatted(value);
    printf("\n");
}

int main(void) {
    char unit;
    int days;

    if (validateTimePeriod(&unit)) return 1;
    if (validateAndConvertToDays(timePeriod.amount, unit, &days)) return 1;

    int years = (unit == 'a') ? timePeriod.amount : days / 365;

    double dailyExpected = calculateExpectedDailyValue();
    double annualExpected = dailyExpected * 365;
    double totalExpected = dailyExpected * days;

    printMessageWithCurrency("Expected daily value: $", dailyExpected);
    printMessageWithCurrency("Expected annual income: $", annualExpected);

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Expected income over %d years: $", years);
    printMessageWithCurrency(buffer, totalExpected);

    return 0;
}