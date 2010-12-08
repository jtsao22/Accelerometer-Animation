#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QTextEdit>
#include <QRegExp>
#include <DoRegExp.h>

int main(int argc, char **argv)
{
        QApplication app(argc, argv);
	QMainWindow window;
	window.resize(640,480);
	QTextEdit regexText(&window);
	QTextEdit searchText(&window);
	QTextEdit matchText(&window);
	QTextEdit totalText(&window);
	QTextEdit selectText(&window);
	QTextEdit regexLabel(&window);
	QTextEdit searchLabel(&window);
	QTextEdit matchLabel(&window);
	QTextEdit selectLabel(&window);
	QPushButton go("Go!",&window);
	DoRegExp dre(&regexText,&searchText,&matchText,&selectText,&totalText);

	regexText.setGeometry(180,40,440,40);
	searchText.setGeometry(180,100,440,40);
	matchText.setGeometry(180,160,440,40);
	totalText.setGeometry(420,220,200,40);
	selectText.setGeometry(180,220,200,40);

	regexLabel.setGeometry(10,40,150,50);
	searchLabel.setGeometry(10,100,150,50);
	selectLabel.setGeometry(10,160,150,50);
	matchLabel.setGeometry(10,220,150,50);

	go.setGeometry(300,300,200,40);

	selectText.setText("0");
	totalText.setText("0");
	regexLabel.setText("Regular Expression");
	searchLabel.setText("Search Expression");
	selectLabel.setText("Match/Capture");
	matchLabel.setText("Capture # of #");

	regexLabel.setAlignment(Qt::AlignCenter);
	searchLabel.setAlignment(Qt::AlignCenter);
	selectLabel.setAlignment(Qt::AlignCenter);
	matchLabel.setAlignment(Qt::AlignCenter);

	matchText.setReadOnly(1);
	regexLabel.setReadOnly(1);
	searchLabel.setReadOnly(1);
	selectLabel.setReadOnly(1);
	matchLabel.setReadOnly(1);
	totalText.setReadOnly(1);

	QObject::connect(&go,SIGNAL(clicked()),&dre,SLOT(doIt()));

	window.show();
        return app.exec();
}
