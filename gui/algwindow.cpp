
#include "algwindow.hpp"
#include "common.hpp"

namespace pat
{

	AlgWindow::AlgWindow(QWidget * parent) : QDialog(parent)
	{
		box_h = new QVBoxLayout;
		box_h_b = new QHBoxLayout;
		box_h_l = new QHBoxLayout;
		box_v = new QVBoxLayout;

		lbl_alg = new QLabel(tr("Algorithm") + ":");
		list_alg = new QComboBox;
		list_alg->addItem(tr("brute force"));
		list_alg->addItem(tr("gradient"));
		list_alg->addItem(tr("downhill simplex"));

		lbl_app = new QLabel(tr("Application") + ":");
		text_edit = new QLineEdit;
		btn_choose = new QPushButton(tr("..."));
		btn_choose->setMaximumSize(24, 24);

		box_h_l->addWidget(text_edit);
		box_h_l->addWidget(btn_choose);

		lbl_count = new QLabel(tr("Max count of iterations") + ":");
		spin_count = new QSpinBox;
		spin_count->setMinimum(8);
		spin_count->setMaximum(1024*1024*1024);
		spin_count->setValue(32);

		lbl_time = new QLabel(tr("Time (in sec)") + ":");
		spin_time = new QSpinBox;
		spin_time->setMinimum(3);
		spin_time->setMaximum(53049600);
		spin_time->setValue(314);
		update_time(314);
		connect(spin_time, SIGNAL(valueChanged(int)), this, SLOT(update_time(int)));

		lbl_eps = new QLabel(tr("Epsilon") + ":");
		spin_eps = new QDoubleSpinBox;
		spin_eps->setDecimals(10);
		spin_eps->setMaximum(1000.0);
		spin_eps->setSingleStep(0.0000000001);
		spin_eps->setValue(0.0000000250);

		btn_create = new QPushButton(tr("Create"));
		btn_cancel = new QPushButton(tr("Cancel"));

		connect(btn_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
		connect(btn_create, SIGNAL(clicked()), this, SLOT(create()));
		connect(btn_choose, SIGNAL(clicked()), this, SLOT(choose_app()));

		box_h->addWidget(lbl_alg);
		box_h->addStretch(1);
		box_h->addWidget(list_alg);
		box_h->addStretch(5);
		box_h->addWidget(lbl_app);
		box_h->addStretch(1);
		box_h->addLayout(box_h_l);
		box_h->addStretch(5);
		box_h->addWidget(lbl_count);
		box_h->addStretch(1);
		box_h->addWidget(spin_count);
		box_h->addStretch(5);

		box_h->addWidget(lbl_time);
		box_h->addStretch(1);
		box_h->addWidget(spin_time);
		box_h->addStretch(5);

		box_h->addWidget(lbl_eps);
		box_h->addStretch(1);
		box_h->addWidget(spin_eps);
		box_h_b->addWidget(btn_create);
		box_h_b->addStretch(1);
		box_h_b->addWidget(btn_cancel);

		box_v->addLayout(box_h);
		box_v->addSpacing(10);
		box_v->addLayout(box_h_b);

		is_create = false;
		setWindowTitle(tr("Optimize of the new application"));
		setLayout(box_v);
		resize(450, 210);
		center_qwidget(this);
	}

	void AlgWindow::update_time(int sec)
	{
		const int sec_in_day = 24 * 60 * 60;
		QTime t(0,0,0,0);
		int d = sec / sec_in_day;
		sec -= d * sec_in_day;
		t = t.addSecs(sec);
		lbl_time->setText(tr("Time (in sec)") + ": " + QString::number(d) + " days " + t.toString("hh:mm:ss"));
		lbl_time->update();
	}

	void AlgWindow::cancel()
	{
		is_create = false;
		close();
	}

	void AlgWindow::create()
	{
		is_create = true;
		close();
	}

	bool AlgWindow::push_create()
	{
		return is_create;
	}

	double AlgWindow::eps()
	{
		return spin_eps->value();
	}

	int AlgWindow::max_time()
	{
		return spin_time->value();
	}

	size_t AlgWindow::max_iter()
	{
		return spin_count->value();
	}

	size_t AlgWindow::method()
	{
		return list_alg->currentIndex();
	}

	QString AlgWindow::app()
	{
		return text_edit->text();
	}

	void AlgWindow::choose_app()
	{
		QString app = QFileDialog::getOpenFileName(0);
		text_edit->setText(app);
	}
}

