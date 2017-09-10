#include "types.h"
#include "gdt.h"

void printf(string str) {
		int8_t* VideoMemory = (int8_t*) 0xb8000;
		int srcIndex = 0;
		int desIndex = 0;
		while (str[srcIndex] != '\0') {
			VideoMemory[desIndex++] = str[srcIndex++]; // text
			VideoMemory[desIndex++] = 0x02; // color manipulation VGA-compatible_text_mode
		}
}

extern "C" void kernelMain(void * multibootStructure, uint32_t magicNumber) {
	printf("Hello world from xr!");

	GlobalDescriptorTable gdt;

	while(1);
}
