/* TODO: A small RAM section (< 32 bytes ?) can be carved out for the kernel that is not initialised like BSS, so that software resets can persist state (ie. unhandled exceptions or NMIs) across resets for debugging or remedial action */
FLASH_SIZE_BYTES = 1024K;
SRAM_SIZE_BYTES = 256K;
BSRAM_SIZE_BYTES = 8K;
KERNEL_STACK_SIZE_WORDS = 128;

ENTRY(_resetHandler);

MEMORY {
	FLASH_INITIAL_SP (r) : ORIGIN = 0x00000000, LENGTH = 4

	FLASH_ISR_VECTORS (r) :
		ORIGIN = ORIGIN(FLASH_INITIAL_SP) + LENGTH(FLASH_INITIAL_SP),
		LENGTH = (15 + 137) * 4

	FLASH_TEXT (rx) :
		ORIGIN = ORIGIN(FLASH_ISR_VECTORS) + LENGTH(FLASH_ISR_VECTORS),
		LENGTH = FLASH_SIZE_BYTES - ORIGIN(FLASH_TEXT)

	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = SRAM_SIZE_BYTES

	BSRAM (rwx) : ORIGIN = 0x47000000, LENGTH = BSRAM_SIZE_BYTES
}

SECTIONS {
	.code.flash.kernel.isr_vector_table (READONLY) : {
		KEEP(*libcrt0.a: (.isr_vector_table.arm))
		KEEP(*libcrt0.a: (.isr_vector_table.mcu))
		ASSERT(
			(. - ADDR(.code.flash.kernel.isr_vector_table) == LENGTH(FLASH_ISR_VECTORS)),
			"The interrupt vector table must contain 15 ARM-defined vectors and 137 PIC32CX1025SG41100-specific vectors");
	} > FLASH_ISR_VECTORS

	.code.reserved.0 0x00100000 : { . += 0x700030; }
	.code.nvm.bocor 0x00800030 (READONLY) : { __linker_code_nvm_bocor = .; . += 4; }
	.code.reserved.1 0x00800034 : { . += 0x4c; }
	.code.nvm.sw0 0x00800080 (READONLY) : { __linker_code_nvm_sw0 = .; . += 8; }
	.code.reserved.2 0x00800088 : { . += 0x3f74; }
	.code.nvm.urow 0x00804000 (READONLY) : { __linker_code_nvm_urow = .; . += 512; }
	.code.reserved.3 0x00804200 : { . += 0x1e10; }
	.code.nvm.serial_number.1 0x00806010 (READONLY) : { __linker_code_nvm_serialNumber_1 = .; . += 4; }
	.code.nvm.serial_number.2 0x00806014 (READONLY) : { __linker_code_nvm_serialNumber_2 = .; . += 4; }
	.code.nvm.serial_number.3 0x00806018 (READONLY) : { __linker_code_nvm_serialNumber_3 = .; . += 4; }
	.code.reserved.4 0x0080601c : { . += 0x1e0; }
	.code.nvm.serial_number.0 0x008061fc (READONLY) : { __linker_code_nvm_serialNumber_0 = .; . += 4; }

	.code.cmcc 0x03000000 (READONLY) : { . += 0x01000000; }
	.code.qspi 0x04000000 (READONLY) : { . += 0x01000000; }
	.code.reserved.1 0x05000000 : { . += 0x1b000000; }

	.sram.data.retained32k.kernel : {
		. = ALIGN(4);
		__linker_sram_data_retained32k_kernel_start = .;
		*libcrt0.a: (.data.retained32k .data.retained32k*)
		*libcrt.a: (.data.retained32k .data.retained32k*)
		*libkernel.a: (.data.retained32k .data.retained32k*)
		. = ALIGN(4);
		__linker_sram_data_retained32k_kernel_pastEnd = .;
	} > SRAM AT> FLASH_TEXT

	.sram.bss.retained32k.kernel : {
		. = ALIGN(4);
		__linker_sram_bss_retained32k_kernel_start = .;
		*libcrt0.a: (.bss.retained32k .bss.retained32k*)
		*libcrt.a: (.bss.retained32k .bss.retained32k*)
		*libkernel.a: (.bss.retained32k .bss.retained32k*)
		. = ALIGN(4);
		__linker_sram_bss_retained32k_kernel_pastEnd = .;
	} > SRAM

	/* TODO: Kernel stack should probably be in the retained section if the rest of SRAM is switched off */

	.sram.data.retained32k.application : {
		. = ALIGN(4);
		__linker_sram_data_retained32k_application_start = .;
		* (.data.retained32k .data.retained32k*)
		. = ALIGN(4);
		__linker_sram_data_retained32k_application_pastEnd = .;
	} > SRAM AT> FLASH_TEXT

	.sram.bss.retained32k.application : {
		. = ALIGN(4);
		__linker_sram_bss_retained32k_application_start = .;
		* (.bss.retained32k .bss.retained32k*)
		. = ALIGN(4);
		__linker_sram_bss_retained32k_application_pastEnd = .;

		ASSERT(
			(__linker_sram_bss_retained32k_application_pastEnd <= ORIGIN(SRAM) + 32K),
			"The total sizeof(.data.retained32k.*) + sizeof(.bss.retained32k.*) is greater than 32KiB and so exceeds the amount of retained SRAM; if the entire SRAM is to be retained then use of these sections is un-necessary");
	} > SRAM

	.sram.data.kernel : {
		. = ALIGN(4);
		__linker_sram_data_kernel_start = .;
		*libcrt0.a: (.data .data*)
		*libcrt.a: (.data .data*)
		*libkernel.a: (.data .data*)
		. = ALIGN(4);
		__linker_sram_data_kernel_pastEnd = .;
	} > SRAM AT> FLASH_TEXT

	.sram.bss.kernel : {
		. = ALIGN(4);
		__linker_sram_bss_kernel_start = .;
		*libcrt0.a: (.bss .bss*)
		*libcrt.a: (.bss .bss*)
		*libkernel.a: (.bss .bss*)
		. = ALIGN(4);
		__linker_sram_bss_kernel_pastEnd = .;
	} > SRAM

	.sram.stack.kernel : {
		. = ALIGN(4);
		__linker_sram_stack_kernel_bottom = .;
		. += (KERNEL_STACK_SIZE_WORDS - 1) * 4;
		__linker_sram_stack_kernel_top = .;
		. += 4;
		__linker_sram_stack_kernel_pastTop = .;
	} > SRAM

	.sram.data.application : {
		. = ALIGN(4);
		__linker_sram_data_application_start = .;
		* (.data .data*)
		__linker_sram_data_application_pastEnd = .;
	} > SRAM AT> FLASH_TEXT

	.sram.bss.application : {
		. = ALIGN(4);
		__linker_sram_bss_application_start = .;
		* (.bss .bss*)
		. = ALIGN(4);
		__linker_sram_bss_application_pastEnd = .;
	} > SRAM

	.bsram.bss.kernel : {
		. = ALIGN(4);
		__linker_bsram_bss_kernel_start = .;
		*libcrt0.a: (.bss.backup .bss.backup*)
		*libcrt.a: (.bss.backup .bss.backup*)
		*libkernel.a: (.bss.backup .bss.backup*)
		. = ALIGN(4);
		__linker_bsram_bss_kernel_pastEnd = .;
	} > BSRAM

	.bsram.bss.application : {
		. = ALIGN(4);
		__linker_bsram_bss_application_start = .;
		* (.bss.backup .bss.backup*)
		. = ALIGN(4);
		__linker_bsram_bss_application_pastEnd = .;
	} > BSRAM

	.code.flash.kernel.init_array (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_kernel_initArray_start = .;
		KEEP(*libcrt0.a: (.init_array))
		KEEP(*libcrt0.a: (SORT_BY_INIT_PRIORITY(.init_array*)))
		KEEP(*libcrt.a: (.init_array))
		KEEP(*libcrt.a: (SORT_BY_INIT_PRIORITY(.init_array*)))
		KEEP(*libkernel.a: (.init_array))
		KEEP(*libkernel.a: (SORT_BY_INIT_PRIORITY(.init_array*)))
		__linker_code_flash_kernel_initArray_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.kernel.fini_array (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_kernel_finiArray_start = .;
		KEEP(*libcrt0.a: (.fini_array))
		KEEP(*libcrt0.a: (SORT_BY_INIT_PRIORITY(.fini_array*)))
		KEEP(*libcrt.a: (.fini_array))
		KEEP(*libcrt.a: (SORT_BY_INIT_PRIORITY(.fini_array*)))
		KEEP(*libkernel.a: (.fini_array))
		KEEP(*libkernel.a: (SORT_BY_INIT_PRIORITY(.fini_array*)))
		__linker_code_flash_kernel_finiArray_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.kernel.rodata (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_kernel_rodata_start = .;
		*libcrt0.a: (.rodata .rodata*)
		*libcrt.a: (.rodata .rodata*)
		*libkernel.a: (.rodata .rodata*)
		__linker_code_flash_kernel_rodata_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.kernel.text (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_kernel_text_start = .;
		*libcrt0.a: (.text .text*)
		*libcrt.a: (.text .text*)
		*libkernel.a: (.text .text*)
		__linker_code_flash_kernel_text_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.kernel.text (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_kernel_text_start = .;
		*libcrt0.a: (.text .text*)
		*libcrt.a: (.text .text*)
		*libkernel.a: (.text .text*)
		__linker_code_flash_kernel_text_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.kernel.extab (READONLY) : {
		. = ALIGN(4);
		KEEP(*libcrt0.a: (.ARM.extab .ARM.extab*))
		KEEP(*libcrt.a: (.ARM.extab .ARM.extab*))
		KEEP(*libkernel.a: (.ARM.extab .ARM.extab*))
	} > FLASH_TEXT

	.code.flash.shared.exidx (READONLY) : {
		. = ALIGN(4);
		__exidx_start = .;
		__linker_code_flash_shared_exidx_kernel_start = .;
		KEEP(*libcrt0.a: (.ARM.exidx .ARM.exidx*))
		KEEP(*libcrt.a: (.ARM.exidx .ARM.exidx*))
		KEEP(*libkernel.a: (.ARM.exidx .ARM.exidx*))
		__linker_code_flash_shared_exidx_kernel_pastEnd = .;
		KEEP(* (.ARM.exidx .ARM.exidx*))
		__linker_code_flash_shared_exidx_application_pastEnd = .;
		__exidx_end = .;
	} > FLASH_TEXT

	.code.flash.application.extab (READONLY) : {
		. = ALIGN(4);
		KEEP(* (.ARM.extab .ARM.extab*))
	} > FLASH_TEXT

	.code.flash.application.init_array (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_application_initArray_start = .;
		KEEP(* (.init_array))
		KEEP(* (SORT_BY_INIT_PRIORITY(.init_array*)))
		__linker_code_flash_application_initArray_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.application.fini_array (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_application_finiArray_start = .;
		KEEP(* (.fini_array))
		KEEP(* (SORT_BY_INIT_PRIORITY(.fini_array*)))
		__linker_code_flash_application_finiArray_pastEnd = .;

		ASSERT(
			(. - __linker_code_flash_application_finiArray_start == 0),
			"Finalisers are not supported / will not be executed by the firmware");
	} > FLASH_TEXT

	.code.flash.application.rodata (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_application_rodata_start = .;
		* (.rodata .rodata*)
		__linker_code_flash_application_rodata_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.application.text (READONLY) : {
		. = ALIGN(4);
		__linker_code_flash_application_text_start = .;
		* (.text .text*)
		__linker_code_flash_application_text_pastEnd = .;
	} > FLASH_TEXT

	.code.flash.initial_stack_pointer (READONLY) : {
		__linker_code_flash_initialStackPointer = .;
		LONG(__linker_sram_stack_kernel_top);
	} > FLASH_INITIAL_SP

	.undefined.0 0x20040000 : { . += 0x1ffc0000; }

	.peripherals.ahb_apb.apba.pac 0x40000000 : { __linker_peripherals_ahbApb_apba_pac = .; . += 0x400; }
	.peripherals.ahb_apb.apba.pm 0x40000400 : { __linker_peripherals_ahbApb_apba_pm = .; . += 0x400; }
	.peripherals.ahb_apb.apba.mclk 0x40000800 : { __linker_peripherals_ahbApb_apba_mclk = .; . += 0x400; }
	.peripherals.ahb_apb.apba.rstc 0x40000c00 : { __linker_peripherals_ahbApb_apba_rstc = .; . += 0x400; }
	.peripherals.ahb_apb.apba.oscctrl 0x40001000 : { __linker_peripherals_ahbApb_apba_oscctrl = .; . += 0x400; }
	.peripherals.ahb_apb.apba.osc32kctrl 0x40001400 : { __linker_peripherals_ahbApb_apba_osc32kctrl = .; . += 0x400; }
	.peripherals.ahb_apb.apba.supc 0x40001800 : { __linker_peripherals_ahbApb_apba_supc = .; . += 0x400; }
	.peripherals.ahb_apb.apba.gclk 0x40001c00 : { __linker_peripherals_ahbApb_apba_gclk = .; . += 0x400; }
	.peripherals.ahb_apb.apba.wdt 0x40002000 : { __linker_peripherals_ahbApb_apba_wdt = .; . += 0x400; }
	.peripherals.ahb_apb.apba.rtc 0x40002400 : { __linker_peripherals_ahbApb_apba_rtc = .; . += 0x400; }
	.peripherals.ahb_apb.apba.eic 0x40002800 : { __linker_peripherals_ahbApb_apba_eic = .; . += 0x400; }
	.peripherals.ahb_apb.apba.freqm 0x40002c00 : { __linker_peripherals_ahbApb_apba_freqm = .; . += 0x400; }
	.peripherals.ahb_apb.apba.sercom0 0x40003000 : { __linker_peripherals_ahbApb_apba_sercom0 = .; . += 0x400; }
	.peripherals.ahb_apb.apba.sercom1 0x40003400 : { __linker_peripherals_ahbApb_apba_sercom1 = .; . += 0x400; }
	.peripherals.ahb_apb.apba.tc0 0x40003800 : { __linker_peripherals_ahbApb_apba_tc0 = .; . += 0x400; }
	.peripherals.ahb_apb.apba.tc1 0x40003c00 : { __linker_peripherals_ahbApb_apba_tc1 = .; . += 0x400; }
	.peripherals.ahb_apb.apba.reserved.0 0x40004000 : { . += 0x400; }

	.peripherals.ahb_apb.apbb.usb 0x41000000 : { __linker_peripherals_ahbApb_apbb_usb = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.dsu 0x41002000 : { __linker_peripherals_ahbApb_apbb_dsu = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.nvmctrl 0x41004000 : { __linker_peripherals_ahbApb_apbb_nvmctrl = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.cmcc 0x41006000 : { __linker_peripherals_ahbApb_apbb_cmcc = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.port 0x41008000 : { __linker_peripherals_ahbApb_apbb_port = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.dmac 0x4100a000 : { __linker_peripherals_ahbApb_apbb_dmac = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.reserved.0 0x4100c000 : { . += 0x2000; }
	.peripherals.ahb_apb.apbb.evsys 0x4100e000 : { __linker_peripherals_ahbApb_apbb_evsys = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.reserved.1 0x41010000 : { . += 0x2000; }
	.peripherals.ahb_apb.apbb.sercom2 0x41012000 : { __linker_peripherals_ahbApb_apbb_sercom2 = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.sercom3 0x41014000 : { __linker_peripherals_ahbApb_apbb_sercom3 = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.tcc0 0x41016000 : { __linker_peripherals_ahbApb_apbb_tcc0 = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.tcc1 0x41018000 : { __linker_peripherals_ahbApb_apbb_tcc1 = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.tc2 0x4101a000 : { __linker_peripherals_ahbApb_apbb_tc2 = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.tc3 0x4101c000 : { __linker_peripherals_ahbApb_apbb_tc3 = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.reserved.2 0x4101e000 : { . += 0x2000; }
	.peripherals.ahb_apb.apbb.ramecc 0x41020000 : { __linker_peripherals_ahbApb_apbb_ramecc = .; . += 0x2000; }
	.peripherals.ahb_apb.apbb.reserved.3 0x41022000 : { . += 0x2000; }

	.peripherals.ahb_apb.apbc.can0 0x42000000 : { __linker_peripherals_ahbApb_apbc_can0 = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.can1 0x42000400 : { __linker_peripherals_ahbApb_apbc_can1 = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.gmac 0x42000800 : { __linker_peripherals_ahbApb_apbc_gmac = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.tcc2 0x42000c00 : { __linker_peripherals_ahbApb_apbc_tcc2 = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.tcc3 0x42001000 : { __linker_peripherals_ahbApb_apbc_tcc3 = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.tc4 0x42001400 : { __linker_peripherals_ahbApb_apbc_tc4 = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.tc5 0x42001800 : { __linker_peripherals_ahbApb_apbc_tc5 = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.pdec 0x42001c00 : { __linker_peripherals_ahbApb_apbc_pdec = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.ac 0x42002000 : { __linker_peripherals_ahbApb_apbc_ac = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.aes 0x42002400 : { __linker_peripherals_ahbApb_apbc_aes = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.trng 0x42002800 : { __linker_peripherals_ahbApb_apbc_trng = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.icm 0x42002c00 : { __linker_peripherals_ahbApb_apbc_icm = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.pukcc 0x42003000 : { __linker_peripherals_ahbApb_apbc_pukcc = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.qspi 0x42003400 : { __linker_peripherals_ahbApb_apbc_qspi = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.ccl 0x42003800 : { __linker_peripherals_ahbApb_apbc_ccl = .; . += 0x400; }
	.peripherals.ahb_apb.apbc.reserved.0 0x42003c00 : { . += 0x400; }

	.peripherals.ahb_apb.apbd.sercom4 0x43000000 : { __linker_peripherals_ahbApb_apbd_sercom4 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.sercom5 0x43000400 : { __linker_peripherals_ahbApb_apbd_sercom5 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.sercom6 0x43000800 : { __linker_peripherals_ahbApb_apbd_sercom6 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.sercom7 0x43000c00 : { __linker_peripherals_ahbApb_apbd_sercom7 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.tcc4 0x43001000 : { __linker_peripherals_ahbApb_apbd_tcc4 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.tc6 0x43001400 : { __linker_peripherals_ahbApb_apbd_tc6 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.tc7 0x43001800 : { __linker_peripherals_ahbApb_apbd_tc7 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.adc0 0x43001c00 : { __linker_peripherals_ahbApb_apbd_adc0 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.adc1 0x43002000 : { __linker_peripherals_ahbApb_apbd_adc1 = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.dac 0x43002400 : { __linker_peripherals_ahbApb_apbd_dac = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.i2s 0x43002800 : { __linker_peripherals_ahbApb_apbd_i2s = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.pcc 0x43002c00 : { __linker_peripherals_ahbApb_apbd_pcc = .; . += 0x400; }
	.peripherals.ahb_apb.apbd.reserved.0 0x43003000 : { . += 0x400; }

	.peripherals.ahb_apb.seeprom 0x44000000 : { __linker_peripherals_ahbApb_seeprom = .; . += 0x1000000; }
	.peripherals.ahb_apb.sdhc0 0x45000000 : { __linker_peripherals_ahbApb_sdhc0 = .; . += 0x1000000; }
	.peripherals.ahb_apb.sdhc1 0x46000000 : { __linker_peripherals_ahbApb_sdhc1 = .; . += 0x1000000; }

	.reserved.0 0x48000000 : { . += 0x98000000; }

	.system.reserved.0 0xe0000000 : { . += 0xe000; }
	.system.scs 0xe000e000 : { __linker_system_scs = .; . += 0x1000; }
	.system.reserved.1 0xe000f000 : { . += 0xf0000; }
	.system.rom_table 0xe00ff000 : { __linker_system_romTable = .; . += 0x1000; }
	.system.reserved.2 0xe0100000 : { . += 0x1ff00000; }

	.ARM.attributes 0 (READONLY) : { KEEP(* (.ARM.attributes)) }
	.comment 0 (READONLY) : { KEEP(* (.comment)) }
	.debug_abbrev 0 (READONLY) : { KEEP(* (.debug_abbrev)) }
	.debug_aranges 0 (READONLY) : { KEEP(* (.debug_aranges)) }
	.debug_frame 0 (READONLY) : { KEEP(* (.debug_frame)) }
	.debug_info 0 (READONLY) : { KEEP(* (.debug_info)) }
	.debug_line 0 (READONLY) : { KEEP(* (.debug_line)) }
	.debug_str 0 (READONLY) : { KEEP(* (.debug_str)) }

	/DISCARD/ : { * (*) }
}
