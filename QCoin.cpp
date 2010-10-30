#include<QCoin.h>

	/* Private data:
	 * 	SoSeparator* root;
	 * 	SoQtExaminerViewer* eViewer;
	 */
QCoin::QCoin( QWidget* parent)
	: QWidget(parent)
{
	root = NULL;
	eViewer = NULL;
}
QCoin::QCoin( const char* scene_graph ,QWidget* parent)
	: QWidget(parent)
{
	//Read data from file
   SoInput sceneInput;
   if (!sceneInput.openFile(scene_graph))
   {
      fprintf(stderr,"Cannot open file %s\n",scene_graph);
      root = NULL;
		eViewer = NULL;
		return;
   }

   root = SoDB::readAll(&sceneInput);
   if (root == NULL)
   {
      fprintf(stderr,"Problem reading file %s\n",scene_graph);
		root = NULL;
		eViewer = NULL;
   }
   root->ref();
   sceneInput.closeFile();
  //Got data from file

  eViewer = new SoQtExaminerViewer(this);
  eViewer->setSceneGraph(root);
  eViewer->show();
}
QCoin::~QCoin()
{
	root->unref();
	delete eViewer;
}

