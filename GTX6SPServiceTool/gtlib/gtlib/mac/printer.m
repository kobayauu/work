#define _IPP_PRIVATE_STRUCTURES 1
#import <Cocoa/Cocoa.h>
#import <cups/cups.h>
#import <net/ethernet.h>
#import <netinet/ip_icmp.h>
#import <netinet/icmp6.h>
#import "ipp_private.h"

#import "ospal.h"
#import "gtx.h"


////////////////////////////////////////
//    内部関数

NSString* PrinterGetAddress(PMPrinter printer)
{
    CFURLRef url;
    PMPrinterCopyDeviceURI(printer, &url);
    NSString* scheme  = (__bridge NSString *) CFURLCopyScheme(url);
    NSString* address = (__bridge NSString *) CFURLCopyNetLocation(url);
    if ([address hasPrefix:@"["] && [address hasSuffix:@"]"]) {
        address = [address substringWithRange:NSMakeRange(1, [address length] - 2)];
    }

    return ([scheme isEqualToString:@"usb"] ? @"" : address);
}

Boolean PrinterIsOnlineLAN(NSString* address)
{
    u_short (^checksum)(u_short *,int) = ^(u_short *buf, int bufsz)
    {
        u_long sum = 0;
        for (; bufsz > 1; bufsz -= 2) sum += *(buf++);
        if (bufsz > 0) sum += *(u_char *)buf;
        sum = (sum & 0xFFFF) + (sum >> 16);
        sum = (sum & 0xFFFF) + (sum >> 16);
        return (u_short)~sum;
    };
    
    // Check address
    struct addrinfo hints = {0}, *res;
    hints.ai_family = AF_UNSPEC; /* IPv4/IPv6両方に対応 */
    hints.ai_socktype = SOCK_DGRAM;
    int err = getaddrinfo([address UTF8String], NULL, &hints, &res);
    if (err != 0) {
        return FALSE;
    }
    
    // Create socket
    int protocol = (res->ai_family==AF_INET ? IPPROTO_ICMP : IPPROTO_ICMPV6);
    int sock = socket(res->ai_family, res->ai_socktype, protocol);
    if (sock < 0) {
        return FALSE;
    }
    
    // Send packet
    struct icmp hdr = {0};
    hdr.icmp_type = (res->ai_family==AF_INET ? ICMP_ECHO : ICMP6_ECHO_REQUEST);
    hdr.icmp_cksum = checksum((unsigned short *)&hdr, sizeof(hdr));
    ssize_t n = sendto(sock, (char *)&hdr, sizeof(hdr), 0, res->ai_addr, res->ai_addrlen);
    if (n < 1) {
        close(sock);
        return FALSE;
    }
    
    // Wait recive packet
    struct timeval tv = {1,0}; //1s
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sock, &fds);
    
    int retval = select(sock+1, &fds, NULL, NULL, &tv);
    if (retval < 0 || !FD_ISSET(sock, &fds)) {
        close(sock);
        return FALSE;
    }
    
    // Recive packet
    char buf[ETHER_MAX_LEN] = {0};
    n = recv(sock, buf, sizeof(buf), 0);
    if (n < 1) {
        close(sock);
        return FALSE;
    }
    
    // Close socket
    close(sock);
    
    // Check result
    if (res->ai_family != AF_INET) {
        return TRUE;
    }

    struct sockaddr_in  *addr       = (struct sockaddr_in *)res->ai_addr;
    struct ip           *iphdrptr   = (void *)buf;
    struct icmp         *icmphdrptr = (void *)(buf + (iphdrptr->ip_hl * 4));
    
    return (iphdrptr->ip_src.s_addr == addr->sin_addr.s_addr
            &&  iphdrptr->ip_p == IPPROTO_ICMP
            &&  icmphdrptr->icmp_type == ICMP_ECHOREPLY);
}

Boolean PrinterIsOnlineUSB(NSString* pid)
{
    // Get the printer's URI
    char uri[1024];
    httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "ipp", nil, "localhost", 0, "/printers/%s",[pid UTF8String]);
    
    // Create a Get-Printer-Attributes request for the printer
    ipp_t *request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);
    ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, uri);
    ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "requested-attributes", NULL, "printer-state-reasons");
    
    // Send the request and get the printer attributes response...
    ipp_t *response = cupsDoRequest(CUPS_HTTP_DEFAULT, request, "/");
    
    // Get the current printer state and the last time the marker-* attributes were updated.
    BOOL onlineFlg = NO;
    ipp_attribute_t *reasons = ippFindAttribute(response, "printer-state-reasons", IPP_TAG_KEYWORD);
    if (reasons)
    {
        // Check online.
        onlineFlg = YES;
        for (int i = 0; i < reasons->num_values; i ++)
        {
            if (!strcmp(reasons->values[i].string.text, "paused"))
            {
                onlineFlg = NO;
                break;
            }
            if (!strcmp(reasons->values[i].string.text, "offline-report")) {
                onlineFlg = NO;
                break;
            }
        }
    }
    
    // Clean up.
    ippDelete(response);
    
    return onlineFlg;
}

Boolean PrinterIsOnline(PMPrinter printer)
{
    NSString *address = PrinterGetAddress(printer);
    if ([address length] > 0) {
        return  PrinterIsOnlineLAN(address);
    }
    else {
        NSString *pid = (__bridge NSString *) PMPrinterGetID(printer);
        return  PrinterIsOnlineUSB(pid);
    }
}

GTX_PRINTER_TYPE GetPrinterType(PMPrinter printer)
{
    CFStringRef model;
    PMPrinterGetMakeAndModelName(printer, &model);
    NSString *value = (__bridge NSString *) model;
    NSString *pid = (__bridge NSString *) PMPrinterGetID(printer);
    NSString *address = PrinterGetAddress(printer);

	GTX_PRINTER_TYPE type = (GTX_PRINTER_TYPE) 0;
    if ([value compare:@"Brother GT-3"] == NSOrderedSame) {
        type = TYPE_GT3;
    }
    else if ([value compare:@"Brother GTX-4"] == NSOrderedSame) {
        type = TYPE_GTX4;
    }
    else if ([value compare:@"Brother GTX pro"] == NSOrderedSame) {
        type = TYPE_GTXpro;
    }
    else if ([value compare:@"Brother GTX-6"] == NSOrderedSame) {
        type = TYPE_GTX6;
    }
    else if ([value compare:@"Brother GTX-6 Extra Colors ORGR"] == NSOrderedSame) {
        type = TYPE_GTX6SP;
    }
    else if ([value compare:@"Brother GTX-6 Ink Server"] == NSOrderedSame) {
        type = TYPE_GTX6IS;
    }

    if ([pid hasSuffix:@"_FileOutput"]) {
        type = type | TYPE_FILEOUTPUT;
    }
    else if ([address length] > 0) {
        type = type | TYPE_LAN;
    }
    else {
        type = type | TYPE_USB;
    }

    return  type;
}

//プリンタ名からプリンターを取得
PMPrinter PrinterGetPMPrinter( LPCTSTR szPrinter )
{
    CFArrayRef list;
    PMServerCreatePrinterList(kPMServerLocal, &list);
    
    int count = (int) CFArrayGetCount(list);
    for (int i = 0; i < count; ++i)
    {
        PMPrinter printer = (PMPrinter) CFArrayGetValueAtIndex(list, i);
        NSString *name = (__bridge NSString *) PMPrinterGetName(printer);
        
        if (strcmp(szPrinter, [name UTF8String]) == 0)
        {
            return printer;
        }
    }
    return nil;
}

GTX_PRINTER_TYPE GTX_GetPrinterType( LPCTSTR szPrinter )
{
    PMPrinter printer = PrinterGetPMPrinter(szPrinter);
    if (printer == nil) {
        return  (GTX_PRINTER_TYPE) 0;
    }

    return  GetPrinterType(printer);
}

void GTX_SUB_GetPID( LPTSTR szPID, LPCTSTR szName )
{
    PMPrinter printer = PrinterGetPMPrinter(szName);
    if (printer == nil) {
        return;
    }

    NSString *pid  = (__bridge NSString *) PMPrinterGetID(printer);
    strcpy(szPID, [pid UTF8String]);
}


////////////////////////////////////////
//    外部関数

int GTX_EnumPrinter( GTX_PRINTER_TYPE type, EnumPrinterCallBack callback, void* pUserData )
{
    CFArrayRef list;
    PMServerCreatePrinterList(kPMServerLocal, &list);
    int count = (int) CFArrayGetCount(list);

    for (int i = 0; i < count; ++i)
    {
        PMPrinter printer = (PMPrinter) CFArrayGetValueAtIndex(list, i);

        GTX_PRINTER_TYPE driverType = GetPrinterType(printer);
        if (! (type & driverType & TYPE_MACHINE_ALL)) {
            continue;
        }
        if (! (type & driverType & TYPE_OUTPUT_ALL)) {
            continue;
        }

        Boolean remote;
        PMPrinterIsRemote(printer, &remote);
        if (remote) {
            continue;
        }

        if (! (type & driverType & TYPE_FILEOUTPUT)
        &&  ! PrinterIsOnline(printer)) {
            continue;
        }

        NSString *printerName = (__bridge NSString *) PMPrinterGetName(printer);
        
        @try {
            if (callback(driverType, [printerName UTF8String], pUserData) == 0) {
                return  -4;
            }
		}
        @catch(...) {
            return  -3;
		}
    }
    return  0;
}

BOOL GTX_GetPrinterAddress( LPTSTR szAddress, LPCTSTR szName )
{
    PMPrinter printer = PrinterGetPMPrinter(szName);
    if (printer == nil) {
        return  FALSE;
    }

    NSString *address = PrinterGetAddress(printer);
    if( [address length] == 0 ) {
        return  FALSE;
    }

    if( szAddress != NULL ) {
        strcpy(szAddress, [address UTF8String]);
    }
    return  TRUE;
}

BOOL GTX_IsOnlineAddress( LPCTSTR szAddress )
{
    NSString *addres = [NSString stringWithUTF8String:szAddress];

    return  PrinterIsOnlineLAN(addres);
}
