#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)


#define ICW1_ICW4	0x01
#define ICW1_INIT	0x10		/* ICW4 (not) needed */
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */

#include <io/io.h>

void pic_remap(int master_offset, int slave_offset)
{
	unsigned char m1 = inb(PIC2_DATA);
	unsigned char m2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);	// Start initialization on both PICs
	outb(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);

	outb(PIC1_DATA, master_offset); 		// Tell each PIC it's offset
	outb(PIC2_DATA, slave_offset);

	outb(PIC1_DATA, 4);				// Tell the master PIC where slave PIC is connected (IRQ2)
	outb(PIC2_DATA, 2);				// Tell slave PIC it's cascade identity (0000 0010)

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, m1);
	outb(PIC2_DATA, m2);
}
