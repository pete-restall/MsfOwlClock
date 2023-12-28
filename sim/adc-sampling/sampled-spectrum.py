import sys
import math
import numpy as np
from numpy.fft import fft

#frequencies_hz = [2e3, 10e3, 12e3, 20e3, 52e3, 60e3, 100e3, 200e3, 2e6]
#magnitudes_db = [-77.7, -46.5, -43, -34, -9.8, 0, -22.5, -35.6, -80]
#frequencies_hz = [52e3] # @ 16kHz
#magnitudes_db = [-25]
#frequencies_hz = [52e3, 68e3] # @ 16kHz / 2 crystals
#magnitudes_db = [-64, -62]
frequencies_hz = [52e3, 68e3] # @ 16kHz / 3 crystals
magnitudes_db = [-88.5, -91]
#frequencies_hz = [36e3] # @ 48kHz
#magnitudes_db = [-38]
#frequencies_hz = [36e3, 68e3] # @ 48kHz / 2 crystals
#magnitudes_db = [-81, -62.8]
#frequencies_hz = [20e3] # @ 80kHz
#magnitudes_db = [-46]
#frequencies_hz = [20e3] # @ 80kHz / 2 crystals
#magnitudes_db = [-88]
#frequencies_hz = [20e3] # @ 80kHz / 3 crystals
#magnitudes_db = [-93.5]
#frequencies_hz = [180e3] # @ 80kHz
#magnitudes_db = [-39]
#frequencies_hz = [100e3] # @ 80kHz / 2 crystals
#magnitudes_db = [-64]
sampling_frequency_hz = int(16e3)
over_sampling_rate = 64 #16
right_shift = 3 #2
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

if len(sys.argv) > 1:
	if sys.argv[1] == "samples":
		print("t,sample")
		for t in range(0, len(samples)):
			print(f"{t / sampling_frequency_hz},{samples[t]}")

	elif sys.argv[1] == "fft":
		print("f_hz,mag")
for i in range(0, len(fft_X) // 2):
			print(f"{fft_frequencies_hz[i]},{fft_X[i]}")
