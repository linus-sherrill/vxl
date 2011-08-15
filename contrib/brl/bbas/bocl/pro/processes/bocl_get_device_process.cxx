// This is brl/bbas/bocl/pro/processes/bocl_get_device_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file
// \brief A process for initializing a bocl manager
//
// \author Vishal Jain
// \date Mar 8, 2011
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <vcl_fstream.h>
#include <bocl/bocl_manager.h>

namespace bocl_get_device_process_globals
{
  const unsigned n_inputs_ = 2;
  const unsigned n_outputs_ = 1;
}

bool bocl_get_device_process_cons(bprb_func_process& pro)
{
  using namespace bocl_get_device_process_globals;
  vcl_vector<vcl_string>  input_types_(n_inputs_);
  input_types_[0] = "vcl_string";
  input_types_[1] = "bocl_manager_child_sptr";

  vcl_vector<vcl_string>  output_types_(n_outputs_);
  output_types_[0] = "bocl_device_sptr";

  return pro.set_input_types(input_types_)
      && pro.set_output_types(output_types_);
}

bool bocl_get_device_process(bprb_func_process& pro)
{
  using namespace bocl_get_device_process_globals;
  unsigned i=0;
  vcl_string device_type = pro.get_input<vcl_string>(i++);
  bocl_manager_child_sptr mgr = pro.get_input<bocl_manager_child_sptr>(i++);

  if (device_type=="gpu" || device_type=="gpu0")
  {
    if (mgr->gpus_.size()==0) return false;
    bocl_device_sptr device = mgr->gpus_[0];
    pro.set_output_val<bocl_device_sptr>(0,device);
    vcl_cout<<*(device.ptr());
    return true;
  }
  else if (device_type=="cpu" || device_type=="cpu0")
  {
    if (mgr->cpus_.size()==0) return false;
    bocl_device_sptr device = mgr->cpus_[0];
    pro.set_output_val<bocl_device_sptr>(0,device);
    return true;
  }
  
  //for multi-gpu setups
  else if(device_type=="gpu1")
  {
      if(mgr->gpus_.size()<2) return false;
      bocl_device_sptr device = mgr->gpus_[1];
      pro.set_output_val<bocl_device_sptr>(0,device);
      return true;
  }  
  else if(device_type=="gpu2")
  {
      if(mgr->gpus_.size()<3) return false;
      bocl_device_sptr device = mgr->gpus_[2];
      pro.set_output_val<bocl_device_sptr>(0,device);
      return true;
  }  

  else
  {
     vcl_cout<<"Cannot recognize device string.  Available devices: \n"; 

     //list gpu options
     vcl_cout<<"  GPUs: ";
     for(int i=0; i<mgr->gpus_.size(); ++i)
        vcl_cout<<"gpu"<<i<<", "; 
     vcl_cout<<'\n';
    
     //list CPU options 
     vcl_cout<<"  CPUs: ";
     for(int i=0; i<mgr->cpus_.size(); ++i)
        vcl_cout<<"cpu"<<i <<", ";
     
     vcl_cout<<vcl_endl; 
     return false;
  }
}
