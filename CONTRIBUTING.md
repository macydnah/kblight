# Contributing

Thank you for investing your time in contributing to this project 🥳🤙! Any contribution you make will be appreciated.

For some laptops the keyboard backlight works out-of-the-box, as the backlight may be managed directly by the hardware firmware, BIOS or UEFI. Some don't do it this way. If yours doesn't work out-of-the-box may be that the keyboard backlight state is reported as an acpi event, meaning it needs to be managed through the Linux kernel `ACPI` subsystem.

At this moment the focus will be on supporting laptops that have it's driver documentation present in the [Linux kernel source tree](https://github.com/torvalds/linux/tree/master/Documentation/admin-guide/laptops). Id est:

* Asus
* LG
* Sony
* ThinkPad

Nevertheless, you're encouraged to make contributions supporting other laptops as well. As I don't personally own other laptop hardware but a VAIO laptop, it's easier and more affordable to read the documentation and then understand the structure and tree location of the device controller files exposed by different laptop drivers —at least in theory— rather than try to guess them.

Different driver means different `kobjects` —like the device controller file ones— exposed through the `sysfs` pseudo-filesystem. In the specific case of VAIO laptops, the linux kernel `sony-laptop` driver exposes the `kbd_backlight` interface under the `/sys/devices/platform/sony-laptop/` tree.

## How to get my laptop supported

Either your laptop is or is not in the aforementioned list, you can help to get it supported. To do this please file an issue with the following information:

* Model of your laptop.
* Location of the device controller file that manages the keyboard backlight.
* The values that are valid to write on said device controller file.

Some possible locations for the device controller file may be:

* `/sys/class/leds/tpacpi::kbd_backlight/brightness`
* `/sys/devices/platform/sony-laptop/kbd_backlight` (On VAIO laptops)

For more insight on the `kbd_backlight` interface see [this](https://wiki.archlinux.org/title/keyboard_backlight).

## Coding style for C code

kblight follows the [Linux kernel coding style](https://www.kernel.org/doc/Documentation/process/coding-style.rst). Some specific rules to note are:

* Lines should not be longer than 80 characters in new code. If lines are longer than this the code could likely be improved by moving some parts to a smaller function.
* Avoid Yoda conditions.
* Avoid multiline if-statements without braces; either use a single line or add the braces.
* Use only C-style comments (`/* */`).
