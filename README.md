<div align="center">

# kblight
### A *light* keyboard back*light* utility

</div>

<p align="center" width="100%">
    <img width="77%" src="img/banner.gif">
</p>

##
<div align="center">

#### Command-line program for controlling the keyboard backlight on laptops running GNU/Linux.
<br />
</div>

<div align="justify">
	
Written in C, aims to be a minimalist and low-level solution that is simple to use and simple to code, following the UNIX "DOTADIW" philosophy. With this program the backlighting mode can be set to:

<br />

* An auto mode, so the backlight turns on as you type and turns off by timeout.
* An always on mode, for pretty dark environments such as midnight.
* An always off mode, for daytime and/or to save battery.

<br />

As it is a command-line program, it can be easily incorporated into other kinds of projects. You can use it the simple way through a terminal; bind it to a particular key of your preference; use it in scripts, cronjobs or timers; turn on/off the backlight depending on the time of the day, and under many other conditions. See [Examples of use](#examples-of-use).

**This project is a WIP**, at this stage only works on VAIO laptops. Please see [Contributing](#contributing) if you want to know how to have your laptop supported.

</div>

## How to use
```
Usage: kblight [ -a | -o | -f | -s ]

  Options:
  -a    Toggle between auto mode and always off mode. Default if no arguments.
  -o    Set always on mode.
  -f    Set always off mode.
  -s    Print the actual active mode to stdout.
```
Remember you need to use sudo with `-a`, `-o` and `-f` options. Also note that options are mutually exclusive.

## How to build & install

Clone this repository and change directory to the source tree:  
```
$ git clone https://github.com/macydnah/kblight
$ cd kblight
```

Then:
```
$ make
$ sudo make install
```

To uninstall:
```
$ sudo make uninstall
```

The default prefix for install/uninstall is `/usr/local`, you may change it to fit your needs editing the `PREFIX` variable inside the `Makefile`.


## Contributing

Thank you for investing your time in contributing to this project 🥳🤙! Any contribution you make will be appreciated. 

At this moment we will be focusing on supporting laptops that have it's driver documentation present in the [Linux kernel source tree](https://github.com/torvalds/linux/tree/master/Documentation/admin-guide/laptops).

See [CONTRIBUTING](CONTRIBUTING.md) for more details.

## License
kblight is licensed under the terms of the [GNU General Public License v3.0](LICENSE)

## Examples of use

<details>
<summary>
	
#### Command line
</summary>

```
[username@hostname ~]$ sudo kblight -a
```
```
[username@hostname ~]$ kblight -s
Actual active mode is: auto
```

</details>

<details>
<summary>

#### Turn on backlight with a Keyboard shortcut
</summary>

It's possible to execute `kblight` at the easiness of pressing a key —much more comfortable than typing commands—.

For this example, it's assumed that you're using `i3-wm` as your window manager, if you're not, please refer to your window manager or desktop environment documentation.

As a prerequisite, configure your system to run `sudo kblight` [without the need to enter sudo password](#run-without-entering-sudo-password).

Now make i3 execute it upon pressing a specific key —or key combination— adding something like these lines to your i3 config file (replace EXAMPLE_KEY to a key of your preference):
```
bindsym EXAMPLE_KEY exec --no-startup-id "sudo kblight"
bindsym Shift+EXAMPLE_KEY exec --no-startup-id "sudo kblight -o"
bindsym EXAMPLE_KEY+EXAMPLE_KEY exec --no-startup-id "sudo kblight -f"
```

If you would want some desktop notification, you could add something like this:
```
bindsym EXAMPLE_KEY\
	exec --no-startup-id "kblight",\
	exec --no-startup-id notify-send -e -t 1444 --icon=input-keyboard "Keyboard light" "$(kblight -s)"
```

This way you can toggle kblight auto mode and get a notification like this at the same time:

![notification-example](img/notification-example.png)
</details>

<details>

<summary>

#### Set auto mode at certain hours at login
</summary>

In this example, `auto` mode is set between 18 hours 'til 07 hours of the next day.

Add the following to your login shell profile, depending on the shell you're using, this file might be `~/.profile`, `~/.bash_profile`, `~/.zsh_profile`, among others:

```
# Turn off kbd_backlight if it's daytime or let them on if nighttime
if [ 10#$(date +%H) -gt 10#07 && 10#$(date +%H) -lt 18 ] ;
       then kblight -f ; kblight -f ;
       else kblight -f ; kblight -a ;
fi
```

</details>

<details>
	
<summary>
	
#### Run without entering sudo password 
</summary>

**Disclaimer:** Be aware that this process can be potentially dangerous **if doing it wrong**. Also remember that if you try this example it's **at your own**, so please do your own research and make sure you understand what you're doing before attempt it.

This is only necessary if you need to execute `kblight` in a way you can't —or don't want to— enter the sudo password at prompt (e.g. if you want to bind `kblight` to a [keyboard shortcut](#turn-on-backlight-with-a-keyboard-shortcut)).

First edit the `/etc/sudoers` file, this file is very sensible to syntax, so **be careful** and edit this file with `visudo` **only**:
```
[username@hostname ~]$ sudo -i
[sudo] password for username:
[root@hostnamme ~]# EDITOR=nano visudo
```
Then add this line to the end of the file —manually typing it if you want to be on the safe side— replacing user_name with your REAL username:
```
user_name ALL=(root) NOPASSWD: /usr/local/bin/kblight
```
Save the changes and close the editor. Now you're able to run `sudo kblight` with no need to enter sudo password.

</details>

## Further reading

[ACPI in Linux](https://www.kernel.org/doc/ols/2005/ols2005v1-pages-59-76.pdf)

[ACPI Support — The Linux Kernel firmware guide](https://www.kernel.org/doc/html/v5.2/firmware-guide/acpi/index.html)

[ACPI Custom Control Method — The Linux Kernel firmware guide](https://www.kernel.org/doc/html/v5.2/firmware-guide/acpi/method-customizing.html)

[Keyboard backlight - ArchWiki](https://wiki.archlinux.org/title/keyboard_backlight)

[Linux kernel coding style](https://www.kernel.org/doc/Documentation/process/coding-style.rst)

[Linux kernel Documentation — laptops](https://github.com/torvalds/linux/tree/master/Documentation/admin-guide/laptops)

[Sudo Example Entries - ArchWiki](https://wiki.archlinux.org/title/Sudo#Example_entries)

[sysfs - \_The\_ filesystem for exporting kernel objects — The Linux Kernel documentation](https://docs.kernel.org/filesystems/sysfs.html)
