#include"stdafx.h"

void LOG_DATA(BYTE *data, long len)
{
	for(long i = 0; i < len; i++)
	{
		TRACE("%02X ",data[i]);
	}
	TRACE("\r\n");
}
static char _asc2hex(char asc)
{
	if ( asc>='0' && asc<='9')
	{
		return asc-'0';
	}
	else if ( asc >= 'a' && asc <= 'f' )
	{
		return asc-'a'+ 10;
	}else if( asc >= 'A' && asc <= 'F')
	{
		return asc-'A' + 10;
	}
	return 0;

}
void Asc2Hex(  BYTE *asc, BYTE *hex, long ascLen)
{
	char htmp,ltmp;
	for(long i = 0; i < ascLen; i+=2 )
	{
		htmp = _asc2hex(*asc);
		asc++;
		ltmp = _asc2hex(*asc);
		asc++;
		*hex = (htmp<<4)|ltmp;
		hex++;
	}
}
void Hex2Asc(  BYTE *hex, BYTE *asc, long hexLen)
{
	char htmp,ltmp;
	for( long i = 0; i < hexLen; i++ )
	{
		htmp = *hex>>4;
		ltmp = *hex&0x0f;
		if( htmp>=0 && htmp<=9 )
		{
			*asc = htmp+'0';
		}
		else
		{
			*asc = (htmp-10)+'A';
		}
		asc++;
		if( ltmp>=0 && ltmp<=9 )
		{
			*asc = ltmp+'0';
		}
		else
		{
			*asc = (ltmp-10)+'A';
		}
		hex++;
		asc++;
	}
}
