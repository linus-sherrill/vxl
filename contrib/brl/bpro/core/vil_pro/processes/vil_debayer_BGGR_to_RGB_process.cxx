// This is brl/bpro/core/vil_pro/processes/vil_debayer_BGGR_to_RGB_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file

#include <bprb/bprb_parameters.h>
#include <vil/vil_save.h>
#include <vil/vil_image_view.h>
#include <vil/vil_rgb.h>

#include <vnl/vnl_matrix.h>
#include <vul/vul_file.h>

//: Constructor
// this process takes 1 input:
// Debayer the image ( BGGR) to RGB
namespace vil_debayer_BGGR_to_RGB_process_globals
{
  const unsigned n_inputs_ =  1;
  const unsigned n_outputs_ = 1;
}

bool vil_debayer_BGGR_to_RGB_process_cons(bprb_func_process& pro)
{
  using namespace vil_debayer_BGGR_to_RGB_process_globals;

  //process takes 1 input
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "vil_image_view_base_sptr";   //scene to operate on

  // process has 0 output:
  vcl_vector<vcl_string>  output_types_(n_outputs_);
  output_types_[0] = "vil_image_view_base_sptr";   //scene to operate on

  return pro.set_input_types(input_types_) && pro.set_output_types(output_types_);
}

static bool isodd(unsigned int x)
{
  if (x % 2==0)
    return false;
  else
    return true;
}


//: Execute the process
bool vil_debayer_BGGR_to_RGB_process(bprb_func_process& pro)
{
  // Sanity check
  if (pro.n_inputs()< 1) {
    vcl_cout << "vil_debayer_BGGR_to_RGB_process: The input number should be 1" << vcl_endl;
    return false;
  }

  // get the inputs
  unsigned i=0;
  //Retrieve image from input
  vil_image_view_base_sptr in_img = pro.get_input<vil_image_view_base_sptr>(i++);
  vil_image_view<vil_rgb<vxl_byte> > * out_img = new vil_image_view<vil_rgb<vxl_byte> >(in_img->ni(),in_img->nj());
  vil_image_view<vil_rgb<vxl_byte> > * debayer_img = new vil_image_view<vil_rgb<vxl_byte> >(in_img->ni(),in_img->nj());
  if (vil_image_view<unsigned char>* in_img_byte= dynamic_cast<vil_image_view<unsigned char>* > (in_img.ptr()))
  {
    for (unsigned k = 0 ; k < in_img_byte->ni(); k++)
    {
      for (unsigned l = 0 ; l < in_img_byte->nj(); l++)
      {
        unsigned char  r=0,g=0,b = 0 ;
        if (k % 2 == 0 && l % 2  == 0)
          b=(*in_img_byte)(k,l);
        else if (k % 2 == 1 && l % 2==1)
          r=(*in_img_byte)(k,l);
        else
          g =(*in_img_byte)(k,l);
        (*out_img)(k,l) = vil_rgb<vxl_byte>(r,g,b);
      }
    }
    // green channel
    for (unsigned k = 1 ; k < in_img_byte->ni()-1; k++)
    {
      for (unsigned l = 1 ; l < in_img_byte->nj()-1; l++)
      {
        unsigned char r = (*out_img)(k,l).R();
        unsigned char g = (*out_img)(k,l).G();
        unsigned char b = (*out_img)(k,l).B();
        //(0,0)
        if (!isodd(k) && !isodd(l))
        {
          g =((int)(*out_img)(k-1,l).G() +(int)(*out_img)(k,l-1).G()+(int)(*out_img)(k,l+1).G()+(int)(*out_img)(k+1,l).G())/4;
          r =((int)(*out_img)(k-1,l-1).R() + (int) (*out_img)(k+1,l-1).R()+(int) (*out_img)(k+1,l+1).R()+ (int) (*out_img)(k-1,l+1).R())/4;
        }
        //(0,1)
        if (!isodd(k) && isodd(l))
        {
          b =((int)(*out_img)(k,l-1).B() +(int)(*out_img)(k,l+1).B())/2;
          r =((int)(*out_img)(k-1,l).R() +(int)(*out_img)(k+1,l).R())/2;
        }
        //(1,0)
        if (isodd(k) && !isodd(l))
        {
          b =((int)(*out_img)(k-1,l).B() +(int)(*out_img)(k+1,l).B())/2;
          r =((int)(*out_img)(k,l-1).R() +(int)(*out_img)(k,l+1).R())/2;
        }
        //(1,1)
        if (isodd(k) && isodd(l))
        {
          b =((int)(*out_img)(k-1,l-1).B() + (int) (*out_img)(k+1,l-1).B()+(int) (*out_img)(k+1,l+1).B()+ (int) (*out_img)(k-1,l+1).B())/4;
          g =((int)(*out_img)(k-1,l).G() +(int)(*out_img)(k,l-1).G()+(int)(*out_img)(k,l+1).G()+(int)(*out_img)(k+1,l).G())/4;
        }
       (*debayer_img)(k,l) = vil_rgb<vxl_byte>(r,g,b);
      }
    }
  }
  pro.set_output_val<vil_image_view_base_sptr>(0, debayer_img);
  return true;
}

