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

cpp_link_args = ['-nostartfiles']

libkernel_srcdir = meson.get_external_property('libkernel_srcdir', 'kernel')
libkernel = library(
	'kernel',
	sources: [
		libkernel_srcdir / '_entrypoint.cc',
		libkernel_srcdir / 'whatever.cc'])

libcrt_srcdir = meson.get_external_property('libcrt_srcdir', libkernel_srcdir / 'crt')
libcrt = library(
	'crt',
	sources: [
		libcrt_srcdir / '_exit.cc',
		libcrt_srcdir / 'abort.cc'])

libcrt0_srcdir = meson.get_external_property('libcrt0_srcdir', libcrt_srcdir / 'crt0')
libcrt0 = library(
	'crt0',
	sources: meson.get_external_property('libcrt0_mcu_srcfiles', native: false))

app_srcdir = meson.get_external_property('app_srcdir', '.')
msf_owl_clock_elf = executable(
	'msf-owl-clock.elf',
	link_whole: [libcrt0, libcrt],
	link_with: [libkernel],
	link_depends: [meson.get_external_property('linker_script', native: false)],
	link_args: ['-nostartfiles', '-T' + meson.project_source_root() / meson.get_external_property('linker_script', native: false)],
	sources: [
		app_srcdir / 'blinky-blinky.cc'])

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
