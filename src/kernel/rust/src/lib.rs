#![no_std]
#![feature(lang_items)]

const CONSOLE_TEXT_PTR: *mut [u8;2] = 0xb8000 as *mut [u8;2];
const CONSOLE_TEXT_WIDTH: usize = 80;
const CONSOLE_TEXT_HEIGTH: usize = 25;

#[no_mangle]
pub extern "C" fn kernel_main()
{
	let mut con = unsafe { core::slice::from_raw_parts_mut(CONSOLE_TEXT_PTR,CONSOLE_TEXT_WIDTH*CONSOLE_TEXT_HEIGTH) };

	for mut arr in con.iter_mut()
	{
		arr[0] = ' ' as u8;
		arr[1] = 10;
	}

	for (i,ch) in "System running!".chars().map(|ch|ch as u8).enumerate()
	{
		if let Some(dat) = con.get_mut(i)
		{
			dat[0] = ch;
		}
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

