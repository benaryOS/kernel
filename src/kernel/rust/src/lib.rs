#![no_std]

#![crate_name = "rust"]
#![crate_type = "lib"]

#![feature(lang_items)]

#[no_mangle]
pub extern "C" fn kernel_main() -> !
{
	loop
	{
	}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality()
{
}

#[lang = "panic_fmt"]
fn panic_fmt() -> !
{
	loop {}
}

