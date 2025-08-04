#ifndef MAIN_H
#define MAIN_H

// Constants
extern const int billDenominations[];
extern const int numBillDenominations;

/**
 * @struct TimePeriod
 * @brief Represents a time period with amount and unit ('d' = days, 'm' = months, 'a' = years).
 */
typedef struct {
    int amount;
    char unit;  ///< Unit of time: 'd', 'm', or 'a'
} TimePeriod;

extern const TimePeriod timePeriod;

/**
 * @brief Calculates the expected daily value from bill denominations.
 * @return Expected daily value as a double.
 */
double calculateExpectedDailyValue(void);

/**
 * @brief Prints a double value formatted as currency with thousands separators and 2 decimal places.
 * @param value The double value to print.
 */
void printCurrencyFormatted(double value);

/**
 * @brief Converts a time period to number of days.
 * @param amount The amount of the time period.
 * @param unit The unit of the time period ('d', 'm', or 'a').
 * @return Number of days corresponding to the time period, or -1 if the unit is invalid.
 */
int convertTimePeriodToDays(int amount, char unit);

/**
 * @brief Validates the global TimePeriod struct ensuring positive amount and valid unit.
 * @param outUnit Pointer to a char where the validated, lowercase unit will be stored.
 * @return 0 if valid, 1 if invalid.
 */
int validateTimePeriod(char* outUnit);

/**
 * @brief Validates conversion from amount and unit to days.
 * @param amount Amount of time.
 * @param unit Unit of time ('d', 'm', or 'a').
 * @param outDays Pointer to int where the converted days will be stored.
 * @return 0 if valid conversion, 1 if error.
 */
int validateAndConvertToDays(int amount, char unit, int* outDays);

/**
 * @brief Prints a message followed by a currency-formatted double value and newline.
 * @param message The message to print before the value.
 * @param value The double value to print.
 */
void printMessageWithCurrency(const char* message, double value);

#endif // MAIN_H