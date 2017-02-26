#ifndef __DBFSTRU
#define __DBFSTRU
//DBASE header structure
typedef struct{
     unsigned char    db;             // file flag
     unsigned char    year;
     unsigned char    month;
     unsigned char    day;
     unsigned char    recTotal[4];        // number of records in file    i~,;~~
     unsigned char   headLength[2];     // 3~4~~, ~_~~,~ (32bits) ~D~fiJ~K~
     unsigned char    recLength[2];       // number of bytes in record    i~~
     unsigned char    other[20];          // other stuff, ~zzj~
}DBFHEAD;

//DBASE field structure
typedef struct{
	unsigned char name[11];           // field name, ~~
	unsigned char type;             // field type, -~J~
	unsigned char fieldoffset[4];    // your guess is as good as mine, -~]~J~t~i~i~
	unsigned char length;            // field length , -~J~~
	unsigned char decimal;            // decimal positions if numeric, d~[~J4~
	unsigned char other[14];         // other stuff??, ~~
}DBFFIELD;




typedef struct{
	 char name[16];
	BOOL     mDelFlag;
	UINT     index;

}INDEXTAB;
#endif