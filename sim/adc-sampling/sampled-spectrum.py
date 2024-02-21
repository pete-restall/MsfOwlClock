import sys
import math
import numpy as np
from numpy.fft import fft

#frequencies_hz = [2e3, 10e3, 12e3, 20e3, 52e3, 60e3, 100e3, 200e3, 2e6]
#magnitudes_db = [-77.7, -46.5, -43, -34, -9.8, 0, -22.5, -35.6, -80]
#frequencies_hz = [52e3, 68e3, 56e3] # @ 16kHz
#magnitudes_db = [-21.3, -29, -4]
#frequencies_hz = [52e3, 68e3] # @ 16kHz / 2 crystals
#magnitudes_db = [-64, -62]
#frequencies_hz = [52e3, 68e3] # @ 16kHz / 3 crystals
#magnitudes_db = [-88.5, -91]
#frequencies_hz = [36e3] # @ 48kHz
#magnitudes_db = [-59.3]
#frequencies_hz = [36e3] # @ 48kHz / ferrite rod antenna only
#magnitudes_db = [-79]
#frequencies_hz = [36e3, 68e3] # @ 48kHz / 2 crystals
#magnitudes_db = [-81, -62.8]
#frequencies_hz = [20e3] # @ 80kHz
#magnitudes_db = [-30]
#frequencies_hz = [20e3] # @ 80kHz / 2 crystals
#magnitudes_db = [-88]
#frequencies_hz = [20e3] # @ 80kHz / 3 crystals
#magnitudes_db = [-93.5]
#frequencies_hz = [100e3] # @ 80kHz
#magnitudes_db = [-63]
#frequencies_hz = [100e3] # @ 80kHz / 2 crystals
#magnitudes_db = [-64]
#frequencies_hz = [180e3, 240e3, 420e3, 900e3, 1.02e6] # @ 120kHz
#magnitudes_db = [-30.5, -33.5, -38.7, -45.5, -48]
frequencies_hz = [180e3] # @ 240kHz
magnitudes_db = [-84]
sampling_frequency_hz = int(240e3)
over_sampling_rate = 4
right_shift = 0
sampling_depth = math.log2(over_sampling_rate) // 2

frequencies = [2 * math.pi * x / (sampling_frequency_hz * over_sampling_rate) for x in frequencies_hz]
magnitudes = [10 ** (y / 20) for y in magnitudes_db]
samples = [0] * sampling_frequency_hz
for t in range(0, len(samples) * over_sampling_rate):
	i = t // over_sampling_rate
	for n in range(0, len(frequencies)):
		samples[i] += min(2**12 - 1, max(-2**12, round(magnitudes[n] * math.sin(frequencies[n] * t) * 2**12)))

	if t % over_sampling_rate == over_sampling_rate - 1:
		samples[i] = samples[i] // over_sampling_rate // 2**right_shift

fft_X = np.abs(fft(samples))
fft_frequencies_hz = np.arange(len(fft_X)) * sampling_frequency_hz / len(fft_X)

goertzel_f_hz = 60e3
goertzel_bin_width_hz = 24
goertzel_N = sampling_frequency_hz // goertzel_bin_width_hz
goertzel_k = int(goertzel_N * goertzel_f_hz / sampling_frequency_hz + 0.5)
goertzel_w = [np.float32(0), np.float32(0)]
goertzel_y = []
goertzel_coefficient = np.float32(2 * math.cos((2 * math.pi / goertzel_N) * goertzel_k))
goertzel_sample_offset = 0
for goertzel_sample_offset in range(0, len(samples), goertzel_N):
	for goertzel_n in range(0, goertzel_N):
		if goertzel_sample_offset + goertzel_n >= len(samples):
			break

		goertzel_temp = goertzel_w[0]
		goertzel_w[0] = samples[goertzel_sample_offset + goertzel_n] + goertzel_coefficient * goertzel_w[0] - goertzel_w[1]
		goertzel_w[1] = goertzel_temp

	goertzel_y += [goertzel_w[0]**2 + goertzel_w[1]**2 - (goertzel_coefficient * goertzel_w[0] * goertzel_w[1])]
	goertzel_w = [np.float32(0), np.float32(0)]

if len(sys.argv) > 1:
	if sys.argv[1] == "samples":
		print("t,sample")
		for t in range(0, len(samples)):
			print(f"{t / sampling_frequency_hz},{samples[t]}")

	elif sys.argv[1] == "fft":
		print("f_hz,mag")
		for i in range(0, len(fft_X) // 2):
			print(f"{fft_frequencies_hz[i]},{fft_X[i]}")

	elif sys.argv[1] == "goertzel":
		print("i,power")
		for i in range(0, len(goertzel_y)):
			print(f"{i},{goertzel_y[i]}")
