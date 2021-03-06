#ifndef EXE_H
#define EXE_H

#include <unicorn/unicorn.h>
#include <map>
#include <string>

struct DosHeader
{
     uint8_t signature[2];
     uint16_t lastsize;
     uint16_t nblocks;
     uint16_t nreloc;
     uint16_t hdrsize;
     uint16_t minalloc;
     uint16_t maxalloc;
     uint16_t ss; // 2 byte ptr
     uint16_t sp; // 2 byte ptr
     uint16_t checksum;
     uint16_t ip; // 2 byte ptr
     uint16_t cs; // 2 byte ptr
     uint16_t relocpos;
     uint16_t noverlay;
     uint16_t reserved1[4];
     uint16_t oem_id;
     uint16_t oem_info;
     uint16_t reserved2[10];
     uint32_t  e_lfanew;
};

struct COFFHeader
{
    uint16_t machine;
    uint16_t numberOfSections;
    uint32_t timeDateStamp;
    uint32_t pointerToSymbolTable;
    uint32_t numberOfSymbols;
    uint16_t sizeOfOptionalHeader;
    uint16_t characteristics;
};

#define COFF_I386 0x14c

struct data_directory
{ 
    uint32_t virtualAddress;
    uint32_t size;
};

struct PEOptHeader
 {
    uint16_t signature; //decimal number 267 for 32 bit, 523 for 64 bit, and 263 for a ROM image. 
    uint8_t majorLinkerVersion; 
    uint8_t minorLinkerVersion;
    uint32_t sizeOfCode;
    uint32_t sizeOfInitializedData;
    uint32_t sizeOfUninitializedData;
    uint32_t addressOfEntryPoint;  //The RVA of the code entry point
    uint32_t baseOfCode;
    uint32_t baseOfData;
    /*The next 21 fields are an extension to the COFF optional header format*/
    uint32_t imageBase;
    uint32_t sectionAlignment;
    uint32_t fileAlignment;
    uint16_t majorOSVersion;
    uint16_t minorOSVersion;
    uint16_t majorImageVersion;
    uint16_t minorImageVersion;
    uint16_t majorSubsystemVersion;
    uint16_t minorSubsystemVersion;
    uint32_t win32VersionValue;
    uint32_t sizeOfImage;
    uint32_t sizeOfHeaders;
    uint32_t checksum;
    uint16_t subsystem;
    uint16_t DLLCharacteristics;
    uint32_t sizeOfStackReserve;
    uint32_t sizeOfStackCommit;
    uint32_t sizeOfHeapReserve;
    uint32_t sizeOfHeapCommit;
    uint32_t loaderFlags;
    uint32_t numberOfRvaAndSizes;
    struct data_directory dataDirectory[16];
};

struct PESection
{
    char name[8];
    union {
        uint32_t physicalAddress;
        uint32_t virtualSize;
    } addr;
    uint32_t virtualAddress;
    uint32_t sizeOfRawData;
    uint32_t pointerToRawData;
    uint32_t pointerToRelocations;
    uint32_t pointerToLinenumbers;
    uint16_t numberOfRelocations;
    uint16_t numberOfLinenumbers;
    uint32_t characteristics;
};

#pragma pack(push, 1)

struct ImportDesc {
	uint32_t name_desc_ptr;
	uint32_t timestamp;
	uint32_t forwarder_chain;
	uint32_t name;
	uint32_t import_ptr_list;
};

#pragma pack(pop)

typedef struct ResourceDirTable
{
    uint32_t characteristics;
    uint32_t timestamp;
    uint16_t major;
    uint16_t minor;
    uint16_t cnt_names;
    uint16_t cnt_ids;
} ResourceDirTable;

typedef struct ResourceDirEntry
{
    union
    {
        uint32_t name_offset;
        uint32_t id;
    };
    uint32_t offset;
} ResourceDirEntry;

typedef struct
{
    uint32_t ptr;
    uint32_t size;
    uint32_t unk;
    uint32_t unk2;
} ResourceData;

#define IMAGE_DIRECTORY_ENTRY_EXPORT	        0
#define IMAGE_DIRECTORY_ENTRY_IMPORT	        1
#define IMAGE_DIRECTORY_ENTRY_RESOURCE	        2
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION	        3
#define IMAGE_DIRECTORY_ENTRY_SECURITY	        4
#define IMAGE_DIRECTORY_ENTRY_BASERELOC	        5
#define IMAGE_DIRECTORY_ENTRY_DEBUG	            6
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE	    7
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR	        8
#define IMAGE_DIRECTORY_ENTRY_TLS	            9
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	    10
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	    11
#define IMAGE_DIRECTORY_ENTRY_IAT	            12
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT	    13
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR	14

#define RT_CURSOR         1
#define RT_BITMAP         2
#define RT_ICON           3
#define RT_MENU           4
#define RT_DIALOG         5
#define RT_STRING         6
#define RT_FONTDIR        7
#define RT_FONT           8
#define RT_ACCELERATOR    9
#define RT_RCDATA         10
#define RT_MESSAGETABLE   11
#define RT_GROUP_CURSOR   12
#define RT_GROUP_ICON     14
#define RT_VERSION        16
#define RT_DLGINCLUDE     17
#define RT_PLUGPLAY       19
#define RT_VXD            20
#define RT_ANICURSOR      21
#define RT_ANIICON        22
#define RT_HTML           23

extern std::map<int, std::map<int, ResourceData*> > resource_id_map;
extern std::map<int, std::map<std::string, ResourceData*> > resource_str_map;

uint32_t load_executable(char* path, uint32_t *image_addr, void **image_mem, uint32_t *image_size, uint32_t *stack_addr, uint32_t *stack_size);
std::string from_wstring(void* wstring, bool tolower = false);

#endif // EXE_H
