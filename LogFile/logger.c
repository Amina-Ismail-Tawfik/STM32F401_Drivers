#include"logger.h"

char priority=Info;
char OutputChannel=Console_ch;
FILE* file=0;
const char* filepath="D:/log.txt";




void timestamp() {
	time_t now;
	struct tm *local;
	char time_str[100];

	now = time(0);
	local = localtime(&now);
	strftime(time_str, sizeof(time_str), "%d-%m-%Y %H:%M:%S", local);

	if(OutputChannel==Console_ch)
	{
		printf("[%s] ", time_str);
	}
	else
	{
		fprintf(file,"[%s] ", time_str);
	}
}



void log_write(LogType_t Type, const char* format, ... )
{

	char* Priority_String[4]={"[INFO]      ","[WARNING]   ","[ERROR]     ","[CRITICAL]  "};
	if (priority<=Type)
	{
		timestamp();
		if (OutputChannel==Console_ch)
		{
			printf("%s",Priority_String[Type]);
			va_list args;
			va_start(args, format);
			vprintf(format, args);
			va_end(args);
			printf("\n");
		}
		else if (OutputChannel==File_ch)
		{
			fprintf(file,"%s",Priority_String[Type]);
			va_list args;
			va_start(args, format);
			vfprintf(file,format, args);
			va_end(args);
			fprintf(file,"\n");
		}

	}


}
void SelectOutputChannel(OutputChannel_t output_ch)
{
	OutputChannel=output_ch;
	if (output_ch==File_ch)
	{

		file = fopen(filepath, "w");

	}
}

void set_priority(LogType_t new_priority)
{
	priority = new_priority;
}
void LogFile_cfg (const char* new_file_path)
{
	filepath=new_file_path;
}

void free_file()
{
	fclose(file);
	file = 0;
}

