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
   if (root)
		root->unref();
	if (eViewer)
		delete eViewer;
}
void QCoin::setRoot(SoSeparator* newRoot)
{
   if (root)
		root->unref();
	root = newRoot;
	root->ref();
   if (!eViewer)
		eViewer = new SoQtExaminerViewer(this);
	eViewer->setSceneGraph(root);
	eViewer->viewAll();
	QCoin::show();
}
void QCoin::show()
{
	if (eViewer)
		eViewer->show();
	QWidget::show();
}
void QCoin::viewAll()
{
	if (eViewer)
		eViewer->viewAll();
}
SoQtExaminerViewer* QCoin::getViewer()
{
	return eViewer;
}
