# benaryOS

## What is it?

benaryOS is a operating system, developed by benaryorg.

It began as a rewrite of benarydingOS.

## Building it

benaryOS is using `make`:

	$ make

This will create a `kernel` file, in a `build`
directory, you can then boot from.

## Booting it

You can boot the kernel using the following options.

### QEMU

Just run `qemu -kernel kernel`.

### ISO

Soon there will be a way to create a `.iso`. For now
you can use the scripts provided by benarydingOS
(https://github.com/benaryorg/benarydingOS).

#### Virtualbox/VMWare

Just use the .iso to boot.

### Real Hardware

Either use grub (see the iso) or boot the iso from a USB/CDROM.

# License

benaryOS is using the GPL (http://www.gnu.org/licenses/).
See LICENSE file or file headers.
