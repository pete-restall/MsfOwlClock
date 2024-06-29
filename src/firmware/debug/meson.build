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

kernel_dir = 'kernel'
kernel_crt_dir = kernel_dir / 'crt'
kernel_crt_crt0_dir = kernel_crt_dir / 'crt0'
kernel_crt_crt0_linker_dir = kernel_crt_crt0_dir / 'linker'
kernel_crt_crt0_mcu_dir = kernel_crt_crt0_dir / 'mcu'
kernel_crt_crt0_mcu_st_dir = kernel_crt_crt0_mcu_dir / 'st'
kernel_crt_crt0_mcu_st_stm32_dir = kernel_crt_crt0_mcu_st_dir / 'stm32'
kernel_crt_crt0_mcu_st_stm32_stm32l432kc_dir = kernel_crt_crt0_mcu_st_stm32_dir / 'stm32l432kc'
kernel_crt_crt0_mcu_st_stm32_stm32l432kc_linker_dir = kernel_crt_crt0_mcu_st_stm32_stm32l432kc_dir / 'linker'

app_dir = 'app'

src_dir = 'src'
libkernel_srcdir = meson.get_external_property('libkernel_srcdir', src_dir / kernel_dir)
libcrt_srcdir = meson.get_external_property('libcrt_srcdir', src_dir / kernel_crt_dir)
libcrt0_srcdir = meson.get_external_property('libcrt0_srcdir', src_dir / kernel_crt_crt0_dir)
app_srcdir = meson.get_external_property('app_srcdir', src_dir / app_dir)

if meson.is_cross_build()
	cpp_link_args = ['-nostartfiles']

	libkernel = library(
		'kernel',
		native: false,
		sources: [
			libkernel_srcdir / '_entrypoint.cc',
			libkernel_srcdir / 'whatever.cc'])

	libcrt = library(
		'crt',
		native: false,
		sources: [
			libcrt_srcdir / '_exit.cc',
			libcrt_srcdir / 'abort.cc'])

	libcrt0 = library(
		'crt0',
		native: false,
		sources: meson.get_external_property('libcrt0_mcu_srcfiles', native: false))

	msf_owl_clock_elf = executable(
		'msf-owl-clock.elf',
		native: false,
		link_whole: [libcrt0, libcrt],
		link_with: [libkernel],
		link_depends: [meson.get_external_property('linker_script', native: false)],
		link_args: ['-nostartfiles', '-T' + meson.project_source_root() / meson.get_external_property('linker_script', native: false)],
		sources: [
			app_srcdir / 'blinky-blinky.cc'],
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

	unit_tests_dir = 'tests/unit'

	kernel_unit_tests = executable(
		'kernel_unit_tests',
		native: true,
		dependencies: [libmettle],
		sources: [
			unit_tests_dir / 'mettle.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerAppFiniArrayTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerAppInitArrayTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerKernelFiniArrayTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerKernelInitArrayTest.cc',
			unit_tests_dir / kernel_crt_crt0_mcu_st_stm32_stm32l432kc_linker_dir / 'LinkerAppSramBssTest.cc',
			unit_tests_dir / kernel_crt_crt0_mcu_st_stm32_stm32l432kc_linker_dir / 'LinkerKernelSramBssTest.cc',
			unit_tests_dir / kernel_crt_crt0_mcu_st_stm32_stm32l432kc_linker_dir / 'LinkerAppSramRetained16kBssTest.cc',
			unit_tests_dir / kernel_crt_crt0_mcu_st_stm32_stm32l432kc_linker_dir / 'LinkerKernelSramRetained16kBssTest.cc'
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
