from  scipy.io import wavfile
import numpy as np

sampling_rate = 8000

with open("decoder_output.txt", "r") as file:
    lines = file.readlines()

samples = np.ndarray(len(lines), dtype=np.int16)

for i, sample in enumerate(lines):
    samples[i] = np.int16(sample)

wavfile.write("audio_after_comp_and_decomp.wav", sampling_rate, samples)



