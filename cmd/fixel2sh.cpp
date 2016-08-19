/*
 * Copyright (c) 2008-2016 the MRtrix3 contributors
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/
 * 
 * MRtrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * For more details, see www.mrtrix.org
 * 
 */


#include "command.h"
#include "image.h"
#include "progressbar.h"

#include "algo/loop.h"

#include "math/SH.h"

#include "fixel_format/helpers.h"
#include "fixel_format/keys.h"

using namespace MR;
using namespace App;



void usage ()
{

  AUTHOR = "Robert E. Smith (robert.smith@florey.edu.au) & David Raffelt (david.raffelt@florey.edu.au)";

  DESCRIPTION
  + "convert a fixel-based sparse-data image into an spherical harmonic image "
    "that can be visualised using the ODF tool in MRview. The output ODF lobes "
    "are scaled according to the values in the input fixel image.";

  ARGUMENTS
  + Argument ("fixel_in", "the input fixel data file.").type_image_in ()
  + Argument ("sh_out",   "the output sh image.").type_image_out ();

  OPTIONS
  + Option ("lmax", "set the maximum harmonic order for the output series (Default: 8)")
  +   Argument ("order").type_integer (0, 30);
}


void run ()
{

  const std::string input_file (argument[0]);
  if (Path::is_dir (input_file))
    throw Exception ("please input the specific fixel data file to be converted (not the fixel folder)");

  Header in_data_header = Header::open (input_file);
  FixelFormat::check_data_file (in_data_header);
  auto in_data_image = in_data_header.get_image<float>();

  Header in_index_header = FixelFormat::find_index_header (Path::dirname (argument[0]));
  if (input_file == in_index_header.name());
    throw Exception ("input fixel data file cannot be the directions file");
  auto in_index_image = in_index_header.get_image<uint32_t>();
  auto in_directions_image = FixelFormat::find_directions_header (Path::dirname (argument[0]), in_index_header).get_image<float>().with_direct_io();

  size_t lmax = 8;
  auto opt = get_options ("lmax");
  if (opt.size())
    lmax = opt[0][0];
  const size_t n_sh_coeff = Math::SH::NforL (lmax);
  Math::SH::aPSF<default_type> aPSF (lmax);

  Header out_header (in_index_header);
  out_header.datatype() = DataType::Float32;
  out_header.datatype().set_byte_order_native();
  out_header.ndim() = 4;
  out_header.size (3) = n_sh_coeff;

  auto sh_image = Image<float>::create (argument[1], out_header);
  std::vector<default_type> sh_values;
  Eigen::Matrix<default_type, Eigen::Dynamic, 1> apsf_values;

  for (auto l1 = Loop ("converting fixel image to sherical harmonic image", in_index_image) (in_index_image, sh_image); l1; ++l1) {
    sh_values.assign (n_sh_coeff, 0.0);
    in_index_image.index(3) = 0;
    uint32_t num_fixels_in_voxel = in_index_image.value();
    in_index_image.index(3) = 1;
    uint32_t offset = in_index_image.value();

    for (size_t fixel = 0; fixel < num_fixels_in_voxel; ++fixel) {
      in_directions_image.index(0) = offset + fixel;
      apsf_values = aPSF (apsf_values, in_directions_image.row(1));
      in_data_image.index(0) = offset + fixel;
      const default_type scale_factor = in_data_image.value();
      for (size_t i = 0; i != n_sh_coeff; ++i)
        sh_values[i] += apsf_values[i] * scale_factor;
    }
    for (auto l2 = Loop (3) (sh_image); l2; ++l2)
      sh_image.value() = sh_values[sh_image.index(3)];
  }
}

