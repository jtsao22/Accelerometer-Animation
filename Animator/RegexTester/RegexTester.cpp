#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QTextEdit>

int main(int argc, char **argv)
{
        QApplication app(argc, argv);
	QMainWindow window;
	window.resize(640,480);
	QTextEdit regexText(&window);
	QTextEdit searchText(&window);
	QTextEdit matchText(&window);
	QTextEdit selectText(&window);
	QTextEdit regexLabel(&window);
	QTextEdit searchLabel(&window);
	QTextEdit matchLabel(&window);
	QTextEdit selectLabel(&window);

	regexText.setGeometry(180,40,440,40);
	searchText.setGeometry(180,100,440,40);
	matchText.setGeometry(180,160,440,40);
	selectText.setGeometry(180,220,440,40);
	regexLabel.setGeometry(10,40,150,50);
	searchLabel.setGeometry(10,100,100,40);
	selectLabel.setGeometry(10,160,100,40);
	matchLabel.setGeometry(10,220,100,40);

	selectText.setText("0");
	regexLabel.setText("Regular Expression");


	matchText.setReadOnly(1);
	window.show();
        return app.exec();
}
