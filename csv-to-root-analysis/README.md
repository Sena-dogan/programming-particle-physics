# FIZ1117 - C++ and ROOT Histogram Assignment

## Related Resources

You can also find more particle physics programming resources at:
https://github.com/Sena-dogan/programming-particle-physics

This project contains the solution for the FIZ1117 assignment, which involves creating and drawing histograms using C++ and ROOT.

## Project Purpose

The project consists of two main programs:

1.  **`csv_to_root`**: This program reads a comma-separated value (CSV) file. It creates separate histograms for the `Energy_GeV`, `pT_GeV`, `Eta`, and `Phi` columns and saves them into a single ROOT file named `output.root`.

2.  **`draw_from_root`**: This program reads the `output.root` file, retrieves the histograms, and draws them in various styles as specified in the assignment (`default`, `errorbars`, `filled`, `logy`, `rebinned`, `normalized`), saving them as `.png` image files. It also prints the underflow and overflow counts for each histogram to the terminal.

## Compilation and Execution

To compile and run these programs, you must have the ROOT framework installed on your system.

### 1. Compilation

Run the following commands in your terminal to compile the C++ source files:

```sh
g++ csv_to_root.cpp -o csv_to_root `root-config --cflags --libs`
g++ draw_from_root.cpp -o draw_from_root `root-config --cflags --libs`
```

### 2. Execution

After compiling, run the following commands to execute the programs:

```sh
./csv_to_root data.csv
./draw_from_root output.root
```