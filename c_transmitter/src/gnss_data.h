#ifndef GNSS_DATA_H
#define GNSS_DATA_H

extern const char* raw_data[][4];
struct GNSS_Struct {
	double time;
	double lat;
	double lon;
	double alt;
};
#endif
