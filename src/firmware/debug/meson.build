project(
	'msf_owl_clock',
	'cpp',
	version: '0.1.0',
	default_options: [
		'cpp_std=c++23',
		'warning_level=everything',
		'debug=true',
		'optimization=2',
		'default_library=static',
		'prefer_static=true'])

src_dir = 'src'
tests_dir = 'tests'
unit_tests_dir = tests_dir / 'unit'

kernel_dir = 'kernel'
kernel_baremetal_dir = kernel_dir / 'bare-metal'
kernel_crt_dir = kernel_dir / 'crt'
kernel_crt_crt0_dir = kernel_crt_dir / 'crt0'
kernel_crt_crt0_linker_dir = kernel_crt_crt0_dir / 'linker'
kernel_crt_crt0_mcu_dir = kernel_crt_crt0_dir / 'mcu'
kernel_crt_crt0_mcu_st_dir = kernel_crt_crt0_mcu_dir / 'st'
kernel_crt_crt0_mcu_st_stm32_dir = kernel_crt_crt0_mcu_st_dir / 'stm32'
kernel_crt_crt0_mcu_st_stm32_stm32l432kc_dir = kernel_crt_crt0_mcu_st_stm32_dir / 'stm32l432kc'
kernel_crt_crt0_mcu_st_stm32_stm32l432kc_linker_dir = kernel_crt_crt0_mcu_st_stm32_stm32l432kc_dir / 'linker'
kernel_crt_picolibc_dir = kernel_crt_dir / 'picolibc'

app_dir = 'app'

extra_cpp_args = [] + meson.get_external_property('mcu_cpp_args', [])
add_global_arguments(extra_cpp_args, language: 'cpp')

if meson.is_cross_build()
	cpp_link_args = ['-nostartfiles']

	libkernel = library(
		'kernel',
		native: false,
		pic: false,
		sources: [
			src_dir / kernel_dir / '_entrypoint.cc'])

	libcrt = library(
		'crt',
		native: false,
		pic: false,
		sources: [
			src_dir / kernel_crt_picolibc_dir / '_exit.cc',
			src_dir / kernel_crt_picolibc_dir / 'abort.cc',
			src_dir / kernel_crt_picolibc_dir / 'atexit.cc',
			src_dir / kernel_crt_picolibc_dir / 'sbrk.cc'])

	libcrt0 = library(
		'crt0',
		native: false,
		pic: false,
		sources: meson.get_external_property('libcrt0_mcu_srcfiles', native: false))

	# TODO: We really need to create something self-contained for the kernel, with all of the libgcc / libc++ support code.  Otherwise we cannot
	# separate the kernel's .init from the app's .init, and also a bootloader would not function because some of the libc++ code the kernel depended
	# upon could be in the app.  Something like a relocatable object file for the kernel ought to work, but the linker scripts will need rewriting to
	# use 'libsmeg.o: * ( .text* )' style rules to ensure the kernel is placed correctly.  Creating a relocatable object file with the custom toolchain
	# that contains everything the kernel needs ought to be as simple as 'g++ -Wl,-r libcrt0.a libcrt.a libkernel.a -o libsmeg.o'

	msf_owl_clock_elf = executable(
		'msf-owl-clock.elf',
		native: false,
		link_whole: [libcrt0, libcrt],
		link_with: [libkernel],
		link_depends: [meson.get_external_property('linker_script', native: false)],
		link_args: ['-nostartfiles', '-T' + meson.project_source_root() / meson.get_external_property('linker_script', native: false)],
		sources: [
			src_dir / app_dir / 'blinky-blinky.cc'],
		include_directories: [
			src_dir
		])

	objcopy = find_program('objcopy').full_path()
	custom_target(
		'msf-owl-clock.hex',
		command: [objcopy, '-j', '.code.flash.*', '-O', 'ihex', '@INPUT@', '@OUTPUT@'],
		input: [msf_owl_clock_elf],
		output: 'msf-owl-clock.hex',
		depends: [msf_owl_clock_elf],
		build_by_default: true)

	custom_target(
		'msf-owl-clock.bin',
		command: [objcopy, '-j', '.code.flash.*', '-O', 'binary', '@INPUT@', '@OUTPUT@'],
		input: [msf_owl_clock_elf],
		output: 'msf-owl-clock.bin',
		depends: [msf_owl_clock_elf],
		build_by_default: true)
else
	mettle = find_program('mettle')
	libmettle = dependency('mettle')

	kernel_unit_tests = executable(
		'kernel_unit_tests',
		native: true,
		dependencies: [libmettle],
		sources: [
			unit_tests_dir / 'mettle.cc',
			unit_tests_dir / 'NonDeterminism.cc',
			unit_tests_dir / kernel_dir / 'ChainedFinalisationTest.cc',
			unit_tests_dir / kernel_dir / 'ChainedInitialisationTest.cc',
			unit_tests_dir / kernel_dir / 'ConstInitialisableTest.cc',
			unit_tests_dir / kernel_dir / 'InitialisableTest.cc',
			unit_tests_dir / kernel_dir / 'NonConstInitialisableTest.cc',
			unit_tests_dir / kernel_baremetal_dir / 'IntegerSequenceTest.cc',
			unit_tests_dir / kernel_baremetal_dir / 'OffsetIntegerSequenceTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerBssMemorySectionTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerDataMemorySectionTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerFiniArraySectionTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerInitArraySectionTest.cc'
		],
		include_directories: [
			src_dir
		])

	test('kernel_unit_tests', mettle, args: [kernel_unit_tests])

	app_unit_tests_dir = unit_tests_dir / 'app'
	app_unit_tests = executable(
		'app_unit_tests',
		native: true,
		dependencies: [libmettle],
		sources: [
			unit_tests_dir / 'mettle.cc',
			app_unit_tests_dir / 'NoddyAppTest.cc'
		],
		include_directories: [
			src_dir
		])

	test('app_unit_tests', mettle, args: [app_unit_tests])
endif
