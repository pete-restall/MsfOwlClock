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
mcu_dir = meson.get_external_property('mcu_dir', 'error-undefined-mcu')

kernel_dir = 'kernel'
kernel_baremetal_dir = kernel_dir / 'bare-metal'
kernel_config_dir = kernel_dir / 'config'
kernel_crt_dir = kernel_dir / 'crt'
kernel_crt_crt0_dir = kernel_crt_dir / 'crt0'
kernel_crt_crt0_linker_dir = kernel_crt_crt0_dir / 'linker'
kernel_crt_crt0_mcu_dir = kernel_crt_crt0_dir / 'mcu'
kernel_crt_crt0_mcu_st_dir = kernel_crt_crt0_mcu_dir / 'st'
kernel_crt_picolibc_dir = kernel_crt_dir / 'picolibc'
kernel_drivers_dir = kernel_dir / 'drivers'
kernel_drivers_config_dir = kernel_drivers_dir / 'config'
kernel_drivers_kernel_dir = kernel_drivers_dir / 'kernel'
kernel_drivers_peripherals_dir = kernel_drivers_dir / 'peripherals'
kernel_integer_sequences_dir = kernel_dir / 'integer-sequences'
kernel_tasks_dir = kernel_dir / 'tasks'
kernel_tasks_config_dir = kernel_tasks_dir / 'config'
kernel_tasks_config_stubs_dir = kernel_tasks_config_dir / 'stubs'
kernel_tuples_dir = kernel_dir / 'tuples'

app_sources_from_kernel = [
	src_dir / kernel_tasks_config_stubs_dir / 'app-task-stacks.cc'
]

app_dir = 'apps/debug'

disable_stdlib_warnings_cpp_args = [
	# Mixing libraries compiled with different ABIs, so irrelevant to us (mainly an issue marshalling std::string across library calls)
	'-Wno-abi-tag' # 'T1' does not have the "cxx11" ABI tag that 'T2'
]

disable_metaprogramming_false_positives_cpp_args = [
	'-Wno-ctor-dtor-privacy', # all member functions in class 'T' are private
	'-Wno-unused-local-typedefs' # typedef 'T' locally defined but not used
]

disable_stylistic_warnings_cpp_args = [
	'-Wno-shadow' # declaration of 'X' shadows a member of 'T'
]

# TODO: Disable the 'noexcept' warnings for the tests, otherwise std::abort() is called on failure and that doesn't allow source / line numbers, etc.
# TODO: We will tolerate these warnings for now but they need looking into...
todo_look_into_these_warnings_cpp_args = [
	# TODO: The strict overflow is useful but std::sort() causes it; look into why / use a local pragma if necessary
	'-Wno-strict-overflow' # assuming signed overflow does not occur when changing X +- C1 cmp C2 to X cmp C2 -+ C1
]

global_disable_warnings_cpp_args = disable_stdlib_warnings_cpp_args + disable_metaprogramming_false_positives_cpp_args + disable_stylistic_warnings_cpp_args
test_disable_warnings_cpp_args = []

extra_cpp_args = global_disable_warnings_cpp_args + meson.get_external_property('mcu_cpp_args', [])
add_global_arguments(extra_cpp_args, language: 'cpp', native: true)
add_global_arguments(extra_cpp_args, language: 'cpp', native: false)

if meson.is_cross_build()
	cpp_link_args = ['-nostartfiles']

	libkernel = library(
		'kernel',
		native: false,
		pic: false,
		sources: [
			src_dir / kernel_dir / '_entrypoint.cc',
			src_dir / kernel_tasks_config_stubs_dir / 'kernel-task-stacks.cc',

			# TODO: The drivers ought to have their own libdrv-XXX.a, built using Meson sub-projects.  Should also give them their own 'src' and 'tests'
			# directories so that they are entirely self-contained, drop-in source libraries.  This is a temporary hack:
			src_dir / kernel_drivers_kernel_dir / 'syscall/mcu/arm/cortex/m4/SvcallIsr.cc'
		],
		include_directories: [
			src_dir
		])

	libcrt = library(
		'crt',
		native: false,
		pic: false,
		sources: [
			src_dir / kernel_crt_picolibc_dir / '_exit.cc',
			src_dir / kernel_crt_picolibc_dir / 'abort.cc',
			src_dir / kernel_crt_picolibc_dir / 'atexit.cc',
			src_dir / kernel_crt_picolibc_dir / 'sbrk.cc'
		],
		include_directories: [
			src_dir
		])

	libcrt0 = library(
		'crt0',
		native: false,
		pic: false,
		sources: meson.get_external_property('libcrt0_mcu_srcfiles', native: false),
		include_directories: [
			src_dir
		])

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
			src_dir / app_dir / 'NopTask.cc'
		] + app_sources_from_kernel,
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
		cpp_args: test_disable_warnings_cpp_args,
		dependencies: [libmettle],
		sources: [
			unit_tests_dir / 'mettle.cc',
			unit_tests_dir / 'NonDeterminism.cc',
			unit_tests_dir / kernel_dir / 'ChainedFinalisationTest.cc',
			unit_tests_dir / kernel_dir / 'ChainedInitialisationTest.cc',
			unit_tests_dir / kernel_dir / 'ConstInitialisableTest.cc',
			unit_tests_dir / kernel_dir / 'InitialisableTest.cc',
			unit_tests_dir / kernel_dir / 'NonConstInitialisableTest.cc',
			unit_tests_dir / kernel_baremetal_dir / 'BitfieldTraitsTest.cc',
			unit_tests_dir / kernel_baremetal_dir / 'BitmaskTest.cc',
			unit_tests_dir / kernel_baremetal_dir / 'IntegerSequenceTest.cc',
			unit_tests_dir / kernel_baremetal_dir / 'OffsetIntegerSequenceTest.cc',
			unit_tests_dir / kernel_config_dir / 'IKernelConfigTest.cc',
			unit_tests_dir / kernel_config_dir / 'IHaveTupleOfKernelConfigsTest.cc',
			unit_tests_dir / kernel_config_dir / 'ITupleOfKernelConfigsTest.cc',
			unit_tests_dir / kernel_crt_dir / 'EntrypointTest.cc',
			unit_tests_dir / kernel_crt_crt0_dir / 'DefaultCrt0KernelConfigTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerBssMemorySectionTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerDataMemorySectionTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerFiniArraySectionTest.cc',
			unit_tests_dir / kernel_crt_crt0_linker_dir / 'LinkerInitArraySectionTest.cc',
			unit_tests_dir / kernel_drivers_dir / 'IIsrTest.cc',
			unit_tests_dir / kernel_drivers_dir / 'IsrApisTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'DriverConfigsFromTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IDriverConfigTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IHaveConfigForDriversTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IHaveConfigForProvidedApisTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IHaveConfigForProvidedIsrsTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IHaveConfigForProvidedSyscallsTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IProvidedApiConfigTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IProvidedIsrConfigTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IProvidedSyscallConfigTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'IsrOrDefaultByIrqFromTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'ITupleOfDriverConfigsTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'ITupleOfProvidedIsrConfigsTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'ITupleOfProvidedApiConfigsTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'ITupleOfProvidedSyscallConfigsTest.cc',
			unit_tests_dir / kernel_drivers_config_dir / 'ProvidedIsrConfigsFromTest.cc',
			unit_tests_dir / kernel_integer_sequences_dir / 'BubbleSortedTest.cc',
			unit_tests_dir / kernel_integer_sequences_dir / 'SortedSetTest.cc',
			unit_tests_dir / kernel_integer_sequences_dir / 'UniqueTest.cc',
			unit_tests_dir / kernel_integer_sequences_dir / 'UtilitiesTest.cc',
			unit_tests_dir / kernel_tasks_dir / 'AppToDriverApisTest.cc',
			unit_tests_dir / kernel_tasks_dir / 'DefaultTaskFactoryTest.cc',
			unit_tests_dir / kernel_tasks_dir / 'DriverToDriverApisTest.cc',
			unit_tests_dir / kernel_tasks_dir / 'DriverToKernelApisTest.cc',
			unit_tests_dir / kernel_tasks_dir / 'ITaskTest.cc',
			unit_tests_dir / kernel_tasks_dir / 'TaskLifecycleTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'RequiredApisFromTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'ResourceToTaskAssociationTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'TaskConfigsFromTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'TaskConfigToResourceAssociationTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'TasksFromTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'TaskStackConfigsFromTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'TaskStackConfigToRamBlockTest.cc',
			unit_tests_dir / kernel_tasks_config_dir / 'TaskStackRamBlockTest.cc',
			unit_tests_dir / kernel_tuples_dir / 'AsTupleTest.cc',
			unit_tests_dir / kernel_tuples_dir / 'TupleCatTest.cc',
			unit_tests_dir / kernel_tuples_dir / 'TupleIndexZipTest.cc',
			unit_tests_dir / kernel_tuples_dir / 'TupleProjectionTest.cc',
			unit_tests_dir / kernel_tuples_dir / 'UniqueTest.cc'
		],
		include_directories: [
			src_dir
		])

	test('kernel_unit_tests', mettle, args: [kernel_unit_tests])

	app_unit_tests_dir = unit_tests_dir / 'apps'
	app_unit_tests = executable(
		'app_unit_tests',
		native: true,
		cpp_args: test_disable_warnings_cpp_args,
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
