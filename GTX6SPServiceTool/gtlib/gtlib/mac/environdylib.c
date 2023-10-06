//
//  dylib_info.c
//
//  Created by Atsushi Tada on 2023/03/16.
//

#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach/mach.h>
#include <mach-o/fat.h>
#include <mach-o/loader.h>


#define SWAP_INT(a) (((a)<<24) | (((a)<<8)&0x00ff0000) | (((a)>>8)&0x0000ff00) | ((a)>>24))


char *file_mmap(const char *file, size_t *size)
{
    int fd;
    if ((fd = open(file, O_RDONLY)) == -1) {
        return NULL;
    }
    
    struct stat stat_buf = {};
    if (fstat(fd, &stat_buf) == -1) {
        close(fd);
        return NULL;
    }
    
    char *addr = mmap(0, stat_buf.st_size, PROT_READ|PROT_WRITE, MAP_FILE|MAP_PRIVATE, fd, 0);
    close(fd);
    if ((intptr_t)addr == -1) {
        return NULL;
    }

    *size = stat_buf.st_size;
    return addr;
}

int get_load_commands(char *addr, size_t size, struct load_command **load_commands, uint32_t *ncmds)
{
    uint32_t magic = *((uint32_t *)addr);
    if (magic == FAT_MAGIC || magic == SWAP_INT(FAT_MAGIC))
    {
        struct fat_arch *fa = (struct fat_arch *)(addr + sizeof(struct fat_header));
        addr = addr + SWAP_INT(fa[0].offset);
        magic = *((uint32_t *)addr);
    }

    if (magic == MH_MAGIC || magic == SWAP_INT(MH_MAGIC))
    {
        *ncmds = ((struct mach_header *)addr)->ncmds;
        *load_commands = (struct load_command *)(addr + sizeof(struct mach_header));
    }
    else if (magic == MH_MAGIC_64 || magic == SWAP_INT(MH_MAGIC_64))
    {
        *ncmds = ((struct mach_header_64 *)addr)->ncmds;
        *load_commands = (struct load_command *)(addr + sizeof(struct mach_header_64));
    }
    else
    {
        return -1;
    }

    return 0;
}

struct dylib_command *get_dylib_info(struct load_command *load_commands, uint32_t ncmds)
{
    struct load_command *lc = load_commands;
    for (int i = 0; i < ncmds; ++i)
    {
        if (lc->cmd == LC_ID_DYLIB)
        {
            return (struct dylib_command *)lc;
        }
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return NULL;
}

int read_dylib_info(const char *file, char *name, uint32_t *timestamp, uint32_t *compatibility_version, uint32_t *current_version)
{
    size_t size;
    char *addr = file_mmap(file, &size);
    if (addr == NULL) return -1;

    uint32_t ncmds = 0;
    struct load_command *load_commands = NULL;
    int result = get_load_commands(addr, size, &load_commands, &ncmds);
    if (result < 0) {
        munmap(addr, size);
        return -2;
    }

    struct dylib_command *dl = get_dylib_info(load_commands, ncmds);
    if (dl == NULL) {
        munmap(addr, size);
        return -3;
    }

    if (name) strcpy(name, (char *)dl + dl->dylib.name.offset);
    if (timestamp) *timestamp = dl->dylib.timestamp;
    if (compatibility_version) *compatibility_version = dl->dylib.compatibility_version;
    if (current_version) *current_version = dl->dylib.current_version;

    munmap(addr, size);
    return 0;
}
