#include <QTextEdit>
#include <QString>
#include <QRegExp>

class DoRegExp: public QObject
{
	Q_OBJECT
private:
	QRegExp re;
	QTextEdit* reg;
	QTextEdit* search;
	QTextEdit* match;
	QTextEdit* select;
	QTextEdit* tot;
	int i;
public:
	DoRegExp(QTextEdit* r,QTextEdit* s,QTextEdit* m,QTextEdit* se,QTextEdit* t):reg(r),search(s),match(m),select(se),tot(t){}
public slots:
	void doIt()
	{
		re.setPattern(reg->toPlainText());
		i = select->toPlainText().toInt();
		if(re.indexIn(search->toPlainText()) > -1)
		{
			tot->setText(QString::number(re.captureCount()));
			if (i >= 0 && i <= re.captureCount())
				match->setText(re.cap(i));
			else
				match->setText("~!~Invalid Capture Number~!~");
		}
		else
			match->setText("~!~No Match~!~");
	
	}

};
