#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  unsigned int numi = 2;
  unsigned int numj = 3;
  unsigned int numk = 2;

  for(unsigned int k = 0; k < numk; k++)
  {
    for(unsigned int j = 0; j < numj; j++)
    {
      for(unsigned int i = 0; i < numi; i++)
      {
        points->InsertNextPoint(i, j, k);
      }
    }
  }

  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(numi, numj, numk);
  structuredGrid->SetPoints(points);

  std::cout << "There are " << structuredGrid->GetNumberOfPoints() << " points." << std::endl; // there should be 2*3*2 = 12 points
  std::cout << "There are " << structuredGrid->GetNumberOfCells() << " cells." << std::endl; // The 12 points define the corners of 2 cubes/cells (4 points are shared by both cubes)

  vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  geometryFilter->SetInputConnection(structuredGrid->GetProducerPort());
#else
  geometryFilter->SetInputData(structuredGrid);
#endif
  geometryFilter->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometryFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(3);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}



/*

#include <vtkSmartPointer.h>

#include <vtkCurvatures.h>

#include <vtkXMLPolyDataReader.h>

#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkColorSeries.h>

#include <vtkPointData.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkScalarBarActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " Filename(.vtp)" << std::endl;
    return EXIT_FAILURE;
  }

  // Create a polydata
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkCurvatures> curvaturesFilter =
    vtkSmartPointer<vtkCurvatures>::New();
  curvaturesFilter->SetInputConnection(reader->GetOutputPort());
  curvaturesFilter->SetCurvatureTypeToMinimum();
  curvaturesFilter->SetCurvatureTypeToMaximum();
  curvaturesFilter->SetCurvatureTypeToGaussian();
  curvaturesFilter->SetCurvatureTypeToMean();
  curvaturesFilter->Update();

  // Get scalar range from command line if present, otherwise use
  // range of computed curvature
  double scalarRange[2];
  if (argc >= 4)
  {
    scalarRange[0] = atof(argv[2]);
    scalarRange[1] = atof(argv[3]);
  }
  else
  {
    curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);
  }

  int scheme = 16;
  if (argc >= 5)
  {
    scheme = atoi(argv[4]);
  }

  // Build a lookup table
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(scheme);
  std::cout << "Using color scheme #: "
            << colorSeries->GetColorScheme() << " is "
            << colorSeries->GetColorSchemeName() << std::endl;

  vtkSmartPointer<vtkColorTransferFunction> lut =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  lut->SetColorSpaceToHSV();

  // Use a color series to create a transfer function
  int numColors = colorSeries->GetNumberOfColors();
  for (int i = 0; i < numColors; i++)
  {
      vtkColor3ub color = colorSeries->GetColor(i);
    double dColor[3];
    dColor[0] = static_cast<double> (color[0]) / 255.0;
    dColor[1] = static_cast<double> (color[1]) / 255.0;
    dColor[2] = static_cast<double> (color[2]) / 255.0;
    double t = scalarRange[0] + (scalarRange[1] - scalarRange[0])
      / (numColors - 1) * i;
    lut->AddRGBPoint(t, dColor[0], dColor[1], dColor[2]);
  }

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(curvaturesFilter->GetOutputPort());
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(scalarRange);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a scalar bar
  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  scalarBar->SetLookupTable(mapper->GetLookupTable());
  scalarBar->SetTitle(
    curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
  scalarBar->SetNumberOfLabels(5);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor2D(scalarBar);

  renderer->SetBackground(.1, .2, .3); // Background color blue

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

/*
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkSurfaceReconstructionFilter.h>
#include <vtkProgrammableSource.h>
#include <vtkContourFilter.h>
#include <vtkReverseSense.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{


  vtkSmartPointer<vtkPolyData> input;

    vtkSmartPointer<vtkXMLPolyDataReader> reader =
	vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName("mesh.vtk");
    reader->Update();
    input = reader->GetOutput();

  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(input->GetPoints());

  // Construct the surface and create isosurface.	
  vtkSmartPointer<vtkSurfaceReconstructionFilter> surf = 
    vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  surf->SetInput(polydata);
#else
  surf->SetInputData(polydata);
#endif

  vtkSmartPointer<vtkContourFilter> cf = 
    vtkSmartPointer<vtkContourFilter>::New();
  cf->SetInputConnection(surf->GetOutputPort());
  cf->SetValue(0, 0.0);

  // Sometimes the contouring algorithm can create a volume whose gradient
  // vector and ordering of polygon (using the right hand rule) are
  // inconsistent. vtkReverseSense cures this problem.
  vtkSmartPointer<vtkReverseSense> reverse = 
    vtkSmartPointer<vtkReverseSense>::New();
  reverse->SetInputConnection(cf->GetOutputPort());
  reverse->ReverseCellsOn();
  reverse->ReverseNormalsOn();

  vtkSmartPointer<vtkPolyDataMapper> map = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  map->SetInputConnection(reverse->GetOutputPort());
  map->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> surfaceActor = 
    vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(map);

  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> ren = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  ren->AddActor(surfaceActor);
  ren->SetBackground(.2, .3, .4);

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;

}
/*
#include <vtkGenericDataObjectReader.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <string>

int main ( int argc, char *argv[] )
{
  // Ensure a filename was specified
  if(argc != 2)
    {
    std::cerr << "Usage: " << argv[0] << " InputFilename" << endl;
    return EXIT_FAILURE;
    }

  // Get the filename from the command line
  std::string inputFilename = argv[1];

  // Get all data from the file
  vtkSmartPointer<vtkGenericDataObjectReader> reader = 
      vtkSmartPointer<vtkGenericDataObjectReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
  
  // All of the standard data types can be checked and obtained like this:
  if(reader->IsFilePolyData())
    {
    std::cout << "output is a polydata" << std::endl;
    vtkPolyData* output = reader->GetPolyDataOutput();
    std::cout << "output has " << output->GetNumberOfPoints() << " points." << std::endl;
    }
  
  return EXIT_SUCCESS;
}
*/
/*
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCleanPolyData.h>
#include <vtkDelaunay3D.h>
#include <vtkXMLPolyDataReader.h>saveVTKFile

int main ( int argc, char *argv[] )
{
  if(argc < 2)
    {
    std::cout << "Usage: " << argv[0]
              << " filename.vtp" << std::endl;
    return EXIT_FAILURE;
    }

  //Read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkDataSetMapper> originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  originalMapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(1,0,0);
  
  // Clean the polydata. This will remove duplicate points that may be
  // present in the input data.
  vtkSmartPointer<vtkCleanPolyData> cleaner =
    vtkSmartPointer<vtkCleanPolyData>::New();
  cleaner->SetInputConnection (reader->GetOutputPort());

  // Generate a tetrahedral mesh from the input points. By
  // default, the generated volume is the convex hull of the points.
  vtkSmartPointer<vtkDelaunay3D> delaunay3D =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3D->SetInputConnection (cleaner->GetOutputPort());

  vtkSmartPointer<vtkDataSetMapper> delaunayMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayMapper->SetInputConnection(delaunay3D->GetOutputPort());

  vtkSmartPointer<vtkActor> delaunayActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayActor->SetMapper(delaunayMapper);
  delaunayActor->GetProperty()->SetColor(1,0,0);
  
  // Generate a mesh from the input points. If Alpha is non-zero, then
  // tetrahedra, triangles, edges and vertices that lie within the
  // alpha radius are output.
  vtkSmartPointer<vtkDelaunay3D> delaunay3DAlpha =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3DAlpha->SetInputConnection (cleaner->GetOutputPort());
  delaunay3DAlpha->SetAlpha(0.1);
  
  vtkSmartPointer<vtkDataSetMapper> delaunayAlphaMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  delaunayAlphaMapper->SetInputConnection(delaunay3DAlpha->GetOutputPort());

  vtkSmartPointer<vtkActor> delaunayAlphaActor =
    vtkSmartPointer<vtkActor>::New();
  delaunayAlphaActor->SetMapper(delaunayAlphaMapper);
  delaunayAlphaActor->GetProperty()->SetColor(1,0,0);
  
  // Visualize
  
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> delaunayRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> delaunayAlphaRenderer =
    vtkSmartPointer<vtkRenderer>::New();
    
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900,300);
  
  renderWindow->AddRenderer(originalRenderer);
  originalRenderer->SetViewport(leftViewport);
  renderWindow->AddRenderer(delaunayRenderer);
  delaunayRenderer->SetViewport(centerViewport);
  renderWindow->AddRenderer(delaunayAlphaRenderer);
  delaunayAlphaRenderer->SetViewport(rightViewport);
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  originalRenderer->AddActor(originalActor);
  delaunayRenderer->AddActor(delaunayActor);
  delaunayAlphaRenderer->AddActor(delaunayAlphaActor);

  originalRenderer->SetBackground(.3, .6, .3);
  delaunayRenderer->SetBackground(.4, .6, .3);
  delaunayAlphaRenderer->SetBackground(.5, .6, .3);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}

*/
