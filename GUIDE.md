### Guide for Setting Up Scattered Points Interpolation

To initiate this process and run the example provided, I will demonstrate using Windows Subsystem for Linux (WSL) on a Windows machine. If you haven't installed WSL yet, there are numerous well-documented tutorials available on YouTube; please refer to one of those for installation guidance.

#### 1. Installing Necessary Libraries

Begin by installing the required libraries using the following commands in WSL:

```bash
sudo apt install build-essential
sudo apt install cmake
sudo apt install git
sudo apt install unzip
sudo apt install libeigen3-dev
sudo apt install tclib tklib tcl-dev dk-dev libfreetype-dev libx11-dev libgl1-mesa-dev libfreeimage-dev xorg-dev libglu1-mesa-dev
```

Once installed, you can close the console.

#### 2. Setting Up the Environment

With the libraries installed, our system is now prepared for the project. Open a terminal in WSL and navigate to the folder containing the Scattered Points Interpolation.

```bash
cd /path/to/Scattered_Points_Interpolation
cd OCCT
```

Move to the `buildwsl` directory:

```bash
cd buildwsl
```

Remove any previous installations:

```bash
sudo rm ./* -R -v
```

#### 3. Building the OCCT Project

Now, let's build the OCCT project using CMake:

```bash
cmake ..
```

This process may take some time; please be patient. Upon completion, you should see a message like:

```
-- Generating done
-- Build files have been written to: /mnt/c/Users/flopezguerrero/Scattered_Points_Interpolation-master/OCCT/buildwsl
```

Now, proceed to build OCCT:

```bash
make -j18
```

This process may be lengthy.

#### 4. Building the Scattered Points Interpolation Project

Once OCCT is built, return to the folder of Scattered Point Interpolation:

```bash
cd ../..
cd buildwsl
```

Remove any previous content:

```bash
sudo rm ./* -R -v
```

Now, build the project along with the provided example (e.g., tiger):

```bash
cmake ..
make -j18
```

Upon completion, you should be able to run the example:

```bash
./example2_bin
```

You're all set to explore the Scattered Points Interpolation project!