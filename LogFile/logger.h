#ifndef LOGGERC_H
#define LOGGERC_H

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

// Enum to represent different types of log messages
typedef enum LogType {
    Info,     ///< Informational message
    Warning,  ///< Warning message
    Error,    ///< Error message
    Critical  ///< Critical error message
} LogType_t;

// Enum to represent different output channels
typedef enum OutputChannel {
    Console_ch,  ///< Output to console
    File_ch      ///< Output to file
} OutputChannel_t;

/**
 * @brief Sets the priority level for logging.
 *
 * This function sets the priority level for logging. The priority level
 * determines which log messages will be written based on their severity.
 *
 * @param new_priority The new priority level to be set.
 *                     It should be one of the values from the LogType_t enum:
 *                     - Info
 *                     - Warning
 *                     - Error
 *                     - Critical
 */
void set_priority(LogType_t new_priority);

/**
 * @brief Selects the output channel for logging.
 *
 * This function selects the output channel for logging. The output channel
 * determines where log messages will be written, either to the console or
 * to a file.
 *
 * @param output_ch The output channel to be selected.
 *                  It should be one of the values from the OutputChannel_t enum:
 *                  - Console_ch
 *                  - File_ch
 */
void SelectOutputChannel(OutputChannel_t output_ch);

/**
 * @brief Configures the log file path.
 *
 * This function configures the log file path. Log messages will be written
 * to the specified file path if the file output channel is selected.
 *
 * @param new_file_path The path of the log file.
 */
void LogFile_cfg(const char* new_file_path);

/**
 * @brief Frees any resources associated with the log file.
 *
 * This function frees any resources associated with the log file, such as
 * closing the file stream.
 */
void free_file();

/**
 * @brief Writes a log message.
 *
 * This function writes a log message with the specified type and format.
 * The format string and additional arguments are similar to the printf function.
 *
 * @param Type   The type of the log message.
 * @param format The format string for the log message.
 * @param ...    Additional arguments to be formatted according to the format string.
 */
void log_write(LogType_t Type, const char* format, ... );


#endif
