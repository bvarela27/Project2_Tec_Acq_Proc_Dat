import soundfile as sf

samples, _ = sf.read("audio.wav")

with open("samples.txt", "w") as file:
    for sample in samples:
        file.write(str(int(sample*(2**15)))+"\n")
