/* Copyright (c) 2008-2019 the MRtrix3 contributors.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Covered Software is provided under this License on an "as is"
 * basis, without warranty of any kind, either expressed, implied, or
 * statutory, including, without limitation, warranties that the
 * Covered Software is free of defects, merchantable, fit for a
 * particular purpose or non-infringing.
 * See the Mozilla Public License v. 2.0 for more details.
 *
 * For more details, see http://www.mrtrix.org/.
 */

#include "command.h"
#include "image.h"
#include "stride.h"
#include "transform.h"
#include "algo/threaded_loop.h"


using namespace MR;
using namespace App;

void usage ()
{
  AUTHOR = "J-Donald Tournier (jdtournier@gmail.com)";

  SYNOPSIS = "Create an initial warp image, representing an identity transformation";

  DESCRIPTION
  + "This is useful to obtain the warp fields from other normalisation "
    "applications, by applying the transformation of interest to the "
    "warp field generated by this program."

  + "The image generated is a 4D image with the same spatial characteristics as "
    "the input template image. It contains 3 volumes, with each voxel containing "
    "its own x,y,z coordinates."

  + "Note that this command can be used to create 3 separate X,Y,Z images "
    "directly (which may be useful to create images suitable for use in the "
    "registration program) using the following syntax:"

  + "  $ warpinit template.mif warp-[].nii";

  ARGUMENTS
  + Argument ("template", "the input template image.").type_image_in ()
  + Argument ("warp", "the output warp image.").type_image_out ();
}


void run ()
{
  auto header = Header::open (argument[0]);

  header.datatype() = DataType::Float32;
  header.ndim() = 4;
  header.size(3) = 3;
  Stride::set (header, Stride::contiguous_along_axis (3, header));

  auto warp = Image<float>::create(argument[1], header);

  Transform transform (header);

  auto func = [&transform](Image<float>& image) {
    Eigen::Vector3 voxel_pos ((float)image.index(0), (float)image.index(1), (float)image.index(2));
    Eigen::Vector3f scanner_pos = (transform.voxel2scanner * voxel_pos).cast<float>();
    for (auto l = Loop (3) (image); l; ++l)
      image.value() = scanner_pos[image.index(3)];
  };

  ThreadedLoop ("generating identity warp", warp, 0, 3)
    .run (func, warp);
}
