#include <testlib/testlib_test.h>
#include <vcl_cmath.h>
#include <vcl_vector.h>
#include <vcl_cstdlib.h>
#include <vsph/vsph_unit_sphere.h>
#include <vsph/vsph_segment_sphere.h>
#include <vsph/vsph_sph_point_2d.h>
#include <vsph/vsph_sph_box_2d.h>
#include <vsph/vsph_sph_cover_2d.h>
#include <vsph/vsph_utils.h>
#include <vnl/vnl_math.h>

static vcl_string MyDIR = "C:/Users/mundy/VisionSystems/Finder/VolumetricQuery/";

static void random_rgb(float& r, float&g, float& b)
{
  float rmax = static_cast<float>(RAND_MAX);
  r = static_cast<float>(vcl_rand())/rmax;
  g = static_cast<float>(vcl_rand())/rmax;
  b = static_cast<float>(vcl_rand())/rmax;
}

static void test_sph_cover()
{
  vsl_b_ifstream is(MyDIR + "unit_sphere_2_75_105.vsl");
  vsph_unit_sphere_sptr usph;
  vsl_b_read(is, usph);
  int nv = usph->size();
  double point_angle = usph->point_angle();//for coast (2 really)
  double dpr = vnl_math::deg_per_rad;
  double th_min = usph->min_theta()/dpr, th_max = usph->max_theta()/dpr;
  double sph_area = vcl_fabs(vcl_cos(th_min)-vcl_cos(th_max))*vnl_math::twopi;
  double ray_area = sph_area/nv;
  double reg_min_theta = 85.0/dpr, reg_max_theta = 95.0/dpr;
  double reg_min_phi = -90.0/dpr, reg_max_phi = 90.0/dpr;
  double dth = 2.0/dpr;
  double s = (reg_max_theta-reg_min_theta - dth)/(reg_max_phi-reg_min_phi);
  vcl_vector<double> data(nv, 0.0);
  vcl_vector<float> cb(3), cf(3);
    random_rgb(cb[0],cb[1],cb[2]);
	 random_rgb(cf[0],cf[1],cf[2]);
  vcl_vector<vcl_vector<float> > cdata(nv, cb);
  int cnt = 0;
  vsph_unit_sphere::iterator sit = usph->begin();
  for (; sit!=usph->end(); ++sit, cnt++)
  {
    vsph_sph_point_2d& sp = *sit;
    if (sp.phi_>=reg_min_phi && sp.phi_<=reg_max_phi){
      double th_up = reg_max_theta - (sp.phi_-reg_min_phi)*s;
      double th_low = th_up - dth; 
	  if(sp.theta_>=th_low && sp.theta_<=th_up){
	data[cnt] = 50.0;
	cdata[cnt] = cf;
	  }
	}
  }
  vcl_string dpath = MyDIR + "slope_region.wrl";
 usph->display_color(dpath, cdata);
    double sigma = (0.1*point_angle)/dpr,  c =300.0;
    int min_size = 10;

    vsph_segment_sphere ssph(*usph, c, min_size, sigma, false);
    vcl_cout << "Start segment\n" << vcl_flush;
    ssph.set_data(data);
    ssph.segment();
    ssph.extract_region_bounding_boxes();
	const vcl_map<int,  vcl_vector<int> >& regs = ssph.regions();
    const vcl_map<int, vsph_sph_box_2d>& boxes = ssph.region_boxes();

  vcl_vector<vsph_sph_box_2d> dboxes;
  vcl_map<int, vsph_sph_box_2d>::const_iterator bit = boxes.begin();
  vcl_vector<vcl_vector<float> > colors;
  for (; bit != boxes.end(); ++bit) {
    dboxes.push_back(bit->second);
    vcl_vector<float> c(3);
    random_rgb(c[0],c[1],c[2]);
    colors.push_back(c);
  }
  vcl_string test_path = MyDIR + "rseg_box_color_2.wrl";
  double tol = 0.001;
  vsph_sph_box_2d::display_boxes(test_path, dboxes, colors, tol);
  vcl_map<int,  vcl_vector<int> >::const_iterator rit = regs.begin();
  const vcl_vector<int>& ray_idx = rit->second;
  bit = boxes.begin();
  vsph_sph_box_2d dia_box = bit->second;
  const vcl_vector<vsph_sph_point_2d>& sph_pts = usph->sph_points_ref();
  vcl_vector<vsph_sph_point_2d> rays;
  for(vcl_vector<int>::const_iterator iit = ray_idx.begin(); 
      iit != ray_idx.end(); ++iit)
	  rays.push_back(sph_pts[*iit]);
  vsph_sph_cover_2d cover(dia_box,rays,ray_area);
}

TESTMAIN(test_sph_cover);
