

#ifndef __AUXILIARY_H__
#define __AUXILIARY_H__

#define LOGI	TRACE

void Hex2Asc(  BYTE *hex, BYTE *asc, long hexLen);
void Asc2Hex(  BYTE *asc, BYTE *hex, long ascLen);
void LOG_DATA(BYTE *data, long len);


#endif /* __AUXILIARY_H__ */