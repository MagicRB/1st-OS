// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include <stddef.h>
#include <stdint.h>
 
#include "vga/vga.h"
#include "pic/pic.h"

// This is our kernel's main function
void kernel_main()
{
	// We're here! Let's initiate the terminal and display a message to show we got here.
 
	// Initiate terminal
	term_init();
 
	// Display some messages
	term_print("Hello, World!\n");
	term_print("Just some random string.\n");

	pic_remap(0x20, 0x28);
}
