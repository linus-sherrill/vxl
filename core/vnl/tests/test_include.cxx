#include <vnl/vnl_fwd.h>

#include <vnl/vnl_T_n.h>
#include <vnl/vnl_alloc.h>
#include <vnl/vnl_bignum.h>
#include <vnl/vnl_block.h>
#include <vnl/vnl_c_vector.h>
#include <vnl/vnl_complex.h>
#include <vnl/vnl_complexify.h>
#include <vnl/vnl_complex_traits.h>
#include <vnl/vnl_copy.h>
#include <vnl/vnl_cost_function.h>
#include <vnl/vnl_cross_product_matrix.h>
#include <vnl/vnl_det.h>
#include <vnl/vnl_diag_matrix.h>
#include <vnl/vnl_double_2.h>
#include <vnl/vnl_double_2x2.h>
#include <vnl/vnl_double_2x3.h>
#include <vnl/vnl_double_3.h>
#include <vnl/vnl_double_3x2.h>
#include <vnl/vnl_double_3x3.h>
#include <vnl/vnl_double_3x4.h>
#include <vnl/vnl_double_4.h>
#include <vnl/vnl_double_4x3.h>
#include <vnl/vnl_double_4x4.h>
#include <vnl/vnl_double_5.h>
#include <vnl/vnl_error.h>
#include <vnl/vnl_fastops.h>
#include <vnl/vnl_file_matrix.h>
#include <vnl/vnl_file_vector.h>
#include <vnl/vnl_finite.h>
#include <vnl/vnl_float_2.h>
#include <vnl/vnl_float_3.h>
#include <vnl/vnl_float_4.h>
#include <vnl/vnl_fortran_copy.h>
#include <vnl/vnl_identity.h>
#include <vnl/vnl_identity_3x3.h>
#include <vnl/vnl_imag.h>
#include <vnl/vnl_int_2.h>
#include <vnl/vnl_int_3.h>
#include <vnl/vnl_int_4.h>
#include <vnl/vnl_int_matrix.h>
#include <vnl/vnl_least_squares_cost_function.h>
#include <vnl/vnl_least_squares_function.h>
#include <vnl/vnl_linear_operators_3.h>
#include <vnl/vnl_linear_system.h>
#include <vnl/vnl_math.h>
#include <vnl/vnl_matlab_filewrite.h>
#include <vnl/vnl_matlab_header.h>
#include <vnl/vnl_matlab_print.h>
#include <vnl/vnl_matlab_print2.h>
#include <vnl/vnl_matlab_print_format.h>
#include <vnl/vnl_matlab_print_scalar.h>
#include <vnl/vnl_matlab_read.h>
#include <vnl/vnl_matlab_write.h>
#include <vnl/vnl_matops.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_matrix_exp.h>
#include <vnl/vnl_matrix_fixed.h>
#include <vnl/vnl_matrix_fixed_ref.h>
#include <vnl/vnl_matrix_ref.h>
#include <vnl/vnl_nonlinear_minimizer.h>
#include <vnl/vnl_numeric_limits.h>
#include <vnl/vnl_numeric_traits.h>
#include <vnl/vnl_operators.h>
#include <vnl/vnl_quaternion.h>
#include <vnl/vnl_rational.h>
#include <vnl/vnl_real.h>
#include <vnl/vnl_real_npolynomial.h>
#include <vnl/vnl_real_polynomial.h>
#include <vnl/vnl_rotation_matrix.h>
#include <vnl/vnl_sample.h>
#include <vnl/vnl_scalar_join_iterator.h>
#include <vnl/vnl_sparse_matrix.h>
#include <vnl/vnl_sparse_matrix_linear_system.h>
#include <vnl/vnl_sym_matrix.h>
#include <vnl/vnl_tag.h>
//#include <vnl/vnl_tensor.h>
//#include <vnl/vnl_tensor_traits.h>
#include <vnl/vnl_trace.h>
#include <vnl/vnl_transpose.h>
#include <vnl/vnl_unary_function.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_vector_dereference.h>
#include <vnl/vnl_vector_fixed.h>
#include <vnl/vnl_vector_fixed_ref.h>
#include <vnl/vnl_vector_ref.h>

#include <vnl/algo/vnl_algo_fwd.h>

#include <vnl/algo/vnl_adjugate.h>
#include <vnl/algo/vnl_amoeba.h>
#include <vnl/algo/vnl_brent.h>
#include <vnl/algo/vnl_chi_squared.h>
#include <vnl/algo/vnl_cholesky.h>
#include <vnl/algo/vnl_complex_eigensystem.h>
#include <vnl/algo/vnl_conjugate_gradient.h>
#include <vnl/algo/vnl_convolve.h>
#include <vnl/algo/vnl_cpoly_roots.h>
#include <vnl/algo/vnl_determinant.h>
#include <vnl/algo/vnl_discrete_diff.h>
#include <vnl/algo/vnl_fft_1d.h>
#include <vnl/algo/vnl_fft_2d.h>
#include <vnl/algo/vnl_fft.h>
#include <vnl/algo/vnl_gaussian_kernel_1d.h>
#include <vnl/algo/vnl_generalized_eigensystem.h>
#include <vnl/algo/vnl_generalized_schur.h>
#include <vnl/algo/vnl_lbfgs.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <vnl/algo/vnl_lsqr.h>
#include <vnl/algo/vnl_matrix_inverse.h>
#include <vnl/algo/vnl_netlib.h>
#include <vnl/algo/vnl_orthogonal_complement.h>
#include <vnl/algo/vnl_powell.h>
#include <vnl/algo/vnl_qr.h>
#include <vnl/algo/vnl_real_eigensystem.h>
#include <vnl/algo/vnl_rnpoly_solve.h>
#include <vnl/algo/vnl_rpoly_roots.h>
#include <vnl/algo/vnl_scatter_3x3.h>
#include <vnl/algo/vnl_sparse_symmetric_eigensystem.h>
#include <vnl/algo/vnl_svd.h>
#include <vnl/algo/vnl_symmetric_eigensystem.h>

int test_include_main(int, char*[]) { return 0; }
