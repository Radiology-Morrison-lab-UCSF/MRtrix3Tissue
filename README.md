# MRtrix3Tissue

MRtrix3Tissue is a fork of the MRtrix3 project. It adds capabilities for 3-Tissue CSD modelling and analysis to a complete and up-to-date version of MRtrix3.

## Quick install

1. Install dependencies by whichever means your system uses. 
   These include: Python (>=2.6), a C++ compiler with full C++11 support (`g++` 4.9 or later, `clang++`), 
   Eigen (>=3.2.8), zlib, OpenGL (>=3.3), and Qt (>=4.8, or at least 5.1 on MacOSX).

2. Clone Git repository and compile:

        git clone https://github.com/3Tissue/MRtrix3Tissue.git MRtrix3Tissue

        cd MRtrix3Tissue

        ./configure

        ./build

3. Set the `PATH`:

    * Bash shell:

      run the `set_path` script provided:

            ./set_path

      or edit the startup `~/.bashrc` or `/etc/bash.bashrc` file manually by adding this line:

            export PATH=/<edit as appropriate>/MRtrix3Tissue/bin:$PATH

    * C shell:

      edit the startup `~/.cshrc` or `/etc/csh.cshrc` file manually by adding this line:

            setenv PATH /<edit as appropriate>/MRtrix3Tissue/bin:$PATH

4. Test installation:

    Command-line:

        mrinfo

    GUI:

        mrview

## Keeping MRtrix3Tissue up to date

1. You can update your installation at any time by opening a terminal in the MRtrix3Tissue folder, and typing:

        git pull

        ./build

2. If this doesn't work immediately, it may be that you need to re-run the configure script:

        ./configure

    and re-run step 1 again.

## Building a specific release of MRtrix3Tissue

You can build a particular release of MRtrix3Tissue by checking out the corresponding _tag_, and using the same procedure as above to build it:

    git checkout 3Tissue_v4.0.0

    ./configure

    ./build
