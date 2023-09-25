#define	GET_BYTE(p)			( *(p) )
#define	GET_WORD(p)			( *(p)<<8 | *(p+1) )
#define	GET_DWORD(p)		( *(p)<<24 | *(p+1)<<16 | *(p+2)<<8 | *(p+3) )
#define SET_BYTE(x,n,v)		{ *(x+n) = (BYTE)(v); }
#define SET_WORD(x,n,v)		{ *(x+n) = (BYTE)(v>>8); *(x+n+1) = (BYTE)(v); }
#define SET_DWORD(x,n,v)	{ *(x+n) = (BYTE)(v>>24); *(x+n+1) = (BYTE)(v>>16); *(x+n+2) = (BYTE)(v>>8); *(x+n+3) = (BYTE)(v); }
