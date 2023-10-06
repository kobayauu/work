#import <Foundation/Foundation.h>
#if (__i386 || __x86_64__)
#import <cpuid.h>
#else
#import <sys/sysctl.h>
#endif

#import "gtx.h"
#import "modpal.h"


///////////////////////////////////////////////////////////
// 関数：内部関数

int read_dylib_info(const char *file, char *name, uint32_t *timestamp, uint32_t *compatibility_version, uint32_t *current_version);

DWORD GetDylibVersion( GTX_PRINTER_TYPE type )
{
    const char *file = NULL;
    if( type == TYPE_GT3    )   file = "/Library/Printers/Brother/GT/libGT3Api.dylib";
    if( type == TYPE_GTX4   )   file = "/Library/Printers/Brother/GT/libGTX4Api.dylib";
    if( type == TYPE_GTXpro )   file = "/Library/Printers/Brother/GT/libGTXproApi.dylib";
    if( type == TYPE_GTX6   )   file = "/Library/Printers/Brother/GT/libGTX6Api.dylib";
    if( type == TYPE_GTX6SP )   file = "/Library/Printers/Brother/GT/libGTX6SPApi.dylib";

    uint32_t current_version = 0;
    read_dylib_info(file, NULL, NULL, NULL, &current_version);
    
    return current_version << 8;
}
DWORD GetBundleVersion( void )
{
    id info = [[NSBundle mainBundle] infoDictionary];
    id ver1 = [info objectForKey:@"CFBundleShortVersionString"];
    id ver2 = [info objectForKey:@"CFBundleVersion"];
    id ary  = [ver1 componentsSeparatedByString:@"."];
    
    BYTE v1=0, v2=0, v3=0, v4=0;
    if ([ary count] > 0) v1 = [ary[0] intValue];
    if ([ary count] > 1) v2 = [ary[1] intValue];
    if ([ary count] > 2) v3 = [ary[2] intValue];
    v4 = [ver2 intValue];
    
    return v1<<24 | v2<<16 | v3<<8 | v4;
}
void GetAppVersion( DWORD* dwVersion, GTX_PRINTER_TYPE type )
{
    //App
    if( dwVersion[0] == -1 )
    {
        dwVersion[0] = GetBundleVersion();
    }

    //API
    if( dwVersion[1] == -1 )
    {
        dwVersion[1] = GetDylibVersion(type);
    }

    //Driver
    if( dwVersion[2] == -1 )
    {
        dwVersion[2] = GetBundleVersion();
    }
}

void GetOSVersion( BYTE* byOS )
{
    NSProcessInfo *pinfo = [NSProcessInfo processInfo];
    NSOperatingSystemVersion ver = [pinfo operatingSystemVersion];

    byOS[0] = 1;
    byOS[1] = ver.majorVersion;
    byOS[2] = ver.minorVersion;
    byOS[3] = ver.patchVersion;
}

void GetCpuID( BYTE* pCpuID )
{
#if (__i386 || __x86_64__)

    int        cpui[4];
    __cpuid(0x80000000, cpui[0],cpui[1],cpui[2],cpui[3]);
    if (cpui[0] >= 0x80000004) {
        __cpuid(0x80000002, cpui[0],cpui[1],cpui[2],cpui[3]);    memcpy( pCpuID     , cpui, sizeof(cpui) );
        __cpuid(0x80000003, cpui[0],cpui[1],cpui[2],cpui[3]);    memcpy( pCpuID + 16, cpui, sizeof(cpui) );
        __cpuid(0x80000004, cpui[0],cpui[1],cpui[2],cpui[3]);    memcpy( pCpuID + 32, cpui, sizeof(cpui) );
    }
    else {
        __cpuid(0x00000000, cpui[0],cpui[1],cpui[2],cpui[3]);   memcpy( pCpuID    , &cpui[1], sizeof(int) );
                                                                memcpy( pCpuID + 4, &cpui[3], sizeof(int) );
                                                                memcpy( pCpuID + 8, &cpui[2], sizeof(int) );
    }

#else   //__i386 || __x86_64__

    size_t size = sizeof(uint32_t);
    uint32_t cpufamily = 0, cpusubfamily = 0, cpufrequency = 0;
    sysctlbyname("hw.cpufamily", &cpufamily, &size, NULL, 0);
    sysctlbyname("hw.cpusubfamily", &cpusubfamily, &size, NULL, 0);
    sysctlbyname("hw.cpufrequency", &cpufrequency, &size, NULL, 0);
    NSString *name = [NSString stringWithFormat: @"AppleSilicon %08X:%08X", cpufamily, cpusubfamily];
    memcpy( pCpuID, [name UTF8String], min([name length], 48));

#endif  //__i386 || __x86_64__
}

void GetMemory( WORD* wMemory )
{
    NSProcessInfo *pinfo = [NSProcessInfo processInfo];

    mach_port_t host_port = mach_host_self();
    vm_size_t pagesize;
    host_page_size(host_port, &pagesize);
    vm_statistics_data_t vm_stat;
    mach_msg_type_number_t host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size);

    wMemory[0] = ( [pinfo physicalMemory] >> 20 );
    wMemory[1] = ( (vm_stat.free_count * pagesize) >> 20 );
    wMemory[2] = ( ((vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count + vm_stat.free_count) * pagesize) >> 20);
}


///////////////////////////////////////////////////////////
// 関数：印刷変数

void GTX_SUB_OptionToEnvironData( BYTE *pData, GTX_PRINTER_TYPE type )
{
	GetAppVersion( (DWORD*)(pData + 4), type );
	GetOSVersion( pData + 16 );
    GetCpuID( pData + 20 );
	GetMemory( (WORD*)(pData + 68) );
}

void GTX_SUB_GetEnvironData( BYTE* pData )
{
	GetOSVersion( pData + 0 );
	GetCpuID( pData + 4 );
	GetMemory( (WORD*)(pData + 52) );
}
