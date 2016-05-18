# benaryOS

## What is it?

benaryOS is a operating system, developed by benaryorg.

This is a complete rewrite using Rust.

## Building it

[![Build Status](https://travis-ci.org/benaryOS/kernel.svg?branch=rewrite)]
(https://travis-ci.org/benaryOS/kernel)

benaryOS is using `make`:

```bash
$ make
```

This will create a `kernel` file you can then boot from.

## Booting it

The kernel is multiboot compliant.

### QEMU

Just run `qemu -kernel kernel`.
Or if you want the serial-output to be logged to
file.log run `qemu -kernel kernel -serial file:file.log`

On Unix you can also let it write to stdout and
read from stdin, by setting the `-serial` parameter to
`stdio`. This would then be `qemu -kernel kernel -serial stdio`.

# License

The rewrite is licensed using the MIT license.

