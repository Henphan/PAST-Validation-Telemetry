#ifndef GNSS_DATA_H
#define GNSS_DATA_H

extern const char* raw_data[][4];
typedef struct{
	double time;
	double lat;
	double lon;
	double alt;
}GNSS_row;
#endif
