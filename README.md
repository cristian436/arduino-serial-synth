# Arduino Serial Synth

A simple synthesizer: notes are played by pressing keys on the **PC keyboard**. A Python script captures the key presses and sends them over **serial** to an Arduino, which generates the tone on a piezo through an **analog filter**.

## Key map
| Keys | Notes |
|---|---|
| `a s d f g h j k` | C4 – C5 (Do Re Mi Fa Sol La Si Do) |
| `w e t y u` | sharps (C# D# F# G# A#) |
| `z x c v b n m` | lower octave (C3 – B3) |
| `space` | stop |

## Hardware
- Arduino Uno / Nano
- Piezo buzzer on pin 13 → analog filter → output

## Usage
1. Flash the sketch.
2. Run the Python script on the PC and start playing.

## Roadmap
- [ ] Split the output into three speakers (bass / mid / treble) with a crossover based on frequency
- [ ] Record the notes played and loop them at a chosen BPM
- [ ] Save the recorded track to a file

## Photos
<!-- Add a photo of the circuit and the filter schematic here -->
