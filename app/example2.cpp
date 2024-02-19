#include <sparse_interp/Types.hpp>
#include <string>
// Add these Open CASCADE headers
#include <Geom_BSplineSurface.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Face.hxx>
#include <STEPControl_Writer.hxx>
#include <Interface_Static.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <Standard_Real.hxx>
#include <StlAPI_Writer.hxx>

using namespace SIBSplines;

std::string example_root_path(SI_MESH_DIR);

// Create a function to convert the Bsurface to an Open CASCADE B-Spline surface
Handle(Geom_BSplineSurface) convertToOCC_BSplineSurface(const Bsurface& surface) {
  TColgp_Array2OfPnt controlPoints(0, surface.control_points.size(), 0, surface.control_points[0].size() );
  for (int i = 0; i < surface.control_points.size(); ++i) 
  {
    for (int j = 0; j < surface.control_points[i].size(); ++j) 
    {
      controlPoints.SetValue(i, j, 
      gp_Pnt(
        surface.control_points[i][j].x(), 
        surface.control_points[i][j].y(), 
        surface.control_points[i][j].z()));
    }
  }
  /*Use the size of the control points*/
  TColStd_Array1OfReal uKnots(0, surface.U.size());
  int interval = 0;
  int i = 0;
  while((interval < surface.U.size()-1)&& (i<surface.U.size()-1))
  {
      std::cout << "surface.U  " << surface.U[i]<< std::endl;
      Standard_Real U = surface.U[i];
      if(surface.U[i] !=surface.U[i -1])
      {
        std::cout << "U is equal to " << U << std::endl;
        uKnots.SetValue(interval, U);
        interval ++;
        i++;
      }
      else
      {

          i++;
      }
  }
  uKnots.Resize(uKnots.Lower(),interval -2 ,true);
  std::cout << "max processed elmts for U is " << interval << std::endl;

  TColStd_Array1OfReal vKnots(0, surface.V.size());
  int intervalV = 0;
  int iV = 0;
  while((intervalV < surface.V.size()-1)&& (iV<surface.V.size()-1))
  {
      std::cout << "surface.V  " << surface.V[iV]<< std::endl;
      Standard_Real V = surface.V[iV];
      if(surface.V[iV] !=surface.V[iV -1])
      {
        std::cout << "V is equal to " << V << std::endl;
        vKnots.SetValue(intervalV, V);
        intervalV ++;
        iV++;
      }
      else
      {
          iV++;
      }
  }
  vKnots.Resize(vKnots.Lower(),intervalV -2,true);
  std::cout << "max processed elements for V is " << intervalV << std::endl;
TColStd_Array1OfInteger uMults(0, interval-2);

    for (int i = 0; i < uMults.Size(); i++) {
      if(i< uMults.Size() -1 )
      {
          uMults(i) = 1;
      }
      else
      {
        uMults(i) = surface.degree1 +1 ;
      }
  }

  TColStd_Array1OfInteger vMults(0, intervalV- 2);
  for (int i = 0; i < vMults.Size(); i++) 
  {
      if(i< vMults.Size() -1 )
      {
          vMults(i) = 1;
      }
      else
      {
        vMults(i) = surface.degree2 +1 ;
      }
  }
  std::cout << "uMults.Size()" << uMults.Size() << std::endl << "vMults.Size()" << vMults.Size() << std::endl;
  std::cout << "uKnots.Size()" << uKnots.Size() << std::endl << "vKnots.Size()" << vKnots.Size() << std::endl;
  controlPoints.Resize(controlPoints.LowerCol(),uMults.Size()-2,controlPoints.LowerRow(),vMults.Size()-2,true);
  Handle(Geom_BSplineSurface) occSurface = 
  new Geom_BSplineSurface(controlPoints, uKnots, vKnots, uMults, vMults, surface.degree1, surface.degree2,false,false);
  return occSurface;
}


void run_mesh_reconstruction(Bsurface& outSurface,
                            Eigen::MatrixXd& SPs,
                            Eigen::MatrixXi& SFs,
                            Eigen::MatrixXd& ver,
                            int local_target_steps,
                            double local_delta,
                            double local_per)
{
	double precision = 0;
	Eigen::MatrixXi F;
	Eigen::MatrixXd param, paramout;
	std::string modelname = "tiger.obj";
	std::string meshfile = example_root_path + modelname;
	std::cout << "reading mesh model: " << meshfile << std::endl;
	// mesh parametrization, and print out the parametrization result as a obj mesh.
	mesh_parameterization(meshfile, ver, param, F);
	paramout.resize(param.rows(), 3);
	Eigen::VectorXd param_zero = Eigen::VectorXd::Zero(param.rows());
	paramout << param, param_zero;
	write_triangle_mesh(example_root_path + "param_" + modelname, paramout, F);

	// construct the surface object
	Bsurface surface;
	// set up the initial parameters.
	int nbr = param.rows();					// the number of data points
	surface.degree1 = 3;					// degree of u direction
	surface.degree2 = 3;					// degree of v direction
	surface.U = { {0, 0, 0, 0, 1, 1, 1, 1} }; 		// the initial U knot vector
	surface.V = surface.U;					// the initial V knot vector
   
	int target_steps = local_target_steps;					// the number of iterations for constructing lists $L$.
	bool enable_max_fix_nbr = true;						// progressively update the knot vectors to make the two knot vectors balanced in length. (true)
	double delta = local_delta/10;						// the parameter to improve the solving stability (per_ours)
	double per = local_per/10;						// the parameter inherited from [Wen-Ke Wang et al, 2008, CAD] (0.5)
	// generate knot vectors to make sure the data points can be interpolated
	surface.generate_interpolation_knot_vectors(surface.degree1, 
  	surface.degree2, 
  	surface.U, 
  	surface.V, 
  	param, 
  	delta, 
  	per, 
  	target_steps, 
  	enable_max_fix_nbr);
	std::cout << "knot vectors generated" << std::endl;
	std::cout << std::to_string(local_target_steps) << std::endl;
	std::cout << std::to_string(delta) << std::endl;
	std::cout << std::to_string(per) << std::endl;

	int visual_nbr = 200; // the discretization scale for the output surface. The mesh will be 400x400

	// basis contains all the basis functions and their 1 and 2 order diffenrential form.
	PartialBasis basis(surface);

	// solve the control points to obtain the surface.
	surface.solve_control_points_for_fairing_surface(surface, param, ver, basis);
	std::cout << "surface solved" << std::endl;

	// convert B-spline surface into a triangle mesh
  	std::cout << "convert B-spline surface into a triangle mesh" << std::endl;
	surface.surface_visulization(surface, visual_nbr, SPs, SFs);
  	std::cout << "surface visulization" << std::endl;
	precision = surface.max_interpolation_err(ver, param, surface);
	std::cout << "maximal interpolation error " << surface.max_interpolation_err(ver, param, surface) << std::endl;

	write_points(example_root_path + "pts" + std::to_string(nbr) + "_m_" + modelname, ver);
	write_triangle_mesh(example_root_path + "intp_" + "p" + std::to_string(nbr) + "_m_" + modelname, SPs, SFs);

	outSurface = surface;
}

int main() {
  Bsurface surface;
  Eigen::MatrixXd SPs;
  Eigen::MatrixXi SFs;
  Eigen::MatrixXd ver;
  
  /**run_mesh_reconstruction(surface, SPs, SFs, ver, 10, 9, 5);/**/
  
/**/
  int min_target_steps = 10;   
  int max_target_steps = 20;
  int step_target_steps = 5;
  
  int min_delta = 5;   
  int max_delta = 9;
  int step_delta = 2;
  
  int min_per = 3;   
  int max_per = 9;
  int step_per = 3;

 for (int current_target_steps = min_target_steps; 
      current_target_steps <= max_target_steps; 
      current_target_steps += step_target_steps) {
      
      for (int current_delta = min_delta; 
      	   current_delta <= max_delta; 
      	   current_delta += step_delta) {

      	   for (int current_per = min_per; 
      	        current_per <= max_per; 
      	        current_per += step_per) {
        
      	   		std::cout<<"test"<<std::endl;
           		run_mesh_reconstruction(surface, SPs, SFs, ver, current_target_steps, current_delta, current_per);
/**/
    try {
    // Create the Open CASCADE B-Spline surface
    std::cout << "Create the Open CASCADE B-Spline surface step 1"  << std::endl;
    Handle(Geom_BSplineSurface) occ_bspline_surface = convertToOCC_BSplineSurface(surface);
    // Convert the B-Spline surface to a TopoDS_Face
    std::cout << "Convert the B-Spline surface to a TopoDS_Face"  << std::endl;
    BRepBuilderAPI_MakeFace makeFace(occ_bspline_surface, Precision::Confusion());
    TopoDS_Face face = makeFace.Face();

  // Initialize the STEP writer
  STEPControl_Writer writer;
  Interface_Static::SetCVal("write.step.schema", "AP214");
  Interface_Static::SetCVal("xstep.cascade.unit","M");
  Interface_Static::SetIVal("write.step.nonmanifold", 1);
  // Add the B-Spline face to the STEP writer
  writer.Transfer(face, STEPControl_AsIs);
  
  /**/std::string filename = std::string("./tiger") + std::to_string(current_target_steps) +std::to_string(current_delta)+std::to_string(current_per)+".step";/**/
  Standard_Boolean success = writer.Write(/**/filename.c_str()/**/ /**"./tiger.step"/**/);


  std::cout << "done !" << std::endl;

  } catch (const Standard_ConstructionError& e) {
    std::cout << std::endl << "Error: " << e.GetMessageString() << std::endl;
    return 1;
  }/**/}}}/**/  

  return 0;
}
