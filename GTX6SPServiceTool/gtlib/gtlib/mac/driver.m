#import <Foundation/Foundation.h>
#import "gtx.h"


//ドライバーのパス
void GTX_GetDriverPath( TCHAR* pcPath )
{
    strcpy( pcPath , "/Library/Printers/Brother/GT/" );
}


//カスタム設定
static NSString* GetTypeFile( GTX_PRINTER_TYPE type )
{
	switch( type ) {
	case TYPE_GT3:		return	@"/Library/Printers/Brother/GT/GT3.plist";
	case TYPE_GTX4:		return	@"/Library/Printers/Brother/GT/GTX4.plist";
	case TYPE_GTXpro:	return	@"/Library/Printers/Brother/GT/GTXpro.plist";
	case TYPE_GTX6:		return	@"/Library/Printers/Brother/GT/GTX6.plist";
	case TYPE_GTX6SP:	return	@"/Library/Printers/Brother/GT/GTX6SP.plist";
	case TYPE_GTX6IS:	return	@"/Library/Printers/Brother/GT/GTX6IS.plist";
	default:			return	NULL;
	}
}
DWORD GTX_GetCustomMode( GTX_PRINTER_TYPE type )
{
    NSString     *file = GetTypeFile(type);
    NSString     *key  = @"SetupMode";

    NSDictionary *dict = [[NSDictionary alloc] initWithContentsOfFile: file];
    int           mode = 0;
    if (dict != nil) {
        mode = [[dict valueForKey: key] intValue];
    }
    return mode;
	
}
