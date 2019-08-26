.. _ss3t_csd_beta1:

ss3t_csd_beta1
==============

Synopsis
--------

SS3T-CSD: beta 1 implementation

Usage
-----

::

    ss3t_csd_beta1 in_dMRI_data in_SFWM_resp out_WM_FOD in_GM_resp out_GM in_CSF_resp out_CSF [ options ]

-  *in_dMRI_data*: Input dMRI dataset
-  *in_SFWM_resp*: Input single-fibre WM response function text file
-  *out_WM_FOD*: Output WM FOD image
-  *in_GM_resp*: Input GM response function text file
-  *out_GM*: Output GM image
-  *in_CSF_resp*: Input CSF response function text file
-  *out_CSF*: Output CSF image

Description
-----------

This is an implementation of SS3T-CSD for beta testing and distribution. Use with caution and check all results carefully.

For more information on how to use SS3T-CSD, please visit https://3Tissue.github.io/doc/ss3t-csd.html

Options
-------

- **-mask** Only perform SS3T-CSD within a (brain) mask.

- **-niter** Number of iterations. (default: 3)

- **-bzero_pct** Weight b=0 images contribution as a percentage of the number of (non b=0) DWIs. (default: 10 per cent)

Additional standard options for Python scripts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **-nocleanup** do not delete intermediate files during script execution, and do not delete scratch directory at script completion.

- **-scratch /path/to/scratch/** manually specify the path in which to generate the scratch directory.

- **-continue <ScratchDir> <LastFile>** continue the script from a previous execution; must provide the scratch directory path, and the name of the last successfully-generated file.

Standard options
^^^^^^^^^^^^^^^^

- **-info** display information messages.

- **-quiet** do not display information messages or progress status. Alternatively, this can be achieved by setting the MRTRIX_QUIET environment variable to a non-empty string.

- **-debug** display debugging messages.

- **-force** force overwrite of output files.

- **-nthreads number** use this number of threads in multi-threaded applications (set to 0 to disable multi-threading).

- **-config key value**  *(multiple uses permitted)* temporarily set the value of an MRtrix config file entry.

- **-help** display this information page and exit.

- **-version** display version information and exit.

References
^^^^^^^^^^

* Dhollander, T. & Connelly, A. A novel iterative approach to reap the benefits of multi-tissue CSD from just single-shell (+b=0) diffusion MRI data. Proc Intl Soc Mag Reson Med, 2016, 3010

--------------



**Author:** Thijs Dhollander (thijs.dhollander@gmail.com)

**Copyright:** Copyright (c) 2019 Thijs Dhollander and The Florey Institute of Neuroscience and Mental Health, Melbourne, Australia. This Software is provided on an "as is" basis, without warranty of any kind, either expressed, implied, or statutory, including, without limitation, warranties that the Software is free of defects, merchantable, fit for a particular purpose or non-infringing.

