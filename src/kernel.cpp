#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

using namespace xros;
using namespace xros::common;
using namespace xros::drivers;
using namespace xros::hardwarecommunication;

void printf(string str) {
		static uint16_t* VideoMemory = (uint16_t*) 0xb8000;
		static uint8_t x = 0, y = 0;

		for(int i = 0; str[i] != '\0'; ++i) {

			switch (str[i]) {
				case '\n':
					y++;
					x=0;
					break;
				default:
					VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
					x++;
			}

			// reach the end of one line
			if (x >= 80) {
				y++;
				x=0;
			}

			// reach the bottom of the page, clean the screen
			if (y >= 25) {
				for (y = 0; y < 25; y++) {
					for (x = 0; x < 80; x++) {
						VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
					}
				}

				x = 0;
				y = 0;
			}

		}
}

void printfHex(uint8_t key) {
	char* foo = "00 ";
	char* hex = "0123456789ABCDEF";
	foo[0] = hex[(key >> 4) & 0xF];
	foo[1] = hex[key & 0xF];
	printf(foo);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler {
	public:
		void OnKeyDown(char c) {
			char* foo = " ";
			foo[0] = c;
			printf(foo);
		}
 };

 class MouseToConsole : public MouseEventHandler {
		int8_t x, y;
		public:

			MouseToConsole() {
				uint16_t* VideoMemory = (uint16_t*)0xb8000;
			  x = 40;
			  y = 12;
			  VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
			                      | (VideoMemory[80*y+x] & 0xF000) >> 4
			                      | (VideoMemory[80*y+x] & 0x00FF);
			}

			void OnMouseMove(int xoffset, int yoffset) {

				static uint16_t* VideoMemory = (uint16_t*)0xb8000;
				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
														| (VideoMemory[80*y+x] & 0xF000) >> 4
														| (VideoMemory[80*y+x] & 0x00FF);

				x += xoffset;
				if(x >= 80) x = 79;
				if(x < 0) x = 0;
				y -= yoffset;
				if(y >= 25) y = 24;
				if(y < 0) y = 0;

				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
														| (VideoMemory[80*y+x] & 0xF000) >> 4
														| (VideoMemory[80*y+x] & 0x00FF);
			}
};

extern "C" void kernelMain(void * multibootStructure, uint32_t magicNumber) {
	printf("Kernel start!\n");

	GlobalDescriptorTable gdt;
	InterruptManager interrupts(&gdt);

	printf("Initializing Hardware, stage 1!\n");

	DriverManager drvManager;
		PrintfKeyboardEventHandler kbhandler;
		KeyboardDriver keyboard(&interrupts, &kbhandler);
		drvManager.AddDriver(&keyboard);

		MouseToConsole mousehandler;
		MouseDriver mouse(&interrupts, &mousehandler);
		drvManager.AddDriver(&mouse);

	printf("Initializing Hardware, stage 2!\n");
		drvManager.ActivateAll();

	printf("Initializing Hardware, stage 3!\n");
	interrupts.Activate();

	while(1);
}
